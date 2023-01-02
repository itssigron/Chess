namespace ChessClient
{
    partial class LoadMovesPrompt
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
            this.MovesInput = new System.Windows.Forms.TextBox();
            this.DelayInput = new System.Windows.Forms.NumericUpDown();
            this.label1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.confirm = new System.Windows.Forms.Button();
            this.errorLabel = new System.Windows.Forms.Label();
            this.movesErrorLabel = new System.Windows.Forms.Label();
            ((System.ComponentModel.ISupportInitialize)(this.DelayInput)).BeginInit();
            this.SuspendLayout();
            // 
            // MovesInput
            // 
            this.MovesInput.Location = new System.Drawing.Point(15, 48);
            this.MovesInput.Name = "MovesInput";
            this.MovesInput.Size = new System.Drawing.Size(773, 20);
            this.MovesInput.TabIndex = 0;
            // 
            // DelayInput
            // 
            this.DelayInput.ImeMode = System.Windows.Forms.ImeMode.NoControl;
            this.DelayInput.Location = new System.Drawing.Point(15, 110);
            this.DelayInput.Maximum = new decimal(new int[] {
            10000,
            0,
            0,
            0});
            this.DelayInput.Name = "DelayInput";
            this.DelayInput.Size = new System.Drawing.Size(120, 20);
            this.DelayInput.TabIndex = 2;
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Font = new System.Drawing.Font("Microsoft Sans Serif", 11F);
            this.label1.Location = new System.Drawing.Point(12, 18);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(271, 18);
            this.label1.TabIndex = 3;
            this.label1.Text = "Please enter the moves you wish to run:";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Font = new System.Drawing.Font("Microsoft Sans Serif", 11F);
            this.label2.Location = new System.Drawing.Point(12, 80);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(385, 18);
            this.label2.TabIndex = 4;
            this.label2.Text = "Please enter the delay in ms before executing each move.";
            // 
            // confirm
            // 
            this.confirm.Font = new System.Drawing.Font("Microsoft Sans Serif", 10F);
            this.confirm.Location = new System.Drawing.Point(728, 130);
            this.confirm.Margin = new System.Windows.Forms.Padding(2);
            this.confirm.Name = "confirm";
            this.confirm.Size = new System.Drawing.Size(96, 28);
            this.confirm.TabIndex = 5;
            this.confirm.Text = "Load Moves";
            this.confirm.UseVisualStyleBackColor = true;
            this.confirm.Click += new System.EventHandler(this.Confirm_Click);
            // 
            // errorLabel
            // 
            this.errorLabel.AutoSize = true;
            this.errorLabel.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F);
            this.errorLabel.ForeColor = System.Drawing.Color.Red;
            this.errorLabel.Location = new System.Drawing.Point(315, 18);
            this.errorLabel.Name = "errorLabel";
            this.errorLabel.Size = new System.Drawing.Size(141, 20);
            this.errorLabel.TabIndex = 6;
            this.errorLabel.Text = "Please fill all inputs";
            this.errorLabel.Visible = false;
            // 
            // movesErrorLabel
            // 
            this.movesErrorLabel.AutoSize = true;
            this.movesErrorLabel.Font = new System.Drawing.Font("Microsoft Sans Serif", 11F);
            this.movesErrorLabel.ForeColor = System.Drawing.Color.Red;
            this.movesErrorLabel.Location = new System.Drawing.Point(316, 21);
            this.movesErrorLabel.Name = "movesErrorLabel";
            this.movesErrorLabel.Size = new System.Drawing.Size(348, 18);
            this.movesErrorLabel.TabIndex = 7;
            this.movesErrorLabel.Text = "The moves string doesn\'t not match the valid format";
            this.movesErrorLabel.Visible = false;
            // 
            // LoadMoves
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(835, 169);
            this.Controls.Add(this.movesErrorLabel);
            this.Controls.Add(this.errorLabel);
            this.Controls.Add(this.confirm);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.DelayInput);
            this.Controls.Add(this.MovesInput);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedDialog;
            this.KeyPreview = true;
            this.MaximizeBox = false;
            this.MinimizeBox = false;
            this.Name = "LoadMoves";
            this.Text = "User Prompt";
            this.TopMost = true;
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.LoadMoves_FormClosing);
            this.KeyDown += new System.Windows.Forms.KeyEventHandler(this.LoadMoves_KeyDown);
            ((System.ComponentModel.ISupportInitialize)(this.DelayInput)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.TextBox MovesInput;
        private System.Windows.Forms.NumericUpDown DelayInput;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Button confirm;
        private System.Windows.Forms.Label errorLabel;
        private System.Windows.Forms.Label movesErrorLabel;
    }
}