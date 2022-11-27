using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace LabWork8
{
    internal class Part_1
    {
        protected double money = 0;
        protected double rejected = 0;
        protected int count = 0;

        public void Run(double[] chances_A, double[] chances_B, double[] chances_C)
        {
            int cost = 10;
            int price = 25;
            int cost_A = 4, cost_B = 6, cost_C = 2;
            double chance_A = 0.06, chance_B = 0.04, chance_C = 0.09;


            for (int i = 0; i < 100; i++)
            {
                money -= cost;

                bool is_A = false;
                bool is_B = false;
                bool is_C = false;

                if (chances_A[i] <= chance_A) is_A = true;
                if (chances_B[i] <= chance_B) is_B = true;
                if (chances_C[i] <= chance_C) is_C = true;

                if (is_A || is_B || is_C)
                    if ((!(is_A && is_B && is_C)) && (is_A ^ is_B ^ is_C))
                    {
                        if (is_A) money -= cost_A;
                        else if (is_B) money -= cost_B;
                        else if (is_C) money -= cost_C;
                    }
                    else
                    {
                        rejected++;
                        continue;
                    }

                money += price;
            }
            count++;
        }

        public void Print_Result()
        {
            Console.WriteLine("Средний общий доход:                         " + Math.Round(((double)money / count), 2).ToString());
            Console.WriteLine("Средняя прибыль от изделия:                  " + Math.Round(((double)money / (100 * count)), 2).ToString());
            Console.WriteLine("Вероятность того, что изделие не забракуют:  " + Math.Round((100d - (double)rejected / count), 2).ToString() + "%");
        }

        public void Clear()
        {
            money = 0;
            rejected = 0;
            count = 0;
        }
    }
}
