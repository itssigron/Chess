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


namespace chessGraphics
{
    public class pipe
    {
        NamedPipeServerStream pipeServer = null;
        StreamString ss;
        int pipeNumber;

        public pipe()
        {
            pipeNumber = 1;
            while(pipeServer == null)
            {
                try
                {
                    pipeServer = new NamedPipeServerStream("chessPipe" + pipeNumber++, PipeDirection.InOut, 1);
                }
                catch (Exception)
                {

                }
            }
            ss = new StreamString(pipeServer);


        }

        public bool connect()
        {

            // Wait for a client to connect
            pipeServer.WaitForConnection();

            return pipeServer.IsConnected;
        }

        public bool isConnected()
        {
            return pipeServer.IsConnected;
        }

        public string getEngineMessage()
        {
            return isConnected() ? ss.getStringFromEngine() : "";
        }

        public void sendEngineMove(string move)
        {
            if (!isConnected())
                return;

            ss.sendMoveToEngine(move);
        }

        public void close()
        {
            pipeServer.Close();
        }
    }



    public class StreamString
    {
        private Stream ioStream;
        private Encoding streamEncoding;

        public StreamString(Stream ioStream)
        {
            this.ioStream = ioStream;
            streamEncoding = new ASCIIEncoding();
        }

        public string getStringFromEngine()
        {
            // protocol:
            // 0  - valid move
            // 1  - valid move (you made check)
            // 2  - valid move, pawn should get promoted
            // 3  - invalid move (not your player)
            // 4  - invalid move (destination is not free)
            // 5  - invalid move (check will occur)
            // 6  - invalid move (out of bounds)
            // 7  - invalid move (illegal movement with piece)
            // 8  - invalid move - source and dest are equal
            // 9  - check mate
            // 10 - stale mate (tie)
            // 11 - insufficient material (tie)
            // 12 - prevoius pawn promotion was valid and approved

            byte[] inBuffer = new byte[1024];
            ioStream.Read(inBuffer, 0, 1024);


            String MyString = Encoding.ASCII.GetString(inBuffer).TrimEnd((Char)0);
            string res = Encoding.ASCII.GetString(inBuffer).TrimEnd((Char)0);
            Debug.WriteLine("[ENGINE]: " + res);

            return res;
        }

        public void sendMoveToEngine(string outString)
        {
            byte[] t = Encoding.ASCII.GetBytes(outString);
            byte[] inBuffer = new byte[t.Length + 1];

            Debug.WriteLine("[GRAPHICS]: " + outString);
            for (int i = 0; i < t.Length; i++)
            {
                inBuffer[i] = t[i];
            }
            inBuffer[inBuffer.Length - 1] = 0;

            try
            {
                ioStream.Write(inBuffer, 0, inBuffer.Length);

                ioStream.Flush();
            }
            catch
            {

            }
        }
    }

}
