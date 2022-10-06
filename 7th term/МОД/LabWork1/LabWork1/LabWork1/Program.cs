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
        private int seed;
        public static int e = 70;

        public Lehmer(int seed)
        {
            if (seed <= 0 || seed == int.MaxValue)
                throw new Exception("Bad seed");
            this.seed = seed;
        }

        public int Next2()
        {
            int z1 = ((a * Program.ri) % m);

            return z1;
        }
    }


    class Program
    {

        public static int ri = 7;

        static void Main(string[] args)
        {
            int e = 70;
            int[] counts = new int[70];
            int iter_count = 10000;
            int actual_part = iter_count / e;

            Lehmer lehmer = new Lehmer(1);
            for (int i = 0; i < iter_count; ++i)
            {
                ri = lehmer.Next2();
                int z1 = ri % Lehmer.e;
                ++counts[z1];
            }
            for (int i = 0; i < counts.Length; ++i)
            {
                Console.WriteLine("" + counts[i]);
            }
            double x = 0;
            double summ = 0;
            for (int i = 0; i < counts.Length; ++i)
            {
                summ += Math.Pow((actual_part - counts[i]), 2) / actual_part;
            }
            x = summ / e;
            Console.WriteLine("X = " + x);
        }
    }
}