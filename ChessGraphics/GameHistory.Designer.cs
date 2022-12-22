namespace ChessGraphics
{
    partial class GameHistory
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
            this.GameHistoryText = new System.Windows.Forms.TextBox();
            this.SuspendLayout();
            // 
            // GameHistoryText
            // 
            this.GameHistoryText.Location = new System.Drawing.Point(12, 12);
            this.GameHistoryText.Name = "GameHistoryText";
            this.GameHistoryText.ReadOnly = true;
            this.GameHistoryText.Size = new System.Drawing.Size(1087, 22);
            this.GameHistoryText.TabIndex = 0;
            // 
            // GameHistory
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 16F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(1114, 48);
            this.Controls.Add(this.GameHistoryText);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedDialog;
            this.MaximizeBox = false;
            this.MinimizeBox = false;
            this.Name = "GameHistory";
            this.Text = "GameHistory";
            this.TopMost = true;
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.TextBox GameHistoryText;
    }
}