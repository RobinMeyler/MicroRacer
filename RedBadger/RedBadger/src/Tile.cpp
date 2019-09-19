#include "Tile.h"

#include <iostream>
Tile::Tile()
{

}

void Tile::initialize(ResourceManager & t_ptrGameAssets)
{
	ptrGameAssets = &t_ptrGameAssets;
}

Tile::~Tile()
{
	
}

void Tile::setPosition(sf::Vector2f t_position)
{
	m_position = t_position;
	m_tileSprite.setPosition(m_position);
}

sf::Vector2f Tile::getPosition()
{
	return m_position;
}

void Tile::setTexture(int t_tileType)
{
	switch (t_tileType)
	{
	case 0:
		//Sand
		m_tileSprite.setTexture(ptrGameAssets->m_gameTextures["Grass"]);
		//m_tileSprite.setTextureRect(m_rect);
		m_tileSprite.setScale(2, 2);
		m_index = 0;
		break;
	case 1:
		// Vertical Road
		m_rect = { 128 * 8, 128 * 7, 128,128 }; // the rect for the texture
		m_tileSprite.setTexture(ptrGameAssets->m_gameTextures["Tile Sheet Two"]);
		m_tileSprite.setTextureRect(m_rect);
		m_tileSprite.scale(2, 2);
		m_index = 1;
		break;
	case 2:
		// Top Left Corner Road
		m_rect = { 128, 0, 128,128 }; // the rect for the texture
		m_tileSprite.setTexture(ptrGameAssets->m_gameTextures["Tile Sheet Two"]);
		m_tileSprite.setTextureRect(m_rect);
		m_tileSprite.scale(2, 2);
		m_index = 2;
		break;
	case 3:
		// straight road horizontal
		m_rect = { 0, 0, 128,128 }; // the rect for the texture
		m_tileSprite.setTexture(ptrGameAssets->m_gameTextures["Tile Sheet Two"]);
		m_tileSprite.setTextureRect(m_rect);
		m_tileSprite.scale(2, 2);
		m_index = 3;
		break;
	case 4:
		// Top Right Corner Road
		m_rect = { 128 * 3, 0, 128,128 }; // the rect for the texture
		m_tileSprite.setTexture(ptrGameAssets->m_gameTextures["Tile Sheet Two"]);
		m_tileSprite.setTextureRect(m_rect);
		m_tileSprite.scale(2, 2);
		m_index = 4;
		break;
	case 5:
		// Bottom Right corner Road
		m_rect = { 128 * 7, 128 * 4, 128,128 }; // the rect for the texture
		m_tileSprite.setTexture(ptrGameAssets->m_gameTextures["Tile Sheet Two"]);
		m_tileSprite.setTextureRect(m_rect);
		m_tileSprite.scale(2, 2);
		m_index = 5;
		break;
	case 6:
		// Bottom Left Corner Road
		m_rect = { 128 * 5, 128 * 4, 128,128 }; // the rect for the texture
		m_tileSprite.setTexture(ptrGameAssets->m_gameTextures["Tile Sheet Two"]);
		m_tileSprite.setTextureRect(m_rect);
		m_tileSprite.scale(2, 2);
		m_index = 6;
		break;
	case 7:
		// Tree
		m_rect = { 128 * 9, 128, 128,128 }; // the rect for the texture
		m_tileSprite.setTexture(ptrGameAssets->m_gameTextures["Tile Sheet"]);
		m_tileSprite.setTextureRect(m_rect);

		m_tileSprite.scale(2, 2);
		m_index = 7;
		break;
	case 8:
		// Raised road
		m_tileSprite.setTexture(ptrGameAssets->m_gameTextures["Raised Road"]);
		m_tileSprite.scale(2, 2);
		m_index = 8;
		break;
	case 9:
		// empty (not used anymore)
		m_tileSprite.setTexture(ptrGameAssets->m_gameTextures["Finish Line"]);
		m_tileSprite.scale(2, 2);
		m_index = 9;
		break;
	case 10:
		// ice road part
		m_tileSprite.setTexture(ptrGameAssets->m_gameTextures["Ice Road"]);
		m_tileSprite.scale(2, 2);
		m_index = 10;
		break;
	case 11:
		// bottom Turn Left road part (AWKWARD TURN)
		m_rect = { 128 * 2, 128 * 5, 128,128 }; // the rect for the texture
		m_tileSprite.setTexture(ptrGameAssets->m_gameTextures["Tile Sheet Two"]);
		m_tileSprite.setTextureRect(m_rect);
		m_tileSprite.scale(2, 2);
		m_index = 11;
		break;
	case 12:
		//Top Turn right road part (AWKWARD TURN)
		m_rect = { 0, 128, 128,128 }; // the rect for the texture
		m_tileSprite.setTexture(ptrGameAssets->m_gameTextures["Tile Sheet Two"]);
		m_tileSprite.setTextureRect(m_rect);
		m_tileSprite.scale(2, 2);
		m_index = 12;
		break;
	case 13:
		//More Top Turn right road part (AWKWARD TURN)
		m_rect = { 128, 128, 128,128 }; // the rect for the texture
		m_tileSprite.setTexture(ptrGameAssets->m_gameTextures["Tile Sheet Two"]);
		m_tileSprite.setTextureRect(m_rect);
		m_tileSprite.scale(2, 2);
		m_index = 13;
		break;
	case 14:
		// MORE bottom Turn Left road part (AWKWARD TURN)
		m_rect = { 128 * 3, 128 * 7, 128,128 }; // the rect for the texture
		m_tileSprite.setTexture(ptrGameAssets->m_gameTextures["Tile Sheet Two"]);
		m_tileSprite.setTextureRect(m_rect);
		m_tileSprite.scale(2, 2);
		m_index = 14;
		break;
	case 15:
		//MORE TEXTURE FOR AWKWARD TURN
		m_rect = { 128 * 4, 128 * 7, 128,128 }; // the rect for the texture
		m_tileSprite.setTexture(ptrGameAssets->m_gameTextures["Tile Sheet Two"]);
		m_tileSprite.setTextureRect(m_rect);
		m_tileSprite.scale(2, 2);
		m_index = 15;
		break;
	case 16:
		//MORE TEXTURE FOR AWKWARD TURN
		m_rect = { 128 * 3, 128 * 3, 128,128 }; // the rect for the texture
		m_tileSprite.setTexture(ptrGameAssets->m_gameTextures["Tile Sheet Two"]);
		m_tileSprite.setTextureRect(m_rect);
		m_tileSprite.scale(2, 2);
		m_index = 16;
		break;
	case 17:
		// UNUSED
		break;
	case 18:
		// big red tent
		m_tileSprite.setTexture(ptrGameAssets->m_gameTextures["Big Red Tent"]);
		//m_tileSprite.scale(2, 2);
		m_index = 18;
		break;
	case 19:
		// small red tent
		m_tileSprite.setTexture(ptrGameAssets->m_gameTextures["Red Tent"]);
		//m_tileSprite.scale(2, 2);
		m_index = 19;
		break; 
	
	default:
		break;
	}
}

sf::Sprite * Tile::getSprite()
{
	return &m_tileSprite;
}

int Tile::getIndex()
{
	return m_index;
}

void Tile::setIndex(int t_index)
{
	m_index = t_index;
}

void Tile::render(sf::RenderWindow & t_window)
{
	t_window.draw(m_tileSprite);
}
