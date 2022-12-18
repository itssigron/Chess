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
using Microsoft.VisualBasic;

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
        }

        private void initForm()
        {
            enginePipe.connect();

            Invoke((MethodInvoker)delegate
            {

                lblWaiting.Visible = false;
                lblCurrentPlayer.Visible = true;
                label1.Visible = true;



                string s = enginePipe.getEngineMessage();

                if (s.Length != (BOARD_SIZE * BOARD_SIZE + 1))
                {
                    MessageBox.Show("The length of the board's string is not according the PROTOCOL");
                    this.Close();

                }
                else
                {
                    isCurPlWhite = (s[s.Length - 1] == '0');
                    paintBoard(s);
                    //checkMateTest();
                    //tieTest();
                    //stalemateTest();
                }

            });

        }

        Thread connectionThread;
        private void Form1_Load(object sender, EventArgs e)
        {
            enginePipe = new pipe();
            //this.Show();

            //MessageBox.Show("Press OK to start waiting for engine to connect...");
            connectionThread = new Thread(initForm);
            connectionThread.Start();
            connectionThread.IsBackground = true;

            //initForm();

        }

        private void Btn_MouseEnter(object sender, EventArgs e)
        {
            Button btn = (Button)sender;
        }
        private void Btn_MouseLeaves(object sender, EventArgs e)
        {
            Button btn = (Button)sender;
        }


        Image getImageBySign(char sign)
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

        private void paintBoard(string board)
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
                    newBtn.MouseEnter += Btn_MouseEnter;
                    newBtn.MouseLeave += Btn_MouseLeaves;
                    newBtn.BackColor = isColBlack ? Color.Gray : Color.White;
                    newBtn.FlatAppearance.BorderColor = btnBoard.FlatAppearance.BorderColor;
                    newBtn.FlatAppearance.BorderSize = btnBoard.FlatAppearance.BorderSize;
                    newBtn.FlatStyle = btnBoard.FlatStyle;

                    newBtn.Size = new System.Drawing.Size(btnBoard.Width, btnBoard.Height);
                    newBtn.Tag = new Square(i, j);
                    pnt = new Point(currentWidth, currentHeight);
                    newBtn.Location = pnt;
                    newBtn.BackgroundImageLayout = ImageLayout.Stretch;

                    newBtn.BackgroundImage = getImageBySign(board[z]);

                    newBtn.Click += lastlbl_Click;

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

        void lastlbl_Click(object sender, EventArgs e)
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

                    Thread t = new Thread(playMove);
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
        string[] messages =  {
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
            "Unknown message"
            };


        string convertEngineToText(string m)
        {
            int res;
            bool b = int.TryParse(m, out res);

            if (!b || res < 0 || res >= messages.Length)
                return messages[messages.Length - 1];

            return messages[res];
        }


        void makeMove(string src, string dest, int sleepTime)
        {
            Thread.Sleep(sleepTime);
            int srcRow = 8 - (src[1] - '0'), srcCol = src[0] - 'a';
            int destRow = 8 - (dest[1] - '0'), destCol = dest[0] - 'a';
            srcSquare = new Square(srcRow, srcCol);
            dstSquare = new Square(destRow, destCol);
            playMove();
        }

        void playMove()
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


                    // should send pipe to engine
                    enginePipe.sendEngineMove(srcSquare.ToString() + dstSquare.ToString());


                    // should get pipe from engine
                    string m = enginePipe.getEngineMessage();

                    if (!enginePipe.isConnected())
                    {
                        MessageBox.Show("Connection to engine has lost. Bye bye.");
                        this.Close();
                        return;
                    }

                    string res = String.Format(convertEngineToText(m), isCurPlWhite ? "White" : "Black");

                    if (res.ToLower().StartsWith("game over"))
                    {
                        isGameOver = true;
                        matBoard[dstSquare.Row, dstSquare.Col].BackgroundImage = matBoard[srcSquare.Row, srcSquare.Col].BackgroundImage;
                        matBoard[srcSquare.Row, srcSquare.Col].BackgroundImage = null;

                        matBoard[srcSquare.Row, srcSquare.Col].FlatAppearance.BorderColor = Color.Blue;
                        matBoard[dstSquare.Row, dstSquare.Col].FlatAppearance.BorderColor = Color.Blue;

                        // quit engine and close pipe
                        enginePipe.sendEngineMove("quit");
                        enginePipe.close();
                    }
                    else if (res.ToLower().StartsWith("valid"))
                    {
                        if (m == "9")
                        {
                            string[] promptions =
                            {
                            "queen",
                            "rook",
                            "bishop",
                            "knight"
                            };

                            string input = "";
                            char type = ' ';

                            // ask user for which piece to promote their pawn until a valid input is provided
                            while (Array.IndexOf(promptions, input.ToLower()) == -1)
                            {
                                input = Interaction.InputBox("Please enter the new piece you wish to get promoted to: (queen/rook/bishop/knight)",
                                    "Pawn Promotion", "", this.ClientSize.Width / 2, this.ClientSize.Height / 2);
                            }

                            switch (input.ToLower())
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

                            matBoard[dstSquare.Row, dstSquare.Col].BackgroundImage = getImageBySign(type);
                            enginePipe.sendEngineMove(dstSquare.ToString() + Char.ToLower(type));
                            m = enginePipe.getEngineMessage(); // get the confirmation message from engine
                            res = convertEngineToText(m);
                        }
                        else
                        {
                            matBoard[dstSquare.Row, dstSquare.Col].BackgroundImage = matBoard[srcSquare.Row, srcSquare.Col].BackgroundImage;
                        }

                        matBoard[srcSquare.Row, srcSquare.Col].BackgroundImage = null;

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

        void checkMateTest()
        {
            Thread move;

            move = new Thread(() => makeMove("h2", "h4", 0));
            move.Start();
            move = new Thread(() => makeMove("g8", "h6", 500));
            move.Start();
            move = new Thread(() => makeMove("h4", "h5", 1000));
            move.Start();
            move = new Thread(() => makeMove("h6", "g4", 1500));
            move.Start();
            move = new Thread(() => makeMove("h5", "h6", 2000));
            move.Start();
            move = new Thread(() => makeMove("g4", "f2", 2500));
            move.Start();
            move = new Thread(() => makeMove("e1", "f2", 3000));
            move.Start();
            move = new Thread(() => makeMove("b8", "c6", 3500));
            move.Start();
            move = new Thread(() => makeMove("b1", "c3", 4000));
            move.Start();
            move = new Thread(() => makeMove("c6", "e5", 4500));
            move.Start();
            move = new Thread(() => makeMove("c3", "e4", 5000));
            move.Start();
            move = new Thread(() => makeMove("e5", "g4", 5500));
            move.Start();
            move = new Thread(() => makeMove("e4", "g3", 6000));
            move.Start();
            move = new Thread(() => makeMove("g4", "e5", 6500));
            move.Start();
            move = new Thread(() => makeMove("g3", "h5", 7000));
            move.Start();
            move = new Thread(() => makeMove("e5", "c4", 7500));
            move.Start();
            move = new Thread(() => makeMove("h5", "f4", 8000));
            move.Start();
            move = new Thread(() => makeMove("c4", "e5", 8500));
            move.Start();
            move = new Thread(() => makeMove("f4", "d3", 9000));
            move.Start();
            move = new Thread(() => makeMove("e5", "g4", 9500));
            move.Start();
            move = new Thread(() => makeMove("d3", "e2", 10000));
            move.Start();
            move = new Thread(() => makeMove("d3", "e1", 10500));
            move.Start();
            move = new Thread(() => makeMove("g4", "h2", 11000));
            move.Start();
            move = new Thread(() => makeMove("f2", "b6", 11500));
            move.Start();
            move = new Thread(() => makeMove("h2", "g4", 12000));
            move.Start();
            move = new Thread(() => makeMove("b6", "a5", 12500));
            move.Start();
            move = new Thread(() => makeMove("g4", "f2", 13000));
            move.Start();
        }

        void tieTest()
        {
            Thread move;

            move = new Thread(() => makeMove("e2", "e4", 0));
            move.Start();
            move = new Thread(() => makeMove("e7", "e5", 500));
            move.Start();
            move = new Thread(() => makeMove("e1", "e3", 1000));
            move.Start();
            move = new Thread(() => makeMove("e8", "e6", 1500));
            move.Start();
            move = new Thread(() => makeMove("e3", "a7", 2000));
            move.Start();
            move = new Thread(() => makeMove("e6", "a2", 2500));
            move.Start();
            move = new Thread(() => makeMove("a7", "a8", 3000));
            move.Start();
            move = new Thread(() => makeMove("a2", "a1", 3500));
            move.Start();
            move = new Thread(() => makeMove("a8", "b8", 4000));
            move.Start();
            move = new Thread(() => makeMove("a1", "b1", 4500));
            move.Start();
            move = new Thread(() => makeMove("b8", "c8", 5000));
            move.Start();
            move = new Thread(() => makeMove("d8", "e7", 5500));
            move.Start();
            move = new Thread(() => makeMove("c8", "b7", 6000));
            move.Start();
            move = new Thread(() => makeMove("b1", "b2", 6500));
            move.Start();
            move = new Thread(() => makeMove("b7", "c7", 7000));
            move.Start();
            move = new Thread(() => makeMove("b2", "c2", 7500));
            move.Start();
            move = new Thread(() => makeMove("d1", "e1", 8000));
            move.Start();
            move = new Thread(() => makeMove("c2", "c1", 8500));
            move.Start();
            move = new Thread(() => makeMove("e1", "e2", 9000));
            move.Start();
            move = new Thread(() => makeMove("c1", "d2", 9500));
            move.Start();
            move = new Thread(() => makeMove("e2", "f3", 10000));
            move.Start();
            move = new Thread(() => makeMove("d2", "e1", 10500));
            move.Start();
            move = new Thread(() => makeMove("c7", "d7", 11000));
            move.Start();
            move = new Thread(() => makeMove("e7", "f6", 11500));
            move.Start();
            move = new Thread(() => makeMove("d7", "e8", 12000));
            move.Start();
            move = new Thread(() => makeMove("e1", "f1", 12500));
            move.Start();
            move = new Thread(() => makeMove("e8", "f8", 13000));
            move.Start();
            move = new Thread(() => makeMove("f1", "g1", 13500));
            move.Start();
            move = new Thread(() => makeMove("f8", "g8", 14000));
            move.Start();
            move = new Thread(() => makeMove("g1", "h1", 14500));
            move.Start();
            move = new Thread(() => makeMove("g8", "h8", 15000));
            move.Start();
            move = new Thread(() => makeMove("h1", "h2", 15500));
            move.Start();
            move = new Thread(() => makeMove("h8", "h7", 16000));
            move.Start();
            move = new Thread(() => makeMove("h2", "g2", 16500));
            move.Start();
            move = new Thread(() => makeMove("f3", "e3", 17000));
            move.Start();
            move = new Thread(() => makeMove("g2", "f2", 17500));
            move.Start();
            move = new Thread(() => makeMove("e3", "d3", 18000));
            move.Start();
            move = new Thread(() => makeMove("f2", "f4", 18500));
            move.Start();
            move = new Thread(() => makeMove("h7", "g7", 19000));
            move.Start();
            move = new Thread(() => makeMove("f6", "e6", 19500));
            move.Start();
            move = new Thread(() => makeMove("g7", "f7", 20000));
            move.Start();
            move = new Thread(() => makeMove("e6", "d6", 20500));
            move.Start();
            move = new Thread(() => makeMove("f7", "h5", 21000));
            move.Start();
            move = new Thread(() => makeMove("f4", "e4", 21500));
            move.Start();
            move = new Thread(() => makeMove("d3", "c3", 22000));
            move.Start();
            move = new Thread(() => makeMove("e4", "h4", 22500));
            move.Start();
            move = new Thread(() => makeMove("h5", "e5", 23000));
            move.Start();
            move = new Thread(() => makeMove("d6", "c6", 23500));
            move.Start();
            move = new Thread(() => makeMove("e5", "h5", 24000));
            move.Start();
            move = new Thread(() => makeMove("h4", "e4", 24500));
            move.Start();
            move = new Thread(() => makeMove("h5", "h4", 25000));
            move.Start();
            move = new Thread(() => makeMove("e4", "a4", 25500));
            move.Start();
            move = new Thread(() => makeMove("h4", "a4", 26000));
            move.Start();
            move = new Thread(() => makeMove("c6", "c5", 26500));
            move.Start();
            move = new Thread(() => makeMove("a4", "b5", 27000));
            move.Start();
            move = new Thread(() => makeMove("c5", "b5", 27500));
            move.Start();
        }

        void stalemateTest()
        {
            Thread move;

            move = new Thread(() => makeMove("e2", "e4", 0));
            move.Start();
            move = new Thread(() => makeMove("a7", "a5", 500));
            move.Start();
            move = new Thread(() => makeMove("e1", "e3", 1000));
            move.Start();
            move = new Thread(() => makeMove("a5", "a4", 1500));
            move.Start();
            move = new Thread(() => makeMove("e3", "a3", 2000));
            move.Start();
            move = new Thread(() => makeMove("b7", "b6", 2500));
            move.Start();
            move = new Thread(() => makeMove("a3", "a4", 3000));
            move.Start();
            move = new Thread(() => makeMove("b6", "b5", 3500));
            move.Start();
            move = new Thread(() => makeMove("a4", "b5", 4000));
            move.Start();
            move = new Thread(() => makeMove("a8", "a7", 4500));
            move.Start();
            move = new Thread(() => makeMove("b5", "b8", 5000));
            move.Start();
            move = new Thread(() => makeMove("a7", "a8", 5500));
            move.Start();
            move = new Thread(() => makeMove("b8", "a8", 6000));
            move.Start();
            move = new Thread(() => makeMove("c7", "c6", 6500));
            move.Start();
            move = new Thread(() => makeMove("a8", "c6", 7000));
            move.Start();
            move = new Thread(() => makeMove("c8", "b7", 7500));
            move.Start();
            move = new Thread(() => makeMove("c6", "b7", 8000));
            move.Start();
            move = new Thread(() => makeMove("d7", "d6", 8500));
            move.Start();
            move = new Thread(() => makeMove("b7", "e7", 9000));
            move.Start();
            move = new Thread(() => makeMove("d8", "c8", 9500));
            move.Start();
            move = new Thread(() => makeMove("e7", "d6", 10000));
            move.Start();
            move = new Thread(() => makeMove("e8", "d8", 10500));
            move.Start();
            move = new Thread(() => makeMove("d6", "d8", 11000));
            move.Start();
            move = new Thread(() => makeMove("c8", "b7", 11500));
            move.Start();
            move = new Thread(() => makeMove("d8", "f8", 12000));
            move.Start();
            move = new Thread(() => makeMove("b7", "c7", 12500));
            move.Start();
            move = new Thread(() => makeMove("f8", "g8", 13000));
            move.Start();
            move = new Thread(() => makeMove("h7", "h6", 13500));
            move.Start();
            move = new Thread(() => makeMove("g8", "h8", 14000));
            move.Start();
            move = new Thread(() => makeMove("g7", "g6", 14500));
            move.Start();
            move = new Thread(() => makeMove("h8", "h6", 15000));
            move.Start();
            move = new Thread(() => makeMove("c7", "c8", 15500));
            move.Start();
            move = new Thread(() => makeMove("h6", "g6", 16000));
            move.Start();
            move = new Thread(() => makeMove("f7", "f6", 16500));
            move.Start();
            move = new Thread(() => makeMove("g6", "f6", 17000));
            move.Start();
            move = new Thread(() => makeMove("c8", "b8", 17500));
            move.Start();
            move = new Thread(() => makeMove("f6", "d4", 18000));
            move.Start();
            move = new Thread(() => makeMove("b8", "a8", 18500));
            move.Start();
            move = new Thread(() => makeMove("d2", "d3", 19000));
            move.Start();
            move = new Thread(() => makeMove("a8", "b8", 19500));
            move.Start();
            move = new Thread(() => makeMove("c1", "f4", 20000));
            move.Start();
            move = new Thread(() => makeMove("f4", "b8", 20500));
            move.Start();
            move = new Thread(() => makeMove("a8", "b8", 21000));
            move.Start();
            move = new Thread(() => makeMove("b8", "a8", 21500));
            move.Start();
            move = new Thread(() => makeMove("f4", "e5", 22000));
            move.Start();
            move = new Thread(() => makeMove("a8", "b7", 22500));
            move.Start();
            move = new Thread(() => makeMove("d4", "d5", 23000));
            move.Start();
            move = new Thread(() => makeMove("b7", "c8", 23500));
            move.Start();
            move = new Thread(() => makeMove("h2", "h4", 24000));
            move.Start();
        }
        
    }
}
