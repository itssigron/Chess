using System;
using System.Text;
using System.IO.Pipes;
using System.IO;
using System.Diagnostics;


namespace chessClient
{
    public class OfflinePipe
    {
        NamedPipeServerStream pipeServer = null;
        StreamString ss;
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
