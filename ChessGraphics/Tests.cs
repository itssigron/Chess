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

        public void CheckMate(int delay)
        {
            form.MakeMoves("h2h4g8h6h4h5h6g4h5h6g4f2e1f2b8c6b1c3c6e5c3e4e5g4e4g3g4e5g3h5e5c4h5f4c4e5f4d3e5g4d3e2d3e1g4h2f2b6h2g4b6a5g4f2"
                , delay);
        }

        public void Tie(int delay)
        {
            form.MakeMoves("e2e4e7e5e1e3e8e6e3a7e6a2a7a8a2a1a8b8a1b1b8c8d8e7c8b7b1b2b7c7b2c2d1e1c2c1e1e2c1d2e2f3d2e1c7d7e7f6d7e8e1f1e8f8f1g1f8g8g1h1g8h8h1h2h8h7h2g2f3e3g2f2e3d3f2f4h7g7f6e6g7f7e6d6f7h5f4e4d3c3e4h4h5e5d6c6e5h5h4e4h5h4e4a4h4a4c6c5a4b5c5b5"
                , delay);
        }

        public void Stalemate(int delay)
        {
            form.MakeMoves("e2e4a7a5e1e3a5a4e3a3b7b6a3a4b6b5a4b5a8a7b5b8a7a8b8a8c7c6a8c6c8b7c6b7d7d6b7e7d8c8e7d6e8d8d6d8c8b7d8f8b7c7f8g8h7h6g8h8g7g6h8h6c7c8h6g6f7f6g6f6c8b8f6d4b8a8d2d3a8b8c1f4f4b8a8b8b8a8f4e5a8b7d4d5b7c8h2h4"
                , delay);
        }
    }
}
