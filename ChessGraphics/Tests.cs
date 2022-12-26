using chessGraphics;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ChessGraphics
{
    internal class Tests
    {
        Form1 form;
        public Tests(Form1 form)
        {
            this.form = form;
        }

        public void CheckMate(int delay = 0)
        {
            form.MakeMoves("f2f4f7f5d2d4c7c6d1d3c6c5d4c5e7e6d3f5e6e5f5e5e8f7e5b8b7b6b8a8b6b5a8a7b5b4a7d7f7g6d7d8b4b3d8c8b3a2a1a2h7h6c8f8g6h7f8f5g7g6f5f8h6h5f8c8h7g7f4f5g7f7c8c6f7f8c6g6f8e7g6g8e7d7g8h8d7c7h8h5c7d7a2a7d7d8h5f7d8c8f7e8"
                , delay);
        }

        /**
        * a test with promotions in the middle of the game
        * the tests pass if the game ends with white winning with checkmate
        * in order for the test to pass, the first promotion should be a Knight, and Queen for the second
        */
        public void CheckMateWithPromotions(int delay = 0)
        {
            form.MakeMoves("d2d4e7e5d1d3c7c5d4d5e5e4d3e4d8e7e4h7b7b6d5d6b6b5d6e7f7f6e7f8e8d8f8g6c5c4a2a4b8c6a4b5a7a6b5a6a8b8a6a7b8b7a7a8b7b8a8b8c6e7b8d6c8a6d6a6d7d6a6d6d8c8d6e7f6f5e7g7g8e7g7e7h8f8e7f8"
                , delay);
        }

        public void Tie(int delay = 0)
        {
            form.MakeMoves("e2e4d7d5d1g4f7f6g4g7f6f5g7h8f5f4h8h7f4f3g2f3g8h6h7h6e7e6h6e6f8e7e6a6d8d6a6a7d6h6a7a8h6h2a8a7h2h1a7a8h1g1a8a7g1g3a7a8g3f3a8a7f3a3a7a8a3a2a8a7a2a1a7a8a1b1a8b8b1b2b8b7b2c2b7c7c2d2e1d2e7h4c7b7h4f2b7b8f2c5b8a8c5a3a8b8a3c1d2e1d5e4b8b7c8h3b7a7h3f1e1f1c1e3f1e2e3f2e2f2e4e3f2e3e8d8a7d7d8d7"
                , delay);
        }

        public void Stalemate(int delay = 0)
        {
            form.MakeMoves("d2d4e7e5d4e5d7d5d1d5c7c6d5c6e8e7c6b7e7e8b7b8c8d7b8a8d7c8a8c8a7a6c8a8a6a5a8a5d8a8a5a8e8e7a8c8f7f6c8b8e7d7b8f8d7c7f8g8c7d7g8h8d7c7h8h7f6f5h7g7c7c8g7g5f5f4g5f4c8b8e5e6b8c8e6e7c8d7h2h3d7e7f4f5e7d8f5f4d8c8f4f5c8b8f5e5b8c8e5d5c8b8c1f4b8c8f4e5"
                , delay);
        }
    }
}
