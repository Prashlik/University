using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Net;
using System.Net.Sockets;
using System.Diagnostics;

namespace Server
{
    internal class Server
    {
        private TcpListener server;
        TcpClient client;
        NetworkStream ns;
        string newStr = "\r\n>";
        string address, path;
        int port;

        public Server(int port)
        {
            path = @"D:\Server\";
            server = new TcpListener(IPAddress.Any, port);
            server.Start();

            server.Server.SendTimeout = 60000;
            server.Server.ReceiveTimeout = 60000;
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
                }
            } while (!is_complete);

            return text;
        }

        private void Command(string argument)
        {
            string command = argument;
            if (argument.Contains(' '))
                command = argument.Remove(argument.IndexOf(' ') + 1);
            argument = argument.Remove(0, argument.IndexOf(' ') + 1);
            double BitRate;

            switch (command)
            {
                case "ECHO ":

                    SendMsg(argument + newStr);
                    break;

                case "UPLOAD ":

                    SendMsg("Loading started!");
                    BitRate = Download(argument);
                    SendMsg("SUCCESS!!\r\nThe Speed was " + Math.Round(BitRate, 2).ToString() + " MB/s" + newStr);
                    break;

                case "DOWNLOAD ":

                    if (File.Exists(path + argument))
                    {
                        SendMsg("Loading started!");
                        BitRate = Upload(argument);
                        SendMsg("SUCCESS!!\r\nThe Speed was " + Math.Round(BitRate, 2).ToString() + " MB/s" + newStr);
                    }
                    else
                    {
                        SendMsg("This file does not exist!");
                        SendMsg(">");
                    }
                    break;

                case "CLOSE":

                    client.Close();
                    break;

                case "TIME":

                    SendMsg(DateTime.Now.ToString() + newStr);
                    break;

                case "NEWSTR":

                    SendMsg(">");
                    break;

                default:

                    SendMsg("Unknown command!" + newStr);
                    break;
            }
        }

        public void Connect()
        {
            while (true)
            {
                try
                {
                    string cmd = string.Empty;
                    client = server.AcceptTcpClient();
                    ns = client.GetStream();
                    ns.Flush();
                    SendMsg("Connected!" + newStr);
                    while (client.Connected)
                    {
                        Command(RecieveMsg());
                    }
                }
                catch (IOException)
                {
                    ReConnect();
                }
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
            IPAddress address = ((IPEndPoint)client.Client.RemoteEndPoint).Address;
            client.Close();
            ns.Close();

            client = server.AcceptTcpClient();
            ns = client.GetStream();
            if (address == ((IPEndPoint)client.Client.RemoteEndPoint).Address && RecieveMsg() == "RECONNECTED")
            {
                return true;
            }
            else
            {
                SendMsg("Connected!" + newStr);
                ns.Flush();
                return false;
            }
        }
    }
}

