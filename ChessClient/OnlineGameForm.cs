using System;
using System.Collections.Generic;
using System.Drawing;
using System.Text.RegularExpressions;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Threading;
using ChessClient;
using System.IO;
using static ChessClient.Properties.Resources;
using System.Reflection;
using Label = System.Windows.Forms.Label;

namespace chessClient
{
    public partial class OnlineGameForm : Form
    {
        private Square srcSquare;
        private Square dstSquare;

        private OnlinePipe enginePipe;
        Button[,] matBoard;

        bool isOwnerWhite = true;
        bool isCurPlWhite = true;
        bool isGameOver = false;
        int DesignVersion = 1;

        const int BOARD_SIZE = 8;
        Color YELLOW_SQUARE = Color.FromArgb(255, 206, 158);
        //Color YELLOW_SQUARE_V2 = Color.FromArgb(238, 238, 210);
        Color ORANGE_SQUARE = Color.FromArgb(209, 139, 71);
        Color GREEN_SQUARE = Color.FromArgb(118, 150, 86);
        string gameHistory = "";
        List<string> promotionsIn = new List<string>(); // list to hold cached promotions of loaded games
        List<string> promotionsOut = new List<string>(); // list to hold promotions to be saved in saved files

        public OnlineGameForm()
        {
            InitializeComponent();
            CenterToScreen();
            label25.SendToBack();
            lblWaiting.BringToFront();
        }

        void ActionOnButtons(string prop, bool val)
        {
            Button[] buttons = new Button[3] { DesignVerBtn, SaveGameBtn, LogHistory };
            foreach (Button button in buttons)
            {
                Type type = button.GetType();
                PropertyInfo property = type.GetProperty(prop);
                property.SetValue(button, val);
            }
        }
        private void InitForm()
        {
            enginePipe.connect();

            Invoke((MethodInvoker)delegate
            {

                lblWaiting.Visible = false;
                lblCurrentPlayer.Visible = true;
                label1.Visible = true;

                ActionOnButtons("Visible", true);


                string s = enginePipe.getEngineMessage();

                // extra 1 character for the player whom this client belongs to,
                if (s.Length != (BOARD_SIZE * BOARD_SIZE + 1))
                {
                    MessageBox.Show("The length of the board's string is not according the PROTOCOL");
                    this.Close();

                }
                else
                {
                    isOwnerWhite = s[BOARD_SIZE * BOARD_SIZE] == '0';
                    PlayerColorLbl.Text = String.Format(PlayerColorLbl.Text, isOwnerWhite ? "White" : "Black");
                    PaintBoard(s);
                    if (!isOwnerWhite)
                    {
                        new Thread(UpdateBoard).Start();
                    }
                }

            });

        }

        Thread connectionThread;
        private void Form1_Load(object sender, EventArgs e)
        {
            enginePipe = new OnlinePipe();
            //this.Show();

            //MessageBox.Show("Press OK to start waiting for engine to connect...");
            connectionThread = new Thread(InitForm);
            connectionThread.Start();
            connectionThread.IsBackground = true;

            //initForm();
        }

        Image GetImageBySign(char sign, int version)
        {
            Image res = null;
            var images = new Dictionary<char, Image[]>()
            {
                { 'q', new Image[2]{ black_queen_v1, black_queen_v2 } },
                { 'Q', new Image[2]{ white_queen_v1, white_queen_v2 } },
                { 'k', new Image[2]{ black_king_v1, black_king_v2 } },
                { 'K', new Image[2]{ white_king_v1, white_king_v2 } },
                { 'p', new Image[2]{ black_pawn_v1, black_pawn_v2 } },
                { 'P', new Image[2]{ white_pawn_v1, white_pawn_v2 } },
                { 'r', new Image[2]{ black_rook_v1, black_rook_v2 } },
                { 'R', new Image[2]{ white_rook_v1 , white_rook_v2 } },
                { 'n', new Image[2]{ black_knight_v1, black_knight_v2 } },
                { 'N', new Image[2]{ white_knight_v1, white_knight_v2 } },
                { 'b', new Image[2]{ black_bishop_v1, black_bishop_v2 } },
                { 'B', new Image[2]{ white_bishop_v1, white_bishop_v2 } }
            };


            if (images.ContainsKey(sign))
            {
                res = images[sign][version - 1];
                res.Tag = sign;
            }

            return res;
        }

        public Color ChangeOpacity(Color color, double opacity)
        {
            // Clamp the opacity value between 0 and 1
            opacity = Math.Max(0, Math.Min(opacity, 1));

            // Convert the opacity value to a byte (0-255)
            byte alpha = (byte)(opacity * 255);

            // Return a new color with the same RGB values as the original color, and the new alpha value
            return Color.FromArgb(alpha, color.R, color.G, color.B);
        }

        Color GetWhiteColor()
        {
            return YELLOW_SQUARE;
        }

        Color GetGrayColor()
        {
            return DesignVersion == 1 ? ORANGE_SQUARE : GREEN_SQUARE;
        }

        Color GetDefaultBorderColor()
        {
            return DesignVersion == 1 ? Color.Black : Color.Black;
        }

        Color GetDefaultValidMoveBorderColor()
        {
            return DesignVersion == 1 ? GREEN_SQUARE : ORANGE_SQUARE;
        }

        Color GetDefaultValidCaptureBorderColor()
        {
            return DesignVersion == 1 ? Color.Red : Color.Red;
        }

        Color GetSquareBackColor(int row, int col)
        {
            if ((row % 2 == 0 && col % 2 == 0) || (row % 2 == 1 && col % 2 == 1))
            {
                return GetWhiteColor();
            }
            else
            {
                return GetGrayColor();
            }
        }

        Color GetSelectedBorderColor()
        {
            return Color.Red;
        }

        void CleanBoard()
        {
            for (int i = 0; i < BOARD_SIZE; i++)
            {
                for (int j = 0; j < BOARD_SIZE; j++)
                {
                    matBoard[i, j].BackColor = GetSquareBackColor(i, j);
                    matBoard[i, j].FlatAppearance.BorderColor = GetDefaultBorderColor();
                }
            }
        }

        // Store the original color of the button
        private Color originalColor;
        private bool shouldRestore = false;

        private void btnBoard_MouseEnter(object sender, EventArgs e)
        {
            // Store the original color of the button
            Button btn = (Button)sender;
            originalColor = btn.BackColor;
            shouldRestore = false;

            // Change the color of the button to half of its opacity
            btn.BackColor = ChangeOpacity(originalColor, 0.5);
        }

        private void btnBoard_MouseLeave(object sender, EventArgs e)
        {
            Button btn = (Button)sender;

            // Return the button to its original color
            if (shouldRestore == true) originalColor = GetSquareBackColor(((Square)btn.Tag).Row, ((Square)btn.Tag).Col);
            btn.BackColor = originalColor;
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

                    //newBtn.FlatAppearance.MouseOverBackColor = btnBoard.FlatAppearance.MouseOverBackColor;
                    newBtn.MouseEnter += btnBoard_MouseEnter;
                    newBtn.MouseLeave += btnBoard_MouseLeave;

                    newBtn.BackColor = isColBlack ? GetWhiteColor() : GetGrayColor();
                    newBtn.FlatAppearance.BorderColor = GetDefaultBorderColor();
                    newBtn.FlatAppearance.BorderSize = btnBoard.FlatAppearance.BorderSize;
                    newBtn.FlatStyle = btnBoard.FlatStyle;

                    newBtn.Size = new Size(btnBoard.Width, btnBoard.Height);
                    newBtn.Tag = new Square(i, j);
                    pnt = new Point(currentWidth, currentHeight);
                    newBtn.Location = pnt;
                    newBtn.BackgroundImageLayout = ImageLayout.Stretch;

                    newBtn.BackgroundImage = GetImageBySign(board[z], DesignVersion);

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

        private void PaintSquares(string board)
        {
            for (int i = 0; i < BOARD_SIZE; i++)
            {
                for (int j = 0; j < BOARD_SIZE; j++)
                {
                    matBoard[i, j].BackgroundImage = GetImageBySign(board[i * BOARD_SIZE + j], DesignVersion);
                }
            }
            PaintSquares();
        }

        private void PaintSquares()
        {
            Button btn;

            for (int i = 0; i < BOARD_SIZE; i++)
            {
                for (int j = 0; j < BOARD_SIZE; j++)
                {
                    btn = matBoard[i, j];

                    btn.BackColor = GetSquareBackColor(i, j);
                    btn.FlatAppearance.BorderColor = GetDefaultBorderColor();

                    btn.BackgroundImage = GetImageBySign((char)(btn.BackgroundImage?.Tag ?? '#'), DesignVersion);

                }
            }
        }
        string[] locationsArray;

        void UpdateBoard()
        {

            string newBoard = enginePipe.getEngineMessage();

            isCurPlWhite = newBoard[BOARD_SIZE * BOARD_SIZE] == '0';
            Invoke((MethodInvoker)delegate
            {
                lblCurrentPlayer.Text = isCurPlWhite ? "White" : "Black";
            });
            SuspendLayout();
            PaintSquares(newBoard);
            ResumeLayout();
        }

        void Lastlbl_Click(object sender, EventArgs e)
        {
            Button b = (Button)sender;
            if (isGameOver)
            {
                return;
            }


            // prevent a player from playing in the name of the other player
            if ((isOwnerWhite && !isCurPlWhite) || (!isOwnerWhite && isCurPlWhite))
            {
                lblResult.Text = "Its not your turn!";
                lblResult.Visible = true;
                label2.Visible = true;
                Refresh();
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
                    matBoard[row, col].BackColor = GetSquareBackColor(row, col);
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
                    matBoard[dstSquare.Row, dstSquare.Col].FlatAppearance.BorderColor = GetSelectedBorderColor();

                    new Thread(PlayMove).Start();
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
                    matBoard[row, col].BackColor = GetDefaultValidMoveBorderColor();
                    if (matBoard[row, col].BackgroundImage != null)
                    {
                        matBoard[row, col].BackColor = GetDefaultValidCaptureBorderColor();
                        matBoard[row, col].FlatAppearance.BorderColor = GetDefaultValidMoveBorderColor();
                    }
                }
                matBoard[srcSquare.Row, srcSquare.Col].FlatAppearance.BorderColor = GetSelectedBorderColor();
            }

        }

        // messages should be according the protocol.
        // index is the message number in the protocol
        readonly string[] messages =  {
            "Valid move",
            "Valid move - you made \"check\"",
            "Valid move - pawn promotion",
            "Valid move - en passant capture",
            "Valid move - king has castled",
            "Invalid move - not your player",
            "Invalid move - destination is not free",
            "Invalid move - \"check\" wil occure",
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

        void CapturePiece(Square square)
        {
            matBoard[square.Row, square.Col].BackgroundImage = null;
        }

        void PutPiece(Square square, char identifier)
        {
            matBoard[square.Row, square.Col].BackgroundImage = GetImageBySign(identifier, DesignVersion);
        }

        void MovePiece(Square src, Square dest)
        {
            matBoard[dest.Row, dest.Col].BackgroundImage = matBoard[src.Row, src.Col].BackgroundImage;
            matBoard[src.Row, src.Col].BackgroundImage = null;
        }

        void ChangeTurn()
        {
            isCurPlWhite = !isCurPlWhite;
            lblCurrentPlayer.Text = isCurPlWhite ? "White" : "Black";
        }

        string GetPromotion()
        {
            string promotion;

            // if we have a cached list of promotions, extract promotion from there
            if (promotionsIn.Count != 0)
            {
                promotion = promotionsIn[0];
                promotionsIn.RemoveAt(0);
            }
            else // otherwise, just prompt user to choose his desired promotion
            {
                PawnPromotionPrompt prompt = new PawnPromotionPrompt();
                promotion = prompt.GetResult();
            }

            promotionsOut.Add(promotion);

            return promotion;
        }

        void PlayMove()
        {
            if (isGameOver)
                return;


            try
            {
                Invoke((MethodInvoker)delegate
                {
                    string m = "";

                    lblEngineCalc.Visible = true;
                    lblMove.Text = string.Format("Move from {0} to {1}", srcSquare, dstSquare);
                    lblMove.Visible = true;
                    label2.Visible = false;
                    lblResult.Visible = false;

                    this.Refresh();

                    if (srcSquare == null || dstSquare == null)
                    {
                        Thread.Sleep(200);
                    }

                    enginePipe.sendEngineMove(srcSquare.ToString() + dstSquare.ToString());
                    bool isValid = false;
                    while (m != "done")
                    {
                        m = enginePipe.getEngineMessage();
                        string res = ConvertEngineToText(m);
                        bool isMoveCode = int.TryParse(m, out int numericValue);
                        if (isMoveCode)
                        {
                            if (res.ToLower().Contains("game over"))
                            {
                                // quit engine, close pipe and remove the load moves/undo/redo buttons,
                                // since its un-useable at that point + set the "log history" button to the same location
                                // as the now-deleted "load moves" button

                                isGameOver = true;

                                enginePipe.sendEngineMove("quit");
                                gameHistory = enginePipe.getEngineMessage(); // get end-game history from engine
                                enginePipe.close();
                            }
                            else if (res.ToLower().Contains("promotion"))
                            {
                                char type = ' ';
                                string promotion = GetPromotion();

                                switch (promotion.ToLower())
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

                                matBoard[dstSquare.Row, dstSquare.Col].BackgroundImage = GetImageBySign(type, DesignVersion);
                                enginePipe.sendEngineMove(dstSquare.ToString() + Char.ToLower(type));
                                m = enginePipe.getEngineMessage(); // get the confirmation message from engine
                                res = String.Format(ConvertEngineToText(m), lblCurrentPlayer.Text, dstSquare.ToString(), promotion);

                                CleanBoard(); // clean board colors after promotion - fixes design issue
                            }

                            matBoard[srcSquare.Row, srcSquare.Col].FlatAppearance.BorderColor = GetDefaultBorderColor();
                            matBoard[dstSquare.Row, dstSquare.Col].FlatAppearance.BorderColor = GetDefaultBorderColor();

                            if (res.ToLower().StartsWith("valid") || res.ToLower().Contains("promoted"))
                            {
                                ChangeTurn();
                                isValid = true;
                            }

                            lblEngineCalc.Visible = false;
                            lblResult.Text = String.Format(res, lblCurrentPlayer.Text);
                            lblResult.Visible = true;
                            label2.Visible = true;
                            this.Refresh();
                        }
                        else
                        {
                            switch (m.Length)
                            {
                                case 4: // move piece from one location to the other
                                    if (m != "done")
                                    {
                                        string src = m.Substring(0, 2);
                                        string dest = m.Substring(2, 2);

                                        MovePiece(new Square(src), new Square(dest));
                                    }
                                    break;
                                case 3: // put a piece at a specific location
                                    string location = m.Substring(0, 2);

                                    PutPiece(new Square(location), m[2]);
                                    break;
                                case 2: // capture a piece at a specific location
                                    CapturePiece(new Square(m));
                                    break;
                                default:
                                    m = "done"; // simply create the exit signal from the loop for any invalid input
                                    break;
                            }
                        }
                    }
                    if (isValid)
                    {
                        new Thread(UpdateBoard).Start();
                    }
                });
            }
            catch
            {

            }
            finally
            {
                if (srcSquare != null)
                    matBoard[srcSquare.Row, srcSquare.Col].FlatAppearance.BorderColor = GetDefaultBorderColor();

                if (dstSquare != null)
                    matBoard[dstSquare.Row, dstSquare.Col].FlatAppearance.BorderColor = GetDefaultBorderColor();

                shouldRestore = true;
                dstSquare = null;
                srcSquare = null;
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

        string getHistory()
        {
            enginePipe.sendEngineMove("history"); // ask engine to give game's history
            gameHistory = gameHistory != "" ? gameHistory : enginePipe.getEngineMessage();
            return gameHistory;
        }
        private void LogHistory_Click(object sender, EventArgs e)
        {
            getHistory();
            GameHistory historyDiaglog = new GameHistory(gameHistory);
            historyDiaglog.ShowDialog();
            if (!isGameOver) gameHistory = "";
        }

        private void Form1_KeyDown(object sender, KeyEventArgs e)
        {
            if (e.Modifiers == Keys.Control)
            {
                if (e.KeyCode == Keys.S) // save game
                {
                    SaveGameBtn.PerformClick();
                }

                if (isGameOver)
                {
                    return;
                }
            }
        }

        private void DesignVerBtn_Click(object sender, EventArgs e)
        {
            DesignVersion = 2 - ((DesignVersion + 1) % 2);
            DesignVerBtn.Text = DesignVerBtn.Text.Substring(0, DesignVerBtn.Text.Length - 1);
            DesignVerBtn.Text += (char)(DesignVersion + '0');

            SuspendLayout();
            PaintSquares();
            if (srcSquare != null)
            {
                srcSquare = null;
                matBoard[srcSquare.Row, srcSquare.Col].PerformClick();
            }
            ResumeLayout();
        }

        void ShowLabel(Label lbl, int duration)
        {
            lbl.Visible = true;

            // hide error message after 4 seconds
            Task.Delay(duration).ContinueWith(_ =>
            {
                Invoke(new MethodInvoker(() => { lbl.Visible = false; }));
            });
        }
        private void SaveGameBtn_Click(object sender, EventArgs e)
        {
            getHistory();
            if (gameHistory == "")
            {
                // show error message for 4 seconds.
                ShowLabel(GameSavedErrorLbl, 4000);
                return;
            }
            SaveFileDialog saveFileDialog = new SaveFileDialog();
            saveFileDialog.Filter = "Chess Game|*.chess";
            saveFileDialog.Title = "Save a Chess Game File";
            saveFileDialog.ShowDialog();

            // If the file name is not an empty string open it for saving.
            if (saveFileDialog.FileName != "")
            {
                StreamWriter file = new StreamWriter(saveFileDialog.FileName);
                file.Write(gameHistory + "\n" + String.Join(",", promotionsOut));
                file.Close();

                // show success message for 4 seconds.
                ShowLabel(GameSavedSuccessLbl, 4000);
            }

            if (!isGameOver)
                gameHistory = "";
        }
    }
}