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
        bool flag = false;

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
            if(isGameOver)
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
            "Invalid move - not your player",
            "Invalid move - destination is not free",
            "Invalid move - chess wil occure",
            "Invalid move - out of bounds",
            "Invalid move - illegeal movement with piece",
            "Invalid move - source and dest are equal",
            "Game over - check mate",
            "Valid move - pawn promotion",
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

                    string res = convertEngineToText(m);

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
    }
}
