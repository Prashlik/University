using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Net;
using System.Net.Sockets;

namespace TCP
{
    public class TCPApp
    {
        NetworkStream ns;

        private void Upload(string name)
        {
            byte[] data = new byte[102400];
            FileStream fstream = File.Open(@".\Files\" + name, FileMode.Open, FileAccess.Read);


            byte[] length = Encoding.UTF8.GetBytes(fstream.Length.ToString());
            ns.Write(length, 0, 1024);

            int size = 0;
            do
            {
                size = fstream.Read(data, 0, data.Length);
                ns.Write(data, 0, size);
            } while (size != 0);

            fstream.Close();
        }

        private void Download(string name)
        {
            try
            {
                byte[] size = new byte[1024];
                byte[] data = new byte[102400];
                long length;
                int count;
                FileStream fstream = File.Open(name, FileMode.Create);

                count = ns.Read(size, 0, 1024);
                length = long.Parse(Encoding.UTF8.GetString(size, 0, count));

                count = 0;
                do
                {
                    count = ns.Read(data, 0, data.Length);
                    fstream.Write(data, 0, data.Length);
                } while (count != 0);

                fstream.Close();
            }
            catch (Exception e)
            {
                Console.WriteLine(e.Message);
            }
        }
    }
}