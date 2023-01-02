using ChessClient;
using System;
using System.Windows.Forms;

namespace chessClient
{
    public class ServerPipe
    {
        readonly Socket socket;

        public ServerPipe()
        {
            socket = new Socket("127.0.0.1", 18079);
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
                catch (Exception) {}
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