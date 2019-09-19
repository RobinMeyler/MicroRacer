#include "Rules.h"
#include "Game.h"


// using Rules for testing
Rules::Rules()
{
}

Rules::Rules(ResourceManager & t_gameAssets) :
	m_testCar(t_gameAssets)
{
}


Rules::~Rules()
{
}

void Rules::clearGUI()
{

}

void Rules::initialize()
{
	testSpa.setPosition(100, 100);
}

void Rules::update(sf::Time t_deltaTime)
{
	handleControllerInput();
	m_testCar.update(t_deltaTime);
}

void Rules::render(sf::RenderWindow & t_window)
{
	t_window.draw(testSpa);
	m_testCar.render(t_window);
}


void Rules::handleControllerInput()
{
	if (INPUT.Hold.A() == true)
	{
		m_testCar.increaseSpeed();
	}
	if (INPUT.Hold.B() == true)
	{
		m_testCar.decreaseSpeed();
	}
	//if (GAME_CONTROLLER.m_currentState.LeftThumbStick.y > 50 || GAME_CONTROLLER.m_currentState.DpadDown == true)
	//{
	//}
	//if (GAME_CONTROLLER.m_currentState.LeftThumbStick.y < -50 || GAME_CONTROLLER.m_currentState.DpadUp == true)
	//{

	//}
	if (INPUT.Hold.Right() == true)
	{
		m_testCar.setRotation(m_testCar.getRotation() + 1.5);
	}
	if (INPUT.Hold.Left() == true)
	{
		m_testCar.setRotation(m_testCar.getRotation() - 1.5);
	}

}

void Rules::runAction(std::string & t_actionString)
{


}