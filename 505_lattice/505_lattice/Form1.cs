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
			for (int i = 1; i <=32; i++)
			{
				for(int j=1;j<=8;j++)
				{
					PictureBox p = new PictureBox();
					p.Name = "{"+i.ToString() + "," + j.ToString()+"}"+",";
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
				array += p.Name;
			}
			else
			{
				p.BackColor = Color.Black;
				num--;
				array=array.Replace(p.Name,"");
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
			if(array!="")
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
					textBox2.AppendText("u8" + " " + str + "[" + num.ToString() + "]" + "[2]=" +
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
	}
}
