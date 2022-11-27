namespace LabWork3
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
            this.pictureBox1 = new System.Windows.Forms.PictureBox();
            this.addBasicImageButton = new System.Windows.Forms.Button();
            this.selectBasic = new System.Windows.Forms.ComboBox();
            this.addTestImageButton = new System.Windows.Forms.Button();
            this.selectTest = new System.Windows.Forms.ComboBox();
            this.deleteCurrentButton = new System.Windows.Forms.Button();
            this.findImage = new System.Windows.Forms.Button();
            this.pictureBox2 = new System.Windows.Forms.PictureBox();
            this.textBox1 = new System.Windows.Forms.TextBox();
            this.clearButton = new System.Windows.Forms.Button();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox2)).BeginInit();
            this.SuspendLayout();
            // 
            // pictureBox1
            // 
            this.pictureBox1.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Stretch;
            this.pictureBox1.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D;
            this.pictureBox1.Location = new System.Drawing.Point(11, 9);
            this.pictureBox1.Margin = new System.Windows.Forms.Padding(2, 2, 2, 2);
            this.pictureBox1.Name = "pictureBox1";
            this.pictureBox1.Size = new System.Drawing.Size(220, 220);
            this.pictureBox1.TabIndex = 0;
            this.pictureBox1.TabStop = false;
            // 
            // addBasicImageButton
            // 
            this.addBasicImageButton.Location = new System.Drawing.Point(235, 11);
            this.addBasicImageButton.Margin = new System.Windows.Forms.Padding(2, 2, 2, 2);
            this.addBasicImageButton.Name = "addBasicImageButton";
            this.addBasicImageButton.Size = new System.Drawing.Size(150, 30);
            this.addBasicImageButton.TabIndex = 1;
            this.addBasicImageButton.Text = "Добавить изображение";
            this.addBasicImageButton.UseVisualStyleBackColor = true;
            this.addBasicImageButton.Click += new System.EventHandler(this.addBasicImageButton_Click);
            // 
            // selectBasic
            // 
            this.selectBasic.FormattingEnabled = true;
            this.selectBasic.Location = new System.Drawing.Point(235, 46);
            this.selectBasic.Name = "selectBasic";
            this.selectBasic.Size = new System.Drawing.Size(150, 21);
            this.selectBasic.Sorted = true;
            this.selectBasic.TabIndex = 2;
            this.selectBasic.Text = "Базовые образы";
            this.selectBasic.SelectedIndexChanged += new System.EventHandler(this.selectBasic_SelectedIndexChanged);
            // 
            // addTestImageButton
            // 
            this.addTestImageButton.Location = new System.Drawing.Point(235, 72);
            this.addTestImageButton.Margin = new System.Windows.Forms.Padding(2, 2, 2, 2);
            this.addTestImageButton.Name = "addTestImageButton";
            this.addTestImageButton.Size = new System.Drawing.Size(150, 30);
            this.addTestImageButton.TabIndex = 3;
            this.addTestImageButton.Text = "Добавить тестовый образ";
            this.addTestImageButton.UseVisualStyleBackColor = true;
            this.addTestImageButton.Click += new System.EventHandler(this.addTestImageButton_Click);
            // 
            // selectTest
            // 
            this.selectTest.FormattingEnabled = true;
            this.selectTest.Location = new System.Drawing.Point(235, 107);
            this.selectTest.Name = "selectTest";
            this.selectTest.Size = new System.Drawing.Size(150, 21);
            this.selectTest.Sorted = true;
            this.selectTest.TabIndex = 4;
            this.selectTest.Text = "Тестовые образы";
            this.selectTest.SelectedIndexChanged += new System.EventHandler(this.selectTest_SelectedIndexChanged);
            // 
            // deleteCurrentButton
            // 
            this.deleteCurrentButton.Location = new System.Drawing.Point(235, 133);
            this.deleteCurrentButton.Margin = new System.Windows.Forms.Padding(2, 2, 2, 2);
            this.deleteCurrentButton.Name = "deleteCurrentButton";
            this.deleteCurrentButton.Size = new System.Drawing.Size(150, 30);
            this.deleteCurrentButton.TabIndex = 5;
            this.deleteCurrentButton.Text = "Удалить текущий";
            this.deleteCurrentButton.UseVisualStyleBackColor = true;
            this.deleteCurrentButton.Click += new System.EventHandler(this.deleteCurrentButton_Click);
            // 
            // findImage
            // 
            this.findImage.Location = new System.Drawing.Point(235, 201);
            this.findImage.Margin = new System.Windows.Forms.Padding(2, 2, 2, 2);
            this.findImage.Name = "findImage";
            this.findImage.Size = new System.Drawing.Size(150, 30);
            this.findImage.TabIndex = 6;
            this.findImage.Text = "Распознать образ";
            this.findImage.UseVisualStyleBackColor = true;
            this.findImage.Click += new System.EventHandler(this.findImage_Click);
            // 
            // pictureBox2
            // 
            this.pictureBox2.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Stretch;
            this.pictureBox2.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D;
            this.pictureBox2.Location = new System.Drawing.Point(389, 9);
            this.pictureBox2.Margin = new System.Windows.Forms.Padding(2, 2, 2, 2);
            this.pictureBox2.Name = "pictureBox2";
            this.pictureBox2.Size = new System.Drawing.Size(220, 220);
            this.pictureBox2.TabIndex = 7;
            this.pictureBox2.TabStop = false;
            // 
            // textBox1
            // 
            this.textBox1.Enabled = false;
            this.textBox1.Location = new System.Drawing.Point(11, 236);
            this.textBox1.Multiline = true;
            this.textBox1.Name = "textBox1";
            this.textBox1.Size = new System.Drawing.Size(598, 139);
            this.textBox1.TabIndex = 8;
            // 
            // clearButton
            // 
            this.clearButton.Location = new System.Drawing.Point(235, 167);
            this.clearButton.Margin = new System.Windows.Forms.Padding(2, 2, 2, 2);
            this.clearButton.Name = "clearButton";
            this.clearButton.Size = new System.Drawing.Size(150, 30);
            this.clearButton.TabIndex = 9;
            this.clearButton.Text = "Удалить всё";
            this.clearButton.UseVisualStyleBackColor = true;
            this.clearButton.Click += new System.EventHandler(this.clearButton_Click);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(620, 391);
            this.Controls.Add(this.clearButton);
            this.Controls.Add(this.textBox1);
            this.Controls.Add(this.pictureBox2);
            this.Controls.Add(this.findImage);
            this.Controls.Add(this.deleteCurrentButton);
            this.Controls.Add(this.selectTest);
            this.Controls.Add(this.addTestImageButton);
            this.Controls.Add(this.selectBasic);
            this.Controls.Add(this.addBasicImageButton);
            this.Controls.Add(this.pictureBox1);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle;
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.Margin = new System.Windows.Forms.Padding(2, 2, 2, 2);
            this.MaximizeBox = false;
            this.MaximumSize = new System.Drawing.Size(736, 430);
            this.MinimizeBox = false;
            this.MinimumSize = new System.Drawing.Size(636, 430);
            this.Name = "Form1";
            this.Text = "LabWork3";
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox2)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.PictureBox pictureBox1;
        private System.Windows.Forms.Button addBasicImageButton;
        private System.Windows.Forms.ComboBox selectBasic;
        private System.Windows.Forms.Button addTestImageButton;
        private System.Windows.Forms.ComboBox selectTest;
        private System.Windows.Forms.Button deleteCurrentButton;
        private System.Windows.Forms.Button findImage;
        private System.Windows.Forms.PictureBox pictureBox2;
        private System.Windows.Forms.TextBox textBox1;
        private System.Windows.Forms.Button clearButton;
    }
}

