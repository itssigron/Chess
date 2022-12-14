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
	Piece* _board[BOARD_SIZE * BOARD_SIZE]; // "2d" array of Piece pointers
	Player* _players[CHESS_PLAYERS]; // array of player pointers
	int _currentPlayer; // index of current player

public:
	//static functions

	/*
	* Gets the stringified location of a numeric index
	* input: the numeric index
	* output: its stringified location
	*/
	static string getLocation(int index);

	/*
	* Gets the stringified location of a row and col
	* input: row and col
	* output: their stringified location
	*/
	static string getLocation(int row, int col);

	void printAllValidLocations(Piece& src);

	/*
	* Gets the numeric index of a stringified location
	* input: the stringified location
	* output: its numeric index
	*/
	static int getIndex(string& location);

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
	* output: the 2d array of Piece pointers
	*/
	Piece** getBoard();

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

	// ---------------------- SETTERS ----------------------

	/*
	* Fill the board with pieces according to the stringified board
	* input: the stringified board
	* output: none
	*/
	void setBoard(const string& board);

	// ---------------------- METHODS ----------------------

	/*
	* Allocates memory for the board and initiate them to null
	* input: none
	* output: none
	*/
	void initBoard();
	/*
	* Moves the source piece into the destination piece,
	* if destination doesnt contain a piece in it, then
	* source piece will be the piece at that location
	* otherwise, free the destination piece and set source piece
	* as its piece at that location
	* input: Source Piece, Destination Piece
	* output: none
	*/
	void movePiece(Piece& src, Piece& dest);

	/*
	* Gets a piece at a specific location
	* input: the piece's stringified location
	* output; that Piece object's reference
	*/
	Piece& getPiece(string location) const;
};