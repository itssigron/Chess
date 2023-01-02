using ChessClient;
using System;
using System.Windows.Forms;

namespace chessClient
{
    public class OnlinePipe
    {
        readonly Socket socket;

        public OnlinePipe()
        {
            socket = new Socket("20.21.96.201", 5555);
        }

        public bool Connect()
        {
            return socket.Connect();
        }

        public bool IsConnected()
        {
            return socket.IsConnected();
        }

        public string GetEngineMessage()
        {
            bool connected = IsConnected();
            string res = "";

            if (connected)
            {
                try
                {
                    res = socket.Recv();
                }
                catch (Exception)
                {
                    connected = false;
                }
            }

            if(!connected)
            {
                MessageBox.Show("The connection to the server has been lost.");
                Environment.Exit(0);
            }

            return res;
        }

        public void SendEngineMove(string move)
        {
            if (!IsConnected())
                return;

            socket.Send(move);
        }

        public void Close()
        {
            socket.Close();
        }
    }
}