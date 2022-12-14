#pragma once
#include "Player.h"
#include <iostream>

// Piece types
#define ROOK 'r'
#define KNIGHT 'n'
#define BISHOP 'b'
#define KING 'k'
#define QUEEN 'q'
#define PAWN 'p'
#define EMPTY_PIECE '#'

// valid moves
#define VALID_MOVE 0 // valid move
#define VALID_CHESS 1 // valid move, current player made a chess
#define VALID_CHECKMATE 8 // valid move, current player made a checkmate

// invalid moves
#define INVALID_SRC_MISSING_PIECE 2 // current player is *not* in src piece
#define INVALID_DEST_PLAYER 3 // current player is *in* dest piece (cant kill his own piece)
#define INVALID_SELF_CHESS 4 // move will cause enemy to chess current player
#define INVALID_INDEX 5 // index is out of valid range
#define INVALID_PIECE_MOVE 6 // the rules of the current piece doesnt allow such move
#define INVALID_SAME_LOCATION 7 // src piece and dest piece are on the same location

using std::string;

// protect against circular reference
class Board;
class Player;

class Piece
{
protected:
	Player* _owner; // the player who owns this piece
	string _location; // the stringifed location of this piece
	char _type; // type of the piece

public:
	Piece(Player* owner, string location, char type);

	//getters
	Player* getOwner();
	string getLocation();
	char getType();

	//setters
	void setLocation(string location);
	void setType(char type);

	// methods
	friend std::ostream& operator<<(std::ostream& os, const Piece& obj);
	int basicValidateMove(Player& currentPlayer, Piece& dest);

	//abstract methods
	virtual int validateMove(Piece& dest) = 0;
};

