#pragma once

#include <iostream>
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include "GUIGlobals.h"
#include "ResourceManager.h"
#include "GUI.h"
#include "Xbox360Controller.h"

class Credits
{
public:
	Credits(ResourceManager & t_gameAssets);
	~Credits();
	void clearGUI();
	void initialize();
	void update(sf::Time t_deltaTime);
	void render(sf::RenderWindow & t_window);
	void handleControllerInput();
	void runAction(std::string & t_actionString);
	void shrinkAnimation(sf::Text * t_title, sf::Text * t_nameOne, sf::Text * t_nameTwo, sf::Text * t_nameThree);	// function that runs the text animation

private:
	sf::Font m_font;							// font used for text
	sf::RectangleShape m_screenOutline;			// rectangle outline for screen edge

	std::vector <sf::Text> m_titles;			// std::vector to store the titles in
	std::vector <sf::Text> m_names;				// std::vector to store the names in

	sf::SoundBuffer m_backScreenBuffer;			// Sound effect for B press (previous screen)
	sf::Sound m_backScreenSound;

	GUI m_GUI;

	enum animationStage { Grow, Pause, ShrinkAway };	// enum for stages
	animationStage m_stage{ animationStage::Grow };	// initially growing
	int index = 0;									// index for use on m_names
	int pauseCount = 0;								// count for pause timer
};

