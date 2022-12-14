#pragma once

#include <iostream>
#include "Player.h"
#include "Piece.h"

#define BOARD_SIZE 8
using std::string;

// protect against circular reference
class Piece;
class Player;

class Board
{
private:
	Piece*** _board;
	Player* _players[2];
	int _currentPlayer;

public:
	//static functions

	static string getLocation(int& index);
	static int getIndex(string& location);

	//constructors

	Board();
	Board(const string& board);
	
	//destructor

	~Board();


	//getters

	Piece*** getBoard() const;
	Player** getPlayers();
	Player& getCurrentPlayer();

	//setters

	void setBoard(const string& board);

	// methods

	void initBoard();
	void setPiece(Piece& src, Piece& dest);
	Piece& getPiece(string location) const;
};