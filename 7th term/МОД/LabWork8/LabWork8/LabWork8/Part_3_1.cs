using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace LabWork8
{
    internal class Part_3_1
    {
        int count = 0;
        double time = 0;
        int precise_count = 0;
        int exceeding = 0;

        double value = 24 * 60;
            public void Run(double[] Rand)
            {
                int t = 0;
                for (int i = 0; i < 5; i++)
                {
                    double cur_time = 0;
                    bool is_precise = true;
                    int number;
                    double r = Rand[++t];
                    if (r < 0.25) number = 3;
                    else if (r < 0.5) number = 4;
                    else if (r < 0.75) number = 5;
                    else number = 6;

                    for (int j = 0; j < number; j++)
                    {
                        if (Rand[++t] < 0.5)
                        {
                            is_precise = false;
                            cur_time += standard_time(new double[2] { Rand[++t], Rand[++t] });
                        }
                        else cur_time += standard_time(new double[2] { Rand[++t], Rand[++t] });
                    }

                    time += cur_time;
                    if (is_precise) precise_count++;
                    if (cur_time > value) exceeding++;
                    count++;
                }
            }

        private double standard_time(double[] Rand)
        {
            double production = 30 + (60 - 30) * Rand[0];
            double test = -10 * Math.Log(1 - Rand[1]);
            return production + test;
        }

        private double precise_time(double[] Rand)
        {
            double production = 40 + (120 - 40) * Rand[0];
            double test = -15 * Math.Log(1 - Rand[1]);
            return production + test;
        }

        public void Print_Result()
        {
            Console.WriteLine("Среднее время изготовления комплекта:        " + Math.Round((time / count), 2).ToString() + " минут");
            Console.WriteLine("Вероятность того, комплект состоит только из высокоточных инструментов: " + Math.Round(((double)precise_count * 100 / count), 2).ToString() + "%");
            Console.WriteLine("Вероятность того, что среднее время превысит 24 часа: " + Math.Round(((double)exceeding * 100 / count), 2).ToString() + "%");
        }

        public void Clear()
        {
            count = 0;
            time = 0;
            precise_count = 0;
            exceeding = 0;
        }
    }
}
