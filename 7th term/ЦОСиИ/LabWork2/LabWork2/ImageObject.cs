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
        private int area, perimeter, height, width;
        private Point centerOfMass, center;
        private float compactness, elongation;
        private float a, b, orientation;

        public ImageObject() 
        {
            points = new List<Point>();
            area = 0;
            perimeter = 0;
            centerOfMass = new Point();
            compactness = 0;
            elongation = 0;
        }
        public ImageObject(List<Point> points)
        {
            this.points = points;
            area = points.Count;
            calculate();
        }
        public ImageObject(ImageObject @object)
        {
            points = @object.points;
            area = @object.area;
            perimeter = @object.perimeter;
            centerOfMass = @object.centerOfMass;
            compactness = @object.compactness;
            elongation = @object.elongation;
            center = @object.center;
            a = @object.a;
            b = @object.b;
            orientation = @object.orientation; 
            height = @object.height;
            width = @object.width;
        }
        public List<Point> Points { get { return points; } }
        public int Area { get { return area; } }
        public int Perimeter { get { return perimeter; } }
        public Point CenterOfMass { get { return centerOfMass; } }
        public float Compactness { get { return compactness; } }
        public float Elongation { get { return elongation; } }
        public float A { get { return a; } }
        public float B { get { return b; } }
        public float Orientation { get { return orientation; } }
        public Point Center { get { return center; } }
        public int Width { get { return width; } }
        public int Height { get { return height; } }
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
            centerOfMass.X = (int)(x / area);
            centerOfMass.Y = (int)(y / area);

            compactness = (float)(Math.Pow(perimeter, 2) / area);   //Вычисление компактности

            float m20 = 0, m02 = 0, m11 = 0;        //Вычисление удлинённости
            for (int i = 0; i < area; i++)
            {
                m20 += (float)Math.Pow((points[i].X - centerOfMass.X), 2);
                m02 += (float)Math.Pow((points[i].Y - centerOfMass.Y), 2);
                m11 += (points[i].X - centerOfMass.X)*(points[i].Y - centerOfMass.Y);
            }
            a = (float)(m20 + m02 + Math.Sqrt(Math.Pow((m20 - m02), 2) + 4 * Math.Pow(m11, 2)));
            b = (float)(m20 + m02 - Math.Sqrt(Math.Pow((m20 - m02), 2) + 4 * Math.Pow(m11, 2)));
            elongation = a / b;

            orientation = (float)Math.Atan((2 * m11 / (m20 - m02))) / 2;    //Вычисление ориентацию

            int xMin = points[0].X, xMax = points[0].X, yMin = points[0].Y, yMax = points[0].Y;
            for (int i = 1; i < area; i++)
            {
                if (points[i].X < xMin) xMin = points[i].X;
                if (points[i].X > xMax) xMax = points[i].X;
                if (points[i].Y < yMin) yMin = points[i].Y;
                if (points[i].Y > yMax) yMax = points[i].Y;                   
            }

            center.X = (xMin + xMax) / 2;
            center.Y = (yMin + yMin) / 2;
            width = xMax - xMin;
            height = yMax - yMin;
        }
    }
}
