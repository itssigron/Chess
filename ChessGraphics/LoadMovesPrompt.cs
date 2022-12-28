using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Diagnostics;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Text.RegularExpressions;
using System.Threading;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace ChessGraphics
{
    public partial class LoadMovesPrompt : Form
    {
        readonly EventWaitHandle handle = new EventWaitHandle(false, EventResetMode.ManualReset);
        public LoadMovesResult result = new LoadMovesResult(null, 0);
        public LoadMovesPrompt()
        {
            InitializeComponent();
            CenterToParent();
            ShowDialog();
        }

        public LoadMovesResult GetResult()
        {
            handle.WaitOne();
            return result;
        }

        private void Confirm_Click(object sender, EventArgs e)
        {
            result.moves = MovesInput.Text;
            result.delay = (int)DelayInput.Value;

            if (result == null || result.moves == null || result.moves == "")
            {
                errorLabel.Visible = true;
            }
            else if (!IsValidMoves(result.moves))
            {
                movesErrorLabel.Visible = true;
            }
            else
            {
                handle.Set();
                Close();
            }
        }

        private void LoadMoves_KeyDown(object sender, KeyEventArgs e)
        {
            if (e.KeyCode == Keys.Enter)
                confirm.PerformClick();
        }

        void LoadMoves_FormClosing(object sender, FormClosingEventArgs e)
        {
            if (e.CloseReason == CloseReason.WindowsShutDown) return;
            result.cancel = !(new StackTrace().GetFrames().Any(x => x.GetMethod().Name == "Close"));
            handle.Set();
        }

        public static bool IsValidMoves(string moves)
        {
            bool isValid = true;
            string[] movesArray = Regex.Split(moves, "(?<=\\G....)");
            string src, dst;

            if (moves.Length < 4)
            {
                isValid = false;
            }
            else
            {
                for (int i = 0; i < movesArray.Length; i++)
                {
                    if (movesArray[i].Length == 0)
                    {
                        continue;
                    }
                    else if (movesArray[i].Length < 4)
                    {
                        isValid = false;
                    }
                    else
                    {
                        src = movesArray[i].Substring(0, 2);
                        dst = movesArray[i].Substring(2);

                        if (!(src.Length == 2 && dst.Length == 2) ||
                            !(src[0] >= 'a' && src[0] <= 'h') || !(dst[0] >= 'a' && dst[0] <= 'h') ||
                            !(src[1] >= '1' && src[1] <= '8') || !(dst[1] >= '1' && dst[1] <= '8'))
                        {
                            isValid = false;
                        }
                    }
                }
            }

            return isValid;
        }
    }
    public class LoadMovesResult
    {
        public string moves;
        public int delay;
        public bool cancel = false;

        public LoadMovesResult(string moves, int delay)
        {
            this.moves = moves;
            this.delay = delay;
        }
    }
}
