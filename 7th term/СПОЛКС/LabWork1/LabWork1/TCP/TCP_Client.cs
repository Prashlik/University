using System.Net.Sockets;

namespace TCP
{
    internal class TCP_Client : TCP_App
    {
        private string address;
        private int port;

        public TCP_Client(string address, int port)
        {
            path = @".\Client\";
            client = new TcpClient();
            this.address = address;
            this.port = port;

            client.Connect(this.address, this.port);
            client.Client.SendTimeout = 60000;
            client.Client.ReceiveTimeout = 60000;
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
                    client.Close();
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
            ns = client.GetStream();
            SendMsg("CONNECTED");
            while (client.Connected)
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
                    client.Close();
                    ns.Close();
                    client = new TcpClient();
                    client.Connect(address, port);
                    client.Client.SendTimeout = 60000;
                    client.Client.ReceiveTimeout = 60000;
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
