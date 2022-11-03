using TCP;

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
                        TCP_Server server = new TCP_Server(1234);
                        Console.Clear();
                        server.Connect();
                        flag = true;
                        break;
                    case "2":
                        Console.Clear();
                        Console.WriteLine("Enter the ip address: ");
                        TCP_Client client = new TCP_Client(Console.ReadLine(), 1234);
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