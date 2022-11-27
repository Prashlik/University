using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Drawing;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace LabWork4
{
    internal class Functions
    {
        public static Bitmap MakeRandomNoize(Bitmap bmp, int percent)
        {
            int height = bmp.Height, width = bmp.Width, area = height * width;
            int count = (height * width * percent) / 100;
            Bitmap newBmp = new Bitmap(bmp);
            Random random = new Random();

            if (percent == 100)
            {
                for (int i = 0; i < count; i++)
                {
                    int h = i / width, w = i - h * width;
                    if (bmp.GetPixel(w, h).GetBrightness() == 1)
                        newBmp.SetPixel(w, h, Color.Black);
                    else newBmp.SetPixel(w, h, Color.White);
                }
                return newBmp;
            }
            for (int i = 0; i < count; i++)
            {
                int temp = random.Next(area);
                int h = temp / width, w = temp - h * width;
                if (bmp.GetPixel(w, h).GetBrightness() == 1)
                    newBmp.SetPixel(w, h, Color.Black);
                else newBmp.SetPixel(w, h, Color.White);
            }

            return newBmp;
        }
        public static Bitmap ToBinary(Bitmap bmp)
        {
            Bitmap newBmp = new Bitmap(bmp.Width, bmp.Height);
            for (int h = 0; h < bmp.Size.Height; h++)
                for (int w = 0; w < bmp.Size.Width; w++)
                    if (bmp.GetPixel(w, h).GetBrightness() < 0.5) newBmp.SetPixel(w, h, Color.Black);
                    else newBmp.SetPixel(w, h, Color.White);
            return newBmp;
        }

        public static void PrintImage(Bitmap bmp, PictureBox pb)
        {
            pb.BackgroundImage = null;
            int steph = pb.Width / (bmp.Width + 1);
            int stepw = pb.Height / (bmp.Height + 1);
            int black = 0;

            Bitmap paint = new Bitmap(bmp.Width * stepw, bmp.Height * steph);

            for (int h = 0; h < bmp.Height; h++)
                for (int w = 0; w < bmp.Width; w++)
                    if (bmp.GetPixel(w, h).GetBrightness() == 0)
                    {
                        black++;
                        for (int y = 0; y < steph; y++)
                            for (int x = 0; x < stepw; x++)
                                paint.SetPixel(w * stepw + x, h * steph + y, Color.Black);
                    }

            pb.BackgroundImageLayout = ImageLayout.Center;
            pb.BackgroundImage = paint;
        }
    }
    class data_info
    {
        public double[] pixels = new double[64];
        public bool is_loaded = false;
        public Bitmap bmp;
    }
}
