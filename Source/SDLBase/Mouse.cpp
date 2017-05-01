#include "Mouse.h"

Mouse::Mouse()
{
	int currentx, currenty;
	currentMouseButtonDown = (SDL_GetMouseState(&currentx, &currenty) & SDL_BUTTON(1));
	mouseButtonStateChange = false;	
	currentMouseLocation = Coord(currentx, currenty);
}


Mouse::~Mouse()
{
}

MouseState Mouse::GetNewMouseState()
{
	int currentx, currenty;

	//update mouse history
	mouseButtonStateChange = currentMouseButtonDown;
	previousMouseLocation = currentMouseLocation;
		
	//bring in current data
	currentMouseButtonDown = (SDL_GetMouseState(&currentx, &currenty) & SDL_BUTTON(1));
	currentMouseLocation = Coord(currentx, currenty);

	mouseButtonStateChange = currentMouseButtonDown^mouseButtonStateChange;

	//compare current data and mouse history
	if (currentMouseButtonDown)
	{
		if (mouseButtonStateChange)
		{
			return Clicked;
		}
		else
		{
			return Pressed;
		}
	}
	else
	{
		if (mouseButtonStateChange)
		{
			return Unclicked;
		}
		else
		{
			return Unpressed;
		}
	}
}

MouseState Mouse::GetMouseState()
{
	if (currentMouseButtonDown)
	{
		if (mouseButtonStateChange)
		{
			return Clicked;
		}
		else
		{
			return Pressed;
		}
	}
	else
	{
		if (mouseButtonStateChange)
		{
			return Unclicked;
		}
		else
		{
			return Unpressed;
		}
	}
}
