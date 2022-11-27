using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Net;
using System.Net.Sockets;
using System.Diagnostics;

namespace Client
{
    internal class Client
    {
        private TcpClient client;
        NetworkStream ns;
        public string newStr = "\r\n>";
        private string address, path;
        private int port;

        public Client(string address, int port)
        {
            path = @"D:\Client\";
            client = new TcpClient();
            this.address = address;
            this.port = port;

            client.Connect(this.address, this.port);
            client.Client.SendTimeout = 60000;
            client.Client.ReceiveTimeout = 60000;
        }

        private void SendMsg(string message_to_send)
        {
            bool is_complete = false;
            do
            {
                try
                {
                    byte[] sendMsg = Encoding.Default.GetBytes(message_to_send);
                    Array.Resize<byte>(ref sendMsg, 1024);
                    ns.Write(sendMsg, 0, sendMsg.Length);
                    is_complete = true;
                }
                catch (IOException)
                {
                    if (!ReConnect())
                        break;
                }
            } while (!is_complete);
        }

        private string RecieveMsg()
        {
            bool is_complete = false;
            byte[] msg = new byte[1024];
            int count;
            string text = string.Empty;
            do
            {
                try
                {
                    count = ns.Read(msg, 0, msg.Length);
                    text = Encoding.UTF8.GetString(msg, 0, count);
                    text = text.TrimEnd('\0');
                    is_complete = true;
                }
                catch (IOException)
                {
                    ReConnect();
                    break;
                }
            } while (!is_complete);

            return text;
        }

        private void Command(string msg)
        {
            string command = msg;
            if (msg.Contains(' '))
                command = msg.Remove(msg.IndexOf(' ') + 1);
            string argument = msg.Remove(0, msg.IndexOf(' ') + 1);

            switch (command)
            {
                case "CLOSE":

                    SendMsg(msg);
                    client.Close();
                    break;

                case "UPLOAD ":

                    if (File.Exists(path + argument))
                    {
                        SendMsg(msg);
                        Console.WriteLine(RecieveMsg());
                        Upload(argument);
                    }
                    else
                    {
                        Console.WriteLine("This file does not exist!");
                        SendMsg("NEWSTR");
                    }
                    break;

                case "DOWNLOAD ":

                    SendMsg(msg);
                    string rmsg = RecieveMsg();
                    if (rmsg == "Loading started!")
                    {
                        Console.WriteLine(rmsg);
                        Download(argument);
                    }
                    else Console.WriteLine(rmsg);
                    break;

                case "":

                    SendMsg("NEWSTR");
                    break;

                default:

                    SendMsg(msg);
                    break;
            }
        }

        public void Connect()
        {
            string text;
            ns = client.GetStream();
            while (client.Connected)
            {
                Console.Write(RecieveMsg());
                text = Console.ReadLine();
                Command(text);
            }
        }

        public double Download(string name)
        {
            byte[] data = new byte[1048576];
            long length, d_length = 0;
            int count;
            bool is_complete = false;
            Stopwatch time = new Stopwatch();
            FileStream fstream = File.Open(path + name, FileMode.Create);

            length = long.Parse(RecieveMsg());

            time.Start();
            do
            {
                try
                {
                    do
                    {
                        count = ns.Read(data, 0, data.Length);
                        d_length += count;
                        fstream.Write(data, 0, count);
                    } while (d_length != length);
                    is_complete = true;
                }
                catch (IOException)
                {
                    if (ReConnect())
                    {
                        byte[] pos = Encoding.UTF8.GetBytes(d_length.ToString());
                        Array.Resize<byte>(ref pos, 1024);
                        ns.Write(pos, 0, 1024);
                    }
                    else
                    {
                        fstream.Close();
                        File.Delete(path + name);
                        break;
                    }
                }
            } while (!is_complete);
            time.Stop();

            fstream.Close();

            return (length / (1024 * 1024) / time.Elapsed.TotalSeconds);
        }

        private double Upload(string name)
        {
            byte[] data = new byte[1048576];
            int size;
            bool is_complete = false;
            long length;
            Stopwatch time = new Stopwatch();

            FileStream fstream = File.Open(path + name, FileMode.Open, FileAccess.Read);
            SendMsg(fstream.Length.ToString());

            time.Start();
            do
            {
                try
                {
                    do
                    {
                        size = fstream.Read(data, 0, data.Length);
                        ns.Write(data, 0, size);
                    } while (fstream.Position != fstream.Length);
                    is_complete = true;
                }
                catch (IOException)
                {
                    if (ReConnect())
                    {
                        byte[] pos = new byte[1024];
                        int count = ns.Read(pos, 0, 1024);
                        long position = long.Parse(Encoding.UTF8.GetString(pos, 0, count));
                        fstream.Position = position;
                    }
                    else
                    {
                        fstream.Close();
                        break;
                    }
                }
            } while (!is_complete);
            time.Stop();

            length = fstream.Length;
            fstream.Close();

            return ((double)length / (1024 * 1024) / time.Elapsed.TotalSeconds);
        }

        private bool ReConnect()
        {
            Console.WriteLine("Подключение разорвано. Попытка переподключения..");
            bool is_connect = false;
            int i = 0;
            do
            {
                try
                {
                    client.Close();
                    ns.Close();
                    client = new TcpClient();
                    client.Connect(address, port);
                    ns = client.GetStream();
                    SendMsg("RECONNECTED");
                    is_connect = true;
                }
                catch (SocketException)
                {
                    if (++i == 5) break;
                    Console.WriteLine("(" + i.ToString() + "/5) Подключение не удалось, повторная попытка через 30 секунд");
                    Thread.Sleep(30000);
                }
            } while (!is_connect);

            if (is_connect)
            {
                Console.WriteLine("Подключение восстановлено!");
            }
            else
            {
                client.Close();
                ns.Close();
                Console.WriteLine("Переподключение не удалось, завершение работы программы...");
                Environment.Exit(0);
            }

            return is_connect;
        }
    }
}
