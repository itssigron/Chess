#pragma warning(disable : 6011)

#include "EmptyPiece.h"
#include <windows.h> // WinApi header
#include "Board.h"
#include "Queen.h"
#include "Rook.h"
#include "Bishop.h"
#include "Knight.h"
#include "Pawn.h"

string Board::getLocation(int index)
{
	// Calculate row and col by the index
	int row = index / BOARD_SIZE;
	int col = index % BOARD_SIZE;

	// BOARD_SIZE - row because we start from top
	return string(1, col + 'a') + (char)((BOARD_SIZE - row) + '0');
}

string Board::getLocation(int row, int col)
{
	return getLocation(getIndex(row, col));
}

string Board::getAllPossibleMoves(Piece& src)
{
	Piece* dest;
	int i = 0, j = 0;
	string locations = "";
	string boardCopy = _board;
	string oldLocation = src.getLocation();
	Player* enemy = _players[WHITE_PLAYER] == src.getOwner() ? _players[BLACK_PLAYER] : _players[WHITE_PLAYER];

	for (i = 0; i < BOARD_SIZE; i++)
	{
		for (j = 0; j < BOARD_SIZE; j++)
		{
			dest = getPiece(getLocation(i, j));

			// make basic checks, if all basic checks passed, make
			// further checks with the current piece
			int result = src.basicValidateMove(getCurrentPlayer(), *dest);
			if (result == VALID_MOVE)
			{
				result = src.validateMove(*dest);
			}
			if (result == VALID_MOVE || result == VALID_PAWN_PROMOTION || result == VALID_EN_PASSANT || result == VALID_CASTLE)
			{
				// empty out source
				_board[src.getIndex()] = '#';

				// move source to desired destination
				_board[dest->getIndex()] = src.getIdentifier();

				src.setLocation(dest->getLocation()); // update piece location

				// if a capture was made, then perform the action on the player's pieces
				if (dest->getType() != EMPTY_PIECE)
				{
					dest->setCaptured(true);
				}

				bool enemyDidChess = madeChess(enemy);

				// restore our board state
				_board = boardCopy;
				src.setLocation(oldLocation);
				dest->setCaptured(false);

				// if its not a self-chess
				if (!enemyDidChess)
				{
					// push valid move's location
					locations += dest->getLocation();
				}
			}

			if (dest->getType() == EMPTY_PIECE)
			{
				delete dest; // free Piece's memory after use
			}
		}
	}

	return locations;
}

void Board::printAllValidLocations(Piece& src)
{
	Piece* dest;
	int i = 0, j = 0;
	string validMovesLocations = getAllPossibleMoves(src);

	for (i = 0; i < BOARD_SIZE; i++)
	{
		for (j = 0; j < BOARD_SIZE; j++)
		{
			dest = getPiece(getLocation(i, j));

			// if its the src, then print it in red
			if (dest->getLocation() == src.getLocation())
			{
				std::cout << "\033[0;31m" << *dest << "\033[0m";
			}
			else
			{
				if (validMovesLocations.find(dest->getLocation()) != string::npos)
				{
					// all valid moves should be printed in green (or blue if its a capture move)
					std::cout << (dest->getType() == EMPTY_PIECE ? "\033[0;32m" : "\033[0;34m") << *dest << "\033[0m";
				}
				else
				{
					std::cout << *dest;
				}
			}
			if (dest->getType() == EMPTY_PIECE)
			{
				delete dest; // free Piece's memory after use
			}
			std::cout << "  ";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

int Board::getIndex(const string& location)
{
	return getIndex(BOARD_SIZE - (location[1] - '0'), location[0] - 'a');
}

int Board::getIndex(const int row, const int col)
{
	return row * BOARD_SIZE + col;
}

Board::Board(const string& board)
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

	// update their location and restore board to its last state
	lastMove->getDestPiece()->setLocation(lastMove->getSrc());
	_board[getIndex(lastMove->getSrc())] = _board[getIndex(lastMove->getDest())];
	_board[getIndex(lastMove->getDest())] = (capturedPiece == nullptr || lastMove->isEnPassant()) ? EMPTY_PIECE : capturedPiece->getIdentifier();
	if (capturedPiece != nullptr)
	{
		capturedPiece->setCaptured(false); // un-capture this piece
		if (lastMove->isEnPassant())
		{
			_board[capturedPiece->getIndex()] = capturedPiece->getIdentifier();
		}
	}
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
	Piece* capturedPiece = lastMove->getCaptured();
	Piece* srcPiece = lastMove->getSrcPiece(), * destPiece = lastMove->getDestPiece();
	char identifier = srcPiece->getIdentifier();
	if (_board[getIndex(lastMove->getDest())] != EMPTY_PIECE)
	{
		lastMove->setCaptured(destPiece);
		getPiece(lastMove->getDest())->setCaptured(true);
	}
	else if (lastMove->isEnPassant())
	{
		int rowOffset = srcPiece->getOwner()->getType() == WHITE_PLAYER ? -1 : 1;
		string capturedPieceLocation = destPiece->getLocation();
		capturedPieceLocation[1] += rowOffset;
		capturedPiece = getPiece(capturedPieceLocation);
		capturedPiece->setCaptured(true);
		lastMove->setCaptured(capturedPiece);
		_board[getIndex(capturedPieceLocation)] = EMPTY_PIECE;
	}
	srcPiece->setLocation(lastMove->getDest()); // update piece location
	_board[getIndex(lastMove->getDest())] = identifier;
	_board[getIndex(lastMove->getSrc())] = EMPTY_PIECE;

	shiftCurrentPlayer();

	// remove move from "redo" history and transfer it into normal moves history
	_movesRedo.pop();
	_movesHistory.push(lastMove);

	return lastMove;
}

Player& Board::getCurrentPlayer() const
{
	return *_players[_currentPlayer];
}

bool Board::madeChess(Player* player)
{
	int i = 0;
	bool whitePlayer = player->getType() == WHITE_PLAYER;
	Player* enemy = _players[whitePlayer ? BLACK_PLAYER : WHITE_PLAYER];
	// enemy's king identifier
	char kingIdentifier = whitePlayer ? KING : toupper(KING);
	Piece* src = nullptr, * king = nullptr;
	bool didChess = false;
	int moveCode = 0;
	char type = ' ';
	std::vector<Piece*> pieces = player->getPieces();
	std::vector<Piece*> enemyPieces = enemy->getPieces();

	// loop through the board to get the enemey king's piece
	for (i = 0; i < enemyPieces.size() && king == nullptr; i++)
	{
		if (enemyPieces[i]->getIdentifier() == kingIdentifier)
		{
			king = enemyPieces[i];
		}
	}

	// loop through the board to check if any of the player's pieces
	// can make a valid move against the enemy king, if yes, its a chess.
	for (i = 0; i < pieces.size() && !didChess; i++)
	{
		// we found one of our player's pieces, lets save it
		src = pieces[i];
		if (!src->isCaptured())
		{
			type = src->getType();

			moveCode = src->basicValidateMove(*player, *king);
			if (moveCode == VALID_MOVE)
			{
				moveCode = src->validateMove(*king);
			}

			// if all checks passed, its a chess!
			if (moveCode == VALID_MOVE || moveCode == VALID_PAWN_PROMOTION || moveCode == VALID_EN_PASSANT || moveCode == VALID_CASTLE)
			{
				didChess = true;
			}
		}
	}

	// return final result
	return didChess;
}

int Board::checkmateOrStalemate(Player* player)
{
	int i = 0, j = 0;
	bool didCheckmate = false;
	bool isStalemate = false;
	bool isCheck = false;
	bool whitePlayer = player->getType() == WHITE_PLAYER;
	Player* enemy = _players[whitePlayer ? BLACK_PLAYER : WHITE_PLAYER];
	Piece* src = nullptr, * dest = nullptr;
	std::vector<Piece*> pieces = player->getPieces();
	std::vector<Piece*> enemyPieces = enemy->getPieces();

	// First, check if the player has made a chess and update flags accordingly
	if (madeChess(player))
	{
		didCheckmate = true;
		isCheck = true;
	}
	else
	{
		isStalemate = true;
	}

	// loop through the board to get the enemey king's piece
	for (i = 0; i < enemyPieces.size() && (didCheckmate || isStalemate); i++)
	{
		src = enemyPieces[i];
		if (!src->isCaptured())
		{

			// save a copy of our board incase of a self-chess
			string boardCopy = _board;
			string location = src->getLocation();

			// set and restore current player so moves for enemy will be valid
			shiftCurrentPlayer();
			string locations = getAllPossibleMoves(*src);
			shiftCurrentPlayer();

			if (locations.length() > 0)
			{
				// if he has atleast one valid move, it cant be a stale mate or checkmate
				didCheckmate = false;
				isStalemate = false;
			}
		}
	}

	// If none of the player's moves allow them to escape the chess,
	// then the player has made a checkmate and the function should
	// return true
	return didCheckmate ? VALID_CHECKMATE : isStalemate ? VALID_STALEMATE : isCheck ? VALID_CHESS : INVALID_CHECKMATE_STALEMATE;
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

	// todo - check for more possible insufficient material cases

	// check if only kings left on the board - its a tie
	return whiteKingFound && blackKingFound && whitePiecesAmount == 1 && blackPiecesAmount == 1;
}


int Board::movePiece(Piece& src, Piece& dest, Move& move)
{
	// save a copy of our board incase of a self-chess
	string boardCopy = _board;
	string oldLocation = src.getLocation();
	// empty out source
	_board[src.getIndex()] = EMPTY_PIECE;

	// move source to desired destination
	_board[dest.getIndex()] = src.getIdentifier();

	src.setLocation(dest.getLocation()); // update piece location

	// if a capture was made, then perform the action on the player's pieces
	if (dest.getType() != EMPTY_PIECE)
	{
		dest.setCaptured(true);
		move.setCaptured(&dest);
	}

	// check if either one of sides did chess
	// and whether they made a self chess or not
	bool whiteDidChess = madeChess(_players[WHITE_PLAYER]);
	bool blackDidChess = madeChess(_players[BLACK_PLAYER]);
	bool whitePlayer = getCurrentPlayer().getType() == WHITE_PLAYER;

	// if its a self-chess
	if ((whiteDidChess && !whitePlayer) || (blackDidChess && whitePlayer))
	{
		// restore our board state and return an invalid move
		_board = boardCopy;
		src.setLocation(oldLocation);
		dest.setCaptured(false);
		move.setCaptured(nullptr);
		return INVALID_SELF_CHESS;
	}

	// a move has occured, therefore clear the "redo" stack
	while (!_movesRedo.empty())
	{
		_movesRedo.pop();
	}

	// piece moved, therefore it should be true
	src.setMoved(true);

	pushMove(&move); // push move to history

	// check if game is over by either checkmate, stalemate or insufficient material draw
	int endgameStatus = isInsufficientMaterial() ? VALID_INSUFFICIENT_MATERIAL : VALID_MOVE;
	if (endgameStatus == VALID_MOVE)
	{
		endgameStatus = checkmateOrStalemate(&getCurrentPlayer());
	}

	if (endgameStatus == VALID_INSUFFICIENT_MATERIAL || endgameStatus == VALID_CHECKMATE || endgameStatus == VALID_STALEMATE)
	{
		return endgameStatus;
	}

	shiftCurrentPlayer();
	// switch turn from black to white and vice versa

	return (whiteDidChess || blackDidChess) ? VALID_CHESS : VALID_MOVE;
}

int Board::promotePiece(Piece* promoted, char newType)
{
	// since this function is called after the move has been complete, we should "switch" the turn to get the previous player
	// which was promoted
	shiftCurrentPlayer();
	Player* player = &getCurrentPlayer();
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

	int endgameStatus = checkmateOrStalemate(&getCurrentPlayer());
	if (endgameStatus == VALID_CHECKMATE || endgameStatus == VALID_STALEMATE || endgameStatus == VALID_CHESS)
	{
		result = endgameStatus;
	}
	else
	{
		result = SUCCESSFUL_PROMOTION;
	}

	// reset current player's state
	shiftCurrentPlayer();

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
