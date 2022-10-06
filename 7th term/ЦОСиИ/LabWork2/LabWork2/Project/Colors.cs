using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace LabWork2
{
    public struct RgbColor
    {
        public int Red, Green, Blue;

        public RgbColor(int Red, int Green, int Blue)
        {
            this.Red = Red;
            this.Green = Green;
            this.Blue = Blue;
        }
    }
    public struct HsbColor
    {
        public double Hue, Saturation, Brightness;

        public HsbColor(double Hue, double Saturation, double Brightness)
        {
            this.Hue = Hue;
            this.Saturation = Saturation;
            this.Brightness = Brightness;
        }
    }
    internal class Colors
    {
        public static HsbColor RgbToHsb(
            RgbColor rgb)
        {
            var r = rgb.Red / 255d;
            var g = rgb.Green / 255d;
            var b = rgb.Blue / 255d;

            var minValue = Math.Min(r, Math.Min(g, b));
            var maxValue = Math.Max(r, Math.Max(g, b));
            var delta = maxValue - minValue;

            double hue = 0;
            double saturation;
            var brightness = maxValue * 100;

            if (Math.Abs(maxValue - 0) < double.Epsilon || Math.Abs(delta - 0) < double.Epsilon)
            {
                hue = 0;
                saturation = 0;
            }
            else
            {
                if (Math.Abs(minValue - 0) < double.Epsilon)
                {
                    saturation = 100;
                }
                else
                {
                    saturation = delta / maxValue * 100;
                }

                if (Math.Abs(r - maxValue) < double.Epsilon)
                {
                    hue = (g - b) / delta;
                }
                else if (Math.Abs(g - maxValue) < double.Epsilon)
                {
                    hue = 2 + (b - r) / delta;
                }
                else if (Math.Abs(b - maxValue) < double.Epsilon)
                {
                    hue = 4 + (r - g) / delta;
                }
            }

            hue *= 60;
            if (hue < 0)
            {
                hue += 360;
            }

            return new HsbColor(hue, saturation, brightness);
        }

        public static RgbColor HsbToRgb(
           HsbColor hsb)
        {
            double red = 0, green = 0, blue = 0;

            double h = hsb.Hue;
            var s = (double)hsb.Saturation / 100;
            var b = (double)hsb.Brightness / 100;

            if (Math.Abs(s - 0) < double.Epsilon)
            {
                red = b;
                green = b;
                blue = b;
            }
            else
            {
                var sectorPosition = h / 60;
                var sectorNumber = (int)Math.Floor(sectorPosition);
                var fractionalSector = sectorPosition - sectorNumber;

                var p = b * (1 - s);
                var q = b * (1 - s * fractionalSector);
                var t = b * (1 - s * (1 - fractionalSector));

                switch (sectorNumber)
                {
                    case 0:
                        red = b;
                        green = t;
                        blue = p;
                        break;

                    case 1:
                        red = q;
                        green = b;
                        blue = p;
                        break;

                    case 2:
                        red = p;
                        green = b;
                        blue = t;
                        break;

                    case 3:
                        red = p;
                        green = q;
                        blue = b;
                        break;

                    case 4:
                        red = t;
                        green = p;
                        blue = b;
                        break;

                    case 5:
                        red = b;
                        green = p;
                        blue = q;
                        break;
                }
            }

            var nRed = Convert.ToInt32(red * 255);
            var nGreen = Convert.ToInt32(green * 255);
            var nBlue = Convert.ToInt32(blue * 255);

            return new RgbColor(nRed, nGreen, nBlue);
        }
    }
}
