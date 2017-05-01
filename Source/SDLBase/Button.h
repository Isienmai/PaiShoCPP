#pragma once
#include "SharedData.h"

class Button
{
	SDL_Rect sourceRect, destRect;
	bool pressed, valid;

public:
	Button();
	Button(SDL_Rect _SourceRect);
	~Button();

	bool Collision(Coord givenPoint);

	SDL_Rect SourceRect() { return sourceRect; }
	SDL_Rect DestRect() { return destRect; }

	bool Pressed() { return pressed; }
	bool Valid() { return valid; }

	void Press() { pressed = true; }
	void UnPress(){ pressed = false; }

	void Validate() { valid = true; }
	void InValidate(){ valid = false; }
};

