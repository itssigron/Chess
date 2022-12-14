#include "Board.h"
#include "Rook.h"
#include "King.h"
#include "Queen.h"
#include "Bishop.h"
#include "Pawn.h"
#include "Knight.h"
#include "EmptyPiece.h"


string Board::getLocation(int& index)
{
	// calculate row and col by the index
	int row = index / BOARD_SIZE;
	int col = index % BOARD_SIZE;

	// BOARD_SIZE - row because we start from top
	return string(1, col + 'a') + (char)((BOARD_SIZE - row) + '0');
}

int Board::getIndex(string& location)
{
	return getIndex(BOARD_SIZE - (location[1] - '0'), location[0] - 'a');
}

int Board::getIndex(int row, int col)
{
	return row * BOARD_SIZE + col;
}

Board::Board(const string& board)
{
	// initiate our 2 players's objects
	_players[WHITE_PLAYER] = new Player(this, WHITE_PLAYER);
	_players[BLACK_PLAYER] = new Player(this, BLACK_PLAYER);

	// last char is which player is starting
	_currentPlayer = board[BOARD_SIZE * BOARD_SIZE] - '0';

	initBoard(); // allocate memory for board
	setBoard(board); //fill its places with pieces
}

Board::~Board()
{
	int i = 0;

	// loop through the board and free all of its memory
	for (i = 0; i < BOARD_SIZE * BOARD_SIZE; i++)
	{
		delete _board[i]; // free the current piece
	}
}

Piece** Board::getBoard()
{
	return _board;
}

Player** Board::getPlayers()
{
	return _players;
}

Player& Board::getCurrentPlayer() const
{
	return *_players[_currentPlayer];
}

void Board::setBoard(const string& board)
{
	int i = 0, j = 0;
	int index = 0;
	Player* player = nullptr; // store the current player
	string location = ""; // store the current location

	// loop through the board to initiate its values with pieces
	for (i = 0; i < BOARD_SIZE; i++)
	{
		for (j = 0; j < BOARD_SIZE; j++)
		{
			index = getIndex(i, j);
			location = Board::getLocation(index); //get stringifed location
			// calculate which player owns this piece
			player = isupper(board[index]) ? _players[WHITE_PLAYER] : _players[BLACK_PLAYER];

			// create the corresponding piece object
			switch (tolower(board[index]))
			{
			case ROOK:
				_board[index] = new Rook(player, location);
				break;
			case KNIGHT:
				_board[index] = new Knight(player, location);
				break;
			case BISHOP:
				_board[index] = new Bishop(player, location);
				break;
			case KING:
				_board[index] = new King(player, location);
				break;
			case QUEEN:
				_board[index] = new Queen(player, location);
				break;
			case PAWN:
				_board[index] = new Pawn(player, location);
				break;
			default:
				// create an empty piece object to represent an empty spot
				_board[index] = new EmptyPiece(nullptr, location);
				break;
			}
		}
	}
}

void Board::initBoard()
{
	int i = 0, j = 0;

	for (i = 0; i < BOARD_SIZE; i++)
	{
		for (j = 0; j < BOARD_SIZE; j++)
		{
			_board[getIndex(i, j)] = nullptr;
		}
	}
}

void Board::movePiece(Piece& src, Piece& dest)
{
	int i = 0, j = 0;
	int srcRow = 0, srcCol = 0;
	int destRow = 0, destCol = 0;
	int index = 0;

	for (i = 0; i < BOARD_SIZE; i++)
	{
		for (j = 0; j < BOARD_SIZE; j++)
		{
			index = getIndex(i, j);
			if (_board[index]->getLocation() == src.getLocation())
			{
				srcRow = i;
				srcCol = j;
			}
			if (_board[index]->getLocation() == dest.getLocation())
			{
				destRow = i;
				destCol = j;
			}
		}
	}

	// empty out source
	_board[getIndex(srcRow, srcCol)] = new EmptyPiece(nullptr, src.getLocation());

	src.setLocation(dest.getLocation()); //update location
	delete _board[getIndex(destRow, destCol)]; // free spot
	_board[getIndex(destRow, destCol)] = &src; // transfer source to dest

	// switch turn from black to white and vice versa
	_currentPlayer = (_currentPlayer + 1) % CHESS_PLAYERS;
}

Piece& Board::getPiece(string location) const
{
	int index = getIndex(location); //get numeric location
	return *_board[index];
}
