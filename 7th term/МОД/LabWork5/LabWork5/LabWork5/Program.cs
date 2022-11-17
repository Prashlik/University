namespace LabWork5
{
    class Program
    {
        const double l = 0.1, m = 10;
        const int count = 100;
        static void Main(string[] args)
        {
            Queuing_system q = new Queuing_system(count, l, m);
            q.Calculate();
            Console.WriteLine("Среднее время обслуживания: " + Math.Round(q.Average_service_time(), 2).ToString() + " секунд");
            Console.WriteLine("Среднее время пребывания заявки в системе: " + q.Average_request_time().ToString() + " секунд");
            Console.WriteLine("Среднее число заявок в системе: " + q.Average_request_count().ToString() + " заявок");
            Console.WriteLine("Процент загрузки обслуживающего прибора: " + Math.Round(q.Channel_workload_percent(), 2).ToString() + "%");
        }
    }

}