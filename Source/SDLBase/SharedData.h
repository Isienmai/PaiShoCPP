#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <iostream>

#define SCREEN_WIDTH 939
#define SCREEN_HEIGHT 739

#define BUTTON_NUMBER 8

enum TileValues
{	
	Rose,
	Chrysanthemum,
	Rhododendron,	
	WhiteJade,
	WhiteLily,
	Jasmine,		
	NULLTILE,
	Knotweed,
	Wheel,
	Rock,
	Boat,
	WhiteDragon,
	WhiteLotus,
};

enum MouseState
{
	Clicked,
	Unclicked,
	Pressed,
	Unpressed,
	Other,
};


struct Coord
{
	double x, y;
	Coord() :x(0), y(0){}
	Coord(double _x, double _y) :x(_x), y(_y){}
	Coord operator+=(const Coord &input){ x += input.x; y += input.y; return *this; }
	bool operator==(const Coord &input1){ if ((input1.x == x) && (input1.y == y)) return true; return false; }
};

