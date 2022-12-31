using System.Windows.Forms;

namespace ChessClient
{
    public partial class GameHistory : Form
    {
        public GameHistory(string history)
        {
            InitializeComponent();
            GameHistoryText.Text = history;
        }
    }
}
