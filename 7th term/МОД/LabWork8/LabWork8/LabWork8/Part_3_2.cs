using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace LabWork8
{
    internal class Part_3_2
    {
        int count = 0;
        double time = 0;
        int subst_count = 0, subst_number = 0;

        public void Run(double[] Rand)
        {
            int t = 0;
            double r_sum;
            double cur_time;
            bool is_serviceable;

            for (int i = 0; i < 2; i++)
            {
                cur_time = 0;
                is_serviceable = true;

                for (int j = 0; j < 5; j++)
                {
                    cur_time += 2 + (5 - 2) * Rand[++t];
                    if (Rand[++t] <= 0.1)
                    {
                        r_sum = 0;
                        for (int k = 0; k < 6; k++)
                            r_sum += Rand[++t];
                        cur_time += 5 + 0.5 * Math.Sqrt(2) * (r_sum - 3);
                        is_serviceable = false;
                        subst_number++;
                    }
                }

                if (is_serviceable)
                    cur_time = -6 * Math.Log(1 - Rand[++t]);
                else
                {
                    cur_time = -10 * Math.Log(1 - Rand[++t]);
                    subst_count++;
                }

                time += cur_time;
                count++;
            }
        }

        public void Print_Result()
        {
            Console.WriteLine("Среднее время работы с прибором:             " + Math.Round((time / count), 2).ToString() + " минут");
            Console.WriteLine("Вероятность того, потребуется хотя бы одна замена: " + Math.Round(((double)subst_count * 100 / count), 2).ToString() + "%");
            Console.WriteLine("Среднее количество заменяемых схем:          " + Math.Round(((double)subst_number / count), 2).ToString());
        }

        public void Clear()
        {
            count = 0;
            time = 0;
            subst_count = 0;
            subst_number = 0;
        }
    }
}
