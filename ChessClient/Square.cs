using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace chessClient
{
    public class Square
    {
        int _colIndex;
        int _rowIndex;

        public Square(int row, int col)
        {
            _rowIndex = row;
            _colIndex = col;
        }

        public Square(string location)
        {
            _rowIndex = 8 - (location[1] - '0');
            _colIndex = location[0] - 'a';
        }

        public int Row
        {
            get { return _rowIndex; }
        }

        public int Col
        {
            get { return _colIndex; }
        }

        public override string ToString()
        {
            return Convert.ToChar('a' + _colIndex).ToString() + (8 - _rowIndex).ToString();
        }
    }
}
