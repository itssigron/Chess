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
            // Set the client ID and initialize the client
            client = new DiscordRpcClient(clientId);

            // Register the events that you want to use
            client.OnReady += (sender, e) =>
            {
                Console.WriteLine("Discord: ready");
            };

            client.OnPresenceUpdate += (sender, e) =>
            {
                Console.WriteLine("Discord: presence update");
            };
        }

        public void Connect()
        {
            // Connect to Discord
            new Thread(() => client.Initialize()).Start();
        }

        public void UpdatePresence(string gameState)
        {
            new Thread(() =>
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
            }).Start();
        }
    }
}
