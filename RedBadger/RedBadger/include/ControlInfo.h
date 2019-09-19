#pragma once

#include <iostream>
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include "GUIGlobals.h"
#include "ResourceManager.h"
#include "GUI.h"
#include "Xbox360Controller.h"


class ControlInfo
{
public:
	ControlInfo(ResourceManager & t_gameAssets);
	~ControlInfo();
	void clearGUI();
	void initialize();
	void update(sf::Time t_deltaTime);
	void render(sf::RenderWindow & t_window);
	void handleControllerInput();
	void runAction(std::string & t_actionString);

private:
	int m_count{ 0 };
	sf::Font m_font;
	sf::Sprite border;
	sf::Sprite m_a;
	sf::Sprite m_rt;
	sf::Sprite m_lt;
	sf::Sprite m_ls;

	GUI m_gui;
};

