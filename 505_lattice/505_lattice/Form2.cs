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
	public partial class Form2 : Form
	{
		public Form2()
		{
			InitializeComponent();
		}

		private void Form2_Load(object sender, EventArgs e)
		{
			label2.Text = "1:未输入图案名则无法生成对应数组。";
			label3.Text = "2:图案名不能以中文命名。";
			label1.Text = "3:如果只生成一张图片则使用图案一,其他的生成的图案无法显示。";
			label4.Text = "4:如果要生成滚动的图案则可使用其他的图案。";
			label5.Text = "By 陈济轩";
		}
	}
}
