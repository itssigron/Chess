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
    public partial class PawnPromotion : Form
    {
        public string result;
        readonly EventWaitHandle handle = new EventWaitHandle(false, EventResetMode.ManualReset);
        public PawnPromotion()
        {
            InitializeComponent();
            CenterToParent();
            ShowDialog();
        }
        public string GetResult()
        {
            handle.WaitOne();
            return result;
        }
        private void ListBox1_SelectedIndexChanged(object sender, EventArgs e)
        {
            result = listBox1.SelectedItem?.ToString();
        }

        private void Confirm_Click(object sender, EventArgs e)
        {
            if (result == "" || result == null)
            {
                errorLabel.Visible = true;
            }
            else
            {
                handle.Set();
                Close();
            }
        }

        private void UserPrompt_KeyDown(object sender, KeyEventArgs e)
        {
            if (e.KeyCode == Keys.Enter)
                confirm.PerformClick();
        }
    }
}
