using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Diagnostics;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace ChessGraphics
{
    public partial class UserPrompt : Form
    {
        public string selected;
        public UserPrompt()
        {
            TopMost = true;
            ControlBox = false;
            MaximizeBox = false;
            MinimizeBox = false;
            ControlBox = false;
            FormBorderStyle = FormBorderStyle.Fixed3D;
            InitializeComponent();
    }

    private void listBox1_SelectedIndexChanged(object sender, EventArgs e)
        {
            selected = listBox1.SelectedItem.ToString();
        }

        private void confirm_Click(object sender, EventArgs e)
        {
            Close();
        }

        private void UserPrompt_KeyDown(object sender, KeyEventArgs e)
        {
            Console.WriteLine(e.KeyCode);
            if (e.KeyCode == Keys.Enter)
                confirm.PerformClick();
        }
    }
}
