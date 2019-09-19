#pragma once
#include "SFML/Graphics.hpp"
#include "ResourceManager.h"

class PlusOneDrop
{
public:
	PlusOneDrop(ResourceManager & t_gameAssets);
	~PlusOneDrop();

	void initialize();
	void update(sf::Time t_deltaTime);
	void render(sf::RenderWindow & t_window);
	void nextPosition();
	sf::RectangleShape getSprite();

private:
	sf::RectangleShape m_image;
	sf::Vector2f positions[5];
	int m_currentPos{ 0 };
	enum class animationState { Grow, Shrink};
	animationState m_state{ animationState::Grow };
};