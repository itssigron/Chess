using System;
using System.Windows.Forms;
using ChessClient;
using System.Diagnostics;
using System.IO;

namespace chessClient
{
    static class Program
    {
        /// <summary>
        /// The main entry point for the application.
        /// </summary>
        [STAThread]
        static void Main()
        {
            Application.EnableVisualStyles();
            Application.SetCompatibleTextRenderingDefault(false);

            string GameMode = new ModeSelection().GetResult();

            if (GameMode == "Online")
            {
                Application.Run(new OnlineGameForm());
            }
            else
            {
                Process.Start(Path.Combine(Application.StartupPath, "ChessOffline.exe"));
                Application.Run(new OfflineGameForm());
            }
        }
    }
}
