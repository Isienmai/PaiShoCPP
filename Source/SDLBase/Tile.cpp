#include "Tile.h"


Tile::Tile()
{
	tileID = NULLTILE;
	location = Coord();
	player1Tile = true;
}

Tile::Tile(int _tileID, Coord _location, bool _player1Tile)
{
	tileID = _tileID;
	location = _location;
	player1Tile = _player1Tile;
}


Tile::~Tile()
{
}

bool Tile::CollidedWithTile(Coord pointToCheck)
{
	int xdif = pointToCheck.x - location.x;
	int ydif = pointToCheck.y - location.y;
	double tosqrt = (xdif * xdif) + (ydif * ydif);
	if (sqrt(tosqrt) > 15)
	{
		return false;
	}
	return true;
}

void Tile::MoveTile(Coord transformation)
{
	location += transformation;
}

void Tile::SetTileID(int newTileID)
{
	tileID = newTileID;
}

void Tile::SetLocation(Coord newLocation)
{
	location = newLocation;
}