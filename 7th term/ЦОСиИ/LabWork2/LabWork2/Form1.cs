using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace LabWork2
{
    public partial class Form1 : Form
    {
        private OpenFileDialog ofd = new OpenFileDialog();
        private SaveFileDialog sfd = new SaveFileDialog();
        private Image img, res;
        public Form1()
        {
            InitializeComponent();
            ofd.Filter = "Pictures(*.jpg)|*.jpg|All files(*.*)|*.*";
            sfd.Filter = "Pictures(*.jpg)|*.jpg|All files(*.*)|*.*";
        }

        private void choose_Click(object sender, EventArgs e)
        {
            if (ofd.ShowDialog() == DialogResult.Cancel)
                return;

            string filename = ofd.FileName;
            img = Image.FromFile(ofd.FileName);
            Image newImage = Functions.ResizeImage(img, Photo.Size);

            Result.BackgroundImage = null;
            Graph2.Image = null;
            ClusterImg.Image = null;

            res = null;
            Photo.BackgroundImage = newImage;

            Functions.DrawGraph((Bitmap)img, Graph1);
        }

        private void transform_Click(object sender, EventArgs e)
        {
            if (img == null)
            {
                MessageBox.Show("Фотография не загружена!");
                return;
            }

            Bitmap resBmp = Functions.TransformImage((Bitmap)img, trackBar1.Value);
            res = (Image)resBmp;
            Image newImage = Functions.ResizeImage((Image)resBmp, Result.Size);
            Result.BackgroundImage = newImage;
            Functions.DrawGraph(resBmp, Graph2);
        }

        private void trackBar1_Scroll(object sender, EventArgs e)
        {
            label3.Text = "Коэффициент: " + trackBar1.Value.ToString();
        }

        private void cluster_Click(object sender, EventArgs e)
        {
            if (res == null)
            {
                MessageBox.Show("Фотография не обработана!");
                return;
            }
            if (!(checkBoxArea.Checked || checkBoxPerimeter.Checked || checkBoxCompactness.Checked || checkBoxElongation.Checked))
            {
                MessageBox.Show("Критерии не выбраны!");
                return;
            }

            Bitmap resBmp = Functions.Filter((Bitmap)res);
            List<Point> points = new List<Point>();
            for (int i = 0; i < resBmp.Width; i++)
                for (int j = 0; j < resBmp.Height; j++)
                    if (resBmp.GetPixel(i, j).GetBrightness() == 1)
                        points.Add(new Point(i, j));

            //for (int i = 0; i < resBmp.Height; i++)
            //{
            //    bool flag = false;
            //    for (int x = -1; x < 2; x++)
            //        for (int y = -1; y < 2; y++)
            //        {
            //            if ((x != 0 && y != 0) || (x == 0 && y == 0)) continue;
            //            if (!points.Contains(new Point((points[i].X + x), (points[i].Y + y))))
            //            {
            //                points.Remove(points[i]);
            //                flag = !flag;
            //                break;
            //            }
            //            if (flag) break;
            //        }
            //}
            
            List<ImageObject> objcts = Functions.Division(points, 150);
            List<List<float>> vals = new List<List<float>>();
            if (checkBoxArea.Checked)
            {
                float max = 0;
                for (int i = 0; i < objcts.Count; i++)
                    if (objcts[i].Area > max) max = objcts[i].Area;

                List<float> temp = new List<float>();
                for (int i = 0; i < objcts.Count; i++)
                    temp.Add((objcts[i].Area / max) * 100);
                vals.Add(temp);
            }
            if (checkBoxPerimeter.Checked)
            {
                float max = 0;
                for (int i = 0; i < objcts.Count; i++)
                    if (objcts[i].Perimeter > max) max = objcts[i].Perimeter;

                List<float> temp = new List<float>();
                for (int i = 0; i < objcts.Count; i++)
                    temp.Add((objcts[i].Perimeter / max) * 100);
                vals.Add(temp);
            }
            if (checkBoxCompactness.Checked)
            {
                float max = 0;
                for (int i = 0; i < objcts.Count; i++)
                    if (objcts[i].Compactness > max) max = objcts[i].Compactness;

                List<float> temp = new List<float>();
                for (int i = 0; i < objcts.Count; i++)
                    temp.Add((objcts[i].Compactness / max) * 100);
                vals.Add(temp);
            }
            if (checkBoxElongation.Checked)
            {
                float max = 0;
                for (int i = 0; i < objcts.Count; i++)
                    if (objcts[i].Elongation > max) max = objcts[i].Elongation;

                List<float> temp = new List<float>();
                for (int i = 0; i < objcts.Count; i++)
                    temp.Add((objcts[i].Elongation / max) * 100);
                vals.Add(temp);
            }

            int k = (int)numericUpDown1.Value;
            Cluster[] cluster = new Cluster[k];
            for (int i = 0; i < k; i++)
                cluster[i] = new Cluster();
            Cluster.Start(k, cluster, objcts, vals);

            Image newImage = Functions.ResizeImage((Image)img, ClusterImg.Size);

            Pen pen = new Pen(Color.Red, 5);
            Random rand = new Random();
            Graphics g = ClusterImg.CreateGraphics();
            int x0 = (ClusterImg.Width - newImage.Width) / 2, y0 = (ClusterImg.Height - newImage.Height) / 2;
            g.DrawImage(newImage, x0, y0);
            for (int i = 0; i < k; i++)
            {
                pen.Color = Color.FromArgb(rand.Next(255), rand.Next(255), rand.Next(255));
                int size = cluster[i].Size();
                List<ImageObject> objects = cluster[i].at();
                for (int j = 0; j < size; j++)
                {
                    int x = x0 + (int)(((float)objects[j].Center.X / img.Width) * newImage.Width);
                    int y = y0 + (int)(((float)objects[j].Center.Y / img.Height) * newImage.Height);
                    int width = (int)(((float)objects[j].Width / img.Width) * newImage.Width);
                    int height = (int)(((float)objects[j].Height / img.Height) * newImage.Height);
                    g.DrawRectangle(pen, x - (width / 2) - 5, y, width + 10, height + 10);
                }
            }
        }
        private void save_Click(object sender, EventArgs e)
        {
            if (sfd.ShowDialog() == DialogResult.Cancel)
                return;

            string filename = sfd.FileName;
            res.Save(filename);
            sfd.FileName = null;
        }
    }
}


