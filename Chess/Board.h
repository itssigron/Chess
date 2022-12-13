#pragma once

#include <iostream>
#include "Player.h"
#include "Piece.h"

using std::string;


class Board
{
private:
	Piece*** _board;
	Player _players[2];
	int _currentPlayer;
	bool _gameFinished;

public:
	//constructors
	Board();
	Board(const string& board);
	
	//destructor
	~Board();


	//getters
	Piece*** getBoard() const;
	const Player* getPlayers() const;
	Player& getCurrentPlayer();
	bool isGameFinished() const;

	//setters
	void setBoard(const string& board);

	// methods
	void initBoard();
	void setPiece(Piece& src, Piece& dest);
	Player* getWinner();
	Piece& getPiece(string location) const;
};