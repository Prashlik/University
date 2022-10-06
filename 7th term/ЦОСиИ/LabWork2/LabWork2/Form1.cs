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

        private void trackBar2_Scroll(object sender, EventArgs e)
        {
            if (trackBar2.Value > trackBar3.Value) trackBar2.Value = trackBar3.Value;
            label4.Text = "Диапазон яркости от " + trackBar2.Value.ToString() + "% до " + trackBar3.Value.ToString() + "%";
        }

        private void trackBar3_Scroll(object sender, EventArgs e)
        {
            if (trackBar3.Value < trackBar2.Value) trackBar3.Value = trackBar2.Value;
            label4.Text = "Диапазон яркости от " + trackBar2.Value.ToString() + "% до " + trackBar3.Value.ToString() + "%";

        }

        private void cluster_Click(object sender, EventArgs e)
        {
            if (img == null)
            {
                MessageBox.Show("Фотография не загружена!");
                return;
            }

            Bitmap resBmp = Functions.ToBinary((Bitmap)res, trackBar2.Value, trackBar3.Value);
            List<Point> points = new List<Point>();
            for (int i = 0; i < resBmp.Width; i++)
                for (int j = 0; j < resBmp.Height; j++)
                    if (resBmp.GetPixel(i, j).GetBrightness() == 1)
                        points.Add(new Point(i, j));

            int k = (int)numericUpDown1.Value;
            Cluster[] cluster = new Cluster[k];
            for (int i = 0; i < k; i++)
                cluster[i] = new Cluster();
            Cluster.Start(k, cluster, points);

            Pen pen = new Pen(Color.Red, 5);
            Graphics g = Result.CreateGraphics();

            for (int i = 0; i < k; i++) {
                int x = (int)(((float)cluster[i].curX / img.Width) * Result.Width);
                int y = (int)(((float)cluster[i].curY / img.Height) * Result.Height); 
                g.DrawRectangle(pen, x, y, 10, 10);
            }
                


            res = (Image)resBmp;
            //Image newImage = Functions.resizeImage((Image)resBmp, Result.Size);
            //Result.BackgroundImage = newImage;
            Functions.DrawGraph(resBmp, Graph2);
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


