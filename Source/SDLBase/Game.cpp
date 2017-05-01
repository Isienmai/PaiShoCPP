#include "Game.h"

Game::Game(Images* display)
{
	displayAddress = display;

	InitOrigins();
	InitTiles();
	
	mouseData = Mouse();

	grabValid = true;
}

void Game::InitOrigins()
{
	for (int i = 0; i < NULLTILE; i++)
	{
		origins[i] = Coord(800, 40 * (i + 1));
	}
}

void Game::InitTiles()
{
	tileSelected = Tile();
}




Game::~Game()
{
}


void Game::Update()
{	
	CheckMouseInput();	
	
	displayAddress->DisplayBoard(board.GetTilesOnBoard());
	displayAddress->DisplayTile(tileSelected);
	displayAddress->DisplayUI(theGUI.GetButtons(), theGUI.GetCurrentPlayerTiles());
	displayAddress->DisplayText(theGUI.GetTurnPlayer(), scores.GetScore());
	displayAddress->FinaliseDisplay();
}

void Game::CheckMouseInput()
{
	mouseData.GetNewMouseState();
	if (displayAddress->LocationOnBoard(mouseData.mouseLocation()))
	{
		UpdateBoard();
	}
	else
	{
		int UIResponse = theGUI.Update(&mouseData);
		if (UIResponse != BUTTON_NUMBER)
		{
			ReactToUI(UIResponse);
		}
	}
}

void Game::ReactToUI(int response)
{
	switch (response)
	{
	case BUTTON_NUMBER - 2:
		board.UpdateBackup();
		theGUI.ValidateAllTileButtons();
		theGUI.InvalidateNextTurn();
		theGUI.InvalidateUndo();
		theGUI.InvalidateNextTurn();
		theGUI.SwitchTurnPlayer();
		scores.UpdateScoreGrid(board.GetBoardPointTiles());
		scores.UpdateScore();
		grabValid = true;
		break;
	case BUTTON_NUMBER - 1:
		board.UndoState();
		tileSelected = Tile();
		theGUI.ValidateAllTileButtons();
		theGUI.InvalidateUndo();
		theGUI.InvalidateNextTurn();
		grabValid = true;
		break;
	default:
		tileSelected = Tile(response,Coord(700,100), theGUI.GetTurnPlayer());
		grabValid = false;
		theGUI.InvalidateAllTileButtons();
		theGUI.ValidateUndo();
		theGUI.ValidateNextTurn();
		break;
	}
}

void Game::UpdateBoard()
{
	switch (mouseData.GetMouseState())
	{
	case Clicked:
		if ((tileSelected.TileID() == NULLTILE) && grabValid)
		{
			tileSelected = board.GrabTile(mouseData.mouseLocation());
			if (tileSelected.Player1Tile() == theGUI.GetTurnPlayer())
			{
				theGUI.InvalidateAllTileButtons();
				grabValid = false;
			}
			else
			{
				board.PlaceTile(tileSelected);
				tileSelected = Tile();
			}
			
		}
		break;
	case Unclicked:
		if (board.PlaceTile(tileSelected))
		{
			tileSelected = Tile();
			theGUI.InvalidateAllTileButtons();
			theGUI.ValidateUndo();
			theGUI.ValidateNextTurn();
		}
		break;
	case Pressed:
		if (tileSelected.CollidedWithTile(mouseData.lastMouseLocation()))
		{
			MoveSelected();
		}		
		break;
	case Unpressed:
		break;
	default:
		break;
	}
}

void Game::MoveSelected()
{
	int xChange = mouseData.mouseLocation().x - mouseData.lastMouseLocation().x, yChange = mouseData.mouseLocation().y - mouseData.lastMouseLocation().y;

	if (tileSelected.TileID() != NULLTILE)
	{
		tileSelected.MoveTile(Coord(xChange, yChange));
	}
}






