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

#define WHITE_PAWNS_INDEX 2 // line after special pieces
#define BLACK_PAWNS_INDEX BOARD_SIZE - 1 // line before special pieces

#define WHITE_FARTHEST_RANK 8
#define BLACK_FARTHEST_RANK 1

// valid moves
#define VALID_MOVE 0 // valid move
#define VALID_CHECK 1 // valid move, current player made a "check"
#define VALID_PAWN_PROMOTION 2 // valid move, current pawn should get promoted
#define VALID_EN_PASSANT 3 // valid move, en passant capture 
#define VALID_CASTLE 4 // valid castle move

// invalid moves
#define INVALID_SRC_MISSING_PIECE 5 // current player is *not* in src piece
#define INVALID_DEST_PLAYER 6 // current player is *in* dest piece (cant kill his own piece)
#define INVALID_SELF_CHECK 7 // move will cause enemy to "check" current player
#define INVALID_INDEX 8 // index is out of valid range
#define INVALID_PIECE_MOVE 9 // the rules of the current piece doesnt allow such move
#define INVALID_SAME_LOCATION 10 // src piece and dest piece are on the same location

// endgame moves
#define VALID_CHECKMATE 11 // valid move, current player made a checkmate
#define VALID_STALEMATE 12 // valid move, a stale mate has occurred
#define VALID_INSUFFICIENT_MATERIAL 13 // valid move, onsufficient material draw has occurred

// other
#define SUCCESSFUL_PROMOTION 14 // a successful pawn promotion

#define INVALID_CHECKMATE_STALEMATE -1 // its neither a checkmate nor stalemate

using std::string;

// protect against circular reference
class Board;
class Player;
class Move;

class Piece
{
protected:
	Player* _owner; // the player who owns this piece
	string _location; // the stringifed location of this piece
	char _type; // type of the piece
	char _identifier; //capital letter for white and small for black
	bool _captured; // whether piece is captured or not 
	Move* _movedAt; // a pointer to the first Move object of this piece

public:

	/*
	* A static function to get the identifier of a piece based on the player's side
	* input: the player's side (WHITE_PLAYER for white and BLACK_PLAYER for black)
	* output: the identifier char
	*/
	static const char getIdentifier(const char& type, const int side);

	// Constructor

	/*
	* Initiates the Piece - defines the owner, location and type of this piece
	* input: owner, stringifed location and piece type
	* output: the Piece
	*/
	Piece(Player* owner, const string location, const char type);

	// Destructor

	/*
	* Clears all memory used in the object
	* input: none
	* output: none
	*/
	~Piece();

	// getters

	/*
	* Gets the owner of this piece
	* input: none
	* output: a pointer to the player object
	*/
	const Player* getOwner() const;

	/*
	* Gets the location of this piece
	* input: none
	* output: the location's string
	*/
	const string& getLocation() const;

	/*
	* Gets the numeric index of this piece
	* input: none
	* output: the piece's numeric index
	*/
	const int getIndex() const;

	/*
	* Gets the type of this piece
	* input: none
	* output: the piece's type char
	*/
	const char& getType() const;

	/*
	* Check whether this piece is captured or not
	* input: none
	* output: the piece's captured state
	*/
	const bool& isCaptured() const;

	/*
	* If piece ever moved, it will return a pointer to its first Move object, nullptr otherwise
	* input: none
	* output: nullptr or Move object pointer
	*/
	const Move* movedAt() const;

	/*
	* Gets the identifier of this piece
	* input: none
	* output: the piece's identifier char
	*/
	const char& getIdentifier() const;

	//setters

	/*
	* Sets the location of this piece
	* input: the location to set
	* output: none
	*/
	void setLocation(const string& location);
	
	/*
	* Sets the type of this piece
	* input: the type to set
	* output: none
	*/
	void setType(const char type);

	/*
	* Sets the piece's captured state
	* input: its new state
	* output: none
	*/
	void setCaptured(const bool isCaptured);

	/*
	* sets the "movedAt" state accordingly
	* input: pointer to the piece's first move
	* output: none
	*/
	void setMovedAt(Move* move);

	// methods

	/*
	* Gets the file of this piece's location
	* input: none
	* output: the file in which this piece is in
	*/
	const char getFile() const;

	/*
	* Gets the rank of this piece's location
	* input: none
	* output: the rank in which this piece is in
	*/
	const int getRank() const;

	/*
	* Performs basic checks on the provided move
	* input: the current player, and the destination piece
	* output: VALID_MOVE if all basic checks were passed, error code otherwise
	*/
	int basicValidateMove(const Player* currentPlayer, Piece& dest);

	//abstract method to validate the move according to its piece type
	virtual int validateMove(Piece& dest) = 0;
};

