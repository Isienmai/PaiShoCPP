#pragma once
#include "SharedData.h"
#include "Tile.h"
#include "List.h"

const int pointOrigin = SCREEN_HEIGHT/-6, pointDifference = SCREEN_HEIGHT/18, tableRadius = SCREEN_HEIGHT/2-SCREEN_HEIGHT/100;

class Board
{
	//Stores the tiles on the Board
	LinkedList<Tile> tilesOnBoard;	
	//stores backup
	LinkedList<Tile> previousState;	

public:
	Board();
	~Board();

	//sees if a tile can be placed, if it can add the tile to the board list, if it can't return false.
	bool PlaceTile(Tile toPlace);
	//returns the highlighted tile and removes it from the list
	Tile GrabTile(Coord givenPoint);
	//Returns a list of tiles with grid points converted to coordinates
	LinkedList<Tile> GetTilesOnBoard();

	void UndoState();

	void UpdateBackup();

	LinkedList<Tile> GetBoardPointTiles(){ return tilesOnBoard; }

private:
	//returns true if the given point is on the Board
	bool WithinBounds(Coord givenPoint);

	//Checks to see if point to check is less than radius distance away from centre
	bool WithinRadius(Coord centre, int radius, Coord pointToCheck);
	

	//Converts a given location to its grid point
	Coord LocationToGridNumber(Coord location);
	//Converts a given grid point to its location
	Coord GridNumberToLocation(Coord gridNumber);

	//returns -1 if no tile in the list is at grid point, else returns the tile's location in the list
	int GridPointTaken(Coord gridPoint);
};

