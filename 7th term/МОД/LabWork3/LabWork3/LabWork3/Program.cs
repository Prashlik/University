namespace LabWork3
{


    class Program
    {
        const int a = 911;
        const int c = 733;
        const int m = 101;
        static int Xprev = 32;
        static double[,] matrix1 = { { 0.2, 0.2, 0.6},
                                     { 0.4, 0.5, 0.1},
                                     { 0.6, 0.1, 0.3} };

        static double[,] matrix2 = { { 0.7, 0.2, 0.1},
                                     { 0.3, 0.5, 0.2},
                                     {   0,   0,   1} };


        static void Main(string[] args)
        {
            // Первая часть
            Console.WriteLine("Первая часть задания:");
            PrintMatrix(matrix1);

            int cond = 0;
            int[] conds = new int[3];
            double[] probability = new double[3];
            int k = 0;
            bool flag = false;
            while (true)
            {
                k++;
                for (int i = 0; i < 100; i++)
                {
                    cond = NextStep(cond, matrix1);
                    conds[cond]++;
                }
                for (int i = 0; i < 3; i++)
                    if (probability[i] == (double)conds[i] / (100 * k))
                    {
                        flag = true;
                    }
                    else 
                    {
                        flag = false;
                        probability[i] = (double)conds[i] / (100 * k);
                    }

                if (flag) break;
                        
            }

                for (int i = 0; i < 3; i++)
                Console.WriteLine($"P{i}: " + probability[i].ToString());


            Console.WriteLine(Environment.NewLine);
            // Вторая часть
            Console.WriteLine("Вторая часть задания:");
            PrintMatrix(matrix2);

            int abs = -1;
            for (int i = 0; i < 3; i++)
                for (int j = 0; j < 3; j++)
                    if (matrix2[i, j] == 1 && i == j)
                    {
                        abs = i;
                        break;
                    }

            if (abs.Equals(-1))
                {
                Console.WriteLine("В матрице нет поглощающего состояния");
                return;
                }
            
            int[] steps = new int[3];

            int x = Xprev;

            for (int j = 0; j < 3; j++)
            {
                if (j == abs) break;
                Xprev = x;

                for (int i = 0; i < 100; i++)
                {
                    cond = j;
                    while (true)
                    {
                        steps[j]++;
                        cond = NextStep(cond, matrix2);
                        if (cond == abs)
                            break;
                    }
                }
            }

            for (int i = 0; i < 3; i++)
                Console.WriteLine($"t{i}: " + ((double)steps[i] / 100).ToString());
        }

        static int NextStep(int s, double[,] matrix)
        {
            double rand = Random();
            if (rand < matrix[s, 0])
                return 0;
            else if (rand >= (matrix[s, 0] + matrix[s, 1]))
                return 2;
            else return 1;            
        }

        static double Random()
        {
            Xprev = (a * Xprev + c) % m;
            return (double)Xprev / 100;
        }

        static void PrintMatrix(double[,] mtrx)
        {
            Console.WriteLine($"{"",-3}{"|S0",-5}{"|S1",-5}{"|S2",-5}{"|"}");
            for (int i = 0; i < 3; i++)
                Console.WriteLine($"{"S" + i.ToString(),-3}{"|" + mtrx[i, 0].ToString(),-5}{"|" + mtrx[i, 1].ToString(),-5}{"|" + mtrx[i, 2].ToString(),-5}{"|"}");
        }
    }
}