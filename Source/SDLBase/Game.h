#pragma once
#include "SharedData.h"
#include "Images.h"
#include <math.h>
#include "List.h"
#include "Mouse.h"
#include "Board.h"
#include "Button.h"
#include "UserInterface.h"
#include "Harmony.h"

//Holds the location of every tile
class Game
{
	//Stores the tile origins
	Coord origins[NULLTILE];
	//stores the tiles on the board
	Board board;
	//Points to the games display class
	Images* displayAddress;
	//Stores the selected tile, to allow it to move free of board constraints
	Tile tileSelected;
	//Stores all mouse data
	Mouse mouseData;
	//Stores UI Data
	UserInterface theGUI;
	//stores the scores
	Harmony scores;		
	//stores wethere or not a grab is allowed
	bool grabValid;

public:
	//Initialises all variables and links the display class
	Game(Images* display);	
private:
	//Initialise the tile origins
	void InitOrigins();
	//Initialise the tiles
	void InitTiles();
	
public:
	~Game();

	//Recieves user input, moves tiles accordingly, updates the display class' data according to tileCentres
	void Update();
private:	
	//ReactToMouseInput
	void CheckMouseInput();
	//React to UI repsons
	void ReactToUI(int response);
	//Perform Board operations
	void UpdateBoard();
	//updates the selected tile and then moves it based on the given mouse location
	void MoveSelected();
	
};

