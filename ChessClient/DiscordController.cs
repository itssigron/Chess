using DiscordRPC;
using System;
using System.Threading;

namespace ChessClient
{
    internal class DiscordController
    {
        // Initialize the Discord client
        private DiscordRpcClient client;

        public DiscordController(string clientId)
        {
            try
            {
                // Set the client ID and initialize the client
                client = new DiscordRpcClient(clientId);
            }
            catch (Exception) { }
        }

        public void Connect()
        {
            // Connect to Discord
            new Thread(() => { try { client.Initialize(); } catch (Exception) { } }).Start();
        }

        public void UpdatePresence(string gameState)
        {
            new Thread(() =>
            {
                try
                {
                    // Set the rich presence information
                    RichPresence presence = new RichPresence()
                    {
                        Details = "Playing chess",
                        State = gameState,
                        Assets = new Assets()
                        {
                            LargeImageKey = "chess-cover",
                            LargeImageText = "Sigron's Chess Game"
                        }
                    };
                    client.SetPresence(presence);
                }
                catch (Exception) { }
            }).Start();
        }
    }
}
