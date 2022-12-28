#include "Move.h"

Move::Move(string source, string destination, Board* board) : Move(board->getPiece(source), board->getPiece(destination), board) {}

Move::Move(Piece* src, Piece* dest, Board* board)
{
	_src = src->getLocation();
	_dest = dest->getLocation();
	_srcPiece = src;
	_destPiece = dest;
	_captured = nullptr;
	_board = board;
	_isEnPassant = false;
	_isCastling = false;
	_isPromoted = false;
}

const string Move::getSrc() const
{
	return _src;
}

const string Move::getDest() const
{
	return _dest;
}

Piece* Move::getSrcPiece(bool force)
{
	if (force)
	{
		_srcPiece = _board->getPiece(_src);
	}

	return _srcPiece;
}

Piece* Move::getDestPiece(bool force)
{
	if (force)
	{
		_destPiece = _board->getPiece(_dest);
	}

	return _destPiece;
}

Piece* Move::getCaptured() const
{
	return _captured;
}

const bool Move::isEnPassant() const
{
	return _isEnPassant;
}

const bool Move::isCastling() const
{
	return _isCastling;
}

const bool Move::isPromoted() const
{
	return _isPromoted;
}

void Move::setCaptured(Piece* piece)
{
	_captured = piece;
}

void Move::setEnPassant(const bool enPassant)
{
	_isEnPassant = true;
}

void Move::setCastling(const bool castling)
{
	_isCastling = castling;
}

void Move::setPromoted(const bool promoted)
{
	_isPromoted = promoted;
}

void Move::make(bool forceUpdate, bool capture)
{
	Piece &src = *getSrcPiece(forceUpdate), &dest = *getDestPiece(forceUpdate);
	string& boardStr = (string&)_board->getBoard();

	// empty out source
	boardStr[src.getIndex()] = '#';

	// move source to desired destination
	boardStr[dest.getIndex()] = src.getIdentifier();

	src.setLocation(dest.getLocation()); // update piece location

	// if a capture was made, then perform the action on the player's pieces
	if (dest.getType() != EMPTY_PIECE)
	{
		dest.setCaptured(true);
		if (capture)
		{
			setCaptured(&dest);
		}
	}
}

void Move::undo(bool uncapture)
{
	string& boardStr = (string&)_board->getBoard();
	Piece* capturedPiece = getCaptured();

	// restore our move and return board to its original state

	getDestPiece(true)->setLocation(_src);
	boardStr[Board::getIndex(_src)] = boardStr[Board::getIndex(_dest)];
	boardStr[Board::getIndex(_dest)] = (capturedPiece == nullptr || isEnPassant()) ? EMPTY_PIECE : capturedPiece->getIdentifier();
	if (capturedPiece != nullptr)
	{
		capturedPiece->setCaptured(false); // un-capture this piece
		if (isEnPassant())
		{
			boardStr[capturedPiece->getIndex()] = capturedPiece->getIdentifier();
		}
	}

	getSrcPiece(true); //re-fetch piece after move undone

	if (uncapture)
	{
		setCaptured(nullptr);
	}
}