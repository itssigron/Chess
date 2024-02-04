using System;
using System.IO;
using System.Linq;
using System.Net;
using System.Net.Sockets;
using System.Text;
using System.Windows.Forms;

namespace ChessClient
{
    internal class Socket
    {
        private TcpClient client;
        // Get a client stream for reading and writing.
        private NetworkStream stream;
        private readonly string ip;
        private readonly int port;
        public Socket(string ip, int port)
        {
            this.ip = ip;
            this.port = port;
        }

        public bool IsConnected()
        {
            return client != null && client.Connected;
        }

        public bool Connect()
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
            // Convert the message into ASCII and store it as a byte array
            byte[] messageBytes = Encoding.ASCII.GetBytes(message);

            // Get the size of the message
            ushort messageSize = (ushort)messageBytes.Length;
            byte[] sizeBytes = BitConverter.GetBytes(messageSize);

            // Send the size header
            stream.Write(sizeBytes, 0, sizeBytes.Length);

            // Send the actual message
            stream.Write(messageBytes, 0, messageBytes.Length);

            Console.WriteLine("Sent: {0}", message);
        }

        public string Recv()
        {
            // Receive the size header (first 2 bytes)
            byte[] sizeBytes = new byte[sizeof(ushort)];
            stream.Read(sizeBytes, 0, sizeBytes.Length);

            // Convert the size from network byte order to host byte order
            ushort messageSize = BitConverter.ToUInt16(sizeBytes, 0);

            // Receive the entire message based on the size received
            byte[] messageBytes = new byte[messageSize];
            stream.Read(messageBytes, 0, messageBytes.Length);

            // Convert the received message bytes to a string
            string result = Encoding.ASCII.GetString(messageBytes);

            Console.WriteLine("Received: {0}", result);

            return result;
        }

        public void Close()
        {
            client.Close();
        }
    }
}