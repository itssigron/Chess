using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Text.RegularExpressions;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Threading;
using System.Diagnostics;
using ChessGraphics;

namespace chessGraphics
{
    public partial class Form1 : Form
    {
        private Square srcSquare;
        private Square dstSquare;

        private pipe enginePipe;
        Button[,] matBoard;

        bool isCurPlWhite = true;
        bool isGameOver = false;

        const int BOARD_SIZE = 8;

        public Form1()
        {
            InitializeComponent();
            CenterToScreen();
        }

        private void InitForm()
        {
            enginePipe.connect();

            Invoke((MethodInvoker)delegate
            {

                lblWaiting.Visible = false;
                lblCurrentPlayer.Visible = true;
                label1.Visible = true;
                LoadMoves.Visible = true;
                LogHistory.Visible = true;
                UndoBtn.Visible = true;
                RedoBtn.Visible = true;



                string s = enginePipe.getEngineMessage();

                if (s.Length != (BOARD_SIZE * BOARD_SIZE + 1))
                {
                    MessageBox.Show("The length of the board's string is not according the PROTOCOL");
                    this.Close();

                }
                else
                {
                    isCurPlWhite = (s[s.Length - 1] == '0');
                    PaintBoard(s);
                    //CheckMateTest(400);
                    //TieTest(400);
                    //StalemateTest(400);
                }

            });

        }

        Thread connectionThread;
        private void Form1_Load(object sender, EventArgs e)
        {
            enginePipe = new pipe();
            //this.Show();

            //MessageBox.Show("Press OK to start waiting for engine to connect...");
            connectionThread = new Thread(InitForm);
            connectionThread.Start();
            connectionThread.IsBackground = true;

            //initForm();

        }

        Image GetImageBySign(char sign)
        {
            switch (sign)
            {
                case 'q':
                    return ChessGraphics.Properties.Resources.q_black;
                case 'Q':
                    return ChessGraphics.Properties.Resources.q_white;
                case 'k':
                    return ChessGraphics.Properties.Resources.k_black;
                case 'K':
                    return ChessGraphics.Properties.Resources.k_white;
                case 'p':
                    return ChessGraphics.Properties.Resources.p_black;
                case 'P':
                    return ChessGraphics.Properties.Resources.p_white;
                case 'r':
                    return ChessGraphics.Properties.Resources.r_black;
                case 'R':
                    return ChessGraphics.Properties.Resources.r_white;
                case 'n':
                    return ChessGraphics.Properties.Resources.n_black;
                case 'N':
                    return ChessGraphics.Properties.Resources.n_white;
                case 'b':
                    return ChessGraphics.Properties.Resources.b_black;
                case 'B':
                    return ChessGraphics.Properties.Resources.b_white;
                case '#':
                    return null;
                default:
                    return ChessGraphics.Properties.Resources.x;

            }
        }

        private void PaintBoard(string board)
        {
            int i, j, z = 0;

            matBoard = new Button[BOARD_SIZE, BOARD_SIZE];

            btnBoard.FlatAppearance.MouseOverBackColor = Color.LightGray;

            Button newBtn;
            Point pnt;

            int currentWidth = btnBoard.Location.X;
            int currentHeight = btnBoard.Location.Y;

            bool isColBlack = true;
            bool isRowBlack = true;

            this.SuspendLayout();

            lblCurrentPlayer.Text = isCurPlWhite ? "White" : "Black";

            for (i = 0; i < BOARD_SIZE; i++)
            {
                currentWidth = btnBoard.Location.X;
                isColBlack = isRowBlack;

                for (j = 0; j < BOARD_SIZE; j++)
                {
                    newBtn = new Button();
                    matBoard[i, j] = newBtn;

                    newBtn.FlatAppearance.MouseOverBackColor = btnBoard.FlatAppearance.MouseOverBackColor;
                    newBtn.BackColor = isColBlack ? Color.Gray : Color.White;
                    newBtn.FlatAppearance.BorderColor = btnBoard.FlatAppearance.BorderColor;
                    newBtn.FlatAppearance.BorderSize = btnBoard.FlatAppearance.BorderSize;
                    newBtn.FlatStyle = btnBoard.FlatStyle;

                    newBtn.Size = new Size(btnBoard.Width, btnBoard.Height);
                    newBtn.Tag = new Square(i, j);
                    pnt = new Point(currentWidth, currentHeight);
                    newBtn.Location = pnt;
                    newBtn.BackgroundImageLayout = ImageLayout.Stretch;

                    newBtn.BackgroundImage = GetImageBySign(board[z]);

                    newBtn.Click += Lastlbl_Click;

                    Controls.Add(newBtn);


                    currentWidth += btnBoard.Width;
                    isColBlack = !isColBlack;
                    z++;

                }

                isRowBlack = !isRowBlack;
                currentHeight += btnBoard.Height;

            }

            Controls.Remove(btnBoard);
            this.ResumeLayout(false);
        }

        string[] locationsArray;

        void Lastlbl_Click(object sender, EventArgs e)
        {
            Button b = (Button)sender;
            if (isGameOver)
            {
                return;
            }

            if (srcSquare != null)
            {
                // un-highlight all previously highlighted possible moves
                // last element is an empty string, therefore exclude it
                for (int i = 0; i < locationsArray.Length - 1; i++)
                {
                    string location = locationsArray[i];
                    int row = 8 - (location[1] - '0');
                    int col = location[0] - 'a';

                    // un-highlight (restore backColor and borderColor) each possible move's border
                    if ((row % 2 == 0 && col % 2 == 0) || (row % 2 == 1 && col % 2 == 1))
                    {
                        matBoard[row, col].BackColor = Color.Gray;
                    }
                    else
                    {
                        matBoard[row, col].BackColor = Color.White;
                    }
                    matBoard[row, col].FlatAppearance.BorderColor = Color.Blue;
                }
                // unselected
                if (matBoard[srcSquare.Row, srcSquare.Col] == b)
                {

                    matBoard[srcSquare.Row, srcSquare.Col].FlatAppearance.BorderColor = Color.Blue;
                    srcSquare = null;
                }
                else
                {
                    dstSquare = (Square)b.Tag;
                    matBoard[dstSquare.Row, dstSquare.Col].FlatAppearance.BorderColor = Color.DarkGreen;

                    Thread t = new Thread(() => PlayMove(false));
                    t.Start();
                    //   t.IsBackground = true;
                    //playMove();
                }
            }
            else
            {
                srcSquare = (Square)b.Tag;
                enginePipe.sendEngineMove(srcSquare.ToString());

                // all possible locations this piece can move to, example output: e5e6e7e8
                string possibleMoves = enginePipe.getEngineMessage();
                locationsArray = Regex.Split(possibleMoves, "(?<=\\G..)");

                // last element is an empty string, therefore exclude it
                for (int i = 0; i < locationsArray.Length - 1; i++)
                {
                    string location = locationsArray[i];
                    int row = 8 - (location[1] - '0');
                    int col = location[0] - 'a';

                    // highlight each possible move, and if its a captureable piece, color its border in red
                    matBoard[row, col].BackColor = Color.Chartreuse;
                    if (matBoard[row, col].BackgroundImage != null) matBoard[row, col].FlatAppearance.BorderColor = Color.Red;
                }

                matBoard[srcSquare.Row, srcSquare.Col].FlatAppearance.BorderColor = Color.DarkGreen;
            }

        }

        // messages should be according the protocol.
        // index is the message number in the protocol
        readonly string[] messages =  {
            "Valid move",
            "Valid move - you made chess",
            "Valid move - pawn promotion",
            "Invalid move - not your player",
            "Invalid move - destination is not free",
            "Invalid move - chess wil occure",
            "Invalid move - out of bounds",
            "Invalid move - illegeal movement with piece",
            "Invalid move - source and dest are equal",
            "Game over - Check mate ({0} won)",
            "Game over - Stale mate (Tie)",
            "Game over - Insufficient material (Tie)",
            "{0} pawn at {1} promoted to a {2}",
            "Unknown message"
            };


        string ConvertEngineToText(string m)
        {
            bool b = int.TryParse(m, out int res);

            if (!b || res < 0 || res >= messages.Length)
                return messages[messages.Length - 1];

            return messages[res];
        }

        void MakeMoves(string moves, int delay)
        {
            string[] movesArray = Regex.Split(moves, "(?<=\\G....)"); // last element will always be empty

            for (int i = 0; i < movesArray.Length - 1; i++)
            {
                string src = movesArray[i].Substring(0, 2);
                string dst = movesArray[i].Substring(2);
                int copy = i; // we must save a copy, otherwise it could run a thread with a different iteration of i
                new Thread(() => MakeMove(src, dst, (copy + 1) * delay)).Start();
            }
        }

        void MakeMove(string src, string dest, int sleepTime)
        {
            Thread.Sleep(sleepTime);
            Debug.WriteLine(src + dest + " | " + sleepTime);
            int srcRow = 8 - (src[1] - '0'), srcCol = src[0] - 'a';
            int destRow = 8 - (dest[1] - '0'), destCol = dest[0] - 'a';
            srcSquare = new Square(srcRow, srcCol);
            dstSquare = new Square(destRow, destCol);
            PlayMove();
        }

        void PlayMove(bool standalone = false, Image img = null) // if true, graphics will not contact engine for the move
        {
            if (isGameOver)
                return;


            try
            {
                Invoke((MethodInvoker)delegate
                {

                    lblEngineCalc.Visible = true;

                    lblMove.Text = string.Format("Move from {0} to {1}", srcSquare, dstSquare);
                    lblMove.Visible = true;
                    //lblEngineCalc.Invalidate();

                    label2.Visible = false;
                    lblResult.Visible = false;

                    this.Refresh();

                    if(srcSquare == null || dstSquare == null)
                    {
                        Thread.Sleep(200);
                    }
                    // should send pipe to engine
                    if(!standalone) enginePipe.sendEngineMove(srcSquare.ToString() + dstSquare.ToString());
                    string m = "Move restored";

                    // should get pipe from engine
                    if(!standalone) m = enginePipe.getEngineMessage();

                    if (!enginePipe.isConnected())
                    {
                        MessageBox.Show("Connection to engine has lost. Bye bye.");
                        this.Close();
                        return;
                    }

                    string res = m;
                    if (!standalone) res = String.Format(ConvertEngineToText(m), lblCurrentPlayer.Text);

                    if (res.ToLower().StartsWith("game over"))
                    {
                        isGameOver = true;
                        matBoard[dstSquare.Row, dstSquare.Col].BackgroundImage = matBoard[srcSquare.Row, srcSquare.Col].BackgroundImage;
                        matBoard[srcSquare.Row, srcSquare.Col].BackgroundImage = null;

                        matBoard[srcSquare.Row, srcSquare.Col].FlatAppearance.BorderColor = Color.Blue;
                        matBoard[dstSquare.Row, dstSquare.Col].FlatAppearance.BorderColor = Color.Blue;


                        // quit engine, close pipe and remove the load moves/undo/redo buttons,
                        // since its un-useable at that point + set the "log history" button to the same location
                        // as the now-deleted "load moves" button

                        LogHistory.Location = LoadMoves.Location;
                        this.Controls.Remove(LoadMoves);
                        this.Controls.Remove(UndoBtn);
                        this.Controls.Remove(RedoBtn);
                        enginePipe.sendEngineMove("quit");
                        enginePipe.close();
                    }
                    else if (res.ToLower().StartsWith("valid") || res.ToLower().Contains("restored"))
                    {
                        if (res.ToLower().Contains("promotion"))
                        {
                            string[] promptions =
                            {
                            "queen",
                            "rook",
                            "bishop",
                            "knight"
                            };

                            char type = ' ';
                            PawnPromotion prompt = new PawnPromotion();
                            string result = prompt.GetResult();

                            switch (result.ToLower())
                            {
                                case "queen":
                                    type = isCurPlWhite ? 'Q' : 'q';
                                    break;
                                case "rook":
                                    type = isCurPlWhite ? 'R' : 'r';
                                    break;
                                case "bishop":
                                    type = isCurPlWhite ? 'B' : 'b';
                                    break;
                                case "knight":
                                    type = isCurPlWhite ? 'N' : 'n';
                                    break;
                            }

                            matBoard[dstSquare.Row, dstSquare.Col].BackgroundImage = GetImageBySign(type);
                            enginePipe.sendEngineMove(dstSquare.ToString() + Char.ToLower(type));
                            m = enginePipe.getEngineMessage(); // get the confirmation message from engine
                            res = String.Format(ConvertEngineToText(m), lblCurrentPlayer.Text, dstSquare.ToString(), result);
                        }
                        else
                        {
                            matBoard[dstSquare.Row, dstSquare.Col].BackgroundImage = matBoard[srcSquare.Row, srcSquare.Col].BackgroundImage;
                        }

                        matBoard[srcSquare.Row, srcSquare.Col].BackgroundImage = img ?? null;

                        matBoard[srcSquare.Row, srcSquare.Col].FlatAppearance.BorderColor = Color.Blue;
                        matBoard[dstSquare.Row, dstSquare.Col].FlatAppearance.BorderColor = Color.Blue;

                        isCurPlWhite = !isCurPlWhite;
                        lblCurrentPlayer.Text = isCurPlWhite ? "White" : "Black";
                    }

                    lblEngineCalc.Visible = false;
                    lblResult.Text = string.Format("{0}", res);
                    lblResult.Visible = true;
                    label2.Visible = true;
                    this.Refresh();
                });


            }
            catch
            {

            }
            finally
            {
                Invoke((MethodInvoker)delegate
                {
                    if (srcSquare != null)
                        matBoard[srcSquare.Row, srcSquare.Col].FlatAppearance.BorderColor = Color.Blue;

                    if (dstSquare != null)
                        matBoard[dstSquare.Row, dstSquare.Col].FlatAppearance.BorderColor = Color.Blue;

                    dstSquare = null;
                    srcSquare = null;

                });
            }

        }

        private void Form1_FormClosed(object sender, FormClosedEventArgs e)
        {
            if (enginePipe.isConnected())
            {
                enginePipe.sendEngineMove("quit");
                enginePipe.close();
            }
        }

        private void CheckMateTest(int delay)
        {
            MakeMoves("h2h4g8h6h4h5h6g4h5h6g4f2e1f2b8c6b1c3c6e5c3e4e5g4e4g3g4e5g3h5e5c4h5f4c4e5f4d3e5g4d3e2d3e1g4h2f2b6h2g4b6a5g4f2"
                , delay);
        }

        private void TieTest(int delay)
        {
            MakeMoves("e2e4e7e5e1e3e8e6e3a7e6a2a7a8a2a1a8b8a1b1b8c8d8e7c8b7b1b2b7c7b2c2d1e1c2c1e1e2c1d2e2f3d2e1c7d7e7f6d7e8e1f1e8f8f1g1f8g8g1h1g8h8h1h2h8h7h2g2f3e3g2f2e3d3f2f4h7g7f6e6g7f7e6d6f7h5f4e4d3c3e4h4h5e5d6c6e5h5h4e4h5h4e4a4h4a4c6c5a4b5c5b5"
                , delay);
        }

        private void StalemateTest(int delay)
        {
            MakeMoves("e2e4a7a5e1e3a5a4e3a3b7b6a3a4b6b5a4b5a8a7b5b8a7a8b8a8c7c6a8c6c8b7c6b7d7d6b7e7d8c8e7d6e8d8d6d8c8b7d8f8b7c7f8g8h7h6g8h8g7g6h8h6c7c8h6g6f7f6g6f6c8b8f6d4b8a8d2d3a8b8c1f4f4b8a8b8b8a8f4e5a8b7d4d5b7c8h2h4"
                , delay);
        }
        private void LoadMoves_Click(object sender, EventArgs e)
        {
            LoadMoves prompt = new LoadMoves();
            LoadMovesResult result = prompt.GetResult();

            if(result.cancel != true) MakeMoves(result.moves, result.delay);
        }

        private void LogHistory_Click(object sender, EventArgs e)
        {
            enginePipe.sendEngineMove("print-history"); // ask engine to print game history
            string gameHistory = enginePipe.getEngineMessage(); // game history, currently unused but it is on the todo list

            MovesRestoreError.Visible = false;
            HistorySuccessLbl.Visible = true;

            // hide success message after 4 seconds
            System.Threading.Tasks.Task.Delay(4000).ContinueWith(_ =>
            {
                Invoke(new MethodInvoker(() => { HistorySuccessLbl.Visible = false; }));
            });
        }

        private void ShowRestoreError()
        {
            HistorySuccessLbl.Visible = false;
            MovesRestoreError.Visible = true;

            // hide success message after 4 seconds
            System.Threading.Tasks.Task.Delay(4000).ContinueWith(_ =>
            {
                Invoke(new MethodInvoker(() => { MovesRestoreError.Visible = false; }));
            });
        }
        private void Form1_KeyDown(object sender, KeyEventArgs e)
        {
            if (e.Modifiers == Keys.Control)
            {
                if(isGameOver)
                {
                    return;
                }

                if (e.KeyCode == Keys.Z) // undo
                {
                    enginePipe.sendEngineMove("undo");
                    string move = enginePipe.getEngineMessage();
                    if (move == "")
                    {
                        ShowRestoreError();
                        return;
                    }
                    string src = move.Substring(0, 2), dest = move.Substring(2, 2);
                    char identifier = move[move.Length - 1];
                    int srcRow = 8 - (src[1] - '0'), srcCol = src[0] - 'a';
                    int destRow = 8 - (dest[1] - '0'), destCol = dest[0] - 'a';
                    srcSquare = new Square(srcRow, srcCol);
                    dstSquare = new Square(destRow, destCol);
                    PlayMove(true, GetImageBySign(identifier)); // play move without contacting engine
                }
                else if (e.KeyCode == Keys.Y) // redo
                {
                    enginePipe.sendEngineMove("redo");
                    string move = enginePipe.getEngineMessage();
                    if (move == "")
                    {
                        ShowRestoreError();
                        return;
                    }
                    string src = move.Substring(0, 2), dest = move.Substring(2, 2);
                    int srcRow = 8 - (src[1] - '0'), srcCol = src[0] - 'a';
                    int destRow = 8 - (dest[1] - '0'), destCol = dest[0] - 'a';
                    srcSquare = new Square(srcRow, srcCol);
                    dstSquare = new Square(destRow, destCol);
                    PlayMove(true);
                }
            }
        }

        private void UndoBtn_Click(object sender, EventArgs e)
        {
            Form1_KeyDown(null, new KeyEventArgs(Keys.Control | Keys.Z)); // trigger ctrl + z
        }

        private void RedoBtn_Click(object sender, EventArgs e)
        {
            Form1_KeyDown(null, new KeyEventArgs(Keys.Control | Keys.Y)); // trigger ctrl + y
        }
    }
}
