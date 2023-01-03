using System;
using System.Windows.Forms;
using ChessClient;
using System.Diagnostics;
using System.IO;
using System.Collections.Generic;
using System.Linq;

namespace chessClient
{
    static class Program
    {
        private static object CreateByTypeName(string typeName)
        {
            // scan for the class type
            var type = (from assembly in AppDomain.CurrentDomain.GetAssemblies()
                        from t in assembly.GetTypes()
                        where t.Name == typeName  // you could use the t.FullName as well
                        select t).FirstOrDefault();

            if (type == null)
                throw new InvalidOperationException("Type not found");

            return Activator.CreateInstance(type);
        }

        /// <summary>
        /// The main entry point for the application.
        /// </summary>
        [STAThread]
        static void Main(string[] args)
        {
            Application.EnableVisualStyles();
            Application.SetCompatibleTextRenderingDefault(false);

            var modes = new Dictionary<string, string>()
            {
                { "Online",  "OnlineGameForm" },
                { "Offline",  "OfflineGameForm" }
            };

            // force offline mode if game was loaded from file
            string GameMode = args.Length > 0 ? "Offline" : new ModeSelection().GetResult();

            if (modes.ContainsKey(GameMode))
            {
                // start the game's engine
                Process engineProcess = Process.Start(Path.Combine(Application.StartupPath, "ChessEngine.exe"));
                Application.Run((Form)CreateByTypeName(modes[GameMode]));

                if (!engineProcess.HasExited)
                {
                    // kill process after use incase form failed to do so
                    engineProcess.Kill();
                    engineProcess.Close();
                }
            }
        }
    }
}
