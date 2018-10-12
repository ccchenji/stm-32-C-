using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace _505_lattice
{
	public partial class Form1 : Form
	{
		Form2 My_explain = new Form2();
		public Form1()
		{
			InitializeComponent();
		}
		string array="";
		int num = 0;
		private void Form1_Load(object sender, EventArgs e)
		{
			comboBox1.Text = "1";
			for (int i=1;i<=4;i++)
			{
				comboBox1.Items.Add(i.ToString());
			}
			for (byte i = 1; i <=32; i++)
			{
				for(byte j =1;j<=8;j++)
				{
					PictureBox p = new PictureBox();
					p.Name = i.ToString() + "," + j.ToString();
					p.Size = new System.Drawing.Size(10, 10);
					if(i<=8)
					{
					   p.Location = new Point(7 + (17 - i) * 12, 7 + (18 - j) * 12);
					}
					if(i>=9&&i<=16)
					{
				       p.Location = new Point(7 + (16 - i) * 12, 7 + (18 - j) * 12);
					}
					if(i>=17&&i<=24)
					{
					   p.Location = new Point(7 + (17 - (i-16)) * 12, 7 + (8 - j) * 12);
					}
					if(i>=25)
					{
					   p.Location = new Point(7 + (16 - (i-16)) * 12, 7 + (8 - j) * 12);
					}
					p.Click += F;
					p.BackColor = Color.Black;
					panel1.Controls.Add(p);
				}
			}
		}
		private void F(object sender, EventArgs e)
		{
			PictureBox p = sender as PictureBox;
			if (p.BackColor==Color.Black)
			{
				p.BackColor = Color.Red;
				num++;
			}
			else
			{
				p.BackColor = Color.Black;
				num--;
			}
		}

		private void label1_Click(object sender, EventArgs e)
		{

		}

		private void button1_Click(object sender, EventArgs e)
		{
			string str = textBox1.Text;
			string str1="";
			int count = 0;
			int all_num = 0;
			int add=0;
			int change=0;
			int flag = 0;
			int picture_num = 0;
			array = "";
			picture_num = 8 * Convert.ToInt32(comboBox1.Text);
			for (byte i = 1; i <= picture_num; i++)
			{
				change = 0;
				foreach (System.Windows.Forms.Control control in panel1.Controls)
				{
					if (control is System.Windows.Forms.PictureBox)
					{

						System.Windows.Forms.PictureBox tb = (System.Windows.Forms.PictureBox)control;
						if (tb.BackColor == Color.Red)
						{
							all_num = Convert.ToInt32(tb.Name.Substring(0, tb.Name.Length - 2));
							if (all_num==i)
							{
								add = Convert.ToInt32(tb.Name.Substring(tb.Name.Length - 1, 1));
								change= change | (0x01 << (add - 1));
							}
						}
					}
				}
			     array += "0x"+change.ToString("X2")+",";
			}
			if (array!="")
			{
				str1 = array.Substring(0, array.Length - 1);
			}
			if(str!="")
			{
                for(int i=0;i<str.Length;i++)
				{
					if((int)str[i]>127)
					{
						count++;
					}
				}
				if(count==0&&num>0)
				{
					textBox2.Clear();
					textBox2.AppendText("u8" + " " + str + "[" + picture_num.ToString() + "]" + "=" +
						"{" + str1 + "}" + ";");
				}
				else
				{
					MessageBox.Show("名字不能是中文字符,点的个数不能为零!!!", "警告!");
				}
			}
		}

		private void button2_Click(object sender, EventArgs e)
		{
			 textBox2.Clear();
			 textBox1.Clear();
			 num = 0;
			foreach (System.Windows.Forms.Control control in panel1.Controls)
			{
				if (control is System.Windows.Forms.PictureBox)
				{

					System.Windows.Forms.PictureBox tb = (System.Windows.Forms.PictureBox)control;

					tb.BackColor = Color.Black;
				}
			}
		}

		private void textBox3_TextChanged(object sender, EventArgs e)
		{

		}

		private void textBox2_TextChanged(object sender, EventArgs e)
		{

		}

		private void label3_Click(object sender, EventArgs e)
		{

		}

		private void pictureBox1_Click(object sender, EventArgs e)
		{

		}

		private void pictureBox1_MouseDoubleClick(object sender, MouseEventArgs e)
		{
			My_explain.ShowDialog();
		}

		private void timer1_Tick(object sender, EventArgs e)
		{
			label7.Text = num.ToString();
		}

		private void comboBox1_SelectedIndexChanged(object sender, EventArgs e)
		{

		}
	}
}
