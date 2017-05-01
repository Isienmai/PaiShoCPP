#pragma once
#include "SharedData.h"

class Tile
{
	int tileID;
	Coord location;
	bool player1Tile;

public:
	Tile();
	Tile(int _tileID, Coord _location, bool _player1Tile);
	~Tile();

	bool CollidedWithTile(Coord pointToCheck);

	void MoveTile(Coord transformation);
	void SetTileID(int newTileID);
	void SetLocation(Coord newLocation);

	int TileID(){ return tileID; }
	Coord Location(){ return location; }
	bool Player1Tile(){ return player1Tile; }
};

