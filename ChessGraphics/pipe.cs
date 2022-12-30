using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.IO.Pipes;
using System.IO;
using System.Threading;
using System.Diagnostics;
using ChessGraphics;

namespace chessGraphics
{
    public class pipe
    {
        Socket socket;
        public int pipeNumber;

        public pipe()
        {
            socket = new Socket("127.0.0.1", 3000);
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
            return isConnected() ? socket.Recv() : "";
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