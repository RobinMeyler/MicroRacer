/// <summary>
/// Began 201/03/2019 Paul O'Callghan
/// Making Heavy Use of Robins Xbox360Controller which is declared an object in GUIGlobals to detec types of inputs such as pressed and held down
/// 
/// Known Bugs: Up down left right detection not accurate to actual input needs to be swapped around
/// </summary>
#pragma once
#include "KeyPress.h"
#include "KeyHold.h"
class InputManager
{
public:
	InputManager();
	~InputManager();

	KeyHold Hold;
	KeyPress PressOnce;



private:

protected:

};