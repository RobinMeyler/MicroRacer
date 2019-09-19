#pragma once
/// <summary>
/// Created by Paul O'Callaghan 21/03/2019
/// This class is to be inherited by Input Manager for distinguishing single press input
/// </summary>

// Make use of key hold for detecting input
#include "KeyHold.h"

class KeyPress
{
public:
	KeyPress();
	~KeyPress();
	bool A();
	bool B();
	bool X();
	bool Y();
	bool Start();

	bool Up();
	bool Down();
	bool Left();
	bool Right();

	bool RB();
	bool LB();

	//bool RightTrigger();
	//bool LeftTrigger();

private:
	bool pressedA = true;
	bool pressedB = true;
	bool pressedX = true;
	bool pressedY = true;
	
	bool pressedStart = true;

	bool pressedUp = true;
	bool pressedDown = true;
	bool pressedLeft = true;
	bool pressedRight = true;

	bool pressedRB = true;
	bool pressedLB = true;

	bool pressedRightTrigger = true;
	bool pressedLeftTrigger = true;


	KeyHold Hold;

};