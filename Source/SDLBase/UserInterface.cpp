#include "UserInterface.h"


UserInterface::UserInterface()
{
	InitButtons();
	currentButton = BUTTON_NUMBER;
	lastButton = BUTTON_NUMBER;
	lastTile = NULLTILE;
	InvalidateNextTurn();
	InvalidateUndo();
	player2sTurn = false;
}

void UserInterface::InitButtons()
{
	//add white tiles
	for (int buttonID = 0; buttonID < 3; buttonID++)
	{
		buttons[buttonID] = Button({ 15, 80 + buttonID * 80, 70, 65 });
	}
	//add red tiles
	for (int buttonID = 0; buttonID < 3; buttonID++)
	{
		buttons[3 + buttonID] = Button({ 115, 80 + buttonID * 80, 70, 65 });
	}
	//add control buttons
	for (int buttonID = 0; buttonID < 2; buttonID++)
	{
		buttons[6 + buttonID] = Button({ 10 + buttonID * 100, 345, 80, 45 });
	}

	//initialise the tile stock
	for (int tile = 0; tile < NULLTILE; tile++)
	{
		playerTileSupplies[0][tile] = 3;
		playerTileSupplies[1][tile] = 3;
	}
}


UserInterface::~UserInterface()
{
}

int UserInterface::Update(Mouse* mouseData)
{
	lastButton = currentButton;
	currentButton = GetButtonSelected(mouseData->mouseLocation());
	if ((lastButton != currentButton) && (lastButton!=BUTTON_NUMBER))
	{
		buttons[lastButton].UnPress();
	}
	if (currentButton != BUTTON_NUMBER)
	{
		int reaction = ReactToMouse(mouseData->GetMouseState());
		if (reaction < NULLTILE)
		{
			lastTile = reaction;
			if (player2sTurn)
			{
				playerTileSupplies[1][reaction]--;
			}
			else
			{
				playerTileSupplies[0][reaction]--;
			}
		}

		if (reaction == BUTTON_NUMBER - 2)
		{
			lastTile = NULLTILE;
		}

		if (reaction == BUTTON_NUMBER - 1)
		{
			if (player2sTurn)
			{
				playerTileSupplies[1][lastTile]++;
			}
			else
			{
				playerTileSupplies[0][lastTile]++;
			}
			lastTile = NULLTILE;
		}

		return reaction;
	}
	else
	{
		return BUTTON_NUMBER;
	}
}

int UserInterface::GetButtonSelected(Coord mouseLocation)
{
	for (int i = 0; i < BUTTON_NUMBER; i++)
	{
		if (buttons[i].Collision(mouseLocation))
		{
			return i;
		}
	}

	return BUTTON_NUMBER;
}

int UserInterface::ReactToMouse(MouseState theMouseState)
{
	if (buttons[currentButton].Valid())
	{
		switch (theMouseState)
		{
		case Clicked:
			buttons[currentButton].Press();
			return currentButton;
			break;
		case Unclicked:
			buttons[currentButton].UnPress();
			break;
		default:
			break;
		}
	}

	return BUTTON_NUMBER;
}

int* UserInterface::GetCurrentPlayerTiles()
{
	if (player2sTurn)
	{
		return playerTileSupplies[1];
	}
	else
	{
		return playerTileSupplies[0];
	}
}

void UserInterface::InvalidateAllTileButtons()
{
	for (int i = 0; i < NULLTILE; i++)
	{
		buttons[i].InValidate();
	}
}

void UserInterface::ValidateAllTileButtons()
{
	for (int i = 0; i < NULLTILE; i++)
	{
		buttons[i].Validate();
	}
}

void UserInterface::InvalidateNextTurn()
{
	buttons[BUTTON_NUMBER - 2].InValidate();
}

void UserInterface::ValidateNextTurn()
{
	buttons[BUTTON_NUMBER - 2].Validate();
}

void UserInterface::InvalidateUndo()
{
	buttons[BUTTON_NUMBER - 1].InValidate();
}

void UserInterface::ValidateUndo()
{
	buttons[BUTTON_NUMBER - 1].Validate();
}

void UserInterface::SwitchTurnPlayer()
{
	player2sTurn = !player2sTurn;
	
	if (player2sTurn)
	{
		for (int i = 0; i < NULLTILE; i++)
		{
			if (playerTileSupplies[1][i] == 0)
			{
				buttons[i].InValidate();
			}
		}
	}
	else
	{
		for (int i = 0; i < NULLTILE; i++)
		{
			if (playerTileSupplies[0][i] == 0)
			{
				buttons[i].InValidate();
			}
		}
	}
	
}