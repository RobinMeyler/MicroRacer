#pragma once

#include <iostream>
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include "GUIGlobals.h"
#include "GUI.h"
#include "Xbox360Controller.h"
#include "Thor/Resources.hpp"
#include "ResourceManager.h"
#include "Car.h"

class Rules
{
public:
	Rules();
	Rules(ResourceManager & t_gameAssets);
	~Rules();
	void clearGUI();
	void initialize();
	void update(sf::Time t_deltaTime);
	void render(sf::RenderWindow & t_window);
	void handleControllerInput();
	void runAction(std::string & t_actionString);

private:
	Car m_testCar;
	sf::Sprite testSpa;
	int m_count{ 0 };
};

