using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace LabWork1
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
            Image newImage = Functions.resizeImage(img, Photo.Size);

            Result.BackgroundImage = null;
            Graph2.Image = null;
            
            Photo.BackgroundImage = newImage;

            Functions.drawGraph((Bitmap)img, Graph1);
        }

        private void transform_Click(object sender, EventArgs e)
        {
            if (img == null)
            {
                MessageBox.Show("Фотография не загружена!");
                return;
            }

            Bitmap resBmp = Functions.transformImage((Bitmap)img, trackBar1.Value);
            res = (Image)resBmp;
            Image newImage = Functions.resizeImage((Image)resBmp, Result.Size);
            Result.BackgroundImage = newImage;
            Functions.drawGraph(resBmp, Graph2);
        }

        private void Filter1_Click(object sender, EventArgs e)
        {
            if (img == null)
            {
                MessageBox.Show("Фотография не загружена!");
                return;
            }

            int[,] mtrx = new int[3,3];
            for (int i = 0; i < 3; i++)
                for (int j = 0; j < 3; j++)
                    mtrx[i, j] = 1;

            Bitmap resBmp = Functions.filter((Bitmap)img, mtrx, 9);
            res = (Image)resBmp;
            Image newImage = Functions.resizeImage((Image)resBmp, Result.Size);
            Result.BackgroundImage = newImage;
            Functions.drawGraph(resBmp, Graph2);
        }

        private void Filter2_Click(object sender, EventArgs e)
        {
            if (img == null)
            {
                MessageBox.Show("Фотография не загружена!");
                return;
            }

            int[,] mtrx = new int[3, 3];
            for (int i = 0; i < 3; i++)
                for (int j = 0; j < 3; j++)
                    mtrx[i, j] = 1;
            mtrx[1, 1] = 2;

            Bitmap resBmp = Functions.filter((Bitmap)img, mtrx, 10);
            res = (Image)resBmp;
            Image newImage = Functions.resizeImage((Image)resBmp, Result.Size);
            Result.BackgroundImage = newImage;
            Functions.drawGraph(resBmp, Graph2);
        }

        private void Filter3_Click(object sender, EventArgs e)
        {
            if (img == null)
            {
                MessageBox.Show("Фотография не загружена!");
                return;
            }

            int[,] mtrx = new int[3, 3];
            for (int i = 0; i < 3; i += 2)
                for (int j = 0; j < 3; j += 2)
                    mtrx[i, j] = 1;
            mtrx[0, 1] = 2;
            mtrx[1, 0] = 2;
            mtrx[1, 2] = 2;
            mtrx[2, 1] = 2;
            mtrx[1, 1] = 4;

            Bitmap resBmp = Functions.filter((Bitmap)img, mtrx, 16);
            res = (Image)resBmp;
            Image newImage = Functions.resizeImage((Image)resBmp, Result.Size);
            Result.BackgroundImage = newImage;
            Functions.drawGraph(resBmp, Graph2);
        }

        private void trackBar1_Scroll(object sender, EventArgs e)
        {
            label3.Text = "Коэффициент: " + trackBar1.Value.ToString();
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


