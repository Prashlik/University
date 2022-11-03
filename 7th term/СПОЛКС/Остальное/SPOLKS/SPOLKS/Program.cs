using System;
using System.Text;
using System.Net;      // потребуется
using System.Net.Sockets;    // потребуется
using SPOLKS.TCP;

class Program
{
    static void Main()
    {
        Server s = new Server(1234);
        s.Connect();
    }
}
