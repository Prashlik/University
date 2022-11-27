using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Net;
using System.Net.Sockets;

namespace TCP
{
    internal class TCPApp_Client: TCPApp
    {
        private TcpClient client;
        private byte[] sendMsg = new byte[100];
        NetworkStream ns;
        public string newStr = "\r\n>";

        public TCPApp_Client(string adress, int port)
        {
            client = new TcpClient();
            client.Connect(adress, port);
        }

        private void SendMsg(string message_to_send)
        {
            sendMsg = Encoding.Default.GetBytes(message_to_send);
            ns.Write(sendMsg, 0, sendMsg.Length);
        }

        private void Command(string str)
        {
            string command = str;
            if (str.Contains(' '))
                command = str.Remove(str.IndexOf(' ') + 1);
            str = str.Remove(0, str.IndexOf(' ') + 1);

            switch (command)
            {
                case "ECHO ":
                    SendMsg(str + newStr);
                    break;
                case "CLOSE":
                    client.Close();
                    break;
                case "TIME":
                    SendMsg(DateTime.Now.ToString() + newStr);
                    break;
                case "":
                    SendMsg(newStr);
                    break;
                default:
                    SendMsg("Unknown command!" + newStr);
                    break;
            }
        }

        public void Connect()
        {
            try
            {
                string text;
                ns = client.GetStream();
                while (client.Connected)
                {
                    byte[] msg = new byte[1024];
                    text = string.Empty;
                    int count = ns.Read(msg, 0, msg.Length);
                    text = Encoding.UTF8.GetString(msg, 0, count);
                    Console.Write(text);
                    text = Console.ReadLine();
                    msg = Encoding.UTF8.GetBytes(text);
                    ns.Write(msg, 0, msg.Length);
                    if (text == "CLOSE")
                        client.Close();
                    else if (text.Contains("UPLOAD "))
                        Upload(text);

                }
            }
            catch (Exception e)
            {
                Console.WriteLine(e.Message);
            }
        }
    }
}

