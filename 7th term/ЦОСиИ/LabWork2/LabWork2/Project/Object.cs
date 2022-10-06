using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Drawing;

namespace LabWork2
{
    internal class ImageObject
    {
        private List<Point> points;
        private int area, perimeter;
        private Point center;
        private float compactness, elongation;

        public ImageObject() 
        {
            points = new List<Point>();
            area = 0;
            perimeter = 0;
            center = new Point();
            compactness = 0;
            elongation = 0;
        }
        public ImageObject(List<Point> points)
        {
            area = points.Count;
            calculate();
        }
        public ImageObject(ImageObject @object)
        {
            points = @object.points;
            area = @object.area;
            perimeter = @object.perimeter;
            center = @object.center;
            compactness = @object.compactness;
            elongation = @object.elongation;
        }
        public List<Point> Points { get { return points; } }
        public int Area { get { return area; } }
        public int Perimeter { get { return perimeter; } }
        public Point Center { get { return center; } }
        public float Compactness { get { return compactness; } }
        public float Elongation { get { return elongation; } }
        private void calculate()
        {
            perimeter = 0;                          //Вычисление периметра
            for (int i = 0; i < area; i++)
            {
                bool flag = false;
                for (int h = -1; h < 2; h++)
                {
                    for (int w = -1; w < 2; w++)
                        if (!points.Contains(new Point((points[i].X + w), (points[i].Y + h))))
                        {
                            perimeter++;
                            flag = !flag;
                            break;
                        }
                    if (flag) break;
                }
            }

            float x = 0, y = 0;                     //Вычисление центра масс
            for (int i = 0; i < area; i++)
            {
                x += points[i].X;
                y += points[i].Y;
            }
            center.X = (int)(x / area);
            center.Y = (int)(y / area);

            compactness = (float)(Math.Pow(perimeter, 2) / area);   //Вычисление компактности

            float m20 = 0, m02 = 0, m11 = 0;        //Вычисление удлинённости
            for (int i = 0; i < area; i++)
            {
                m20 += (float)Math.Pow((points[i].X - center.X), 2);
                m02 += (float)Math.Pow((points[i].Y - center.Y), 2);
                m11 += (points[i].X - center.X)*(points[i].Y - center.Y);
            }
            elongation = (float)((m20 + m02 + Math.Sqrt(Math.Pow((m20 - m02), 2) + 4 * Math.Pow(m11, 2))) / (m20 + m02 - Math.Sqrt(Math.Pow((m20 - m02), 2) + 4 * Math.Pow(m11, 2))));
        }
    }
}
