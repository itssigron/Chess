using ChessClient;

namespace chessClient
{
    public class OnlinePipe
    {
        Socket socket;
        public int pipeNumber;

        public OnlinePipe()
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