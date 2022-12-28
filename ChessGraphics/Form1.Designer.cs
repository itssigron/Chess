﻿namespace chessGraphics
{
    partial class Form1
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(Form1));
            this.btnBoard = new System.Windows.Forms.Button();
            this.lblMove = new System.Windows.Forms.Label();
            this.lblResult = new System.Windows.Forms.Label();
            this.label1 = new System.Windows.Forms.Label();
            this.lblCurrentPlayer = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.lblWaiting = new System.Windows.Forms.Label();
            this.lblEngineCalc = new System.Windows.Forms.Label();
            this.label11 = new System.Windows.Forms.Label();
            this.label12 = new System.Windows.Forms.Label();
            this.label13 = new System.Windows.Forms.Label();
            this.label14 = new System.Windows.Forms.Label();
            this.label15 = new System.Windows.Forms.Label();
            this.label16 = new System.Windows.Forms.Label();
            this.label17 = new System.Windows.Forms.Label();
            this.label18 = new System.Windows.Forms.Label();
            this.LoadMoves = new System.Windows.Forms.Button();
            this.LogHistory = new System.Windows.Forms.Button();
            this.MovesRestoreError = new System.Windows.Forms.Label();
            this.UndoBtn = new System.Windows.Forms.Button();
            this.RedoBtn = new System.Windows.Forms.Button();
            this.DesignVerBtn = new System.Windows.Forms.Button();
            this.loadingLbl = new System.Windows.Forms.Label();
            this.SaveGameBtn = new System.Windows.Forms.Button();
            this.GameSavedSuccessLbl = new System.Windows.Forms.Label();
            this.LoadGameBtn = new System.Windows.Forms.Button();
            this.GameSavedErrorLbl = new System.Windows.Forms.Label();
            this.GameFileBorder1 = new System.Windows.Forms.Panel();
            this.GameRankBorder1 = new System.Windows.Forms.Panel();
            this.label3 = new System.Windows.Forms.Label();
            this.label4 = new System.Windows.Forms.Label();
            this.label5 = new System.Windows.Forms.Label();
            this.label6 = new System.Windows.Forms.Label();
            this.label7 = new System.Windows.Forms.Label();
            this.label8 = new System.Windows.Forms.Label();
            this.label9 = new System.Windows.Forms.Label();
            this.label10 = new System.Windows.Forms.Label();
            this.GameFileBorder2 = new System.Windows.Forms.Panel();
            this.label27 = new System.Windows.Forms.Label();
            this.label28 = new System.Windows.Forms.Label();
            this.label29 = new System.Windows.Forms.Label();
            this.label30 = new System.Windows.Forms.Label();
            this.label31 = new System.Windows.Forms.Label();
            this.label32 = new System.Windows.Forms.Label();
            this.label33 = new System.Windows.Forms.Label();
            this.label34 = new System.Windows.Forms.Label();
            this.panel1 = new System.Windows.Forms.Panel();
            this.label19 = new System.Windows.Forms.Label();
            this.label20 = new System.Windows.Forms.Label();
            this.label21 = new System.Windows.Forms.Label();
            this.label22 = new System.Windows.Forms.Label();
            this.label23 = new System.Windows.Forms.Label();
            this.label24 = new System.Windows.Forms.Label();
            this.label25 = new System.Windows.Forms.Label();
            this.label26 = new System.Windows.Forms.Label();
            this.GameFileBorder1.SuspendLayout();
            this.GameRankBorder1.SuspendLayout();
            this.GameFileBorder2.SuspendLayout();
            this.panel1.SuspendLayout();
            this.SuspendLayout();
            // 
            // btnBoard
            // 
            this.btnBoard.AutoEllipsis = true;
            this.btnBoard.BackColor = System.Drawing.Color.Black;
            this.btnBoard.BackgroundImage = ((System.Drawing.Image)(resources.GetObject("btnBoard.BackgroundImage")));
            this.btnBoard.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Stretch;
            this.btnBoard.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.btnBoard.Location = new System.Drawing.Point(65, 58);
            this.btnBoard.Margin = new System.Windows.Forms.Padding(4);
            this.btnBoard.Name = "btnBoard";
            this.btnBoard.Size = new System.Drawing.Size(89, 76);
            this.btnBoard.TabIndex = 2;
            this.btnBoard.Tag = "a8";
            this.btnBoard.UseVisualStyleBackColor = false;
            this.btnBoard.Visible = false;
            // 
            // lblMove
            // 
            this.lblMove.AutoSize = true;
            this.lblMove.Font = new System.Drawing.Font("Arial Narrow", 14.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.lblMove.ForeColor = System.Drawing.Color.Red;
            this.lblMove.Location = new System.Drawing.Point(839, 123);
            this.lblMove.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.lblMove.Name = "lblMove";
            this.lblMove.Size = new System.Drawing.Size(203, 29);
            this.lblMove.TabIndex = 4;
            this.lblMove.Text = "move from {0} to {1}";
            this.lblMove.Visible = false;
            // 
            // lblResult
            // 
            this.lblResult.AutoSize = true;
            this.lblResult.Font = new System.Drawing.Font("Arial Narrow", 14.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.lblResult.ForeColor = System.Drawing.Color.Red;
            this.lblResult.Location = new System.Drawing.Point(839, 210);
            this.lblResult.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.lblResult.Name = "lblResult";
            this.lblResult.Size = new System.Drawing.Size(40, 29);
            this.lblResult.TabIndex = 5;
            this.lblResult.Text = "{0}";
            this.lblResult.Visible = false;
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Font = new System.Drawing.Font("Arial Narrow", 14.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label1.ForeColor = System.Drawing.Color.Red;
            this.label1.Location = new System.Drawing.Point(839, 32);
            this.label1.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(160, 29);
            this.label1.TabIndex = 6;
            this.label1.Text = "Current player: ";
            this.label1.Visible = false;
            // 
            // lblCurrentPlayer
            // 
            this.lblCurrentPlayer.AutoSize = true;
            this.lblCurrentPlayer.Font = new System.Drawing.Font("Arial Narrow", 14.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.lblCurrentPlayer.ForeColor = System.Drawing.Color.Red;
            this.lblCurrentPlayer.Location = new System.Drawing.Point(999, 32);
            this.lblCurrentPlayer.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.lblCurrentPlayer.Name = "lblCurrentPlayer";
            this.lblCurrentPlayer.Size = new System.Drawing.Size(67, 29);
            this.lblCurrentPlayer.TabIndex = 7;
            this.lblCurrentPlayer.Text = "White";
            this.lblCurrentPlayer.Visible = false;
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Font = new System.Drawing.Font("Arial Narrow", 14.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label2.ForeColor = System.Drawing.Color.Red;
            this.label2.Location = new System.Drawing.Point(839, 170);
            this.label2.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(198, 29);
            this.label2.TabIndex = 8;
            this.label2.Text = "Result from engine:";
            this.label2.Visible = false;
            // 
            // lblWaiting
            // 
            this.lblWaiting.AutoSize = true;
            this.lblWaiting.BackColor = System.Drawing.Color.Transparent;
            this.lblWaiting.Font = new System.Drawing.Font("Arial Narrow", 36F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.lblWaiting.ForeColor = System.Drawing.Color.Red;
            this.lblWaiting.Location = new System.Drawing.Point(295, 268);
            this.lblWaiting.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.lblWaiting.Name = "lblWaiting";
            this.lblWaiting.Size = new System.Drawing.Size(761, 69);
            this.lblWaiting.TabIndex = 100;
            this.lblWaiting.Text = "Waiting for engine to connect...";
            // 
            // lblEngineCalc
            // 
            this.lblEngineCalc.AutoSize = true;
            this.lblEngineCalc.Font = new System.Drawing.Font("Arial Narrow", 14.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.lblEngineCalc.ForeColor = System.Drawing.Color.Red;
            this.lblEngineCalc.Location = new System.Drawing.Point(839, 79);
            this.lblEngineCalc.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.lblEngineCalc.Name = "lblEngineCalc";
            this.lblEngineCalc.Size = new System.Drawing.Size(221, 29);
            this.lblEngineCalc.TabIndex = 10;
            this.lblEngineCalc.Text = "Engine is calculating...";
            this.lblEngineCalc.Visible = false;
            // 
            // label11
            // 
            this.label11.AutoSize = true;
            this.label11.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(33)))), ((int)(((byte)(33)))), ((int)(((byte)(33)))));
            this.label11.Font = new System.Drawing.Font("Arial Narrow", 15.75F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label11.ForeColor = System.Drawing.Color.White;
            this.label11.Location = new System.Drawing.Point(711, 6);
            this.label11.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label11.Name = "label11";
            this.label11.Size = new System.Drawing.Size(28, 31);
            this.label11.TabIndex = 26;
            this.label11.Text = "h";
            // 
            // label12
            // 
            this.label12.AutoSize = true;
            this.label12.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(33)))), ((int)(((byte)(33)))), ((int)(((byte)(33)))));
            this.label12.Font = new System.Drawing.Font("Arial Narrow", 15.75F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label12.ForeColor = System.Drawing.Color.White;
            this.label12.Location = new System.Drawing.Point(618, 2);
            this.label12.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label12.Name = "label12";
            this.label12.Size = new System.Drawing.Size(28, 31);
            this.label12.TabIndex = 27;
            this.label12.Text = "g";
            // 
            // label13
            // 
            this.label13.AutoSize = true;
            this.label13.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(33)))), ((int)(((byte)(33)))), ((int)(((byte)(33)))));
            this.label13.Font = new System.Drawing.Font("Arial Narrow", 15.75F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label13.ForeColor = System.Drawing.Color.White;
            this.label13.Location = new System.Drawing.Point(532, 6);
            this.label13.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label13.Name = "label13";
            this.label13.Size = new System.Drawing.Size(21, 31);
            this.label13.TabIndex = 28;
            this.label13.Text = "f";
            // 
            // label14
            // 
            this.label14.AutoSize = true;
            this.label14.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(33)))), ((int)(((byte)(33)))), ((int)(((byte)(33)))));
            this.label14.Font = new System.Drawing.Font("Arial Narrow", 15.75F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label14.ForeColor = System.Drawing.Color.White;
            this.label14.Location = new System.Drawing.Point(443, 4);
            this.label14.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label14.Name = "label14";
            this.label14.Size = new System.Drawing.Size(26, 31);
            this.label14.TabIndex = 29;
            this.label14.Text = "e";
            // 
            // label15
            // 
            this.label15.AutoSize = true;
            this.label15.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(33)))), ((int)(((byte)(33)))), ((int)(((byte)(33)))));
            this.label15.Font = new System.Drawing.Font("Arial Narrow", 15.75F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label15.ForeColor = System.Drawing.Color.White;
            this.label15.Location = new System.Drawing.Point(351, 5);
            this.label15.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label15.Name = "label15";
            this.label15.Size = new System.Drawing.Size(28, 31);
            this.label15.TabIndex = 30;
            this.label15.Text = "d";
            // 
            // label16
            // 
            this.label16.AutoSize = true;
            this.label16.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(33)))), ((int)(((byte)(33)))), ((int)(((byte)(33)))));
            this.label16.Font = new System.Drawing.Font("Arial Narrow", 15.75F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label16.ForeColor = System.Drawing.Color.White;
            this.label16.Location = new System.Drawing.Point(262, 4);
            this.label16.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label16.Name = "label16";
            this.label16.Size = new System.Drawing.Size(26, 31);
            this.label16.TabIndex = 31;
            this.label16.Text = "c";
            // 
            // label17
            // 
            this.label17.AutoSize = true;
            this.label17.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(33)))), ((int)(((byte)(33)))), ((int)(((byte)(33)))));
            this.label17.Font = new System.Drawing.Font("Arial Narrow", 15.75F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label17.ForeColor = System.Drawing.Color.White;
            this.label17.Location = new System.Drawing.Point(173, 5);
            this.label17.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label17.Name = "label17";
            this.label17.Size = new System.Drawing.Size(28, 31);
            this.label17.TabIndex = 32;
            this.label17.Text = "b";
            // 
            // label18
            // 
            this.label18.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(33)))), ((int)(((byte)(33)))), ((int)(((byte)(33)))));
            this.label18.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.label18.Font = new System.Drawing.Font("Arial Narrow", 15.75F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label18.ForeColor = System.Drawing.Color.White;
            this.label18.Location = new System.Drawing.Point(84, 4);
            this.label18.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label18.Name = "label18";
            this.label18.Size = new System.Drawing.Size(27, 31);
            this.label18.TabIndex = 33;
            this.label18.Text = "a";
            // 
            // LoadMoves
            // 
            this.LoadMoves.Font = new System.Drawing.Font("Microsoft Sans Serif", 9F);
            this.LoadMoves.Location = new System.Drawing.Point(1320, 18);
            this.LoadMoves.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.LoadMoves.Name = "LoadMoves";
            this.LoadMoves.Size = new System.Drawing.Size(113, 42);
            this.LoadMoves.TabIndex = 50;
            this.LoadMoves.Text = "Load moves";
            this.LoadMoves.UseVisualStyleBackColor = true;
            this.LoadMoves.Visible = false;
            this.LoadMoves.Click += new System.EventHandler(this.LoadMoves_Click);
            // 
            // LogHistory
            // 
            this.LogHistory.Font = new System.Drawing.Font("Microsoft Sans Serif", 9F);
            this.LogHistory.Location = new System.Drawing.Point(1320, 65);
            this.LogHistory.Margin = new System.Windows.Forms.Padding(4);
            this.LogHistory.Name = "LogHistory";
            this.LogHistory.Size = new System.Drawing.Size(113, 42);
            this.LogHistory.TabIndex = 51;
            this.LogHistory.Text = "Log History";
            this.LogHistory.UseVisualStyleBackColor = true;
            this.LogHistory.Visible = false;
            this.LogHistory.Click += new System.EventHandler(this.LogHistory_Click);
            // 
            // MovesRestoreError
            // 
            this.MovesRestoreError.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F);
            this.MovesRestoreError.ForeColor = System.Drawing.Color.Red;
            this.MovesRestoreError.Location = new System.Drawing.Point(1183, 126);
            this.MovesRestoreError.Name = "MovesRestoreError";
            this.MovesRestoreError.Size = new System.Drawing.Size(265, 75);
            this.MovesRestoreError.TabIndex = 53;
            this.MovesRestoreError.Text = "No moves left to restore";
            this.MovesRestoreError.Visible = false;
            // 
            // UndoBtn
            // 
            this.UndoBtn.Font = new System.Drawing.Font("Microsoft Sans Serif", 9F);
            this.UndoBtn.Location = new System.Drawing.Point(1172, 18);
            this.UndoBtn.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.UndoBtn.Name = "UndoBtn";
            this.UndoBtn.Size = new System.Drawing.Size(141, 42);
            this.UndoBtn.TabIndex = 54;
            this.UndoBtn.Text = "Undo (Ctrl + Z)";
            this.UndoBtn.UseVisualStyleBackColor = true;
            this.UndoBtn.Visible = false;
            this.UndoBtn.Click += new System.EventHandler(this.UndoBtn_Click);
            // 
            // RedoBtn
            // 
            this.RedoBtn.Font = new System.Drawing.Font("Microsoft Sans Serif", 9F);
            this.RedoBtn.Location = new System.Drawing.Point(1172, 64);
            this.RedoBtn.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.RedoBtn.Name = "RedoBtn";
            this.RedoBtn.Size = new System.Drawing.Size(141, 42);
            this.RedoBtn.TabIndex = 55;
            this.RedoBtn.Text = "Redo (Ctrl + Y)";
            this.RedoBtn.UseVisualStyleBackColor = true;
            this.RedoBtn.Visible = false;
            this.RedoBtn.Click += new System.EventHandler(this.RedoBtn_Click);
            // 
            // DesignVerBtn
            // 
            this.DesignVerBtn.Font = new System.Drawing.Font("Microsoft Sans Serif", 11.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.DesignVerBtn.Location = new System.Drawing.Point(1213, 242);
            this.DesignVerBtn.Margin = new System.Windows.Forms.Padding(4);
            this.DesignVerBtn.Name = "DesignVerBtn";
            this.DesignVerBtn.Size = new System.Drawing.Size(216, 46);
            this.DesignVerBtn.TabIndex = 101;
            this.DesignVerBtn.Text = "Design Version #1";
            this.DesignVerBtn.UseVisualStyleBackColor = true;
            this.DesignVerBtn.Visible = false;
            this.DesignVerBtn.Click += new System.EventHandler(this.DesignVerBtn_Click);
            // 
            // loadingLbl
            // 
            this.loadingLbl.AutoSize = true;
            this.loadingLbl.BackColor = System.Drawing.Color.Transparent;
            this.loadingLbl.Font = new System.Drawing.Font("Arial Narrow", 50F, System.Drawing.FontStyle.Bold);
            this.loadingLbl.ForeColor = System.Drawing.Color.Red;
            this.loadingLbl.Location = new System.Drawing.Point(101, 282);
            this.loadingLbl.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.loadingLbl.Name = "loadingLbl";
            this.loadingLbl.Size = new System.Drawing.Size(576, 98);
            this.loadingLbl.TabIndex = 102;
            this.loadingLbl.Text = "Loading Game...";
            this.loadingLbl.Visible = false;
            // 
            // SaveGameBtn
            // 
            this.SaveGameBtn.BackColor = System.Drawing.SystemColors.ActiveBorder;
            this.SaveGameBtn.Font = new System.Drawing.Font("Microsoft Tai Le", 11.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.SaveGameBtn.ForeColor = System.Drawing.SystemColors.ControlText;
            this.SaveGameBtn.Location = new System.Drawing.Point(1213, 370);
            this.SaveGameBtn.Margin = new System.Windows.Forms.Padding(4);
            this.SaveGameBtn.Name = "SaveGameBtn";
            this.SaveGameBtn.Size = new System.Drawing.Size(216, 46);
            this.SaveGameBtn.TabIndex = 103;
            this.SaveGameBtn.Text = "Save Game";
            this.SaveGameBtn.UseVisualStyleBackColor = false;
            this.SaveGameBtn.Visible = false;
            this.SaveGameBtn.Click += new System.EventHandler(this.SaveGameBtn_Click);
            // 
            // GameSavedSuccessLbl
            // 
            this.GameSavedSuccessLbl.Cursor = System.Windows.Forms.Cursors.Default;
            this.GameSavedSuccessLbl.Font = new System.Drawing.Font("Microsoft Sans Serif", 13F);
            this.GameSavedSuccessLbl.ForeColor = System.Drawing.Color.Green;
            this.GameSavedSuccessLbl.Location = new System.Drawing.Point(1164, 428);
            this.GameSavedSuccessLbl.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.GameSavedSuccessLbl.Name = "GameSavedSuccessLbl";
            this.GameSavedSuccessLbl.Size = new System.Drawing.Size(265, 54);
            this.GameSavedSuccessLbl.TabIndex = 104;
            this.GameSavedSuccessLbl.Text = "Game was successfully saved!";
            this.GameSavedSuccessLbl.Visible = false;
            // 
            // LoadGameBtn
            // 
            this.LoadGameBtn.BackColor = System.Drawing.SystemColors.ActiveBorder;
            this.LoadGameBtn.Font = new System.Drawing.Font("Microsoft Tai Le", 11.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.LoadGameBtn.ForeColor = System.Drawing.SystemColors.ControlText;
            this.LoadGameBtn.Location = new System.Drawing.Point(1213, 305);
            this.LoadGameBtn.Margin = new System.Windows.Forms.Padding(4);
            this.LoadGameBtn.Name = "LoadGameBtn";
            this.LoadGameBtn.Size = new System.Drawing.Size(216, 46);
            this.LoadGameBtn.TabIndex = 105;
            this.LoadGameBtn.Text = "Load Game";
            this.LoadGameBtn.UseVisualStyleBackColor = false;
            this.LoadGameBtn.Visible = false;
            this.LoadGameBtn.Click += new System.EventHandler(this.LoadGameBtn_Click);
            // 
            // GameSavedErrorLbl
            // 
            this.GameSavedErrorLbl.Cursor = System.Windows.Forms.Cursors.Default;
            this.GameSavedErrorLbl.Font = new System.Drawing.Font("Microsoft Sans Serif", 13F);
            this.GameSavedErrorLbl.ForeColor = System.Drawing.Color.Red;
            this.GameSavedErrorLbl.Location = new System.Drawing.Point(1127, 428);
            this.GameSavedErrorLbl.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.GameSavedErrorLbl.Name = "GameSavedErrorLbl";
            this.GameSavedErrorLbl.Size = new System.Drawing.Size(321, 54);
            this.GameSavedErrorLbl.TabIndex = 106;
            this.GameSavedErrorLbl.Text = "Error: Cannot save game. No moves have been made.";
            this.GameSavedErrorLbl.Visible = false;
            // 
            // GameFileBorder1
            // 
            this.GameFileBorder1.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(33)))), ((int)(((byte)(33)))), ((int)(((byte)(33)))));
            this.GameFileBorder1.Controls.Add(this.label13);
            this.GameFileBorder1.Controls.Add(this.label11);
            this.GameFileBorder1.Controls.Add(this.label12);
            this.GameFileBorder1.Controls.Add(this.label14);
            this.GameFileBorder1.Controls.Add(this.label15);
            this.GameFileBorder1.Controls.Add(this.label16);
            this.GameFileBorder1.Controls.Add(this.label17);
            this.GameFileBorder1.Controls.Add(this.label18);
            this.GameFileBorder1.Location = new System.Drawing.Point(12, 14);
            this.GameFileBorder1.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.GameFileBorder1.Name = "GameFileBorder1";
            this.GameFileBorder1.Size = new System.Drawing.Size(820, 44);
            this.GameFileBorder1.TabIndex = 107;
            // 
            // GameRankBorder1
            // 
            this.GameRankBorder1.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(33)))), ((int)(((byte)(33)))), ((int)(((byte)(33)))));
            this.GameRankBorder1.Controls.Add(this.label3);
            this.GameRankBorder1.Controls.Add(this.label4);
            this.GameRankBorder1.Controls.Add(this.label5);
            this.GameRankBorder1.Controls.Add(this.label6);
            this.GameRankBorder1.Controls.Add(this.label7);
            this.GameRankBorder1.Controls.Add(this.label8);
            this.GameRankBorder1.Controls.Add(this.label9);
            this.GameRankBorder1.Controls.Add(this.label10);
            this.GameRankBorder1.Location = new System.Drawing.Point(12, 49);
            this.GameRankBorder1.Margin = new System.Windows.Forms.Padding(4);
            this.GameRankBorder1.Name = "GameRankBorder1";
            this.GameRankBorder1.Size = new System.Drawing.Size(53, 624);
            this.GameRankBorder1.TabIndex = 110;
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(33)))), ((int)(((byte)(33)))), ((int)(((byte)(33)))));
            this.label3.Font = new System.Drawing.Font("Arial Narrow", 15.75F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label3.ForeColor = System.Drawing.Color.White;
            this.label3.Location = new System.Drawing.Point(12, 30);
            this.label3.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(26, 31);
            this.label3.TabIndex = 40;
            this.label3.Text = "8";
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(33)))), ((int)(((byte)(33)))), ((int)(((byte)(33)))));
            this.label4.Font = new System.Drawing.Font("Arial Narrow", 15.75F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label4.ForeColor = System.Drawing.Color.White;
            this.label4.Location = new System.Drawing.Point(12, 334);
            this.label4.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(26, 31);
            this.label4.TabIndex = 34;
            this.label4.Text = "4";
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(33)))), ((int)(((byte)(33)))), ((int)(((byte)(33)))));
            this.label5.Font = new System.Drawing.Font("Arial Narrow", 15.75F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label5.ForeColor = System.Drawing.Color.White;
            this.label5.Location = new System.Drawing.Point(12, 258);
            this.label5.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(26, 31);
            this.label5.TabIndex = 35;
            this.label5.Text = "5";
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(33)))), ((int)(((byte)(33)))), ((int)(((byte)(33)))));
            this.label6.Font = new System.Drawing.Font("Arial Narrow", 15.75F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label6.ForeColor = System.Drawing.Color.White;
            this.label6.Location = new System.Drawing.Point(12, 562);
            this.label6.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(26, 31);
            this.label6.TabIndex = 36;
            this.label6.Text = "1";
            // 
            // label7
            // 
            this.label7.AutoSize = true;
            this.label7.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(33)))), ((int)(((byte)(33)))), ((int)(((byte)(33)))));
            this.label7.Font = new System.Drawing.Font("Arial Narrow", 15.75F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label7.ForeColor = System.Drawing.Color.White;
            this.label7.Location = new System.Drawing.Point(12, 486);
            this.label7.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label7.Name = "label7";
            this.label7.Size = new System.Drawing.Size(26, 31);
            this.label7.TabIndex = 37;
            this.label7.Text = "2";
            // 
            // label8
            // 
            this.label8.AutoSize = true;
            this.label8.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(33)))), ((int)(((byte)(33)))), ((int)(((byte)(33)))));
            this.label8.Font = new System.Drawing.Font("Arial Narrow", 15.75F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label8.ForeColor = System.Drawing.Color.White;
            this.label8.Location = new System.Drawing.Point(12, 410);
            this.label8.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label8.Name = "label8";
            this.label8.Size = new System.Drawing.Size(26, 31);
            this.label8.TabIndex = 38;
            this.label8.Text = "3";
            // 
            // label9
            // 
            this.label9.AutoSize = true;
            this.label9.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(33)))), ((int)(((byte)(33)))), ((int)(((byte)(33)))));
            this.label9.Font = new System.Drawing.Font("Arial Narrow", 15.75F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label9.ForeColor = System.Drawing.Color.White;
            this.label9.Location = new System.Drawing.Point(12, 182);
            this.label9.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label9.Name = "label9";
            this.label9.Size = new System.Drawing.Size(26, 31);
            this.label9.TabIndex = 39;
            this.label9.Text = "6";
            // 
            // label10
            // 
            this.label10.AutoSize = true;
            this.label10.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(33)))), ((int)(((byte)(33)))), ((int)(((byte)(33)))));
            this.label10.Font = new System.Drawing.Font("Arial Narrow", 15.75F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label10.ForeColor = System.Drawing.Color.White;
            this.label10.Location = new System.Drawing.Point(12, 106);
            this.label10.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label10.Name = "label10";
            this.label10.Size = new System.Drawing.Size(26, 31);
            this.label10.TabIndex = 41;
            this.label10.Text = "7";
            // 
            // GameFileBorder2
            // 
            this.GameFileBorder2.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(33)))), ((int)(((byte)(33)))), ((int)(((byte)(33)))));
            this.GameFileBorder2.Controls.Add(this.label27);
            this.GameFileBorder2.Controls.Add(this.label28);
            this.GameFileBorder2.Controls.Add(this.label29);
            this.GameFileBorder2.Controls.Add(this.label30);
            this.GameFileBorder2.Controls.Add(this.label31);
            this.GameFileBorder2.Controls.Add(this.label32);
            this.GameFileBorder2.Controls.Add(this.label33);
            this.GameFileBorder2.Controls.Add(this.label34);
            this.GameFileBorder2.Location = new System.Drawing.Point(12, 668);
            this.GameFileBorder2.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.GameFileBorder2.Name = "GameFileBorder2";
            this.GameFileBorder2.Size = new System.Drawing.Size(820, 44);
            this.GameFileBorder2.TabIndex = 108;
            // 
            // label27
            // 
            this.label27.AutoSize = true;
            this.label27.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(33)))), ((int)(((byte)(33)))), ((int)(((byte)(33)))));
            this.label27.Font = new System.Drawing.Font("Arial Narrow", 15.75F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label27.ForeColor = System.Drawing.Color.White;
            this.label27.Location = new System.Drawing.Point(532, 6);
            this.label27.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label27.Name = "label27";
            this.label27.Size = new System.Drawing.Size(21, 31);
            this.label27.TabIndex = 28;
            this.label27.Text = "f";
            // 
            // label28
            // 
            this.label28.AutoSize = true;
            this.label28.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(33)))), ((int)(((byte)(33)))), ((int)(((byte)(33)))));
            this.label28.Font = new System.Drawing.Font("Arial Narrow", 15.75F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label28.ForeColor = System.Drawing.Color.White;
            this.label28.Location = new System.Drawing.Point(711, 6);
            this.label28.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label28.Name = "label28";
            this.label28.Size = new System.Drawing.Size(28, 31);
            this.label28.TabIndex = 26;
            this.label28.Text = "h";
            // 
            // label29
            // 
            this.label29.AutoSize = true;
            this.label29.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(33)))), ((int)(((byte)(33)))), ((int)(((byte)(33)))));
            this.label29.Font = new System.Drawing.Font("Arial Narrow", 15.75F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label29.ForeColor = System.Drawing.Color.White;
            this.label29.Location = new System.Drawing.Point(618, 2);
            this.label29.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label29.Name = "label29";
            this.label29.Size = new System.Drawing.Size(28, 31);
            this.label29.TabIndex = 27;
            this.label29.Text = "g";
            // 
            // label30
            // 
            this.label30.AutoSize = true;
            this.label30.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(33)))), ((int)(((byte)(33)))), ((int)(((byte)(33)))));
            this.label30.Font = new System.Drawing.Font("Arial Narrow", 15.75F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label30.ForeColor = System.Drawing.Color.White;
            this.label30.Location = new System.Drawing.Point(443, 4);
            this.label30.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label30.Name = "label30";
            this.label30.Size = new System.Drawing.Size(26, 31);
            this.label30.TabIndex = 29;
            this.label30.Text = "e";
            // 
            // label31
            // 
            this.label31.AutoSize = true;
            this.label31.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(33)))), ((int)(((byte)(33)))), ((int)(((byte)(33)))));
            this.label31.Font = new System.Drawing.Font("Arial Narrow", 15.75F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label31.ForeColor = System.Drawing.Color.White;
            this.label31.Location = new System.Drawing.Point(351, 5);
            this.label31.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label31.Name = "label31";
            this.label31.Size = new System.Drawing.Size(28, 31);
            this.label31.TabIndex = 30;
            this.label31.Text = "d";
            // 
            // label32
            // 
            this.label32.AutoSize = true;
            this.label32.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(33)))), ((int)(((byte)(33)))), ((int)(((byte)(33)))));
            this.label32.Font = new System.Drawing.Font("Arial Narrow", 15.75F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label32.ForeColor = System.Drawing.Color.White;
            this.label32.Location = new System.Drawing.Point(262, 4);
            this.label32.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label32.Name = "label32";
            this.label32.Size = new System.Drawing.Size(26, 31);
            this.label32.TabIndex = 31;
            this.label32.Text = "c";
            // 
            // label33
            // 
            this.label33.AutoSize = true;
            this.label33.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(33)))), ((int)(((byte)(33)))), ((int)(((byte)(33)))));
            this.label33.Font = new System.Drawing.Font("Arial Narrow", 15.75F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label33.ForeColor = System.Drawing.Color.White;
            this.label33.Location = new System.Drawing.Point(173, 5);
            this.label33.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label33.Name = "label33";
            this.label33.Size = new System.Drawing.Size(28, 31);
            this.label33.TabIndex = 32;
            this.label33.Text = "b";
            // 
            // label34
            // 
            this.label34.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(33)))), ((int)(((byte)(33)))), ((int)(((byte)(33)))));
            this.label34.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.label34.Font = new System.Drawing.Font("Arial Narrow", 15.75F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label34.ForeColor = System.Drawing.Color.White;
            this.label34.Location = new System.Drawing.Point(84, 4);
            this.label34.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label34.Name = "label34";
            this.label34.Size = new System.Drawing.Size(27, 31);
            this.label34.TabIndex = 33;
            this.label34.Text = "a";
            // 
            // panel1
            // 
            this.panel1.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(33)))), ((int)(((byte)(33)))), ((int)(((byte)(33)))));
            this.panel1.Controls.Add(this.label19);
            this.panel1.Controls.Add(this.label20);
            this.panel1.Controls.Add(this.label21);
            this.panel1.Controls.Add(this.label22);
            this.panel1.Controls.Add(this.label23);
            this.panel1.Controls.Add(this.label24);
            this.panel1.Controls.Add(this.label25);
            this.panel1.Controls.Add(this.label26);
            this.panel1.Location = new System.Drawing.Point(779, 49);
            this.panel1.Margin = new System.Windows.Forms.Padding(4);
            this.panel1.Name = "panel1";
            this.panel1.Size = new System.Drawing.Size(53, 624);
            this.panel1.TabIndex = 200;
            // 
            // label19
            // 
            this.label19.AutoSize = true;
            this.label19.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(33)))), ((int)(((byte)(33)))), ((int)(((byte)(33)))));
            this.label19.Font = new System.Drawing.Font("Arial Narrow", 15.75F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label19.ForeColor = System.Drawing.Color.White;
            this.label19.Location = new System.Drawing.Point(12, 30);
            this.label19.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label19.Name = "label19";
            this.label19.Size = new System.Drawing.Size(26, 31);
            this.label19.TabIndex = 40;
            this.label19.Text = "8";
            // 
            // label20
            // 
            this.label20.AutoSize = true;
            this.label20.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(33)))), ((int)(((byte)(33)))), ((int)(((byte)(33)))));
            this.label20.Font = new System.Drawing.Font("Arial Narrow", 15.75F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label20.ForeColor = System.Drawing.Color.White;
            this.label20.Location = new System.Drawing.Point(12, 334);
            this.label20.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label20.Name = "label20";
            this.label20.Size = new System.Drawing.Size(26, 31);
            this.label20.TabIndex = 34;
            this.label20.Text = "4";
            // 
            // label21
            // 
            this.label21.AutoSize = true;
            this.label21.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(33)))), ((int)(((byte)(33)))), ((int)(((byte)(33)))));
            this.label21.Font = new System.Drawing.Font("Arial Narrow", 15.75F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label21.ForeColor = System.Drawing.Color.White;
            this.label21.Location = new System.Drawing.Point(12, 258);
            this.label21.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label21.Name = "label21";
            this.label21.Size = new System.Drawing.Size(26, 31);
            this.label21.TabIndex = 35;
            this.label21.Text = "5";
            // 
            // label22
            // 
            this.label22.AutoSize = true;
            this.label22.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(33)))), ((int)(((byte)(33)))), ((int)(((byte)(33)))));
            this.label22.Font = new System.Drawing.Font("Arial Narrow", 15.75F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label22.ForeColor = System.Drawing.Color.White;
            this.label22.Location = new System.Drawing.Point(12, 562);
            this.label22.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label22.Name = "label22";
            this.label22.Size = new System.Drawing.Size(26, 31);
            this.label22.TabIndex = 36;
            this.label22.Text = "1";
            // 
            // label23
            // 
            this.label23.AutoSize = true;
            this.label23.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(33)))), ((int)(((byte)(33)))), ((int)(((byte)(33)))));
            this.label23.Font = new System.Drawing.Font("Arial Narrow", 15.75F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label23.ForeColor = System.Drawing.Color.White;
            this.label23.Location = new System.Drawing.Point(12, 486);
            this.label23.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label23.Name = "label23";
            this.label23.Size = new System.Drawing.Size(26, 31);
            this.label23.TabIndex = 37;
            this.label23.Text = "2";
            // 
            // label24
            // 
            this.label24.AutoSize = true;
            this.label24.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(33)))), ((int)(((byte)(33)))), ((int)(((byte)(33)))));
            this.label24.Font = new System.Drawing.Font("Arial Narrow", 15.75F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label24.ForeColor = System.Drawing.Color.White;
            this.label24.Location = new System.Drawing.Point(12, 410);
            this.label24.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label24.Name = "label24";
            this.label24.Size = new System.Drawing.Size(26, 31);
            this.label24.TabIndex = 38;
            this.label24.Text = "3";
            // 
            // label25
            // 
            this.label25.AutoSize = true;
            this.label25.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(33)))), ((int)(((byte)(33)))), ((int)(((byte)(33)))));
            this.label25.Font = new System.Drawing.Font("Arial Narrow", 15.75F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label25.ForeColor = System.Drawing.Color.White;
            this.label25.Location = new System.Drawing.Point(12, 182);
            this.label25.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label25.Name = "label25";
            this.label25.Size = new System.Drawing.Size(26, 31);
            this.label25.TabIndex = 39;
            this.label25.Text = "6";
            // 
            // label26
            // 
            this.label26.AutoSize = true;
            this.label26.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(33)))), ((int)(((byte)(33)))), ((int)(((byte)(33)))));
            this.label26.Font = new System.Drawing.Font("Arial Narrow", 15.75F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label26.ForeColor = System.Drawing.Color.White;
            this.label26.Location = new System.Drawing.Point(12, 106);
            this.label26.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label26.Name = "label26";
            this.label26.Size = new System.Drawing.Size(26, 31);
            this.label26.TabIndex = 41;
            this.label26.Text = "7";
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 16F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(1445, 740);
            this.Controls.Add(this.panel1);
            this.Controls.Add(this.GameFileBorder2);
            this.Controls.Add(this.GameRankBorder1);
            this.Controls.Add(this.GameFileBorder1);
            this.Controls.Add(this.GameSavedErrorLbl);
            this.Controls.Add(this.LoadGameBtn);
            this.Controls.Add(this.GameSavedSuccessLbl);
            this.Controls.Add(this.SaveGameBtn);
            this.Controls.Add(this.loadingLbl);
            this.Controls.Add(this.DesignVerBtn);
            this.Controls.Add(this.RedoBtn);
            this.Controls.Add(this.UndoBtn);
            this.Controls.Add(this.MovesRestoreError);
            this.Controls.Add(this.LogHistory);
            this.Controls.Add(this.LoadMoves);
            this.Controls.Add(this.lblEngineCalc);
            this.Controls.Add(this.lblWaiting);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.lblCurrentPlayer);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.lblResult);
            this.Controls.Add(this.lblMove);
            this.Controls.Add(this.btnBoard);
            this.ForeColor = System.Drawing.SystemColors.ActiveCaptionText;
            this.KeyPreview = true;
            this.Margin = new System.Windows.Forms.Padding(4);
            this.MaximizeBox = false;
            this.Name = "Form1";
            this.Text = "Chess Graphics";
            this.FormClosed += new System.Windows.Forms.FormClosedEventHandler(this.Form1_FormClosed);
            this.Load += new System.EventHandler(this.Form1_Load);
            this.KeyDown += new System.Windows.Forms.KeyEventHandler(this.Form1_KeyDown);
            this.GameFileBorder1.ResumeLayout(false);
            this.GameFileBorder1.PerformLayout();
            this.GameRankBorder1.ResumeLayout(false);
            this.GameRankBorder1.PerformLayout();
            this.GameFileBorder2.ResumeLayout(false);
            this.GameFileBorder2.PerformLayout();
            this.panel1.ResumeLayout(false);
            this.panel1.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button btnBoard;
        private System.Windows.Forms.Label lblMove;
        private System.Windows.Forms.Label lblResult;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label lblCurrentPlayer;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label lblWaiting;
        private System.Windows.Forms.Label lblEngineCalc;
        private System.Windows.Forms.Label label11;
        private System.Windows.Forms.Label label12;
        private System.Windows.Forms.Label label13;
        private System.Windows.Forms.Label label14;
        private System.Windows.Forms.Label label15;
        private System.Windows.Forms.Label label16;
        private System.Windows.Forms.Label label17;
        private System.Windows.Forms.Label label18;
        private System.Windows.Forms.Button LoadMoves;
        private System.Windows.Forms.Button LogHistory;
        private System.Windows.Forms.Label MovesRestoreError;
        private System.Windows.Forms.Button UndoBtn;
        private System.Windows.Forms.Button RedoBtn;
        private System.Windows.Forms.Button DesignVerBtn;
        private System.Windows.Forms.Label loadingLbl;
        private System.Windows.Forms.Button SaveGameBtn;
        private System.Windows.Forms.Label GameSavedSuccessLbl;
        private System.Windows.Forms.Button LoadGameBtn;
        private System.Windows.Forms.Label GameSavedErrorLbl;
        private System.Windows.Forms.Panel GameFileBorder1;
        private System.Windows.Forms.Panel GameRankBorder1;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.Label label7;
        private System.Windows.Forms.Label label8;
        private System.Windows.Forms.Label label9;
        private System.Windows.Forms.Label label10;
        private System.Windows.Forms.Panel GameFileBorder2;
        private System.Windows.Forms.Label label27;
        private System.Windows.Forms.Label label28;
        private System.Windows.Forms.Label label29;
        private System.Windows.Forms.Label label30;
        private System.Windows.Forms.Label label31;
        private System.Windows.Forms.Label label32;
        private System.Windows.Forms.Label label33;
        private System.Windows.Forms.Label label34;
        private System.Windows.Forms.Panel panel1;
        private System.Windows.Forms.Label label19;
        private System.Windows.Forms.Label label20;
        private System.Windows.Forms.Label label21;
        private System.Windows.Forms.Label label22;
        private System.Windows.Forms.Label label23;
        private System.Windows.Forms.Label label24;
        private System.Windows.Forms.Label label25;
        private System.Windows.Forms.Label label26;
    }
}

