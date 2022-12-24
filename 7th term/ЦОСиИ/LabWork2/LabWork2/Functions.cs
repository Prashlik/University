using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Drawing;
using System.Windows.Forms;

namespace LabWork2
{
    internal class Functions
    {
        public static Image ResizeImage(Image imgToResize, Size size)
        {
            float ratW = (float)size.Width / imgToResize.Width;
            float ratH = (float)size.Height / imgToResize.Height;
            if (ratW < ratH)
                size.Height = (int)((float)imgToResize.Height * ratW);
            else
                size.Width = (int)((float)imgToResize.Width * ratH);

            return (Image)(new Bitmap(imgToResize, size));
        }
        public static void DrawGraph(Bitmap bmp, PictureBox graph)
        {
            int[] hist = new int[256];
            int a;
            for (int h = 0; h < bmp.Height; h++)
                for (int w = 0; w < bmp.Width; w++)
                {
                    a = (int)(bmp.GetPixel(w, h).GetBrightness() * 255);
                    hist[a]++;
                }

            Graphics g = graph.CreateGraphics();
            g.Clear(Color.White);
            Pen pen = new Pen(Color.Black, 1);

            float step = 1;
            float mult = (float)graph.Height / hist.Max();
            int height = graph.Height;

            for (int i = 0; i < 256; i++)
                g.DrawLine(pen, step * (i + 1), height - (float)hist[i] * mult, step * (i + 1), height - 1);
        }
        public static Bitmap TransformImage(Bitmap bmp, int c)
        {
            int width = bmp.Width;
            int height = bmp.Height;
            Bitmap resBmp = new Bitmap(width, height);

            for (int h = 0; h < height; h++)
                for (int w = 0; w < width; w++)
                {
                    RgbColor tempRgb;
                    HsbColor tempHsb;

                    tempRgb.Red = bmp.GetPixel(w, h).R;
                    tempRgb.Green = bmp.GetPixel(w, h).G;
                    tempRgb.Blue = bmp.GetPixel(w, h).B;

                    tempHsb = Colors.RgbToHsb(tempRgb);

                    //tempHsb.Brightness = (c * Math.Log(1 + ((tempHsb.Brightness / 100d) * 255)));

                    tempHsb.Brightness = ((Math.Pow(Math.E, (tempHsb.Brightness / c)) - 1) / 255) * 100d;
                    if (tempHsb.Brightness > 255) tempHsb.Brightness = 255;
                    else if (tempHsb.Brightness < 0) tempHsb.Brightness = 0;

                    tempHsb.Brightness = (tempHsb.Brightness / 255) * 100;

                    tempRgb = Colors.HsbToRgb(tempHsb);
                    resBmp.SetPixel(w, h, Color.FromArgb(255, tempRgb.Red, tempRgb.Green, tempRgb.Blue));
                }

            return resBmp;
        }
        public static Bitmap Filter(Bitmap bmp)
        {
            int[,] mtrx = new int[3, 3];
            for (int i = 0; i < 3; i += 2)
                for (int j = 0; j < 3; j += 2)
                    mtrx[i, j] = 1;
            mtrx[0, 1] = 2;
            mtrx[1, 0] = 2;
            mtrx[1, 2] = 2;
            mtrx[2, 1] = 2;
            mtrx[1, 1] = 4;

            int width = bmp.Width;
            int height = bmp.Height;
            int c = 16;

            for (int h = 1; h < height - 1; h++)
                for (int w = 1; w < width - 1; w++)
                {
                    int tempc = c;
                    float red = 0, green = 0, blue = 0;
                    for (int i = 0; i < 3; i++)
                        for (int j = 0; j < 3; j++)
                        {
                            if ((w - 1 + j) < 0 && (h - 1 + i) < 0 && (w - 1 + j) > width && (h - 1 + i) < height)
                            {
                                tempc -= mtrx[i, j];
                                continue;
                            }
                            red += mtrx[i, j] * bmp.GetPixel(w - 1 + j, h - 1 + i).R;
                            green += mtrx[i, j] * bmp.GetPixel(w - 1 + j, h - 1 + i).G;
                            blue += mtrx[i, j] * bmp.GetPixel(w - 1 + j, h - 1 + i).B;
                        }
                    red /= tempc;
                    green /= tempc;
                    blue /= tempc;
                    bmp.SetPixel(w, h, Color.FromArgb((int)red, (int)green, (int)blue));
                }

            return bmp;
        }
        public static Bitmap ToBinary(Bitmap bmp)
        {
            Bitmap res = new Bitmap(bmp.Width, bmp.Height);
            double max_brightness = 0;

            for (int i = 0; i < bmp.Height; i++)
                for (int j = 0; j < bmp.Width; j++)
                    if (bmp.GetPixel(j, i).GetBrightness() > max_brightness)
                        max_brightness = bmp.GetPixel(j, i).GetBrightness();



            for (int i = 0; i < bmp.Height; i++)
                for (int j = 0; j < bmp.Width; j++)
                {
                    if (bmp.GetPixel(j, i).GetBrightness() < (max_brightness / 2))
                        res.SetPixel(j, i, Color.Black);
                    else
                    {
                        res.SetPixel((int)j, i, Color.White);
                    }
                }

            return res;
        }
        public static List<ImageObject> Division(List<Point> points, int min)
        {
            List<ImageObject> objects = new List<ImageObject>();
            List<Point> temp = new List<Point>();

            while (points.Count != 0)
            {
                temp.Clear();
                FindNeigh(temp, points, points[0]);
                if (temp.Count > min)
                    objects.Add(new ImageObject(temp));
            }

            return objects;
        }
        public static void FindNeigh(List<Point> temp, List<Point> points, Point point)
        {
            temp.Add(point);
            points.Remove(point);
            for (int y = -1; y < 2; y++)
                for (int x = -1; x < 2; x++)
                {
                    if (x == 0 && y == 0) continue;
                    Point p = new Point((point.X + x), (point.Y + y));
                    if (points.Contains(p))
                    {
                        FindNeigh(temp, points, p);
                    }
                }
        }
    }
}
