#pragma once

/// <summary>
/// Class For Mini Map
/// </summary>



#include "ResourceManager.h"


class MiniMap
{
public:
	MiniMap();
	~MiniMap();

	void initialize();
	void update(sf::Time t_deltaTime, sf::Vector2f t_playersPosition, sf::Vector2f t_AIPositions[3]);
	void render(sf::RenderWindow & t_window);




private:

	sf::Texture m_miniMapTexture;
	sf::Sprite m_miniMap;

	sf::CircleShape m_player;
	sf::CircleShape m_AI[3];

	float m_tempXPos;
	float m_tempYPos;

	sf::RectangleShape m_outline; // an outline for the mini map

};