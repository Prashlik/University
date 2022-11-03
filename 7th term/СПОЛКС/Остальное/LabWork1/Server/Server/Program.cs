namespace Server
{
    internal class Program
    {
        static void Main()
        {
            Server s = new Server(1234);
            s.Connect();
        }
    }
}