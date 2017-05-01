#pragma once
#include "SharedData.h"
#include "Tile.h"
#include "List.h"

#define BOARD_SIZE 22

class Harmony
{
	int score[2];
	Tile tileGrid[BOARD_SIZE][BOARD_SIZE];

public:
	Harmony();
	~Harmony();

	//updates the internal grid with a set of tiles. Tiles must be located using gridpoint values, not pixel values
	void UpdateScoreGrid(LinkedList<Tile> tileList);

	//updates the score based on the internal tile grid
	void UpdateScore();
private:
	//Updates the harmony scores based on the input tiles
	void AddTileHarmony(Tile* heldTile, Tile selectedTile);

public:
	//returns the scores
	int* GetScore(){ return score; }
};

