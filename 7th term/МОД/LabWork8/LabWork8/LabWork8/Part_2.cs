using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace LabWork8
{
    internal class Part_2
    {
        protected int count = 0;
        protected double X = 0;
        protected int exceeding = 0;
        protected double value = 0;

        public void Run_1(double[] R)
        {
            double temp;
            for (int i = 0; i < 100; i++)
            {
                if (R[i] < 0.1) temp = (R[i] + 0.3) / 0.0002;
                else if (R[i] < 0.5) temp = (R[i] + 0.9) / 0.0005;
                else temp = (R[i] + 0.2) / 0.00025;

                X += temp;
                if (temp > value) exceeding++;
                count++;
            }
        }

        public void Run_2(double[] R1, double[] R2)
        {
            int a = 1500;
            int b = 4800;
            double fmax = 0.0005;

            double Rs1, Rs2, FR;

            for (int i = 0; i < 100; i++)
            {
                Rs1 = a + (b - a) * R1[i];
                Rs2 = fmax * R2[i];

                if (Rs2 >= 1500 && Rs2 <= 2000) FR = 0.0002;
                else if (Rs2 > 2000 && Rs2 <= 2800) FR = 0.0005;
                else FR = 0.00025;

                if (Rs2 <= FR)
                    X += Rs1;
                else continue;

                if (Rs1 > value) exceeding++;
                count++;

            }
        }

        public void Print_Result()
        {
            Console.WriteLine("Среднее значение X:                          " + Math.Round((X / count), 2).ToString());
            Console.WriteLine("Вероятность того, что X превысит значение " + value.ToString() + " : " + Math.Round(((double)exceeding * 100 / count), 2).ToString() + "%");
        }

        public void Clear()
        {
            count = 0;
            X = 0;
            exceeding = 0;
        }
    }
}
