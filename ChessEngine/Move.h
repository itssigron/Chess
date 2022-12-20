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
	Board* _board;
	Piece* _captured;
public:
	static int id;
	Move(string source, string destination, Board* board);
	const string getSrc() const;
	const string getDest() const;

	Piece* getSrcPiece() const;
	Piece* getDestPiece() const;

	Piece* getCaptured();
	void setCaptured(Piece* piece);
};

