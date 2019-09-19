#include "PlusOneDrop.h"

PlusOneDrop::PlusOneDrop(ResourceManager & t_gameAssets) 
{
	m_image.setTexture(&t_gameAssets.m_gameTextures["Plus One Drop"]);
	m_image.setOrigin(m_image.getSize().x / 2, m_image.getSize().x / 2);
	initialize();
}

PlusOneDrop::~PlusOneDrop()
{
}

void PlusOneDrop::initialize()
{
	positions[0] = sf::Vector2f(2900, 1100);
	positions[1] = sf::Vector2f(2100, 1400);
	positions[2] = sf::Vector2f(1000, 2155); //hard one
	positions[3] = sf::Vector2f(550, 700);
	positions[0] = sf::Vector2f(2100, 600);
}

void PlusOneDrop::update(sf::Time t_deltaTime)
{
	m_image.setPosition(positions[m_currentPos]);

	switch (m_state)
	{
	case PlusOneDrop::animationState::Grow:
		m_image.setSize(sf::Vector2f(m_image.getSize().x + 0.5, m_image.getSize().x + 0.5));
		break;
	case PlusOneDrop::animationState::Shrink:
		m_image.setSize(sf::Vector2f(m_image.getSize().x - 0.5, m_image.getSize().x - 0.5));
		break;
	default:
		break;
	}

	if (m_image.getSize().x > 50)
	{
		m_state = animationState::Shrink;
	}
	else if (m_image.getSize().x < 40)
	{
		m_state = animationState::Grow;
	}


}

void PlusOneDrop::render(sf::RenderWindow & t_window)
{
	t_window.draw(m_image);
}

void PlusOneDrop::nextPosition()
{
	m_currentPos++;
}

sf::RectangleShape PlusOneDrop::getSprite()
{
	return m_image;
}
