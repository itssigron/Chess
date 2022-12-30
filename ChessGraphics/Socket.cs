using System;
using System.IO;
using System.Linq;
using System.Net;
using System.Net.Sockets;
using System.Text;
using System.Windows.Forms;

namespace ChessGraphics
{
    internal class Socket
    {
        private TcpClient client;
        // Get a client stream for reading and writing.
        private NetworkStream stream;
        private string ip;
        private int port;
        public Socket(string ip, int port)
        {
            this.ip = ip;
            this.port = port;
        }

        public bool isConnected()
        {
            return client == null ? false : client.Connected;
        }

        public bool connect()
        {
            if (client == null || client.Connected == false)
            {
                client = new TcpClient(ip, port);
                stream = client.GetStream();

                return client.Connected;
            }
            {
                throw new Exception("The client is already connected.");
            }
        }

        public void Send(string message)
        {
            message += ".";
            // Translate the passed message into ASCII and store it as a Byte array.
            Byte[] data = Encoding.ASCII.GetBytes(message);

            // Send the message to the connected TcpServer.
            stream.Write(data, 0, data.Length);

            Console.WriteLine("Sent: {0}", message);
        }

        public string Recv()
        {
            string result = "";

            // Receive messages until a dot is encountered
            while (true)
            {
                // Receive a single byte
                Byte[] data = new Byte[1];
                int bytesReceived = stream.Read(data, 0, 1);
                if (bytesReceived == 0)
                {
                    // Connection closed by server
                    break;
                }

                // Append the received byte to the message
                string s = Encoding.ASCII.GetString(data);

                // Check if the message is complete (ends with a dot)
                if (s == ".")
                {
                    break;
                }

                result += s;
            }

            Console.WriteLine("Received: {0}", result);

            return result;
        }

        public void close()
        {
            client.Close();
        }
    }
}