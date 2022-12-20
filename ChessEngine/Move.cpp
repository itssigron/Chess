#include "Move.h"

int Move::id = 0; // initiate starting id

Move::Move(string source, string destination, Board* board)
{
	_src = source;
	_dest = destination;
	_captured = nullptr;
	_board = board;
}

const string Move::getSrc() const
{
	return _src;
}

const string Move::getDest() const
{
	return _dest;
}

Piece* Move::getSrcPiece() const
{
	return _board->getPiece(_src);
}

Piece* Move::getDestPiece() const
{
	return _board->getPiece(_dest);
}

Piece* Move::getCaptured()
{
	return _captured;
}

void Move::setCaptured(Piece* piece)
{
	_captured = piece;
}
