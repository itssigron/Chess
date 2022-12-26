#pragma once
#include <string>
#include "Board.h"

using std::string;

class Board;
class Piece;

class Move
{
private:
	string _src;
	string _dest;
	Piece* _srcPiece;
	Piece* _destPiece;
	Board* _board;
	Piece* _captured;
	bool _isEnPassant;
	bool _isCastling;
	bool _isPromoted;
public:
	/*
	* builds the object by stringified source and destination
	* input: source location string, destination location string and the board associated with this move
	* output: the Move object
	*/
	Move(string source, string destination, Board* board);

	/*
	* builds the object by already-fetched source and destination pieces
	* input: source piece, destination piece and the board associated with this move
	* output: the Move object
	*/
	Move(Piece* src, Piece* dest, Board* board);

	/*
	* Gets the source location
	* input: none
	* output: source location
	*/
	const string getSrc() const;

	/*
	* Gets the destination location
	* input: none
	* output: destination location
	*/
	const string getDest() const;

	/*
	* Gets the source piece with option to re-fetch by pre-given location to the constructor
	* input: whether to re-fetch the source piece or use the cached one (default = false for cached piece)
	* output: the source piece
	*/
	Piece* getSrcPiece(bool force = false);

	/*
	* Gets the destination piece with option to re-fetch by pre-given location to the constructor
	* input: whether to re-fetch the destination piece or use the cached one (default = false for cached piece)
	* output: the destination piece
	*/
	Piece* getDestPiece(bool force = false);

	/*
	* Gets the captured piece of this move
	* input: none
	* output: the captured piece of this move if any (null if none)
	*/
	Piece* getCaptured();

	/*
	* Checks if move is en passant
	* input: none
	* output: whether this move is an en passant capture
	*/
	bool isEnPassant();

	/*
	* Checks if move is castling
	* input: none
	* output: whether this move made castling
	*/
	bool isCastling();

	/*
	* Checks if move caused pawn promotion
	* input: none
	* output: whether this move caused pawn promoted
	*/
	bool isPromoted();

	/*
	* Sets the piece captured by this move
	* input: the piece which was captured by this move
	* output: none
	*/
	void setCaptured(Piece* piece);

	/*
	* Sets the en passant state of this move
	* input: whether this move caused en passant
	* output: none
	*/
	void setEnPassant(bool enPassant);

	/*
	* Sets the castling state of this move
	* input: whether this move caused castling
	* output: none
	*/
	void setCastling(bool castling);

	/*
	* Sets the promotion state of this move
	* input: whether this move caused pawn promotion
	* output: none
	*/
	void setPromoted(bool promoted);
	
	/*
	* Makes the move and reflect the changes on the board
	* input: whether to re-fetch source and destination pieces (false by default) and whether to apply capture state in this move
	* output: none
	*/
	void make(bool forceUpdate = false, bool capture = true);

	/*
	* Restoring the move and reflect the changes on the board
	* input: whether to apply an uncapture for this move
	* output: none
	*/
	void undo(bool uncapture = true);
};

