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
using System.Drawing.Imaging;
using System.IO;

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
        int DesignVersion = 1;

        const int BOARD_SIZE = 8;
        Color YELLOW_SQUARE = Color.FromArgb(238, 238, 210);
        Color GREEN_SQUARE = Color.FromArgb(118, 150, 86);
        string gameHistory = "";

        public Form1()
        {
            InitializeComponent();
            CenterToScreen();
            label25.SendToBack();
            lblWaiting.BringToFront();
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
                DesignVerBtn.Visible = true;



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
                    //Tests tests = new Tests(this);
                    //tests.CheckMate(400);
                    //tests.Tie(400);
                    //tests.Stalemate(400);
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
        private byte[] ToByteArray(Image image)
        {
            using (MemoryStream stream = new MemoryStream())
            {
                ((Bitmap)image).Save(stream, ImageFormat.Png);
                return stream.ToArray();
            }
        }

        char GetSignByImageV1(Image image)
        {
            if (image != null)
            {
                // Convert the image to a byte array
                byte[] imageData;
                using (MemoryStream stream = new MemoryStream())
                {
                    image.Save(stream, ImageFormat.Png);
                    imageData = stream.ToArray();
                }

                if (Enumerable.SequenceEqual(imageData, ToByteArray(ChessGraphics.Properties.Resources.q_black)))
                {
                    return 'q';
                }
                else if (Enumerable.SequenceEqual(imageData, ToByteArray(ChessGraphics.Properties.Resources.q_white)))
                {
                    return 'Q';
                }
                else if (Enumerable.SequenceEqual(imageData, ToByteArray(ChessGraphics.Properties.Resources.k_black)))
                {
                    return 'k';
                }
                else if (Enumerable.SequenceEqual(imageData, ToByteArray(ChessGraphics.Properties.Resources.k_white)))
                {
                    return 'K';
                }
                else if (Enumerable.SequenceEqual(imageData, ToByteArray(ChessGraphics.Properties.Resources.p_black)))
                {
                    return 'p';
                }
                else if (Enumerable.SequenceEqual(imageData, ToByteArray(ChessGraphics.Properties.Resources.p_white)))
                {
                    return 'P';
                }
                else if (Enumerable.SequenceEqual(imageData, ToByteArray(ChessGraphics.Properties.Resources.r_black)))
                {
                    return 'r';
                }
                else if (Enumerable.SequenceEqual(imageData, ToByteArray(ChessGraphics.Properties.Resources.r_white)))
                {
                    return 'R';
                }
                else if (Enumerable.SequenceEqual(imageData, ToByteArray(ChessGraphics.Properties.Resources.n_black)))
                {
                    return 'n';
                }
                else if (Enumerable.SequenceEqual(imageData, ToByteArray(ChessGraphics.Properties.Resources.n_white)))
                {
                    return 'N';
                }
                else if (Enumerable.SequenceEqual(imageData, ToByteArray(ChessGraphics.Properties.Resources.b_black)))
                {
                    return 'b';
                }
                else if (Enumerable.SequenceEqual(imageData, ToByteArray(ChessGraphics.Properties.Resources.b_white)))
                {
                    return 'B';
                }
                else
                {
                    return 'x';
                }
            }
            else
            {
                return '#';
            }
        }

        char GetSignByImageV2(Image image)
        {
            if (image != null)
            {
                // Convert the image to a byte array
                byte[] imageData;
                using (MemoryStream stream = new MemoryStream())
                {
                    image.Save(stream, ImageFormat.Png);
                    imageData = stream.ToArray();
                }

                if (Enumerable.SequenceEqual(imageData, ToByteArray(ChessGraphics.Properties.Resources.black_queen)))
                {
                    return 'q';
                }
                else if (Enumerable.SequenceEqual(imageData, ToByteArray(ChessGraphics.Properties.Resources.white_queen)))
                {
                    return 'Q';
                }
                else if (Enumerable.SequenceEqual(imageData, ToByteArray(ChessGraphics.Properties.Resources.black_king)))
                {
                    return 'k';
                }
                else if (Enumerable.SequenceEqual(imageData, ToByteArray(ChessGraphics.Properties.Resources.white_king)))
                {
                    return 'K';
                }
                else if (Enumerable.SequenceEqual(imageData, ToByteArray(ChessGraphics.Properties.Resources.black_pawn)))
                {
                    return 'p';
                }
                else if (Enumerable.SequenceEqual(imageData, ToByteArray(ChessGraphics.Properties.Resources.white_pawn)))
                {
                    return 'P';
                }
                else if (Enumerable.SequenceEqual(imageData, ToByteArray(ChessGraphics.Properties.Resources.black_rook)))
                {
                    return 'r';
                }
                else if (Enumerable.SequenceEqual(imageData, ToByteArray(ChessGraphics.Properties.Resources.white_rook)))
                {
                    return 'R';
                }
                else if (Enumerable.SequenceEqual(imageData, ToByteArray(ChessGraphics.Properties.Resources.black_knight)))
                {
                    return 'n';
                }
                else if (Enumerable.SequenceEqual(imageData, ToByteArray(ChessGraphics.Properties.Resources.white_knight)))
                {
                    return 'N';
                }
                else if (Enumerable.SequenceEqual(imageData, ToByteArray(ChessGraphics.Properties.Resources.black_bishop)))
                {
                    return 'b';
                }
                else if (Enumerable.SequenceEqual(imageData, ToByteArray(ChessGraphics.Properties.Resources.white_bishop)))
                {
                    return 'B';
                }
                else
                {
                    return 'x';
                }
            }
            else
            {
                return '#';
            }
        }

        char GetSignByImage(Image image)
        {
            if (DesignVersion == 2)
            {
                return GetSignByImageV1(image);
            }
            else
            {
                return GetSignByImageV2(image);
            }
        }
        Image GetImageBySignV1(char sign)
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

        Image GetImageBySignV2(char sign)
        {
            switch (sign)
            {
                case 'q':
                    return ChessGraphics.Properties.Resources.black_queen;
                case 'Q':
                    return ChessGraphics.Properties.Resources.white_queen;
                case 'k':
                    return ChessGraphics.Properties.Resources.black_king;
                case 'K':
                    return ChessGraphics.Properties.Resources.white_king;
                case 'p':
                    return ChessGraphics.Properties.Resources.black_pawn;
                case 'P':
                    return ChessGraphics.Properties.Resources.white_pawn;
                case 'r':
                    return ChessGraphics.Properties.Resources.black_rook;
                case 'R':
                    return ChessGraphics.Properties.Resources.white_rook;
                case 'n':
                    return ChessGraphics.Properties.Resources.black_knight;
                case 'N':
                    return ChessGraphics.Properties.Resources.white_knight;
                case 'b':
                    return ChessGraphics.Properties.Resources.black_bishop;
                case 'B':
                    return ChessGraphics.Properties.Resources.white_bishop;
                case '#':
                    return null;
                default:
                    return ChessGraphics.Properties.Resources.x;

            }
        }

        Image GetImageBySign(char sign)
        {
            if(DesignVersion == 1)
            {
                return GetImageBySignV1(sign);
            }
            else
            {
                return GetImageBySignV2(sign);
            }
        }

        Color GetWhiteColor()
        {
            return DesignVersion == 1 ? Color.White : YELLOW_SQUARE; 
        }

        Color GetGrayColor()
        {
            return DesignVersion == 1 ? Color.Gray : GREEN_SQUARE;
        }

        Color GetDefaultBorderColor()
        {
            return DesignVersion == 1 ? Color.Blue : Color.Black;
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
                    newBtn.BackColor = isColBlack ? GetWhiteColor() : GetGrayColor();
                    newBtn.FlatAppearance.BorderColor = GetDefaultBorderColor();
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
                        matBoard[row, col].BackColor = GetWhiteColor();
                    }
                    else
                    {
                        matBoard[row, col].BackColor = GetGrayColor();
                    }
                    matBoard[row, col].FlatAppearance.BorderColor = GetDefaultBorderColor();
                }
                // unselected
                if (matBoard[srcSquare.Row, srcSquare.Col] == b)
                {

                    matBoard[srcSquare.Row, srcSquare.Col].FlatAppearance.BorderColor = GetDefaultBorderColor();
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
                    matBoard[row, col].BackColor = Color.DarkOrange;
                    if (matBoard[row, col].BackgroundImage != null)
                    {
                        matBoard[row, col].BackColor = Color.Red;
                        matBoard[row, col].FlatAppearance.BorderColor = Color.DarkOrange;
                    }
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
            "Valid move - en passant capture",
            "Valid move - king has castled",
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

        public void MakeMoves(string moves, int delay)
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

        // if standalone=true, graphics will perform the move only on the form and will not contact engine
        void PlayMove(bool standalone = false, Image img = null, bool isEnPassant = false)
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

                    if (srcSquare == null || dstSquare == null)
                    {
                        Thread.Sleep(200);
                    }
                    // should send pipe to engine
                    if (!standalone) enginePipe.sendEngineMove(srcSquare.ToString() + dstSquare.ToString());
                    string m = "Move restored";

                    // should get pipe from engine
                    if (!standalone) m = enginePipe.getEngineMessage();

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

                        matBoard[srcSquare.Row, srcSquare.Col].FlatAppearance.BorderColor = GetDefaultBorderColor();
                        matBoard[dstSquare.Row, dstSquare.Col].FlatAppearance.BorderColor = GetDefaultBorderColor();


                        // quit engine, close pipe and remove the load moves/undo/redo buttons,
                        // since its un-useable at that point + set the "log history" button to the same location
                        // as the now-deleted "load moves" button

                        LogHistory.Location = LoadMoves.Location;
                        this.Controls.Remove(LoadMoves);
                        this.Controls.Remove(UndoBtn);
                        this.Controls.Remove(RedoBtn);
                        enginePipe.sendEngineMove("quit");
                        gameHistory = enginePipe.getEngineMessage(); // get end-game history from engine
                        enginePipe.close();
                    }
                    else if (res.ToLower().StartsWith("valid") || res.ToLower().Contains("restored"))
                    {
                        if(res.ToLower().Contains("castle"))
                        {
                            matBoard[dstSquare.Row, dstSquare.Col].BackgroundImage = matBoard[srcSquare.Row, srcSquare.Col].BackgroundImage;
                            int row = dstSquare.Row;
                            int srcCol = dstSquare.Col == 6 ? 7 : 0;
                            int dstCol = srcCol == 7 ? 5 : 3;
                            matBoard[row, dstCol].BackgroundImage = matBoard[row, srcCol].BackgroundImage;
                            matBoard[row, srcCol].BackgroundImage = null;
                        }
                        else if (res.ToLower().Contains("promotion"))
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
                        else if (res.ToLower().Contains("en passant"))
                        {
                            int rowOffset = isCurPlWhite ? 1 : -1;
                            matBoard[dstSquare.Row + rowOffset, dstSquare.Col].BackgroundImage = null;
                            matBoard[dstSquare.Row, dstSquare.Col].BackgroundImage = matBoard[srcSquare.Row, srcSquare.Col].BackgroundImage;
                        }
                        else if (isEnPassant)
                        {
                            int rowOffset = isCurPlWhite ? -1 : 1;
                            matBoard[srcSquare.Row + rowOffset, srcSquare.Col].BackgroundImage = img;
                            matBoard[dstSquare.Row, dstSquare.Col].BackgroundImage = matBoard[srcSquare.Row, srcSquare.Col].BackgroundImage;
                            matBoard[srcSquare.Row, srcSquare.Col].BackgroundImage = null;
                        }
                        else
                        {
                            matBoard[dstSquare.Row, dstSquare.Col].BackgroundImage = matBoard[srcSquare.Row, srcSquare.Col].BackgroundImage;
                        }

                        // only possible case for this conditon is a "redo"
                        if (standalone && !isEnPassant)
                        {
                            int rowOffset = isCurPlWhite ? 1 : -1;
                            matBoard[dstSquare.Row + rowOffset, dstSquare.Col].BackgroundImage = null;
                            matBoard[dstSquare.Row, dstSquare.Col].BackgroundImage = matBoard[srcSquare.Row, srcSquare.Col].BackgroundImage;
                        }

                        if (!isEnPassant) matBoard[srcSquare.Row, srcSquare.Col].BackgroundImage = img ?? null;

                        matBoard[srcSquare.Row, srcSquare.Col].FlatAppearance.BorderColor = GetDefaultBorderColor();
                        matBoard[dstSquare.Row, dstSquare.Col].FlatAppearance.BorderColor = GetDefaultBorderColor();

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
                        matBoard[srcSquare.Row, srcSquare.Col].FlatAppearance.BorderColor = GetDefaultBorderColor();

                    if (dstSquare != null)
                        matBoard[dstSquare.Row, dstSquare.Col].FlatAppearance.BorderColor = GetDefaultBorderColor();

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

            if (result.cancel != true) MakeMoves(result.moves, result.delay);
        }

        private void LogHistory_Click(object sender, EventArgs e)
        {
            enginePipe.sendEngineMove("history"); // ask engine to give game's history
            gameHistory = gameHistory != "" ? gameHistory : enginePipe.getEngineMessage();

            GameHistory historyDiaglog = new GameHistory(gameHistory);
            historyDiaglog.ShowDialog();
            if(!isGameOver) gameHistory = "";
        }

        private void ShowRestoreError()
        {
            MovesRestoreError.Visible = true;

            // hide success message after 4 seconds
            Task.Delay(4000).ContinueWith(_ =>
            {
                Invoke(new MethodInvoker(() => { MovesRestoreError.Visible = false; }));
            });
        }
        private void Form1_KeyDown(object sender, KeyEventArgs e)
        {
            if (e.Modifiers == Keys.Control)
            {
                if (isGameOver)
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
                    char identifier = move[4];
                    bool isEnPassant = move[move.Length - 1] == '1';
                    int srcRow = 8 - (src[1] - '0'), srcCol = src[0] - 'a';
                    int destRow = 8 - (dest[1] - '0'), destCol = dest[0] - 'a';
                    srcSquare = new Square(srcRow, srcCol);
                    dstSquare = new Square(destRow, destCol);
                    PlayMove(true, GetImageBySign(identifier), isEnPassant); // play move without contacting engine
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

        private void DesignVerBtn_Click(object sender, EventArgs e)
        {
            DesignVersion = 2 - ((DesignVersion + 1) % 2);
            DesignVerBtn.Text = DesignVerBtn.Text.Substring(0, DesignVerBtn.Text.Length - 1);
            DesignVerBtn.Text += (char)(DesignVersion + '0');

            int i, j;

            Button btn;
            bool isRowBlack = true;

            this.SuspendLayout();

            for (i = 0; i < BOARD_SIZE; i++)
            {
                bool isColBlack = isRowBlack;

                for (j = 0; j < BOARD_SIZE; j++)
                {
                    btn = matBoard[i, j];

                    btn.BackColor = isColBlack ? GetWhiteColor() : GetGrayColor();
                    btn.FlatAppearance.BorderColor = GetDefaultBorderColor();

                    btn.BackgroundImage = GetImageBySign(GetSignByImage(btn.BackgroundImage));

                    isColBlack = !isColBlack;
                }
                isRowBlack = !isRowBlack;
            }

            if(srcSquare != null)
            {
                i = srcSquare.Row;
                j = srcSquare.Col;
                srcSquare = null;
                matBoard[i, j].PerformClick();
            }

            this.ResumeLayout();
        }
    }
}
