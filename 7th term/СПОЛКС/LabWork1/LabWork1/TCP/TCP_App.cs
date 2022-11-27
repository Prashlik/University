using System.Text;
using System.Net.Sockets;
using System.Diagnostics;

namespace TCP
{
    abstract class TCP_App
    {
        protected TcpClient client;
        protected NetworkStream ns;
        protected string path;

        public TCP_App() { }

        protected void SendMsg(string message_to_send)
        {
            bool is_complete = false;
            do
            {
                try
                {
                    byte[] sendMsg = Encoding.Default.GetBytes(message_to_send);
                    Array.Resize(ref sendMsg, 1024);
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

        protected string RecieveMsg()
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
                        count = ns.Read(data, 0, data.Length);
                        d_length += count;
                        fstream.Write(data, 0, count);
                    } while (fstream.Position < length);
                    is_complete = true;
                }
                catch (IOException)
                {
                    if (ReConnect())
                    {
                        byte[] pos = Encoding.UTF8.GetBytes(d_length.ToString());
                        Array.Resize(ref pos, 1024);
                        ns.Write(pos, 0, 1024);
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
                        position = long.Parse(Encoding.UTF8.GetString(pos, 0, count));
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
