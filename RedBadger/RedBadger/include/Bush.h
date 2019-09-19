#pragma once

#include "GUIGlobals.h"
#include "ResourceManager.h"
#include "Transform.h"
#include "Collider.h"
#include <SFML/Graphics.hpp>

class Bush
{
public:
	Bush();
	~Bush();

	Transform transform;

	void setActive(bool t_active);
	bool isActive();
	sf::Sprite getSprite();
	sf::Vector2f getSize();
	void setPosition(sf::Vector2f t_position);

	void render(sf::RenderWindow & t_window);
	/*
	sf::Sprite bush;
	sf::Texture bushTexture;
	*/

	sf::Sprite bush;
	sf::Texture bushTexture;
	sf::Vector2f m_spriteSize;
	bool m_active = false;

	void init();
	void initTexture();
private:/*
	sf::Sprite bush;
	sf::Texture bushTexture;
	sf::Vector2f m_spriteSize;
	bool m_active = false;*/

	static bool textureSet;



};


