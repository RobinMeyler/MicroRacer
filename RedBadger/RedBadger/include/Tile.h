#pragma once

#include "SFML/Graphics.hpp"
#include "ResourceManager.h"

/// <summary>
/// A class that holds info for every tile
/// Position/Texture/Friction etc..
/// </summary>
class Tile
{
public:

	Tile();
	void initialize(ResourceManager & t_ptrGameAssets);
	~Tile();
	void setPosition(sf::Vector2f t_position);
	sf::Vector2f getPosition();
	void setTexture(int t_tileType);
	sf::Sprite * getSprite();
	int getIndex();
	
	void setIndex(int t_index);
	int m_index{ 0 };
	void render(sf::RenderWindow &t_window);

private:
	ResourceManager * ptrGameAssets;

	sf::Vector2f m_position;
	//sf::Texture m_texture;     // 
	sf::IntRect m_rect;
	sf::Sprite m_tileSprite;
};