#include "KeyHold.h"
bool KeyHold::A()
{
	controller.update();
	return controller.m_currentState.A;
}

bool KeyHold::B()
{
	controller.update();

	return controller.m_currentState.B;
}

bool KeyHold::X()
{
	controller.update();

	return controller.m_currentState.X;
}

bool KeyHold::Y()
{
	controller.update();

	return controller.m_currentState.Y;
}

bool KeyHold::Start()
{
	controller.update();

	return controller.m_currentState.Start;
}

bool KeyHold::Up()
{
	controller.update();

	if (controller.m_currentState.LeftThumbStick.y < -controllerDeadZone || controller.m_currentState.DpadUp)
	{
		return true;
	}

	return false;
}

bool KeyHold::Down()
{
	controller.update();

	if (controller.m_currentState.LeftThumbStick.y > controllerDeadZone || controller.m_currentState.DpadDown)
	{
		return true;
	}

	return false;
}

bool KeyHold::Left()
{
	controller.update();

	if (controller.m_currentState.LeftThumbStick.x < -controllerDeadZone || controller.m_currentState.DpadLeft)
	{
		return true;
	}

	return false;
}

bool KeyHold::Right()
{
	controller.update();

	if (controller.m_currentState.LeftThumbStick.x > controllerDeadZone || controller.m_currentState.DpadRight)
	{
		return true;
	}

	return false;
}

bool KeyHold::RB()
{
	controller.update();

	return controller.m_currentState.RB;
}

bool KeyHold::LB()
{
	controller.update();

	return controller.m_currentState.LB;
}

bool KeyHold::RightTrigger()
{
	controller.update();

	if (controller.m_currentState.RTrigger < -10)
	{
		return true;
	}
	return false;
}

bool KeyHold::LeftTrigger()
{
	controller.update();
	if (controller.m_currentState.LTrigger > 10)
	{
		return true;
	}
	return false;
}

Xbox360Controller & KeyHold::getController()
{
	controller.update();
	return controller;
}
