#include "Images.h"

Images::Images()
{	
	TTF_Init();
	InitialiseSDLVisuals();
	LoadImages();
	InitialiseSourceRects();
	InitialiseDestRects();		
}

void Images::InitialiseSDLVisuals()
{
	mainWindow = SDL_CreateWindow("Pai Sho", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	renderer = SDL_CreateRenderer(mainWindow, -1, SDL_RENDERER_ACCELERATED);
}

void Images::LoadImages()
{
	gameBoard = SDL_CreateTextureFromSurface(renderer, IMG_Load("Images/HDBoard.png"));
	tiles = SDL_CreateTextureFromSurface(renderer, IMG_Load("Images/Tiles.png"));
	tilesP2 = SDL_CreateTextureFromSurface(renderer, IMG_Load("Images/TilesP2.png"));
	buttonsSource = SDL_CreateTextureFromSurface(renderer, IMG_Load("Images/Buttons.png"));
	buttonsSource2 = SDL_CreateTextureFromSurface(renderer, IMG_Load("Images/Buttonstest2.png"));
	buttonsSource3 = SDL_CreateTextureFromSurface(renderer, IMG_Load("Images/Buttonstest3.png"));
	theFont = TTF_OpenFont("Images/apl385.ttf", 12);
}

void Images::InitialiseSourceRects()
{
	tileTargets[Jasmine] = GetTileRectangleAt(TILESOURCEW * 0, TILESOURCEH * 0);
	tileTargets[WhiteJade] = GetTileRectangleAt(TILESOURCEW * 0, TILESOURCEH * 1);
	tileTargets[WhiteLily] = GetTileRectangleAt(TILESOURCEW * 0, TILESOURCEH * 2);

	tileTargets[Chrysanthemum] = GetTileRectangleAt(TILESOURCEW * 1, TILESOURCEH * 0);
	tileTargets[Rose] = GetTileRectangleAt(TILESOURCEW * 1, TILESOURCEH * 1);
	tileTargets[Rhododendron] = GetTileRectangleAt(TILESOURCEW * 1, TILESOURCEH * 2);

	tileTargets[Knotweed] = GetTileRectangleAt(TILESOURCEW * 2, TILESOURCEH * 0);
	tileTargets[Boat] = GetTileRectangleAt(TILESOURCEW * 2, TILESOURCEH * 1);
	tileTargets[WhiteDragon] = GetTileRectangleAt(TILESOURCEW * 2, TILESOURCEH * 2);

	tileTargets[Wheel] = GetTileRectangleAt(TILESOURCEW * 3, TILESOURCEH * 0);
	tileTargets[Rock] = GetTileRectangleAt(TILESOURCEW * 3, TILESOURCEH * 1);
	tileTargets[WhiteLotus] = GetTileRectangleAt(TILESOURCEW * 3, TILESOURCEH * 2);
}

void Images::InitialiseDestRects()
{
	boardViewport = { 0, 0, SCREEN_HEIGHT, SCREEN_HEIGHT };
}

SDL_Rect Images::GetTileRectangleAt(int x, int y)
{
	return{ x, y, TILESOURCEW, TILESOURCEH };
}


Images::~Images()
{
	SDL_DestroyTexture(gameBoard);
	gameBoard = nullptr;
}


void Images::DisplayBoard(LinkedList<Tile> _tiles)
{
	SDL_RenderClear(renderer);
	
	DisplayBoardBackground();	
	DisplayTiles(&_tiles);

	_tiles.DestroyMe();
}

void Images::DisplayBoardBackground()
{
	SDL_RenderClear(renderer);

	SDL_SetRenderDrawColor(renderer, 200, 0, 200, 0);
	SDL_RenderFillRect(renderer, &boardViewport);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);

	SDL_RenderCopy(renderer, gameBoard, NULL, &boardViewport);
}

void Images::DisplayTiles(LinkedList<Tile>* _tiles)
{
	int listLength = _tiles->GetLength();
	Tile selectedTile;

	for (int i = 0; i < listLength; i++)
	{
		selectedTile = _tiles->GetItem(i);
		DisplayTile(selectedTile);
	}
}


void Images::DisplayUI(Button buttons[], int* currentPlayerTiles)
{
	SDL_Surface* tileQuantity = nullptr;
	SDL_Texture* tileQuantityTexture = nullptr;
	SDL_Rect* tileQuantityLocation = nullptr;

	SDL_Rect tempRect = { SCREEN_HEIGHT, 0, SCREEN_WIDTH - SCREEN_HEIGHT, SCREEN_HEIGHT };

	SDL_RenderCopy(renderer, buttonsSource, nullptr, &tempRect);

	for (int i = 0; i < BUTTON_NUMBER; i++)
	{
		tempRect = buttons[i].SourceRect();
		tempRect.x += SCREEN_HEIGHT;
		if (buttons[i].Pressed())
		{
			SDL_RenderCopy(renderer, buttonsSource2, &buttons[i].SourceRect(), &tempRect);
		}
		else
		{
			if (!buttons[i].Valid())
			{
				SDL_RenderCopy(renderer, buttonsSource3, &buttons[i].SourceRect(), &tempRect);
			}
			else
			{
				SDL_RenderCopy(renderer, buttonsSource, &buttons[i].SourceRect(), &tempRect);
			}			
		}			
	}

	for (int i = 0; i < NULLTILE; i++)
	{
		tileQuantity = TTF_RenderText_Solid(theFont, std::to_string(currentPlayerTiles[i]).c_str(), SDL_Color{ 0, 0, 0, 200 });
		tileQuantityTexture = SDL_CreateTextureFromSurface(renderer, tileQuantity);
		if (i < 3)
		{
			tileQuantityLocation = new SDL_Rect({ SCREEN_HEIGHT + 25, 90 + i*80, 30, 45 });
		}
		else
		{
			tileQuantityLocation = new SDL_Rect({ SCREEN_HEIGHT + 125, 90 + (i-3)*80, 30, 45 });
		}

		SDL_RenderCopy(renderer, tileQuantityTexture, nullptr, tileQuantityLocation);

		SDL_FreeSurface(tileQuantity);
		tileQuantity = nullptr;

		SDL_DestroyTexture(tileQuantityTexture);
		tileQuantityTexture = nullptr;

		delete(tileQuantityLocation);
		tileQuantityLocation = nullptr;
	}
}

void Images::DisplayText(bool player2turn, int* scores)
{
	SDL_Surface* p1ScoreText = TTF_RenderText_Solid(theFont, std::to_string(scores[0]).c_str(), SDL_Color{ 100, 200, 200, 200 });
	SDL_Surface* p2ScoreText = TTF_RenderText_Solid(theFont, std::to_string(scores[1]).c_str(), SDL_Color{ 100, 200, 200, 200 });
	
	SDL_Texture* player1ScoreTexture = SDL_CreateTextureFromSurface(renderer, p1ScoreText);
	SDL_Texture* player2ScoreTexture = SDL_CreateTextureFromSurface(renderer, p2ScoreText);

	SDL_FreeSurface(p1ScoreText);
	SDL_FreeSurface(p2ScoreText);

	
	SDL_Rect tempRect = { 0, 0, 200, 25 };
	SDL_Rect P1score = { 20 + SCREEN_HEIGHT, 20, 60, 20 };
	SDL_Rect P2score = { 120 + SCREEN_HEIGHT, 20, 60, 20 };
	SDL_Texture* turnText;

	SDL_Surface* playerTurnText;

	if (player2turn)
	{		
		playerTurnText = TTF_RenderText_Solid(theFont, "Player 2's turn", SDL_Color{ 100, 200, 200, 200 });
		
	}
	else
	{
		playerTurnText = TTF_RenderText_Solid(theFont, "Player 1's turn", SDL_Color{ 100, 200, 200, 200 });
	}
	
	turnText = SDL_CreateTextureFromSurface(renderer, playerTurnText);
	SDL_FreeSurface(playerTurnText);

	SDL_RenderCopy(renderer, turnText, nullptr, &tempRect);
	SDL_DestroyTexture(turnText);

	SDL_RenderCopy(renderer, player1ScoreTexture, nullptr, &P1score);
	SDL_DestroyTexture(player1ScoreTexture);
	SDL_RenderCopy(renderer, player2ScoreTexture, nullptr, &P2score);
	SDL_DestroyTexture(player2ScoreTexture);
}

void Images::DisplayTile(Tile toDisplay)
{
	if (toDisplay.TileID() != NULLTILE)
	{
		SDL_Rect* tempRectangle = new SDL_Rect({ toDisplay.Location().x - (TILEWIDTH / 2), toDisplay.Location().y - (TILEHEIGHT / 2), TILEWIDTH, TILEHEIGHT });

		if (toDisplay.Player1Tile())
		{
			SDL_RenderCopy(renderer, tiles, &tileTargets[toDisplay.TileID()], tempRectangle);
		}
		else
		{
			SDL_RenderCopy(renderer, tilesP2, &tileTargets[toDisplay.TileID()], tempRectangle);
		}

		
		delete(tempRectangle);
	}
}

void Images::DisplayPoints(Tile inputGrid[25][25])
{
	SDL_SetRenderDrawColor(renderer, 0, 200, 200, 0);
	for (int i = 0; i < 25; i++)
	{
		for (int j = 0; j < 25; j++)
		{
			if ((i == 12) && (j == 12))
			{
				SDL_SetRenderDrawColor(renderer, 200, 0, 200, 0);
				SDL_RenderDrawPoint(renderer, inputGrid[i][j].Location().x, inputGrid[i][j].Location().y);
				SDL_SetRenderDrawColor(renderer, 0, 200, 200, 0);
			}
			else
			{
				SDL_RenderDrawPoint(renderer, inputGrid[i][j].Location().x, inputGrid[i][j].Location().y);
			}
			
		}
	}	
}

void Images::FinaliseDisplay()
{
	SDL_RenderPresent(renderer);
}

bool Images::LocationOnBoard(Coord location)
{
	if ((location.x < 0) || (location.x > boardViewport.w))
	{
		return false;
	}
	if ((location.y < 0) || (location.y > boardViewport.h))
	{
		return false;
	}
	return true;
}