#include "KeyPress.h"
#include <iostream>
KeyPress::KeyPress()
{
}

KeyPress::~KeyPress()
{
	std::cout << "ggggg" << std::endl;
}

bool KeyPress::A()
{
	if (Hold.A())
	{
		if (pressedA == false)
		{
			pressedA = true;
			return true;
		}
		// If button already been pressed once and not let go
		return false;
	}
	// Not held
	pressedA = false;
	return false;
}

bool KeyPress::B()
{
	if (Hold.B())
	{
		if (pressedB == false)
		{
			pressedB = true;
			return true;
		}
		// If button already been pressed once and not let go
		return false;
	}

	// Not held
	pressedB = false;
	return false;
}

bool KeyPress::X()
{
	if (Hold.X())
	{
		if (pressedX == false)
		{
			pressedX = true;
			return true;
		}
		// If button already been pressed once and not let go
		return false;
	}
	// Not held
	pressedX = false;
	return false;
}

bool KeyPress::Y()
{
	if (Hold.Y())
	{
		if (pressedY == false)
		{
			pressedY = true;
			return true;
		}
		// If button already been pressed once and not let go
		return false;
	}

	// Not held
	pressedY = false;
	return false;
}

bool KeyPress::Start()
{
	if (Hold.Start())
	{
		if (pressedStart == false)
		{
			pressedStart = true;
			return true;
		}
		// If button already been pressed once and not let go
		return false;
	}

	// Not held
	pressedStart = false;
	return false;
}

bool KeyPress::Up()
{
	if (Hold.Up())
	{
		if (pressedUp == false)
		{
			pressedUp = true;
			return true;
		}
		// If button already been pressed once and not let go
		return false;
	}

	// Not held
	pressedUp = false;
	return false;
}

bool KeyPress::Down()
{
	if (Hold.Down())
	{
		if (pressedDown == false)
		{
			pressedDown = true;
			return true;
		}
		// If button already been pressed once and not let go
		return false;
	}

	// Not held
	pressedDown = false;
	return false;
}

bool KeyPress::Left()
{
	if (Hold.Left())
	{
		if (pressedLeft == false)
		{
			pressedLeft = true;
			return true;
		}
		// If button already been pressed once and not let go
		return false;
	}
	pressedLeft = false;
	return false;
}

bool KeyPress::Right()
{
	if (Hold.Right())
	{
		if (pressedRight == false)
		{
			pressedRight = true;
			return true;
		}
		// If button already been pressed once and not let go
		return false;
	}

	// Not held
	pressedRight = false;
	return false;
}

bool KeyPress::RB()
{
	if (Hold.RB())
	{
		if (pressedRB == false)
		{
			pressedRB = true;
			return true;
		}
		// If button already been pressed once and not let go
		return false;
	}
	pressedRB = false;
	return false;
}

bool KeyPress::LB()
{
	if (Hold.LB())
	{
		if (pressedLB == false)
		{
			pressedLB = true;
			return true;
		}
		// If button already been pressed once and not let go
		return false;
	}
	// 
	pressedLB = false;
	return false;
}