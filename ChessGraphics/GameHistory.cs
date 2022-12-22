using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace ChessGraphics
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
