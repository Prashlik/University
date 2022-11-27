using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Drawing;

namespace LabWork3
{
    internal class Hopfield
    {
        private int[,] examples;
        private double[,] w;
        private int size, count;
        private List<Bitmap> bitmaps;

        public Hopfield()
        {
            examples = null;
            w = null;
            size = 0;
            bitmaps = new List<Bitmap>();
        }

        public Hopfield(int[,] examples, double[,] w, int size, List<Bitmap> bitmaps)
        {
            this.examples = examples;
            this.w = w;
            this.size = size;
            this.bitmaps = bitmaps;
        }

        public Hopfield(Hopfield temp)
        {
            this.examples = temp.examples;
            this.w = temp.w;
            this.size = temp.size;
            this.bitmaps = temp.bitmaps;
        }

        public Hopfield(List<Element> elements, int size)
        {
            this.count = elements.Count();
            bitmaps = new List<Bitmap>();
            this.size = size;
            examples = new int[elements.Count, size];
            w = new double[size, size];
            for (int i = 0; i < elements.Count; i++)
                bitmaps.Add((Bitmap)elements[i].Image);
            Teach();
        }

        private void Teach()
        {
            int a = (int)Math.Sqrt(size);
            for (int k = 0; k < bitmaps.Count; k++)                         //Заполнение обучающих массивов
                for (int h = 0; h < a; h++)
                    for (int w = 0; w < a; w++)
                    {
                        if (bitmaps[k].GetPixel(w, h).GetBrightness() == 0)
                            examples[k, h * a + w] = 1;
                        else examples[k, h * a + w] = -1;
                    }

            for (int k = 0; k < count; k++)
                for (int i = 0; i < size; i++)
                    for (int j = 0; j < size; j++)
                        w[i, j] += examples[k, i] * examples[k, j];

            for (int i = 0; i < size; i++)
                for (int j = 0; j < size; j++)
                    w[i, j] /= count;

            for (int i = 0; i < size; i++)
                w[i, i] = 0;
        }

        public Bitmap Find(Bitmap bmp) 
        {
            double[] t = new double[size];
            double[] y = new double[size];

            for (int h = 0; h < bmp.Height; h++)
                for (int w = 0; w < bmp.Width; w++)
                    if (bmp.GetPixel(w, h).GetBrightness() == 0)
                        t[h * bmp.Width + w] = 1;
                    else t[h * bmp.Width + w] = -1;

            for (int k = 0; k < 10; k++)
            {
                for (int i = 0; i < size; i++)
                    for (int j = 0; j < size; j++)
                        y[i] += w[i, j] * t[j];


                for (int i = 0; i < size; i++)
                    t[i] = Functions.Sign(y[i]);
            }


            int a = (int)Math.Sqrt(size);
            Bitmap result = new Bitmap(a, a);
            for (int h = 0; h < result.Height; h++)
                for (int w = 0; w < result.Width; w++)
                    if (t[a * h + w] == -1) result.SetPixel(w, h, Color.White);
                    else result.SetPixel(w, h, Color.Black);

            return result;
        }
    }
}
