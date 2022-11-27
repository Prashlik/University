using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Net;
using System.Net.Sockets;

namespace SOCKET
{
    internal class Client
    {
        private Socket LocalSocket, RemoteSocket;
        private EndPoint RemoteEndPoint;
        private string path = @".\Client\";
        private const string newStr = "\r\n>";

        public Client(int port, string ip)
        {
            LocalSocket = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Raw);
            LocalSocket.Bind(new IPEndPoint(IPAddress.Parse(ip), port));
            LocalSocket.Listen();
        }

        public void Run()
        {
            string command = string.Empty;
            while (true)
            {
                RemoteSocket = LocalSocket.Accept();
                RemoteEndPoint = RemoteSocket.RemoteEndPoint;
                while (RemoteSocket.Connected)
                {
                    RecieveMessage(ref command);
                    Command(command);
                }
            }
        }

        private void Command(string recieved_message)
        {
            string answer = string.Empty;

            string command = recieved_message;
            if (recieved_message.Contains(' '))
                command = recieved_message.Remove(recieved_message.IndexOf(' ') + 1);
            string argument = recieved_message.Remove(0, recieved_message.IndexOf(' ') + 1);
            double BitRate;

            switch (command)
            {
                case "ECHO ":

                    answer = argument + newStr;
                    break;

                //case "UPLOAD ":

                //    SendMessage("Loading started!");
                //    BitRate = SendMessage(argument, 0);
                //    if (BitRate == -1) break;
                //    SendMessage("SUCCESS!!\r\nThe Speed was " + Math.Round(BitRate, 2).ToString() + " MB/s" + newStr);
                //    break;

                //case "DOWNLOAD ":

                //    if (File.Exists(path + argument))
                //    {
                //        SendMessage("Loading started!");
                //        BitRate = Upload(argument, 0);
                //        if (BitRate == -1) break;
                //        RecieveMsg();
                //        SendMsg("SUCCESS!!\r\nThe Speed was " + Math.Round(BitRate, 2).ToString() + " MB/s" + newStr);
                //    }
                //    else
                //    {
                //        SendMsg("This file does not exist!");
                //        SendMsg(">");
                //    }
                //    break;

                case "CLOSE":

                    RemoteSocket.Shutdown(SocketShutdown.Both);
                    RemoteSocket.Close();
                    break;

                case "TIME":

                    answer = DateTime.Now.ToString() + newStr;
                    break;

                case "NEWSTR":

                    answer = ">";
                    break;

                default:

                    answer = "Unknown command!" + newStr;
                    break;
            }

            SendMessage(answer);
        }

        private bool Download()
        {
            return true;
        }

        private bool Upload()
        {
            return true;
        }

        private bool SendData(byte[] data)
        {
            RemoteSocket.ReceiveTimeout = 10000;
            bool is_sent = false;
            int attempts = 0;
            do
            {
                try
                {
                    RemoteSocket.Send(data);
                    RemoteSocket.Receive(data);
                    is_sent = true;
                }
                catch (SocketException)
                {
                    attempts++;
                    if (attempts == 5)
                        if (!Reconnect())
                            return false;
                }
                catch (ObjectDisposedException)
                {
                    if (!Reconnect())
                        return false;
                }
            } while (!is_sent);
            return true;
        }

        private int RecieveData(ref byte[] data)
        {
            RemoteSocket.ReceiveTimeout = 50000;
            int count = 0, attempts = 0;
            try
            {
                count = RemoteSocket.Receive(data);
                string DataLength = count.ToString();
                RemoteSocket.Send(Encoding.Default.GetBytes(DataLength, 0, DataLength.Length));
            }
            catch (SocketException)
            {
                attempts++;
                if (attempts == 5)
                    if (!Reconnect())
                        return -1;
            }
            catch (ObjectDisposedException)
            {
                if (!Reconnect())
                    return -1;
            }
            return count;
        }

        private bool SendMessage(string message)
        {
            return SendData(Encoding.Default.GetBytes(message));
        }

        private bool RecieveMessage(ref string message)
        {
            byte[] data = new byte[256];
            int length = RecieveData(ref data);
            if (length != -1)
            {
                message = Encoding.Default.GetString(data, 0, length);
                return true;
            }
            else return false;
        }

        private bool Reconnect()
        {
            RemoteSocket.Shutdown(SocketShutdown.Both);
            RemoteSocket.Close();
            RemoteSocket = LocalSocket.Accept();
            if (RemoteSocket.RemoteEndPoint == RemoteEndPoint)
            {
                return true;
            }
            else return false;
            RemoteEndPoint = RemoteSocket.RemoteEndPoint;
            return true;
        }
    }
}

