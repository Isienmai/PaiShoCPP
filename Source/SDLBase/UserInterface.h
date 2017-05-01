#pragma once
#include "SharedData.h"
#include "List.h"
#include "Tile.h"
#include "Button.h"
#include "Mouse.h"

class UserInterface
{
	//Stores the UI Buttons
	Button buttons[BUTTON_NUMBER];
	//stores each player's left tiles
	int playerTileSupplies[2][NULLTILE];
	//stores the currently highlighted button and the previous highlighted button
	int currentButton, lastButton, lastTile;
	//stores if it is player 1's turn
	bool player2sTurn;

public:
	UserInterface();
private:
	void InitButtons();

public:
	~UserInterface();

	int Update(Mouse* mouseData);
private:
	//Return the ID of the current Button
	int GetButtonSelected(Coord mouseLocation);
	//reacts to the mouse input
	int ReactToMouse(MouseState theMouseState);

public:
	Button* GetButtons(){ return buttons; }
	int* GetCurrentPlayerTiles();

	//used to set all tile adding buttons to invalid/valid
	void InvalidateAllTileButtons();
	void ValidateAllTileButtons();

	void InvalidateNextTurn();
	void ValidateNextTurn();

	void InvalidateUndo();
	void ValidateUndo();

	void SwitchTurnPlayer();
	bool GetTurnPlayer(){ return player2sTurn; }
};

