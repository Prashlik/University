using System;
using System.Drawing;
using System.Windows.Forms;
using System.IO;
using System.Collections.Generic;

namespace LabWork4
{
    public partial class Form1 : Form
    {
        OpenFileDialog ofd;
        data_info[] pictures;
        bool is_teached = false;
        List<Element> testImages;
        Network nw;

        public Form1()
        {
            InitializeComponent();
            pictures = new data_info[6];
            for (int i = 0; i < pictures.Length; i++)
                pictures[i] = new data_info();
            ofd = new OpenFileDialog();
            nw = new Network();
            testImages = new List<Element>();
        }

        private void pictureButton1_Click(object sender, EventArgs e)
        {
            addImage(pictureBox1, 1);
        }

        private void pictureButton2_Click(object sender, EventArgs e)
        {
            addImage(pictureBox2, 2);
        }

        private void pictureButton3_Click(object sender, EventArgs e)
        {
            addImage(pictureBox3, 3);
        }

        private void pictureButton4_Click(object sender, EventArgs e)
        {
            addImage(pictureBox4, 4);
        }

        private void pictureButton5_Click(object sender, EventArgs e)
        {
            addImage(pictureBox5, 5);
        }

        private void pictureButtonTest_Click(object sender, EventArgs e)
        {
            addImage(pictureBoxTest, 0);
            selectPicture.Text = "Выберите тестовое изображение...";
            matchText1.Text = String.Empty;
            matchText2.Text = String.Empty;
            matchText3.Text = String.Empty;
            matchText4.Text = String.Empty;
            matchText5.Text = String.Empty;

        }

        private void teachButton_Click(object sender, EventArgs e)
        {
            int ra = 0, right, maxra = 0;
            double predict;
            int epoch = 0;

            for (int i = 1; i <= 5; i++)
                if (pictures[i].is_loaded == false)
                {
                    MessageBox.Show("Не все изображения загружены!");
                    return;
                }

            int pop;
            nw.Init(3, new int[3] { 64, 20, 5 });
            while (ra / 500 * 100 < 90)
            {
                ra = 0;
                for (int i = 0; i < 5; i++)
                {
                    nw.SetInput(pictures[i + 1].pixels);
                    right = i;
                    predict = nw.ForwardFeed();
                    if (predict != right)
                    {
                        nw.BackPropogation(right);
                        nw.WeightsUpdater(0.2 * Math.Exp(-epoch / 20d));
                    }
                    else
                        ra++;
                }
                if (maxra <= ra) { maxra = ra; pop = epoch;  }
                epoch++;
                if (epoch == 20)
                    break;
            }

            is_teached = true;

            selectPicture.Items.Clear();
            testImages.Clear();
            for (int i = 1; i <= 5; i++)
            {
                string name = i.ToString() + "_picture";

                for (int j = 0; j <= 100; j += 10)
                {
                    testImages.Add(new Element(Functions.MakeRandomNoize(pictures[i].bmp, j), name + "_" + j.ToString() + "%"));
                    selectPicture.Items.Add(name + "_" + j.ToString() + "%");
                }
                for (int j = 35; j <= 45; j += 10)
                {
                    testImages.Add(new Element(Functions.MakeRandomNoize(pictures[i].bmp, j), name + "_" + j.ToString() + "%"));
                    selectPicture.Items.Add(name + "_" + j.ToString() + "%");
                }
            }
        }

        private void runButton_Click(object sender, EventArgs e)
        {
            if (!pictures[0].is_loaded)
            {
                MessageBox.Show("Тестовое изображение не загружено!");
                return;
            }
            else if (!is_teached)
            {
                MessageBox.Show("Нейросеть не обучена!");
                return;
            }

            double[] vals = new double[5];
            double max, min, tmp;
            nw.SetInput(pictures[0].pixels);
            int k = (int)nw.ForwardFeed();

            max = nw[0];
            min = nw[0];

            for (int i = 0; i < 5; i++)
            {
                vals[i] = nw[i];
                if (nw[i] > max) max = nw[i];
                else if (nw[i] < min) min = nw[i];
            }

            tmp = max - min;
            tmp = 100 / tmp;

            for (int i = 0; i < 5; i++)
            {
                vals[i] -= min;
                vals[i] *= tmp;
            }

            matchText1.Text = vals[0].ToString();
            matchText2.Text = vals[1].ToString();
            matchText3.Text = vals[2].ToString();
            matchText4.Text = vals[3].ToString();
            matchText5.Text = vals[4].ToString();
        }

        private void clearButton_Click(object sender, EventArgs e)
        {
            matchText1.Text = String.Empty;
            matchText2.Text = String.Empty;
            matchText3.Text = String.Empty;
            matchText4.Text = String.Empty;
            matchText5.Text = String.Empty;
            pictureBox1.BackgroundImage = null;
            pictureBox2.BackgroundImage = null;
            pictureBox3.BackgroundImage = null;
            pictureBox4.BackgroundImage = null;
            pictureBox5.BackgroundImage = null;
            pictureBoxTest.BackgroundImage = null;

            for (int i = 0; i < 6; i++)
                pictures[i].is_loaded = false;

            is_teached = false;
            selectPicture.Items.Clear();
            testImages.Clear();
            selectPicture.Text = "Выберите тестовое изображение...";
        }

        private void selectPicture_SelectedIndexChanged(object sender, EventArgs e)
        {
            string name = selectPicture.Text;
            pictures[0].bmp = testImages.Find(t => t.Name == name).Image;
            pictures[0].is_loaded = true;

            for (int h = 0; h < 8; h++)
                for (int w = 0; w < 8; w++)
                    pictures[0].pixels[(h * 8) + w] = pictures[0].bmp.GetPixel(w, h).GetBrightness();

            Functions.PrintImage(pictures[0].bmp, pictureBoxTest);

            matchText1.Text = String.Empty;
            matchText2.Text = String.Empty;
            matchText3.Text = String.Empty;
            matchText4.Text = String.Empty;
            matchText5.Text = String.Empty;

        }

        private bool addImage(PictureBox pb, int number)
        {
            if (number != 0)
                is_teached = false;
            if (ofd.ShowDialog() == DialogResult.Cancel)
                return false;
            string name = Path.GetFileNameWithoutExtension(ofd.FileName);
            Image img = Image.FromFile(ofd.FileName);

            if (img.Height != 8 || img.Width != 8)
            {
                MessageBox.Show("Неподходящий размер изображения!");
                return false;
            }

            Bitmap bmp = Functions.ToBinary((Bitmap)img);
            ofd.FileName = null;
            Functions.PrintImage(bmp, pb);
            for (int y = 0; y < 8; y++)
                for (int x = 0; x < 8; x++)
                    pictures[number].pixels[y * 8 + x] = bmp.GetPixel(x, y).GetBrightness();
            pictures[number].is_loaded = true;
            pictures[number].bmp = bmp;
            return true;
        }
    }
}

