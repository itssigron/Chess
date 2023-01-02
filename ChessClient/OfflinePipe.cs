using System;
using System.Text;
using System.IO.Pipes;
using System.IO;
using System.Diagnostics;


namespace chessClient
{
    public class OfflinePipe
    {
        readonly NamedPipeServerStream pipeServer = null;
        readonly StreamString ss;
        public int pipeNumber;

        public OfflinePipe()
        {
            pipeNumber = 1;
            while (pipeServer == null)
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

        public bool Connect()
        {

            // Wait for a client to connect
            pipeServer.WaitForConnection();

            return pipeServer.IsConnected;
        }

        public bool IsConnected()
        {
            return pipeServer.IsConnected;
        }

        public string GetEngineMessage()
        {
            return IsConnected() ? ss.GetStringFromEngine() : "";
        }

        public void SendEngineMove(string move)
        {
            if (!IsConnected())
                return;

            ss.SendMoveToEngine(move);
        }

        public void Close()
        {
            pipeServer.Close();
        }
    }



    public class StreamString
    {
        private readonly Stream ioStream;

        public StreamString(Stream ioStream)
        {
            this.ioStream = ioStream;
        }

        public string GetStringFromEngine()
        {
            byte[] inBuffer = new byte[1024];
            ioStream.Read(inBuffer, 0, 1024);

            return Encoding.ASCII.GetString(inBuffer).TrimEnd((Char)0);
        }

        public void SendMoveToEngine(string outString)
        {
            byte[] t = Encoding.ASCII.GetBytes(outString);
            byte[] inBuffer = new byte[t.Length + 1];

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
