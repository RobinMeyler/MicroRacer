#pragma once

#include <iostream>
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include "ResourceManager.h"
#include "GUIGlobals.h"

#include "GUI.h"
#include "Xbox360Controller.h"

class Options
{
public:
	Options(ResourceManager & t_gameassets);
	~Options();
	void clearGUI();
	void initialize();
	void update(sf::Time t_deltaTime);
	void render(sf::RenderWindow & t_window);
	void handleControllerInput();
	void runAction(std::string & t_actionString);
	void setupShader();
private:
	int m_count{ 0 };
	float m_rotate{ 3 };
	GUI m_gui;

	sf::Font m_font;
	sf::Sprite m_wheel;
	sf::Sprite m_body;


	sf::SoundBuffer m_wheelTurnBuffer;
	sf::Sound m_wheelTurnSFX;
	sf::SoundBuffer m_confirmBuffer;
	sf::Sound m_confirmSFX;
	sf::SoundBuffer m_backBuffer;
	sf::Sound m_backSFX;

	sf::Sprite renderSprite;
	sf::RenderTexture renderTexture;
	sf::Texture distortionMap;
	sf::Shader shader1;
	float distortionFactor = .015f;
	float riseFactor = .15f;
	int m_delay{ 0 };
	sf::Clock clock;
};

