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
	char _identifier; //capital letter for white and small for black
	bool _captured; // whether piece is captured or not 

public:
	// Constructor

	/*
	* Initiates the Piece - defines the owner, location and type of this piece
	* input: owner, stringifed location and piece type
	* output: the Piece
	*/
	Piece(Player* owner, string location, char type);

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
	Player* getOwner() const;

	/*
	* Gets the location of this piece
	* input: none
	* output: the location's string
	*/
	string& getLocation();

	/*
	* Gets the numeric index of this piece
	* input: none
	* output: the piece's numeric index
	*/
	int getIndex();

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
	void setLocation(string& location);
	
	/*
	* Sets the type of this piece
	* input: the type to set
	* output: none
	*/
	void setType(char& type);

	/*
	* Sets the piece's captured state
	* input: its new state
	* output: none
	*/
	void setCaptured(bool isCaptured);

	// methods

	/*
	* A streaming operator, allows us to print the type of this piece,
	* by printing the Piece object itself
	* input: the output stream and the Piece object
	*/
	friend std::ostream& operator<<(std::ostream& os, const Piece& obj);

	/*
	* Performs basic checks on the provided move
	* input: the current player, and the destination piece
	* output: VALID_MOVE if all basic checks were passed, error code otherwise
	*/
	int basicValidateMove(Player& currentPlayer, Piece& dest);

	//abstract method to validate the move according to its piece type
	virtual int validateMove(Piece& dest) = 0;
};

