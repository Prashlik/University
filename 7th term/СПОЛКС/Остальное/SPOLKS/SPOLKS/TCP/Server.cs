using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Net;
using System.Net.Sockets;

namespace TCP
{
    internal class TCPApp_Server: TCPApp
    {
        private TcpListener server;
        private byte[] sendMsg = new byte[100];
        TcpClient client;
        NetworkStream ns;
        string newStr = "\r\n>";

        public TCPApp_Server(int port)
        {
            server = new TcpListener(IPAddress.Any, port);
            server.Start();
        }

        private void SendMsg(string message_to_send)
        {
            byte[] sendMsg = new byte[100];
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
                case "UPLOAD ":
                    Download(str);
                    SendMsg("SUCCESS!!" + newStr);
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
            while (true)
            {
                string cmd = string.Empty;
                client = server.AcceptTcpClient();
                ns = client.GetStream();
                SendMsg("Connected!" + newStr);
                while (client.Connected)
                {
                    byte[] msg = new byte[1024];
                    int count = ns.Read(msg, 0, msg.Length);
                    cmd = Encoding.UTF8.GetString(msg, 0, count);
                    Command(cmd);
                }
            }
        }
    }
}
