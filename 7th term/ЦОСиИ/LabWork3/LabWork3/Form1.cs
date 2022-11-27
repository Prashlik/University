using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.IO;

namespace LabWork3
{
    public partial class Form1 : Form
    {
        OpenFileDialog ofd = new OpenFileDialog();
        List<Element> basicImages = new List<Element>();
        List<Element> testImages = new List<Element>();
        Element currentImage;
        int a, size;
        bool isSomethingAdded = false;

        public Form1()
        {
            InitializeComponent();
            ofd.Filter = "Pictures(*.png)|*.png|Pictures(*.jpg)|*.jpg|All files(*.*)|*.*";
        }

        private void addBasicImageButton_Click(object sender, EventArgs e)
        {
            if (!addImage()) return;
            selectBasic.Items.Add(currentImage.Name);
            basicImages.Add(currentImage);

            for (int i = 0; i <= 100; i += 10)
            {
                testImages.Add(new Element(Functions.MakeRandomNoize((Bitmap)currentImage.Image, i), currentImage.Name + "_" + i.ToString() + "%"));
                selectTest.Items.Add(currentImage.Name + "_" + i.ToString() + "%");
            }
            for (int i = 35; i <= 45; i += 10)
            {
                testImages.Add(new Element(Functions.MakeRandomNoize((Bitmap)currentImage.Image, i), currentImage.Name + "_" + i.ToString() + "%"));
                selectTest.Items.Add(currentImage.Name + "_" + i.ToString() + "%");
            }
        }

        private void addTestImageButton_Click(object sender, EventArgs e)
        {
            if (!addImage()) return;
            selectTest.Items.Add(currentImage.Name);
            testImages.Add(currentImage);
        }

        private void selectBasic_SelectedIndexChanged(object sender, EventArgs e)
        {
            string name = selectBasic.Text;
            currentImage = new Element(basicImages.Find(t => t.Name == name));
            textBox1.Text = null;
            Functions.PrintImage((Bitmap)currentImage.Image, pictureBox1, textBox1);
            selectTest.Text = "Тестовые образы";
            pictureBox2.BackgroundImage = null;
        }

        private void selectTest_SelectedIndexChanged(object sender, EventArgs e)
        {
            string name = selectTest.Text;
            currentImage = new Element(testImages.Find(t => t.Name == name));
            textBox1.Text = null;
            Functions.PrintImage((Bitmap)currentImage.Image, pictureBox1, textBox1);
            selectBasic.Text = "Базовые образы";
            pictureBox2.BackgroundImage = null;
        }

        private void deleteCurrentButton_Click(object sender, EventArgs e)
        {
            if (basicImages.Remove(currentImage))
            {
                string name = currentImage.Name;
                Element element;
                selectBasic.Items.Remove(name);

                for (int i = 0; i <= 100; i += 10)
                {
                    element = testImages.Find(t => t.Name == (name + "_" + i.ToString() + "%"));
                    testImages.Remove(element);
                    selectTest.Items.Remove(name + "_" + i.ToString() + "%");
                }
                for (int i = 35; i <= 45; i += 10)
                {
                    element = testImages.Find(t => t.Name == (name + "_" + i.ToString() + "%"));
                    testImages.Remove(element);
                    selectTest.Items.Remove(name + "_" + i.ToString() + "%");
                }
            }
            else
            {
                testImages.Remove(currentImage);
                selectTest.Items.Remove(currentImage.Name);
            }
            if (testImages.Count == 0 && basicImages.Count == 0)
                isSomethingAdded = false;
            selectTest.Text = "Тестовые образы";
            selectBasic.Text = "Базовые образы";
            pictureBox1.BackgroundImage = null;
            pictureBox2.BackgroundImage = null;
            textBox1.Text = null;
        }

        private void clearButton_Click(object sender, EventArgs e)
        {
            testImages.Clear();
            basicImages.Clear();
            selectBasic.Items.Clear();
            selectTest.Items.Clear();
            selectTest.Text = "Тестовые образы";
            selectBasic.Text = "Базовые образы";
            pictureBox1.BackgroundImage = null;
            pictureBox2.BackgroundImage = null;
            textBox1.Text = null;
            isSomethingAdded = false;
        }

        private void findImage_Click(object sender, EventArgs e)
        {
            Hopfield h = new Hopfield(basicImages, size);
            Bitmap found = h.Find((Bitmap)currentImage.Image);
            textBox1.Text = "Первое изображение:" + Environment.NewLine;
            Functions.PrintImage((Bitmap)currentImage.Image, pictureBox2, textBox1);
            textBox1.Text += "Полученное изображение:" + Environment.NewLine;
            Functions.PrintImage(found, pictureBox2, textBox1);

            bool flag = false;
            int i;
            for (i = 0; i < basicImages.Count; i++)
            {
                if (Functions.CompareImages((Bitmap)basicImages[i].Image, found))
                {
                    flag = true;
                    break;
                }
            }
            if (flag)
                textBox1.Text += "Полученное изображение совпадает с: " + basicImages[i].Name + Environment.NewLine;
            else textBox1.Text += "Полученное изображение не совпадает ни с одним  базовым изображением" + Environment.NewLine;
        }

        private bool addImage()
        {
            if (ofd.ShowDialog() == DialogResult.Cancel)
                return false;
            string name = Path.GetFileNameWithoutExtension(ofd.FileName);
            Image img = Image.FromFile(ofd.FileName);

            if (basicImages.Exists(t => t.Name == name) || testImages.Exists(t => t.Name == name))
            {
                MessageBox.Show("Изображение с таким именем уже существует!");
                return false;
            }
            if (img.Height != img.Width)
            {
                MessageBox.Show("Изображение не квадратное!");
                return false;
            }
            if (img.Height * img.Width != size && isSomethingAdded)
            {
                MessageBox.Show("Изображение не подходит по размеру!");
                return false;
            }
            if (!isSomethingAdded)
            {
                a = img.Width;
                size = a * a;
                isSomethingAdded = true;
            }

            Bitmap bmp = Functions.ToBinary((Bitmap)img);
            
            currentImage = new Element((Image)bmp, name);
            ofd.FileName = null;
            selectTest.Text = "Тестовые образы";
            selectBasic.Text = "Базовые образы";
            pictureBox1.BackgroundImage = null;
            pictureBox2.BackgroundImage = null;
            textBox1.Text = null;
            Functions.PrintImage(bmp, pictureBox1, textBox1);
            return true;
        }
    }
}
