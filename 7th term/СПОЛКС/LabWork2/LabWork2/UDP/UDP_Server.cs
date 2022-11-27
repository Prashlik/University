using System.Net;
using System.Net.Sockets;

namespace UDP
{
    internal class UDP_Server : UDP_App
    {
        private const string newStr = "\r\n>";
        private bool is_connected;
        private IPAddress ConnectedAddress;

        public UDP_Server(int LocalPort) : base (LocalPort)
        {
            path = @".\Server\";

            UdpUnit.Client.SendTimeout = 60000;
            UdpUnit.Client.ReceiveTimeout = 60000;
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

                    //UdpUnit.Close();
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
                //if (RecieveMsg() == "RECONNECTED")
                //{
                //    ns.Flush();
                //    client.Close();
                //}
                RecieveMsg();
                ConnectedAddress = RecievedAddress;
                is_connected = true;
                SendMsg("Connected!" + newStr);
                while (is_connected)
                {
                    msg = RecieveMsg();
                    if (msg != string.Empty)
                        Command(msg);
                }
            }
        }

        protected override bool ReConnect()
        {
            //string msg = RecieveMsg();
            //if (base.ConnectedAddress == ((IPEndPoint)client.Client.RemoteEndPoint).Address.ToString())
            //{
            //    if (msg == "RECONNECTED")
            //        return true;
            //    else
            //        return false;
            //}
            //else
            //{
            //    SendMsg("Connected!" + newStr);
            //    ns.Flush();
            //    return false;
            //}
            return false;
        }
    }
}