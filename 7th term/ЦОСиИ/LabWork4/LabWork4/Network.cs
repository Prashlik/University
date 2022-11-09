using System;
using System.Drawing;

namespace LabWork4
{
    internal class Network
    {
        private int L;
        private int[] size;
        private Matrix[] weights;
        private double[][] bios;
        private double[][] neurons_val, neurons_err;
        private double[] neurons_bios_val;

        public void Init(int L, int[] size)
        {
            this.L = L;
            this.size = size;
            this.weights = new Matrix[L - 1];
            this.bios = new double[L - 1][];

            Random r = new Random();

            for (int i = 0; i < L - 1; i++)
            {
                weights[i] = new Matrix();
                weights[i].Init(size[i + 1], size[i]);
                bios[i] = new double[size[i + 1]];

                for (int j = 0; j < size[i + 1]; j++)
                    bios[i][j] = r.NextDouble();
            }
            neurons_val = new double[L][];
            neurons_err = new double[L][];
            for (int i = 0; i < L; i++)
            { 
                neurons_val[i] = new double[size[i]];
                neurons_err[i] = new double[size[i]];
            }
            neurons_bios_val = new double[L - 1];
            for (int i = 0; i < L - 1; i++)
                neurons_bios_val[i] = 1;
        }

        public void SetInput(double[] values)
        {
            for (int i = 0; i < size[0]; i++)
                neurons_val[0][i] = values[i];
        }

        private double[] Activate(double[] values)
        {
            double[] result = new double[values.Length];
            for (int i = 0; i < values.Length; i++)
            {
                result[i] = Math.Tanh(values[i]);
            }

            return result;
        }

        private double ActivateDer(double value)
        {
            double result;

            result = 1 / Math.Pow((Math.Cosh(value)), 2);

            return result;
        }

        public double ForwardFeed()
        {
            for (int k = 1; k < L; k++)
            {
                neurons_val[k] = Matrix.Multi(weights[k - 1], neurons_val[k - 1]);
                neurons_val[k] = Matrix.SumVector(neurons_val[k], bios[k - 1]);
                neurons_val[k] = Activate(neurons_val[k]);
            }

            int pred = SearchMaxIndex(neurons_val[L - 1]);
            return pred;
        }

        private int SearchMaxIndex(double[] vector)
        {
            double max = vector[0];
            int index = 0;

            for (int i = 1; i < vector.Length; i++)
                if (vector[i] > max)
                {
                    index = i;
                    max = vector[i];
                }

            return index;
        }

        public void BackPropogation(int expect)
        {
            for (int i = 0; i < size[L - 1]; i++)
            {
                if (i != expect)
                    neurons_err[L - 1][i] = -neurons_val[L - 1][i] * ActivateDer(neurons_val[L - 1][i]);
                else
                    neurons_err[L - 1][i] = 1d - neurons_val[L - 1][i] * ActivateDer(neurons_val[L - 1][i]);
            }

            for (int k = L - 2; k > 0; k--)
            {
                neurons_err[k] = Matrix.Multi_T(weights[k], neurons_err[k + 1]);
                for (int j = 0; j < size[k]; j++)
                    neurons_err[k][j] *= ActivateDer(neurons_val[k][j]);
            }
        }

        public void WeightsUpdater(double lr)
        {
            for (int i = 0; i < L - 1; i++)
                for (int j = 0; j < size[i + 1]; j++)
                    for (int k = 0; k < size[i]; k++)
                        weights[i][j, k] += neurons_val[i][k] * neurons_err[i + 1][j] * lr;
           
            for (int i = 0; i < L - 1; i++)
                for (int k = 0; k < size[i + 1]; k++) bios[i][k] += neurons_err[i + 1][k] * lr;
        }

        public double this[int x]
        {
            get { return neurons_val[L - 1][x]; }
        }
    }
}
