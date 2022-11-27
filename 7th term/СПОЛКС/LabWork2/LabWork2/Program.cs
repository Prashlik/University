using UDP;

namespace Server
{
    internal class Program
    {
        static void Main()
        {
            bool flag = false;
            do
            {
                Console.WriteLine("0.Exit");
                Console.WriteLine("1.Server");
                Console.WriteLine("2.Client");
                switch (Console.ReadLine())
                {
                    case "0":
                        flag = true;
                        break;
                    case "1":
                        UDP_Server server = new UDP_Server(1234);
                        Console.Clear();
                        server.Connect();
                        flag = true;
                        break;
                    case "2":
                        Console.Clear();
                        Console.WriteLine("Enter the ip address: ");
                        UDP_Client client = new UDP_Client(Console.ReadLine(), 1234, 2345);
                        Console.Clear();
                        client.Connect();
                        flag = true;
                        break;
                    default:
                        Console.WriteLine("Unknown command!");
                        break;
                }
                Console.Clear();
            } while (!flag);


        }
    }
}