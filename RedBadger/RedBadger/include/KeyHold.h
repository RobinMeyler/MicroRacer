#pragma once
/// <summary>
/// Created by Paul O'Callaghan 21/03/2019
/// This class is to be inherited by Input Manager for distinguishing held input
/// </summary>

#include "Xbox360Controller.h"

class KeyHold
{
public:
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

	bool RightTrigger();
	bool LeftTrigger();

	Xbox360Controller & getController();
private:
	Xbox360Controller controller;

protected:
	float controllerDeadZone = 50;
};