namespace LabWork5
{
    internal class Queuing_system
    {
        int time, free_time, request_count;
        int count;
        double l, m;
        Request[] R;
        Random_functions random;

        public Queuing_system(int count, double l, double m)
        {
            this.count = count;
            this.l = l;
            this.m = m;
            request_count = 0;
            R = new Request[count];
            random = new Random_functions();

            this.Init();
        }

        private void Init()
        {
            for (int i = 0; i < count; i++)
            {
                R[i] = new Request();
                R[i].coming_time = F_Function(random.System_Random());
                R[i].processing_time = G_Function(random.System_Random());
            }
            for (int i = 1; i < count; i++)
            {
                R[i].coming_time += R[i - 1].coming_time;
            }
        }

        public void Calculate()
        {
            time = 0;
            free_time = 0;
            int num = 0, requests = 0;
            bool is_free = true;

            while (true)
            {
                request_count += requests;

                while (num < count && R[num].coming_time == time)
                {
                    requests++;
                    num++;
                }                

                if (is_free)
                {
                    if (requests == 0)
                        free_time++;
                    else
                    {
                        R[num - requests].starting_time = time;
                        is_free = false;
                    }
                }
                else
                {
                    if (R[num - requests].starting_time + R[num - requests].processing_time == time)
                    {
                        is_free = true;
                        requests--;
                        time--;
                    }
                }

                if (num == count && requests == 0)
                    break;
                time++;
            }
        }

        private int F_Function(double F)
        {
            return (int)((Math.Log(1 - F) / (-l)) * 100);
        }

        private int G_Function(double G)
        {
            return (int)(m * Math.Sqrt(-Math.Log(1 - G)) * 100);
        }

        public double Average_service_time()
        {
            return (double)(time - free_time) / (count * 100);
        }

        public double Average_request_time()
        {
            double temp = 0;
            for (int i = 0; i < count; i++)
            {
                temp = R[i].starting_time - R[i].coming_time;
            }
            return temp / (count * 100);
        }

        public double Average_request_count()
        {
            return request_count / time;
        }

        public double Channel_workload_percent()
        {
            return (double)(time - free_time) * 100 / time;
        }
    }

    internal class Request
    {
        public int coming_time;
        public int processing_time;
        public int starting_time;
    }
}
