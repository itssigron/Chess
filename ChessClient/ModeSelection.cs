using System;
using System.Threading;
using System.Windows.Forms;

namespace ChessClient
{
    public partial class ModeSelection : Form
    {
        public string result = "";
        readonly EventWaitHandle handle = new EventWaitHandle(false, EventResetMode.ManualReset);
        public ModeSelection()
        {
            InitializeComponent();
            CenterToScreen();
            ShowDialog();
        }

        public string GetResult()
        {
            handle.WaitOne();
            return result;
        }

        private void OnlineBtn_Click(object sender, EventArgs e)
        {
            result = ((Button)sender).Text;
            Close();
            handle.Set();
        }

        private void OfflineBtn_Click(object sender, EventArgs e)
        {
            result = ((Button)sender).Text;
            Close();
            handle.Set();
        }

        private void ModeSelection_FormClosed(object sender, FormClosedEventArgs e)
        {

            handle.Set();
        }
    }
}
