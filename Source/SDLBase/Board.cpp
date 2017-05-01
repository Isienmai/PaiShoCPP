#include "Board.h"

Board::Board()
{
}


Board::~Board()
{
	tilesOnBoard.DestroyMe();
}

bool Board::PlaceTile(Tile toPlace)
{
	toPlace.SetLocation(LocationToGridNumber(toPlace.Location()));
	if ((GridPointTaken(toPlace.Location())==-1) && (WithinBounds(GridNumberToLocation(toPlace.Location()))))
	{
		tilesOnBoard.AddItem(Tile(toPlace));
		return true;
	}
	return false;
}

Tile Board::GrabTile(Coord givenPoint)
{
	int listIDofTile = GridPointTaken(LocationToGridNumber(givenPoint));
	if ((WithinRadius(GridNumberToLocation(LocationToGridNumber(givenPoint)), 15, givenPoint))&&(listIDofTile !=-1))
	{
		Tile temp = tilesOnBoard.GetItem(listIDofTile);
		temp.SetLocation(GridNumberToLocation(temp.Location()));
		tilesOnBoard.RemoveItem(listIDofTile);
		return temp;
	}
	return Tile();
}

LinkedList<Tile> Board::GetTilesOnBoard()
{
	
	LinkedList<Tile> toReturn;
	Tile tempTile;

	for (int i = 0; i < tilesOnBoard.GetLength(); i++)
	{
		tempTile = tilesOnBoard.GetItem(i);
		tempTile.SetLocation(GridNumberToLocation(tempTile.Location()));
 		toReturn.AddItem(Tile(tempTile));
	}

	return toReturn;
}

void Board::UndoState()
{
	tilesOnBoard.DestroyMe();
	tilesOnBoard = LinkedList<Tile>();
	for (int i = 0; i < previousState.GetLength(); i++)
	{
		tilesOnBoard.AddItem(previousState.GetItem(i));
	}
}

void Board::UpdateBackup()
{
	previousState.DestroyMe();
	previousState = LinkedList<Tile>();
	for (int i = 0; i < tilesOnBoard.GetLength(); i++)
	{
		previousState.AddItem(tilesOnBoard.GetItem(i));
	}
}

bool Board::WithinRadius(Coord centre, int radius, Coord pointToCheck)
{
	int xdif = pointToCheck.x - centre.x;
	int ydif = pointToCheck.y - centre.y;
	double tosqrt = (xdif * xdif) + (ydif * ydif);
	if (sqrt(tosqrt) > radius)
	{
		return false;
	}
	return true;
}

bool Board::WithinBounds(Coord givenPoint)
{
	return WithinRadius(GridNumberToLocation(Coord(12, 12)), tableRadius, givenPoint);
}

Coord Board::LocationToGridNumber(Coord location)
{
	int gridX, gridY;

	gridX = ((location.x - pointOrigin) / pointDifference) + 0.5;
	gridY = ((location.y - pointOrigin) / pointDifference) + 0.5;

	return Coord(gridX, gridY);
}

Coord Board::GridNumberToLocation(Coord gridNumber)
{
	return Coord(pointOrigin + (int)gridNumber.x * pointDifference, pointOrigin + (int)gridNumber.y * pointDifference);
}

int Board::GridPointTaken(Coord gridPoint)
{
	for (int i = 0; i < tilesOnBoard.GetLength(); i++)
	{
		if (gridPoint == tilesOnBoard.GetItem(i).Location())
		{
			return i;
		}
	}
	return -1;
}
