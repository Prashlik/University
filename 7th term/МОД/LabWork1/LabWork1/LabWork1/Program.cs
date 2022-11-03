using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;


namespace Lemer
{

    public class Lehmer
    {
        private const int a = 11817;
        private const int m = 36471;

        public int Next()
        {
            int z1 = ((a * Program.ri) % m);

            return z1;
        }
    }
    public class Method
    {
        private const double first = 4598754, second = 8653147;

        public static void Run()
        {
            double[] random = new double[20];
            random[0] = first;
            random[1] = second;
            for (int i = 0, j = 0; i < 20; i++)
            {
                double temp = random[j] * random[j + 1];
                string nextrand = temp.ToString();
                int poz = (nextrand.Length / 4) % 4 == 3 ? nextrand.Length / 4 + 1 : nextrand.Length / 4;
                int len = (nextrand.Length / 4) % 4 == 1 || (nextrand.Length / 4) % 4 == 2 ?
                    nextrand.Length / 2 + 1 : nextrand.Length / 2;
                nextrand = nextrand.Substring(poz, len);
                random[i] = Convert.ToDouble(nextrand);
                if (i > 1) j++;
            }
            for (int i = 0; i < random.Length; i++)
            {
                Console.WriteLine("" + random[i]);
            }
        }
    }
    class Program
    {

        public static int ri = 7;

        static void Main(string[] args)
        {
            int e = 20;
            int[] counts = new int[e];
            int iter_count = 10000;
            int actual_part = iter_count / e;

            Lehmer lehmer = new();
            for (int i = 0; i < iter_count; ++i)
            {
                ri = lehmer.Next();
                int z1 = ri % e;
                counts[z1]++;
            }
            for (int i = 0; i < e; ++i)
            {
                Console.WriteLine("" + counts[i]);
            }
            double x;
            double summ = 0;
            for (int i = 0; i < counts.Length; ++i)
            {
                summ += Math.Pow((actual_part - counts[i]), 2) / actual_part;
            }
            x = summ / e;
            Console.WriteLine("X = " + x + Environment.NewLine);
            Method.Run();
        }
    }
}