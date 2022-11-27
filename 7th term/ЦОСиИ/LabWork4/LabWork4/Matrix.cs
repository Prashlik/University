using System;

namespace LabWork4
{
    internal class Matrix
    {
        private double[,] matrix;
        private int row, col;

        public void Init(int row, int col)
        {
            matrix = new double[row, col];
            this.row = row;
            this.col = col;

            this.Rand();
        }

        private void Rand()
        {
            Random r = new Random();
            
            for (int i = 0; i < row; i++)
                for (int j = 0; j < col; j++)
                    matrix[i, j] = r.NextDouble();
        }

        public static double[] Multi(Matrix m, double[] neuron)
        {
            double[] result = new double[m.row];
            for (int i = 0; i < m.row; i++)
            {
                double temp = 0;
                for (int j = 0; j < m.col; j++)
                    temp += m.matrix[i, j] * neuron[j];

                result[i] = temp;
            }

            return result;
        }

        public static double[] Multi_T(Matrix m, double[] neuron)
        {
            double[] result = new double[m.col];
            for (int i = 0; i < m.col; i++)
            {
                double temp = 0;
                for (int j = 0; j < m.row; j++)
                    temp += m.matrix[j, i] * neuron[j];

                result[i] = temp;
            }

            return result;
        }

        public static double[] SumVector(double[] a, double[] b)
        {
            double[] result = new double[a.Length];
            for (int i = 0; i < result.Length; i++)
                result[i] = a[i] + b[i];

            return result;
        }

        public double this[int x, int y]
        {
            get { return matrix[x, y]; }
            set { matrix[x, y] = value; }
        }      
    }
}
