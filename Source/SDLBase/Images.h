#pragma once

#include "SharedData.h"
#include "List.h"
#include "Board.h"
#include "Button.h"
#include <SDL_ttf.h>
#include <string>
using namespace std;

const int TILESOURCEW = 54, TILESOURCEH = 54;
const int TILEWIDTH = 30, TILEHEIGHT = 30;

class Images
{
	//the game window and its renderer
	SDL_Window* mainWindow = nullptr;
	SDL_Renderer* renderer = nullptr;
	
	//The board and tile files loaded as textures
	SDL_Texture* gameBoard = nullptr;
	SDL_Texture* tiles = nullptr;
	SDL_Texture* tilesP2 = nullptr;
	SDL_Texture* buttonsSource = nullptr;
	SDL_Texture* buttonsSource2 = nullptr;
	SDL_Texture* buttonsSource3 = nullptr;

	//The font
	TTF_Font* theFont = nullptr;

	//The source rectangle for each tile within the tiles' tilesheet
	SDL_Rect tileTargets[NULLTILE];

	//the destination rectangle for the board
	SDL_Rect boardViewport;
	

public:
	Images();
private:
	//creates the window and renderer
	void InitialiseSDLVisuals();
	void LoadImages();
	void InitialiseSourceRects();
	void InitialiseDestRects();
	//Returns an SDL_Rect of tile dimensions with source at given point
	SDL_Rect GetTileRectangleAt(int x, int y);

public:
	~Images();

	//Displays the board followed by the tiles
	void DisplayBoard(LinkedList<Tile> _tiles);
private:
	void DisplayBoardBackground();
	void DisplayTiles(LinkedList<Tile>* tiles);

public:
	//Displays the UI
	void DisplayUI(Button buttons[], int* playerTiles);

	void DisplayText(bool player1turn, int* scores);


	void DisplayTile(Tile toDisplay);
	void DisplayPoints(Tile inputGrid[25][25]);
	void FinaliseDisplay();

	//Returns true if the given location is in the board viewport
	bool LocationOnBoard(Coord location);		
};

