using ChessClient;
using System;
using System.Windows.Forms;

namespace chessClient
{
    public class OnlinePipe
    {
        Socket socket;
        public int pipeNumber;

        public OnlinePipe()
        {
            socket = new Socket("20.21.96.201", 5555);
        }

        public bool connect()
        {
            return socket.connect();
        }

        public bool isConnected()
        {
            return socket.isConnected();
        }

        public string getEngineMessage()
        {
            bool connected = isConnected();
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

        public void sendEngineMove(string move)
        {
            if (!isConnected())
                return;

            socket.Send(move);
        }

        public void close()
        {
            socket.close();
        }
    }
}