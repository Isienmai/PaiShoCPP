#pragma once
#include "SharedData.h"
class Mouse
{
	Coord currentMouseLocation, previousMouseLocation;
	bool currentMouseButtonDown, mouseButtonStateChange;

public:
	Mouse();
	~Mouse();
	MouseState GetNewMouseState();
	MouseState GetMouseState();
	Coord mouseLocation(){ return currentMouseLocation; }
	Coord lastMouseLocation(){ return previousMouseLocation; }
};

