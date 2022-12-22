#pragma once

#include <iostream>
#include "Player.h"
#include "Piece.h"
#include "Move.h"
#include <stack>

#define BOARD_SIZE 8
#define CHESS_PLAYERS 2
#define EACH_PLAYER_ROWS 2 // amount of rows each player has filled with pieces

using std::string;

// protect against circular reference
class Move;
class Piece;
class Player;

class Board
{
private:
	string _board;
	Player* _players[CHESS_PLAYERS]; // array of player pointers
	std::stack<Move*> _movesHistory; // store all moves of the game in order to be able to go "undo" moves
	std::stack<Move*> _movesRedo; // store "undo" moves in order to be able to "redo" them in case of a mistake
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
	* gets a string with all the locations of all possible moves this src can make
	input: the src piece
	output: all possible locations, i.e: "e3e4e5"
	*/
	string getAllPossibleMoves(Piece& src);

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
	* Gets the stack of the move's history
	* input: none
	* output: the stack of the game's moves history
	*/
	const std::stack<Move*>& getMovesStack() const;

	/*
	* Gets the moves's history by order (only valid moves which played during the game)
	* for example if a2 moved to a4 and then h7 moved to h5, the result will be "a2a4h7h5"
	* input: none
	* output: moves's history string
	*/
	string getMoveHistory();

	/*
	* Pushes a Move object to the history of moves
	* input: the move to push
	* output: none
	*/
	void pushMove(Move* move);

	/*
	* Undo the last move
	* input: none
	* output: the move which "undo" applied to
	*/
	Move* undoMove();

	/*
	* Undo the last move
	* input: none
	* output: the move which "redo" applied to
	*/
	Move* redoMove();

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

	/*
	* Checks if the player made a check(mate) or a stalemate
	* input: the player to check for
	* output: result code
	*/
	int checkmateOrStalemate(Player* player);

	/*
	* Checks if the board is in an insufficient material state
	* input: none
	* output: true if is in an insufficient material state, false otherwise
	*/
	bool isInsufficientMaterial();

	/*
	* Moves the source piece into the destination piece,
	* if destination doesnt contain a piece in it, then
	* source piece will be the piece at that location
	* otherwise, free the destination piece and set source piece
	* as its piece at that location
	* input: Source Piece, Destination Piece
	* output: result move code (possible "chess")
	*/
	int movePiece(Piece& src, Piece& dest, Move& move);

	/*
	* Promotes a piece (usually a pawn) to a better one (queen/rook/bishop/knight)
	* input: the piece to promote, the type in which he will be promoted to
	* output: result code
	*/
	int promotePiece(Piece* promoted, char newType);

	/*
	* Gets a Piece object for a specific location on the board
	* input: the piece's stringified location
	* output; that Piece object's
	(dynamically allocated, user's responsibility to delete)
	*/
	Piece* getPiece(string location) const;
};