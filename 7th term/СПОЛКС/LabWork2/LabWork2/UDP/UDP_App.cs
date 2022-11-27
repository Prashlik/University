using System.Text;
using System.Net;
using System.Net.Sockets;
using System.Diagnostics;

namespace UDP
{
    abstract class UDP_App
    {
        protected IPAddress ConnectedAddress, RecievedAddress;
        protected int RemotePort, LocalPort;
        protected UdpClient UdpUnit;
        protected string path;

        public UDP_App(int LocalPort) 
        {
            this.LocalPort = LocalPort;
            this.UdpUnit = new UdpClient(LocalPort);
        }

        protected void SendMsg(string message_to_send)
        {
            bool is_complete = false;
            do
            {
                try
                {
                    byte[] sendMsg = Encoding.Default.GetBytes(message_to_send);
                    Array.Resize(ref sendMsg, 1024);
                    UdpUnit.Send(sendMsg, sendMsg.Length);
                    is_complete = true;
                }
                catch (IOException)
                {
                    if (!ReConnect())
                        break;
                }
            } while (!is_complete);
        }

        protected string RecieveMsg()
        {
            IPEndPoint endPoint = null;
            bool is_complete = false;
            byte[] msg = new byte[1024];
            int count;
            string text = string.Empty;
            do
            {
                try
                {
                    msg = UdpUnit.Receive(ref endPoint);
                    RecievedAddress = endPoint.Address;
                    if (RecievedAddress == ConnectedAddress)
                    {
                        text = Encoding.UTF8.GetString(msg, 0, msg.Length);
                        text = text.TrimEnd('\0');
                        is_complete = true;
                    }
                }
                catch (IOException)
                {
                    if (!ReConnect())
                        break;
                }
            } while (!is_complete);

            if (is_complete)
                return text;
            else return string.Empty;
        }

        protected double Download(string name, long position)
        {
            IPEndPoint endPoint = null;
            byte[] data = new byte[1048576];
            long length, d_length = 0;
            int count;
            bool is_complete = false;
            Stopwatch time = new();
            FileStream fstream = File.Open(path + name, FileMode.OpenOrCreate);
            fstream.Position = position;

            length = long.Parse(RecieveMsg());

            time.Start();
            do
            {
                try
                {
                    do
                    {
                        data = UdpUnit.Receive(ref endPoint);
                        RecievedAddress = endPoint.Address;
                        if (RecievedAddress == ConnectedAddress)
                        d_length += data.Length;
                        fstream.Write(data, 0, data.Length);
                    } while (fstream.Position < length);
                    is_complete = true;
                }
                catch (IOException)
                {
                    if (ReConnect())
                    {
                        byte[] pos = Encoding.UTF8.GetBytes(d_length.ToString());
                        Array.Resize(ref pos, 1024);
                        UdpUnit.Send(pos, 1024);
                    }
                    else
                    {
                        fstream.Close();
                        File.Delete(path + name);
                        return -1;
                    }
                }
            } while (!is_complete);
            time.Stop();

            fstream.Close();

            return length / (1024 * 1024) / time.Elapsed.TotalSeconds;
        }

        protected double Upload(string name, long position)
        {
            IPEndPoint endPoint = new IPEndPoint(ConnectedAddress, RemotePort);
            byte[] data = new byte[1048576];
            int size;
            bool is_complete = false;
            long length;
            Stopwatch time = new();

            FileStream fstream = File.Open(path + name, FileMode.Open, FileAccess.Read);
            fstream.Position = position;
            SendMsg(fstream.Length.ToString());

            time.Start();
            do
            {
                try
                {
                    do
                    {
                        size = fstream.Read(data, 0, data.Length);
                        UdpUnit.Send(data, size);
                    } while (fstream.Position != fstream.Length);
                    is_complete = true;
                }
                catch (IOException)
                {
                    if (ReConnect())
                    {
                        byte[] pos;
                        //bool is_recieved = false;
                        //while (!is_recieved)
                        //{
                            pos = UdpUnit.Receive(ref endPoint);
                            //if (endPoint.Address == ConnectedAddress) is_recieved = true;
                        //}
                        position = long.Parse(Encoding.UTF8.GetString(pos, 0, pos.Length));
                        fstream.Position = position;
                    }
                    else
                    {
                        fstream.Close();
                        return -1;
                    }
                }
            } while (!is_complete);
            time.Stop();



            length = fstream.Length;
            fstream.Close();

            return (double)length / (1024 * 1024) / time.Elapsed.TotalSeconds;
        }

        protected abstract bool ReConnect();

        protected abstract void Command(string msg);

        public abstract void Connect();
    }
}
