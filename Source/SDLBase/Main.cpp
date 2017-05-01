#include "Main.h"

int main(int argc, char* args[])
{
	SDL_Init(SDL_INIT_VIDEO);
	IMG_Init(IMG_INIT_PNG);

	MainLoop();
	ExitGame();
	return 0;
}

void MainLoop()
{
	SDL_Event eventList;
	Images* visualContent = new Images();
	Game theGame = Game(visualContent);
	
	bool quit = false;	

	while (!quit)
	{		
		while (SDL_PollEvent(&eventList) != 0)
		{
			if ((eventList.type == SDL_QUIT) || ((eventList.type == SDL_KEYDOWN) && (eventList.key.keysym.sym == SDLK_ESCAPE)))
			{
				quit = true;
			}
		}		
		theGame.Update();		
	}

}

void ExitGame()
{	
	SDL_Quit();
}