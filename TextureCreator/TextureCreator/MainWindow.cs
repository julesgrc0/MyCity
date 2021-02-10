using System;
using System.Collections.Generic;
using System.IO;
using System.Drawing;
using System.Windows.Forms;

namespace TextureCreator
{
    public partial class MainWindow : Form
    {
        private int rowCount = 10;
        private int columnCount = 10;
        private new List<Rgba> matrix = new List<Rgba>();
        private Color colorDefault;

        private struct Rgba
        {
            public int r;
            public int g;
            public int b;
            public int a;
        }

        public MainWindow()
        {
            InitializeComponent();
            this.SetupButtons();
            this.SetupMatrix();
        }

        private void SetupMatrix()
        {
            for (int i = 0; i < 100; i++)
            {
                Rgba it = new Rgba();
                it.a = 255;
                it.r = 0;
                it.g = 0;
                it.b = 0;

                matrix.Add(it);
            }
        }

        private void SetupButtons()
        {
            this.colorDefault = ColorTranslator.FromHtml("#000");
            this.tableLayoutPanel1.ColumnCount = columnCount;
            this.tableLayoutPanel1.RowCount = rowCount;

            this.tableLayoutPanel1.ColumnStyles.Clear();
            this.tableLayoutPanel1.RowStyles.Clear();

            for (int i = 0; i < columnCount; i++)
            {
                this.tableLayoutPanel1.ColumnStyles.Add(new ColumnStyle(SizeType.Percent, 100 / columnCount));
            }
            for (int i = 0; i < rowCount; i++)
            {
                this.tableLayoutPanel1.RowStyles.Add(new RowStyle(SizeType.Percent, 100 / rowCount));
            }

            for (int i = 0; i < rowCount; i++)
            {
                for (int j = 0; j < columnCount; j++)
                {
                    Button btn = new Button();
                    btn.Click += Btn_Click;
                    btn.KeyPress += Btn_KeyPress;
                    btn.Text = i.ToString() + j.ToString();

                    btn.ForeColor = ColorTranslator.FromHtml("#000");
                    btn.BackColor = ColorTranslator.FromHtml("#000");
                    btn.FlatAppearance.BorderColor = ColorTranslator.FromHtml("#000");
                    btn.TabStop = false;
                    btn.FlatStyle = FlatStyle.Flat;
                    btn.FlatAppearance.BorderSize = 0;
                    btn.Margin = new Padding(0,0,0,0);
                    btn.MouseEnter += Btn_MouseEnter; ;
                    btn.MouseLeave += Btn_MouseLeave;

                    btn.Name = string.Format("btn_{0}{1}", i, j);
                    btn.Dock = DockStyle.Fill;
                    this.tableLayoutPanel1.Controls.Add(btn, j, i);
                }
            }
        }

        private Color actualBtn;

        private void Btn_MouseLeave(object sender, EventArgs e)
        {
            Button btn = (Button)sender;
            btn.ForeColor = this.actualBtn;
            btn.BackColor = this.actualBtn;
            btn.FlatAppearance.BorderColor = this.actualBtn;
        }

        private void Btn_MouseEnter(object sender, EventArgs e)
        {
            Button btn = (Button)sender;
            this.actualBtn = btn.BackColor;
            int r = 255 - this.actualBtn.R;
            int g = 255 - this.actualBtn.G;
            int b = 255 - this.actualBtn.B;

            btn.ForeColor = Color.FromArgb(r, g, b, 255);
            btn.BackColor = Color.FromArgb(r, g, b, 255);
            btn.FlatAppearance.BorderColor = Color.FromArgb(r, g, b, 255);
        }

        private void Btn_KeyPress(object sender, KeyPressEventArgs e)
        {
            Button btn = (Button)sender;

            ColorDialog color = new ColorDialog();
            color.AllowFullOpen = true;
            color.AnyColor = true;

            if (color.ShowDialog() == DialogResult.OK)
            {
                int index = int.Parse(btn.Text);
                Rgba it = new Rgba();
                it.a = 255;
                it.r = color.Color.R;
                it.g = color.Color.G;
                it.b = color.Color.B;

                this.matrix[index] = it;

                btn.ForeColor = color.Color;
                btn.BackColor = color.Color;
                btn.FlatAppearance.BorderColor = color.Color;
                this.actualBtn = btn.BackColor;
            }
        }

        private void Btn_Click(object sender, EventArgs e)
        {
            Button btn = (Button)sender;

            int index = int.Parse(btn.Text);

            Rgba it = new Rgba();
            it.a = 255;
            it.r = this.colorDefault.R;
            it.g = this.colorDefault.G;
            it.b = this.colorDefault.B;

            this.matrix[index] = it;

            btn.ForeColor = this.colorDefault;
            btn.BackColor = this.colorDefault;
            btn.FlatAppearance.BorderColor = this.colorDefault;
            this.actualBtn = btn.BackColor;
        }

        private void SetDefaultColor(object sender, EventArgs e)
        {
            ColorDialog color = new ColorDialog();
            color.AllowFullOpen = true;
            color.AnyColor = true;

            if (color.ShowDialog() == DialogResult.OK)
            {
                this.colorDefault = color.Color;
            }
            this.Text = string.Format("TextureCreator - {0} {1} {2}",color.Color.R,color.Color.G,color.Color.B);
        }

        private void ExportTexture(object sender, EventArgs e)
        {
            string Result = "";
            foreach(Rgba c in this.matrix)
            {
                Result += string.Format("{0} {1} {2} {3}\n",c.r,c.g,c.b,c.a); 
            }

            SaveFileDialog save = new SaveFileDialog();

            save.Title = "Export Box Texture";
            save.FileName = "texture";
            save.DefaultExt = "box";
            save.InitialDirectory = "C:\\";
            save.Filter = "box files (*.box)|*.box";
            save.FilterIndex = 2;
            save.RestoreDirectory = true;

            if (save.ShowDialog() == DialogResult.OK)
            {
                File.WriteAllText(save.FileName, Result);
            }
        }

        private void Exit(object sender, EventArgs e)
        {
            this.Close();
        }
    }
}
