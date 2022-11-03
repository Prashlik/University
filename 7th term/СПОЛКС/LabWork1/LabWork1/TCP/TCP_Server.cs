using System.Net;
using System.Net.Sockets;

namespace TCP
{
    internal class TCP_Server : TCP_App
    {
        private TcpListener server;
        private const string newStr = "\r\n>";

        public TCP_Server(int port)
        {
            path = @".\Server\";
            server = new TcpListener(IPAddress.Any, port);
            server.Start();

            server.Server.SendTimeout = 60000;
            server.Server.ReceiveTimeout = 60000;
        }

        protected override void Command(string msg)
        {
            string command = msg;
            if (msg.Contains(' '))
                command = msg.Remove(msg.IndexOf(' ') + 1);
            string argument = msg.Remove(0, msg.IndexOf(' ') + 1);
            double BitRate;

            switch (command)
            {
                case "ECHO ":

                    SendMsg(argument + newStr);
                    break;

                case "UPLOAD ":

                    SendMsg("Loading started!");
                    BitRate = Download(argument, 0);
                    if (BitRate == -1) break;
                    SendMsg("SUCCESS!!\r\nThe Speed was " + Math.Round(BitRate, 2).ToString() + " MB/s" + newStr);
                    break;

                case "DOWNLOAD ":

                    if (File.Exists(path + argument))
                    {
                        SendMsg("Loading started!");
                        BitRate = Upload(argument, 0);
                        if (BitRate == -1) break;
                        RecieveMsg();
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

        public override void Connect()
        {
            while (true)
            {

                string msg = string.Empty;
                client = server.AcceptTcpClient();
                ns = client.GetStream();
                if (RecieveMsg() == "RECONNECTED")
                {
                    ns.Flush();
                    client.Close();
                }
                SendMsg("Connected!" + newStr);
                while (client.Connected)
                {
                    msg = RecieveMsg();
                    if (msg != string.Empty)
                        Command(msg);
                }
            }
        }

        protected override bool ReConnect()
        {
            IPAddress address = ((IPEndPoint)client.Client.RemoteEndPoint).Address;
            client.Close();
            ns.Close();

            client = server.AcceptTcpClient();
            ns = client.GetStream();
            string msg = RecieveMsg();
            if (address.ToString() == ((IPEndPoint)client.Client.RemoteEndPoint).Address.ToString())
            {
                if (msg == "RECONNECTED")
                    return true;
                else
                    return false;
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