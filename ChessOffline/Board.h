#pragma once

#include <iostream>
#include "Player.h"
#include "Piece.h"
#include "Move.h"
#include <stack>

#define BOARD_SIZE 8
#define CHESS_PLAYERS 2
#define EACH_PLAYER_ROWS 2 // Amount of rows each player has filled with pieces

#define QUEENSIDE_ROOK_COL 0
#define KINGSIDE_ROOK_COL 7

#define POSSIBLE_QUEENSIDE_CASTLE_COL QUEENSIDE_ROOK_COL + 2
#define POSSIBLE_KINGSIDE_CASTLE_COL KINGSIDE_ROOK_COL - 1 
#define POSSIBLE_BLACK_CASTLE_ROW 0
#define POSSIBLE_WHITE_CASTLE_ROW 7

#define AFTER_KINGSIDE_CASTLE_ROOK 5
#define AFTER_QUEENSIDE_CASTLE_ROOK 3

#define BLACK_KING_INDEX 4
#define WHITE_KING_INDEX 12

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
	* Gets the stringified location of a file and rank
	* input: file and rank
	* output: their stringified location
	*/
	static string getLocation(const char file, const char rank);

	/*
	* Gets the stringified location of a file and numeric rank
	* input: file and numeric rank
	* output: their stringified location
	*/
	static string getLocation(const char file, const int rank);

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
	static int getIndex(const int row, const int col);

	/*
	* gets a string with all the locations of all possible moves this src can make
	* input: the src piece and a possible player overwrite for the current player
	* output: all possible locations, i.e: "e3e4e5"
	*/
	string getAllPossibleMoves(Piece& src, const Player* player = nullptr);

	/*
	* Checks if a specific move will cause self-check
	* input: src piece, dest piece
	* output: true if yes, false otherwise
	*/
	bool moveWillCauseCheck(Piece& src, Piece& dest);


	// ---------------------- CONSTRUCTOR ----------------------

	/*
	* Initiate our Board object
	* input: the stringified board
	* output: the Board object
	*/
	Board(const string& board, const string& filePath);
	
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
	const Player** getPlayers() const;

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
	const string getMoveHistory() const;

	/*
	* Pushes a Move object to the history of moves
	* input: the move to push
	* output: none
	*/
	void pushMove(Move* move);

	/*
	* Shifts the current player
	* input: none
	* output: none
	*/
	void shiftCurrentPlayer();

	/*
	* Undoing the last move
	* input: none
	* output: the move which "undo" applied to
	*/
	Move* undoMove();

	/*
	* "Redo" the last move, its not actually redoing it, it simply returns the move which needs to be redone
	* and then we simply apply the same "play" logic to that move
	* input: none
	* output: the move which "redo" applied to
	*/
	Move* redoMove();

	/*
	* Gets the current player
	* input: none
	* output: a reference to the current player
	*/
	const Player* getCurrentPlayer() const;

	/*
	* Gets the current enemy
	* input: none
	* output: a pointer to the current enemy player
	*/
	const Player* getEnemy(const Player* player) const;


	// ---------------------- METHODS ----------------------

	/*
	* Validates the move and returns move code accordingly
	* input: src and dest pieces
	* output: the move code
	*/
	int validateMove(const Player* currentPlayer, Piece& src, Piece& dest) const;

	/*
	* checks if a specific move code can be considered a non-endgame valid move
	* input: the move code to check for
	* output: true if a valid move which doesnt result in an endgame, false otherwise
	*/
	bool isValidMove(const int& moveCode) const;

	/*
	* Check if a player made a "check" over the other player
	* input: Player pointer
	* output: whether a "check" occured over the other player or not
	*/
	bool madeCheck(const Player* player);

	/*
	* Checks if the player made a check(mate) or a stalemate
	* input: the player to check for
	* output: result code
	*/
	int checkmateOrStalemate(const Player* player);

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
	* otherwise, capture the destination piece and set source piece
	* as its piece at that location
	* functions also checks against "self-check" and endgame
	* input: Source Piece, Destination Piece
	* output: result move code (possible one of our end-game move codes)
	*/
	int movePiece(Piece& src, Piece& dest, Move& move);

	/*
	* Promotes a piece (usually a pawn) to a better one (queen/rook/bishop/knight)
	* input: the piece to promote, the type in which he will be promoted to
	* output: result code
	*/
	int promotePiece(Piece* promoted, char newType);

	/*
	* Gets a Piece object for a specific location (stringified) on the board
	* input: the piece's stringified location
	* output; that Piece's object ('EmptyPiece's are dynamically allocated, user's responsibility to delete)
	*/
	Piece* getPiece(string location) const;

	/*
	* Gets a Piece object for a specific location (numeric) on the board
	* input: the piece's numeric location
	* output; that Piece's object ('EmptyPiece's are dynamically allocated, user's responsibility to delete)
	*/
	Piece* getPiece(int index) const;

	/*
	* Gets a Piece object for a specific location (numeric - row and col) on the board
	* input: the piece's numeric row and col
	* output; that Piece's object ('EmptyPiece's are dynamically allocated, user's responsibility to delete)
	*/
	Piece* getPiece(int row, int col) const;
};