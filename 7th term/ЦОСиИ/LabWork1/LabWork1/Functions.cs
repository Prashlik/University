using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Drawing;
using System.Windows.Forms;

namespace LabWork1
{
    public class Functions
    {
        public static Image resizeImage(Image imgToResize, Size size)
        {
            float ratW = (float)size.Width / imgToResize.Width;
            float ratH = (float)size.Height / imgToResize.Height;
            if (ratW < ratH)
                size.Height = (int)((float)imgToResize.Height * ratW);
            else
                size.Width = (int)((float)imgToResize.Width * ratH);

            return (Image)(new Bitmap(imgToResize, size));
        }

        public static void drawGraph(Bitmap bmp, PictureBox graph)
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

        public static Bitmap transformImage(Bitmap bmp, int c)
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

                    tempHsb.Brightness = (c * Math.Log(1 + ((tempHsb.Brightness / 100d) * 255)));
                    if (tempHsb.Brightness > 255) tempHsb.Brightness = 255;
                    else if (tempHsb.Brightness < 0) tempHsb.Brightness = 0;

                    tempHsb.Brightness = (tempHsb.Brightness / 255) * 100;

                    tempRgb = Colors.HsbToRgb(tempHsb);
                    resBmp.SetPixel(w, h, Color.FromArgb(255, tempRgb.Red, tempRgb.Green, tempRgb.Blue));
                }

            return resBmp;
        }

        public static Bitmap filter(Bitmap bmp, int[,] mtrx, int c)
        {
            int width = bmp.Width;
            int height = bmp.Height;

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

    }
}
