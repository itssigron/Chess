using System;
using System.Threading;
using System.Windows.Forms;

namespace ChessClient
{
    public partial class PawnPromotionPrompt : Form
    {
        public string result;
        readonly EventWaitHandle handle = new EventWaitHandle(false, EventResetMode.ManualReset);
        public PawnPromotionPrompt()
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
