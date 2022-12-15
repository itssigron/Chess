#pragma once

#include <iostream>
#include "Player.h"
#include "Piece.h"

#define BOARD_SIZE 8
#define CHESS_PLAYERS 2

using std::string;

// protect against circular reference
class Piece;
class Player;

class Board
{
private:
	string _board;
	Player* _players[CHESS_PLAYERS]; // array of player pointers
	int _currentPlayer; // index of current player

public:
	//static functions

	/*
	* Gets the stringified location of a numeric index
	* input: the numeric index
	* output: its stringified location
	*/
	static string getLocation(const int index);

	/*
	* Gets the stringified location of a row and col
	* input: row and col
	* output: their stringified location
	*/
	static string getLocation(const int row, const int col);

	/*
	* Prints the board with src colored in red and all valid moves colored in green
	* input: the src piece to check all locations against
	* output: none
	*/
	void printAllValidLocations(Piece& src);

	/*
	* Gets the numeric index of a stringified location
	* input: the stringified location
	* output: its numeric index
	*/
	static int getIndex(const string& location);

	/*
	* Gets the numeric index by row and col
	* input: row and col
	* output: their absolute
	*/
	static int getIndex(int row, int col);

	// ---------------------- CONSTRUCTOR ----------------------

	/*
	* Initiate our Board object
	* input: the stringified board
	* output: the Board object
	*/
	Board(const string& board);
	
	// ---------------------- DESTRUCTOR ----------------------

	/*
	* De-allocates (free) all used memory in our Board object
	* input: none
	* output: none
	*/
	~Board();

	// ---------------------- GETTERS ----------------------

	/*
	* Gets the board
	* input: none
	* output: the board's string
	*/
	string& getBoard();

	/*
	* Gets the players
	* input: none
	* output: the array of Player pointers
	*/
	Player** getPlayers();

	/*
	* Gets the current player
	* input: none
	* output: a reference to the current player
	*/
	Player& getCurrentPlayer() const;


	// ---------------------- METHODS ----------------------

	/*
	* Check if a player made a chess over the other player
	* input: Player pointer
	* output: whether a chess occured over the other player or not
	*/
	bool madeChess(Player* player);

	bool madeCheckmate(Player* player);

	/*
	* Moves the source piece into the destination piece,
	* if destination doesnt contain a piece in it, then
	* source piece will be the piece at that location
	* otherwise, free the destination piece and set source piece
	* as its piece at that location
	* input: Source Piece, Destination Piece
	* output: result move code (possible "chess")
	*/
	int movePiece(Piece& src, Piece& dest);

	/*
	* Gets a Piece object for a specific location on the board
	* input: the piece's stringified location
	* output; that Piece object's
	(dynamically allocated, user's responsibility to delete)
	*/
	Piece* getPiece(string location) const;
};