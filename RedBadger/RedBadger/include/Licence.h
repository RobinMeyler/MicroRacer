#pragma once

#include <iostream>
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include "GUIGlobals.h"

#include "GUI.h"
#include "Label.h"
#include "Xbox360Controller.h"
#include "ResourceManager.h"

class Licence
{
public:
	Licence(ResourceManager & t_gameAssets);
	~Licence();

	void initialize();
	void update(sf::Time t_deltaTime);
	void render(sf::RenderWindow & t_window);
	void handleControllerInput();
	void runAction(std::string & t_actionString);

private:
	int m_count{ 0 };

	sf::Texture m_cloudTexture;
	sf::Texture m_skyTexture;
	sf::Texture m_mountainTexture;
	sf::Texture m_treeTexture;
	sf::Texture m_roadTexture;

	sf::Text m_pressA;
	sf::Font m_font;

	sf::Texture m_carSpritesTexture[4];
	sf::Sprite m_car;
	float carPositionX = 0;

	sf::Sprite m_cloud;
	float cloudX = 0;

	sf::Sprite m_sky;
	float skyX = 0;

	sf::Sprite m_mountain;
	float mountainX = 0;

	sf::Sprite m_tree;
	float treeX = 0;

	sf::Sprite m_road;
	float roadX = 0;

	void UpdateSprite();
	int m_spriteCount = 0;
	int m_spriteTextureIndex = 0;

	bool switchScene = false;


	sf::SoundBuffer m_confirmBuffer;
	sf::Sound m_confirmSFX;

	sf::Texture m_buttonATexture;
	sf::Sprite m_buttonA;
	float m_buttonScale = 1;
	bool m_increase = true;

	bool pressedA = false;
	int m_counterButtonFlash = 0;


	sf::Sprite m_logo;
	sf::Texture m_logoTexture;


};


