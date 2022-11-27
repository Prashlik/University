using System.Net;
using System.Net.Sockets;

namespace UDP
{
    internal class UDP_Client : UDP_App
    {
        private bool is_connected;

        public UDP_Client(string RemoteAddress, int RemotePort, int LocalPort) : base (LocalPort)
        {
            path = @".\Client\";
            this.ConnectedAddress = IPAddress.Parse(RemoteAddress);
            this.RemotePort = RemotePort;

            UdpUnit.Connect(this.ConnectedAddress, this.RemotePort);
            is_connected = true;
            UdpUnit.Client.SendTimeout = 60000;
            UdpUnit.Client.ReceiveTimeout = 60000;
        }

        protected override void Command(string msg)
        {
            string command = msg;
            if (msg.Contains(' '))
                command = msg.Remove(msg.IndexOf(' ') + 1);
            string argument = msg.Remove(0, msg.IndexOf(' ') + 1);

            switch (command)
            {
                case "CLOSE":

                    SendMsg(msg);
                    UdpUnit.Close();
                    break;

                case "UPLOAD ":

                    if (File.Exists(path + argument))
                    {
                        SendMsg(msg);
                        Console.WriteLine(RecieveMsg());
                        Upload(argument, 0);
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
                        Download(argument, 0);
                        SendMsg("RECIEVED");
                    }
                    else Console.WriteLine(rmsg);
                    break;

                case "":

                    SendMsg("NEWSTR");
                    break;

                case "CLEAR":

                    Console.Clear();
                    SendMsg("NEWSTR");
                    break;

                default:

                    SendMsg(msg);
                    break;
            }
        }

        public override void Connect()
        {
            string text;
            SendMsg("CONNECTED");
            while (true)
            {
                Console.Write(RecieveMsg());
                text = Console.ReadLine();
                Command(text);
            }
        }

        protected override bool ReConnect()
        {
            Console.WriteLine("Подключение разорвано. Попытка переподключения..");
            bool is_connect = false;
            int i = 0;
            do
            {
                try
                {
                    UdpUnit.Close();
                    UdpUnit = new UdpClient();
                    UdpUnit.Connect(ConnectedAddress, RemotePort);
                    UdpUnit.Client.SendTimeout = 60000;
                    UdpUnit.Client.ReceiveTimeout = 60000;
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
                UdpUnit.Close();
                Console.WriteLine("Переподключение не удалось, завершение работы программы...");
                Environment.Exit(0);
            }

            return is_connect;
        }
    }
}
