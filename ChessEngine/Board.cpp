#pragma warning(disable : 6011)

#include "EmptyPiece.h"
#include <windows.h> // WinApi header
#include "Board.h"
#include "Queen.h"
#include "Rook.h"
#include "Bishop.h"
#include "Knight.h"
#include "Pawn.h"
#include <fstream>

string Board::getLocation(int index)
{
	return getLocation(index / BOARD_SIZE, index % BOARD_SIZE);
}

string Board::getLocation(int row, int col)
{
	// BOARD_SIZE - row because we start from top
	return string(1, col + 'a') + (char)((BOARD_SIZE - row) + '0');
}

string Board::getLocation(const char file, const char rank)
{
	return string(1, file) + rank;
}

string Board::getLocation(const char file, const int rank)
{
	return getLocation(file, (char)(rank + '0'));
}

int Board::getIndex(const string& location)
{
	return getIndex(BOARD_SIZE - (location[1] - '0'), location[0] - 'a');
}

int Board::getIndex(const int row, const int col)
{
	return row * BOARD_SIZE + col;
}

Board::Board(const string& board, const string& filePath)
{

	// last char is which player is starting
	_currentPlayer = board[BOARD_SIZE * BOARD_SIZE] - '0';
	_board = board;
	_board.pop_back(); // remove the starting player char

	// initiate our 2 players's objects
	_players[WHITE_PLAYER] = new Player(this, WHITE_PLAYER);
	_players[BLACK_PLAYER] = new Player(this, BLACK_PLAYER);
}

Board::~Board()
{
	// free the memory of our players
	delete _players[WHITE_PLAYER];
	delete _players[BLACK_PLAYER];

	// clear board's string
	_board.clear();
}

string Board::getAllPossibleMoves(Piece& src, Player* player)
{
	int i = 0, j = 0;
	Piece* dest;
	Player* enemy = getEnemy(player == nullptr ? &getCurrentPlayer() : src.getOwner());
	string locations = "";

	if (src.getType() == EMPTY_PIECE) // empty piece may not move anywere..
	{
		return "";
	}

	for (i = 0; i < BOARD_SIZE; i++)
	{
		for (j = 0; j < BOARD_SIZE; j++)
		{
			dest = getPiece(i, j);

			// if its a valid move and not a "self-check"
			if (isValidMove(validateMove(player == nullptr ? getCurrentPlayer() : *player, src, *dest)) && !moveWillCauseCheck(src, *dest))
			{
				// push valid move's location
				locations += dest->getLocation();
			}

			if (dest->getType() == EMPTY_PIECE)
			{
				delete dest; // free Piece's memory after use
			}
		}
	}

	return locations;
}

bool Board::moveWillCauseCheck(Piece& src, Piece& dest)
{
	Move move(&src, &dest, this);
	Player* enemy = getEnemy(src.getOwner());

	// if move caused chess - its an invalid move
	move.make();
	bool enemyDidChess = madeCheck(enemy);
	move.undo();

	return enemyDidChess;
}

string& Board::getBoard()
{
	return _board;
}

Player** Board::getPlayers()
{
	return _players;
}

const std::stack<Move*>& Board::getMovesStack() const
{
	return _movesHistory;
}

string Board::getMoveHistory()
{
	string result = "";
	Move* cur = nullptr;
	std::stack<Move*> copy = _movesHistory;

	while (!copy.empty())
	{
		cur = copy.top();

		// + result at the end because a stack is last in first out (reversed)
		result = cur->getSrc() + cur->getDest() + result;
		copy.pop();
	}

	return result;
}

void Board::pushMove(Move* move)
{
	_movesHistory.push(move);
}

void Board::shiftCurrentPlayer()
{
	_currentPlayer = (_currentPlayer + 1) % CHESS_PLAYERS;
}

Move* Board::undoMove()
{
	Move* lastMove = nullptr;
	Piece* capturedPiece = nullptr;

	if (_movesHistory.size() == 0)
	{
		return nullptr;
	}

	lastMove = _movesHistory.top();
	capturedPiece = lastMove->getCaptured();

	lastMove->undo(false);
	shiftCurrentPlayer();

	// remove move from history
	_movesHistory.pop();
	// push "undo"ed move into the "redo" stack so user will be able to redo aswell
	_movesRedo.push(lastMove);
	return lastMove;
}
Move* Board::redoMove()
{
	if (_movesRedo.size() == 0)
	{
		return nullptr;
	}
	Move* lastMove = _movesRedo.top();

	// remove move from "redo" history and transfer it into normal moves history
	_movesRedo.pop();
	_movesHistory.push(lastMove);

	return lastMove;
}

Player& Board::getCurrentPlayer() const
{
	return *_players[_currentPlayer];
}

Player* Board::getEnemy(Player* player) const
{
	return _players[!player->getType()];
}

int Board::validateMove(Player& currentPlayer, Piece& src, Piece& dest) const
{
	int moveCode = src.basicValidateMove(currentPlayer, dest);
	if (moveCode == VALID_MOVE)
	{
		moveCode = src.validateMove(dest);
	}

	return moveCode;
}

bool Board::isValidMove(const int& moveCode) const
{
	return moveCode == VALID_MOVE || moveCode == VALID_PAWN_PROMOTION || moveCode == VALID_EN_PASSANT || moveCode == VALID_CASTLE;
}

bool Board::madeCheck(Player* player)
{
	int i = 0;

	Piece* src = nullptr;
	bool didCheck = false;
	int moveCode = 0;
	std::vector<Piece*> pieces = player->getPieces();

	// get the enemy's king
	Piece* king = getEnemy(player)->getKing();

	// loop through the board to check if any of the player's pieces
	// can make a valid move against the enemy king, if yes, its a check.
	for (i = 0; i < pieces.size() && !didCheck; i++)
	{
		// we found one of our player's pieces, lets save it
		src = pieces[i];
		if (!src->isCaptured())
		{
			// if all checks passed, its a "check"!
			didCheck = isValidMove(validateMove(*player, *src, *king));
		}
	}

	// return final result
	return didCheck;
}

int Board::checkmateOrStalemate(Player* player)
{
	int i = 0, j = 0;
	bool isCheck = false, isCheckmate = false, isStalemate = false;
	Player* enemy = getEnemy(player);
	Piece *src = nullptr, *dest = nullptr;
	std::vector<Piece*>& pieces = player->getPieces(), & enemyPieces = enemy->getPieces();

	// First, check if the player has made a "check" and update flags accordingly
	if (madeCheck(player))
	{
		isCheckmate = true;
		isCheck = true;
	}
	else
	{
		isStalemate = true;
	}

	// loop through the board to get the enemey king's piece
	for (i = 0; i < enemyPieces.size() && (isCheckmate || isStalemate); i++)
	{
		src = enemyPieces[i];
		if (!src->isCaptured())
		{
			string locations = getAllPossibleMoves(*src, enemy);

			if (locations.length() > 0)
			{
				// if he has atleast one valid move, it cant be neither a stale mate nor a checkmate
				isCheckmate = false;
				isStalemate = false;
			}
		}
	}

	// If none of the player's moves allow them to escape the "check",
	// then the player has made a checkmate and the function should
	// return true
	return isCheckmate ? VALID_CHECKMATE : isStalemate ? VALID_STALEMATE : isCheck ? VALID_CHECK : INVALID_CHECKMATE_STALEMATE;
}

bool Board::isInsufficientMaterial()
{
	Player* whitePlayer = _players[WHITE_PLAYER], * blackPlayer = _players[BLACK_PLAYER];
	Piece* piece = nullptr;
	std::vector<Piece*> whitePieces = whitePlayer->getPieces(), blackPieces = blackPlayer->getPieces();
	bool whiteKingFound = false, blackKingFound = false;
	int whitePiecesAmount = 0, blackPiecesAmount = 0;
	int i = 0;

	for (i = 0; i < whitePieces.size(); i++)
	{
		piece = whitePieces[i];
		if (!piece->isCaptured())
		{
			whitePiecesAmount++;
			if (piece->getType() == KING)
			{
				whiteKingFound = true;
			}
		}
	}

	for (i = 0; i < blackPieces.size(); i++)
	{
		piece = blackPieces[i];
		if (!piece->isCaptured())
		{
			blackPiecesAmount++;
			if (piece->getType() == KING)
			{
				blackKingFound = true;
			}
		}
	}

	// possible todo - check for more possible insufficient material cases

	// check if only kings left on the board - its a tie
	return whiteKingFound && blackKingFound && whitePiecesAmount == 1 && blackPiecesAmount == 1;
}


int Board::movePiece(Piece& src, Piece& dest, Move& move)
{
	move.make();

	// check if either one of sides did "check"
	// and whether they made a "self-check" or not
	bool whiteDidChess = madeCheck(_players[WHITE_PLAYER]);
	bool blackDidChess = madeCheck(_players[BLACK_PLAYER]);
	bool whitePlayer = src.getOwner()->getType() == WHITE_PLAYER;

	// if its a "self-check"
	if ((whiteDidChess && !whitePlayer) || (blackDidChess && whitePlayer))
	{
		// restore our board state and return an invalid move
		move.undo();
		return INVALID_SELF_CHECK;
	}

	if (_movesHistory.empty() || (!_movesHistory.empty() && &move != _movesHistory.top()))
	{
		pushMove(&move); // push move to history only if its not a "redo" move

		// a move has occured, therefore clear the "redo" stack
		while (!_movesRedo.empty())
		{
			_movesRedo.pop();
		}
	}

	// piece moved, therefore it should be true
	src.setMoved(true);

	// check if game is over by either checkmate, stalemate or insufficient material draw
	int endgameStatus = isInsufficientMaterial() ? VALID_INSUFFICIENT_MATERIAL : VALID_MOVE;
	if (endgameStatus == VALID_MOVE)
	{
		endgameStatus = checkmateOrStalemate(src.getOwner());
	}

	if (endgameStatus == VALID_INSUFFICIENT_MATERIAL || endgameStatus == VALID_CHECKMATE || endgameStatus == VALID_STALEMATE)
	{
		return endgameStatus;
	}

	shiftCurrentPlayer();
	// switch turn from black to white and vice versa

	return (whiteDidChess || blackDidChess) ? VALID_CHECK : VALID_MOVE;
}

int Board::promotePiece(Piece* promoted, char newType)
{
	Player* player = promoted->getOwner();
	std::vector<Piece*>& pieces = player->getPieces();
	string location = promoted->getLocation();
	Piece* newPiece = nullptr;
	int i = 0;
	bool foundPiece = false;
	int result = 0;

	for (i = 0; i < pieces.size() && !foundPiece; i++)
	{
		foundPiece = pieces[i]->getLocation() == location;
	}

	i--; // to get the index of pieces in which "promoted" is in

	switch (newType)
	{
	case QUEEN:
		newPiece = new Queen(player, location);
		break;
	case ROOK:
		newPiece = new Rook(player, location);
		break;
	case BISHOP:
		newPiece = new Bishop(player, location);
		break;
	case KNIGHT:
		newPiece = new Knight(player, location);
		break;
	default:
		// a default "promotion"
		newPiece = new Pawn(player, location);
	}

	delete promoted;										  // we dont need this piece anymore
	pieces[i] = newPiece;									  // assign our new promoted piece to the pieces vector
	_board[newPiece->getIndex()] = newPiece->getIdentifier(); // update the board

	// check if promotion caused check/checkmate/stalemate

	int endgameStatus = checkmateOrStalemate(player);
	if (endgameStatus == VALID_CHECKMATE || endgameStatus == VALID_STALEMATE || endgameStatus == VALID_CHECK)
	{
		result = endgameStatus;
	}
	else
	{
		result = SUCCESSFUL_PROMOTION;
	}

	return result;
}

Piece* Board::getPiece(const string location) const
{
	int i = 0;
	int index = getIndex(location); // get numeric location
	Piece* piece = nullptr;
	Player* player = isupper(_board[index]) ? _players[WHITE_PLAYER] : _players[BLACK_PLAYER];
	std::vector<Piece*> pieces = player->getPieces();

	if (_board[index] == EMPTY_PIECE)
	{
		// create an empty piece object
		piece = new EmptyPiece(nullptr, location);
	}
	else
	{
		for (i = 0; i < pieces.size(); i++)
		{
			if (pieces[i]->getLocation() == location && !pieces[i]->isCaptured())
			{
				piece = pieces[i];
			}
		}
	}

	return piece;
}

Piece* Board::getPiece(const int index) const
{
	return getPiece(getLocation(index));
}

Piece* Board::getPiece(const int row, const int col) const
{
	return getPiece(getLocation(row, col));
}