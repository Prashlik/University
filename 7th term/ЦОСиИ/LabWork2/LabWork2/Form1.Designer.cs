namespace LabWork2
{
    partial class Form1
    {
        /// <summary>
        /// Обязательная переменная конструктора.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Освободить все используемые ресурсы.
        /// </summary>
        /// <param name="disposing">истинно, если управляемый ресурс должен быть удален; иначе ложно.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Код, автоматически созданный конструктором форм Windows

        /// <summary>
        /// Требуемый метод для поддержки конструктора — не изменяйте 
        /// содержимое этого метода с помощью редактора кода.
        /// </summary>
        private void InitializeComponent()
        {
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(Form1));
            this.choose = new System.Windows.Forms.Button();
            this.Photo = new System.Windows.Forms.PictureBox();
            this.Graph1 = new System.Windows.Forms.PictureBox();
            this.label1 = new System.Windows.Forms.Label();
            this.Graph2 = new System.Windows.Forms.PictureBox();
            this.Result = new System.Windows.Forms.PictureBox();
            this.label2 = new System.Windows.Forms.Label();
            this.transform = new System.Windows.Forms.Button();
            this.trackBar1 = new System.Windows.Forms.TrackBar();
            this.label3 = new System.Windows.Forms.Label();
            this.save = new System.Windows.Forms.Button();
            this.cluster = new System.Windows.Forms.Button();
            this.numericUpDown1 = new System.Windows.Forms.NumericUpDown();
            this.ClusterImg = new System.Windows.Forms.PictureBox();
            this.label4 = new System.Windows.Forms.Label();
            this.checkBoxArea = new System.Windows.Forms.CheckBox();
            this.checkBoxPerimeter = new System.Windows.Forms.CheckBox();
            this.checkBoxCompactness = new System.Windows.Forms.CheckBox();
            this.checkBoxElongation = new System.Windows.Forms.CheckBox();
            this.label5 = new System.Windows.Forms.Label();
            ((System.ComponentModel.ISupportInitialize)(this.Photo)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.Graph1)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.Graph2)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.Result)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.trackBar1)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDown1)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.ClusterImg)).BeginInit();
            this.SuspendLayout();
            // 
            // choose
            // 
            this.choose.Location = new System.Drawing.Point(277, 311);
            this.choose.Name = "choose";
            this.choose.Size = new System.Drawing.Size(303, 57);
            this.choose.TabIndex = 0;
            this.choose.Text = "Выбрать фото";
            this.choose.UseVisualStyleBackColor = true;
            this.choose.Click += new System.EventHandler(this.choose_Click);
            // 
            // Photo
            // 
            this.Photo.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Center;
            this.Photo.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D;
            this.Photo.Location = new System.Drawing.Point(0, 0);
            this.Photo.Name = "Photo";
            this.Photo.Size = new System.Drawing.Size(429, 305);
            this.Photo.TabIndex = 1;
            this.Photo.TabStop = false;
            // 
            // Graph1
            // 
            this.Graph1.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D;
            this.Graph1.Location = new System.Drawing.Point(9, 310);
            this.Graph1.Margin = new System.Windows.Forms.Padding(2);
            this.Graph1.Name = "Graph1";
            this.Graph1.Size = new System.Drawing.Size(264, 338);
            this.Graph1.TabIndex = 2;
            this.Graph1.TabStop = false;
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Font = new System.Drawing.Font("Microsoft Sans Serif", 10.2F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.label1.Location = new System.Drawing.Point(6, 651);
            this.label1.Margin = new System.Windows.Forms.Padding(2, 0, 2, 0);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(187, 34);
            this.label1.TabIndex = 3;
            this.label1.Text = "Гистограмма яркости \r\nисходного изображения";
            // 
            // Graph2
            // 
            this.Graph2.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D;
            this.Graph2.Location = new System.Drawing.Point(585, 310);
            this.Graph2.Margin = new System.Windows.Forms.Padding(2);
            this.Graph2.Name = "Graph2";
            this.Graph2.Size = new System.Drawing.Size(264, 338);
            this.Graph2.TabIndex = 4;
            this.Graph2.TabStop = false;
            // 
            // Result
            // 
            this.Result.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Center;
            this.Result.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D;
            this.Result.Location = new System.Drawing.Point(427, 0);
            this.Result.Name = "Result";
            this.Result.Size = new System.Drawing.Size(429, 305);
            this.Result.TabIndex = 5;
            this.Result.TabStop = false;
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Font = new System.Drawing.Font("Microsoft Sans Serif", 10.2F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.label2.Location = new System.Drawing.Point(582, 648);
            this.label2.Margin = new System.Windows.Forms.Padding(2, 0, 2, 0);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(244, 34);
            this.label2.TabIndex = 6;
            this.label2.Text = "Гистограмма яркости \r\nрезультирующего изображения";
            // 
            // transform
            // 
            this.transform.Location = new System.Drawing.Point(277, 375);
            this.transform.Name = "transform";
            this.transform.Size = new System.Drawing.Size(303, 57);
            this.transform.TabIndex = 7;
            this.transform.Text = "Коррекция изображения";
            this.transform.UseVisualStyleBackColor = true;
            this.transform.Click += new System.EventHandler(this.transform_Click);
            // 
            // trackBar1
            // 
            this.trackBar1.Location = new System.Drawing.Point(277, 437);
            this.trackBar1.Margin = new System.Windows.Forms.Padding(2);
            this.trackBar1.Maximum = 50;
            this.trackBar1.Minimum = 1;
            this.trackBar1.Name = "trackBar1";
            this.trackBar1.Size = new System.Drawing.Size(303, 45);
            this.trackBar1.TabIndex = 8;
            this.trackBar1.TickStyle = System.Windows.Forms.TickStyle.Both;
            this.trackBar1.Value = 1;
            this.trackBar1.Scroll += new System.EventHandler(this.trackBar1_Scroll);
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Font = new System.Drawing.Font("Microsoft Sans Serif", 10.2F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.label3.Location = new System.Drawing.Point(347, 477);
            this.label3.Margin = new System.Windows.Forms.Padding(2, 0, 2, 0);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(166, 17);
            this.label3.TabIndex = 9;
            this.label3.Text = "Коэффициент (1..50)\r\n";
            // 
            // save
            // 
            this.save.Location = new System.Drawing.Point(277, 628);
            this.save.Name = "save";
            this.save.Size = new System.Drawing.Size(303, 57);
            this.save.TabIndex = 13;
            this.save.Text = "Сохранить результат";
            this.save.UseVisualStyleBackColor = true;
            this.save.Click += new System.EventHandler(this.save_Click);
            // 
            // cluster
            // 
            this.cluster.Location = new System.Drawing.Point(277, 500);
            this.cluster.Name = "cluster";
            this.cluster.Size = new System.Drawing.Size(256, 57);
            this.cluster.TabIndex = 17;
            this.cluster.Text = "Кластеризация";
            this.cluster.UseVisualStyleBackColor = true;
            this.cluster.Click += new System.EventHandler(this.cluster_Click);
            // 
            // numericUpDown1
            // 
            this.numericUpDown1.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.numericUpDown1.Location = new System.Drawing.Point(537, 515);
            this.numericUpDown1.Margin = new System.Windows.Forms.Padding(2);
            this.numericUpDown1.Maximum = new decimal(new int[] {
            20,
            0,
            0,
            0});
            this.numericUpDown1.Minimum = new decimal(new int[] {
            1,
            0,
            0,
            0});
            this.numericUpDown1.Name = "numericUpDown1";
            this.numericUpDown1.Size = new System.Drawing.Size(43, 26);
            this.numericUpDown1.TabIndex = 18;
            this.numericUpDown1.Value = new decimal(new int[] {
            1,
            0,
            0,
            0});
            // 
            // ClusterImg
            // 
            this.ClusterImg.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Center;
            this.ClusterImg.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D;
            this.ClusterImg.Location = new System.Drawing.Point(854, 0);
            this.ClusterImg.Name = "ClusterImg";
            this.ClusterImg.Size = new System.Drawing.Size(573, 648);
            this.ClusterImg.TabIndex = 19;
            this.ClusterImg.TabStop = false;
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Font = new System.Drawing.Font("Microsoft Sans Serif", 10.2F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.label4.Location = new System.Drawing.Point(1058, 651);
            this.label4.Margin = new System.Windows.Forms.Padding(2, 0, 2, 0);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(203, 17);
            this.label4.TabIndex = 20;
            this.label4.Text = "Результат кластеризации";
            // 
            // checkBoxArea
            // 
            this.checkBoxArea.AutoSize = true;
            this.checkBoxArea.Location = new System.Drawing.Point(339, 582);
            this.checkBoxArea.Name = "checkBoxArea";
            this.checkBoxArea.Size = new System.Drawing.Size(73, 17);
            this.checkBoxArea.TabIndex = 22;
            this.checkBoxArea.Text = "Площадь";
            this.checkBoxArea.UseVisualStyleBackColor = true;
            // 
            // checkBoxPerimeter
            // 
            this.checkBoxPerimeter.AutoSize = true;
            this.checkBoxPerimeter.Location = new System.Drawing.Point(339, 605);
            this.checkBoxPerimeter.Name = "checkBoxPerimeter";
            this.checkBoxPerimeter.Size = new System.Drawing.Size(77, 17);
            this.checkBoxPerimeter.TabIndex = 23;
            this.checkBoxPerimeter.Text = "Периметр";
            this.checkBoxPerimeter.UseVisualStyleBackColor = true;
            // 
            // checkBoxCompactness
            // 
            this.checkBoxCompactness.AutoSize = true;
            this.checkBoxCompactness.Location = new System.Drawing.Point(422, 582);
            this.checkBoxCompactness.Name = "checkBoxCompactness";
            this.checkBoxCompactness.Size = new System.Drawing.Size(99, 17);
            this.checkBoxCompactness.TabIndex = 24;
            this.checkBoxCompactness.Text = "Компактность";
            this.checkBoxCompactness.UseVisualStyleBackColor = true;
            // 
            // checkBoxElongation
            // 
            this.checkBoxElongation.AutoSize = true;
            this.checkBoxElongation.Location = new System.Drawing.Point(422, 605);
            this.checkBoxElongation.Name = "checkBoxElongation";
            this.checkBoxElongation.Size = new System.Drawing.Size(105, 17);
            this.checkBoxElongation.TabIndex = 25;
            this.checkBoxElongation.Text = "Удлиннённость";
            this.checkBoxElongation.UseVisualStyleBackColor = true;
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Font = new System.Drawing.Font("Microsoft Sans Serif", 10.2F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.label5.Location = new System.Drawing.Point(316, 560);
            this.label5.Margin = new System.Windows.Forms.Padding(2, 0, 2, 0);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(235, 17);
            this.label5.TabIndex = 26;
            this.label5.Text = "Признаки для кластеризации:";
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.AutoSize = true;
            this.AutoSizeMode = System.Windows.Forms.AutoSizeMode.GrowAndShrink;
            this.ClientSize = new System.Drawing.Size(1155, 687);
            this.Controls.Add(this.label5);
            this.Controls.Add(this.checkBoxElongation);
            this.Controls.Add(this.checkBoxCompactness);
            this.Controls.Add(this.checkBoxPerimeter);
            this.Controls.Add(this.checkBoxArea);
            this.Controls.Add(this.label4);
            this.Controls.Add(this.ClusterImg);
            this.Controls.Add(this.numericUpDown1);
            this.Controls.Add(this.cluster);
            this.Controls.Add(this.save);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.trackBar1);
            this.Controls.Add(this.transform);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.Result);
            this.Controls.Add(this.Graph2);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.Graph1);
            this.Controls.Add(this.Photo);
            this.Controls.Add(this.choose);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedToolWindow;
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.MaximizeBox = false;
            this.MaximumSize = new System.Drawing.Size(1442, 739);
            this.MinimizeBox = false;
            this.MinimumSize = new System.Drawing.Size(1154, 675);
            this.Name = "Form1";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "LabWork2";
            ((System.ComponentModel.ISupportInitialize)(this.Photo)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.Graph1)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.Graph2)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.Result)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.trackBar1)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDown1)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.ClusterImg)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button choose;
        private System.Windows.Forms.PictureBox Photo;
        private System.Windows.Forms.PictureBox Graph1;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.PictureBox Graph2;
        private System.Windows.Forms.PictureBox Result;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Button transform;
        private System.Windows.Forms.TrackBar trackBar1;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Button save;
        private System.Windows.Forms.Button cluster;
        private System.Windows.Forms.NumericUpDown numericUpDown1;
        private System.Windows.Forms.PictureBox ClusterImg;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.CheckBox checkBoxArea;
        private System.Windows.Forms.CheckBox checkBoxPerimeter;
        private System.Windows.Forms.CheckBox checkBoxCompactness;
        private System.Windows.Forms.CheckBox checkBoxElongation;
        private System.Windows.Forms.Label label5;
    }
}

