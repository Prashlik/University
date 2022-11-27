using System;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.IO;

namespace Client
{
    internal class Program
    {
        static void Main()
        {
            
            Client s = new Client(Console.ReadLine(), 1234);
            s.Connect();
        }
    }
}