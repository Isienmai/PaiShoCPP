#include "Button.h"


Button::Button()
{
	sourceRect = {};
	destRect = sourceRect;
	destRect.x += SCREEN_HEIGHT;
	pressed = false;
	valid = true;
}

Button::Button(SDL_Rect _SourceRect)
{
	sourceRect = _SourceRect;
	destRect = sourceRect;
	destRect.x += SCREEN_HEIGHT;
	pressed = false;
	valid = true;
}

Button::~Button()
{
}

bool Button::Collision(Coord givenPoint)
{
	if (((givenPoint.x > destRect.x) && (givenPoint.x < destRect.x + destRect.w)) && ((givenPoint.y > destRect.y) && (givenPoint.y < destRect.y + destRect.h)))
	{
		return true;
	}
	return false;
}
