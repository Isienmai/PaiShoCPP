#include "Harmony.h"


Harmony::Harmony()
{
	score[0] = 0;
	score[1] = 0;
}


Harmony::~Harmony()
{
}

void Harmony::UpdateScoreGrid(LinkedList<Tile> tileList)
{
	for (int i = 0; i < BOARD_SIZE; i++)
	{
		for (int j = 0; j < BOARD_SIZE; j++)
		{
			tileGrid[i][j] = Tile();
		}
	}
	Tile temp;
	for (int i = 0; i < tileList.GetLength(); i++)
	{
		temp = tileList.GetItem(i);
		tileGrid[(int)temp.Location().x][(int)temp.Location().y] = temp;
	}
}

void Harmony::UpdateScore()
{
	score[0] = 0;
	score[1] = 0;
	Tile lastGrabbedTile = Tile(), currentTile;

	for (int outerNum = 0; outerNum < BOARD_SIZE; outerNum++)
	{
		for (int innerNum = 0; innerNum < BOARD_SIZE; innerNum++)
		{
			currentTile = tileGrid[outerNum][innerNum];
			AddTileHarmony(&lastGrabbedTile, currentTile);
		}
		lastGrabbedTile = Tile();

		for (int innerNum = 0; innerNum < BOARD_SIZE; innerNum++)
		{
			currentTile = tileGrid[innerNum][outerNum];
			AddTileHarmony(&lastGrabbedTile, currentTile);
		}
		lastGrabbedTile = Tile();
	}
}

void Harmony::AddTileHarmony(Tile* heldTile, Tile selectedTile)
{
	if ((selectedTile.TileID() != NULLTILE) && (heldTile->TileID() != NULLTILE) && (heldTile->Player1Tile() == selectedTile.Player1Tile()))
	{
		int total = heldTile->TileID() + selectedTile.TileID();

		if (total == NULLTILE - 1)
		{
			score[heldTile->Player1Tile()] -= 1;
		}
		else if (total % 2 != 0)
		{
			score[heldTile->Player1Tile()] += 1;
		}
	}

	if (selectedTile.TileID() != NULLTILE)
	{
		*heldTile = selectedTile;
	}
}