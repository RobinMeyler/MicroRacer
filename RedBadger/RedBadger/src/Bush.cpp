#include "Bush.h"

Bush::Bush()
{
	
	
}

Bush::~Bush()
{
	std::cout << "~Bush()" << std::endl;
}

void Bush::setActive(bool t_active)
{
	m_active = t_active;
}

bool Bush::isActive()
{
	return m_active;
}

sf::Sprite Bush::getSprite()
{
	return bush;
}

sf::Vector2f Bush::getSize()
{
	return m_spriteSize;
}

void Bush::setPosition(sf::Vector2f t_position)
{
	bush.setPosition(t_position);
}

void Bush::render(sf::RenderWindow & t_window)
{
	t_window.draw(bush);
}

void Bush::init()
{
	setActive(false);

	if (!bushTexture.loadFromFile("./ASSETS/IMAGES/bush.png"))
	{
		std::cout << "Could not find file at " << "./ASSETS/IMAGES/bush.png)" << std::endl;
	}

	bush.setTexture(bushTexture);
	bush.setOrigin(sf::Vector2f(43, 43));
	
	m_spriteSize = static_cast<sf::Vector2f>(bush.getTexture()->getSize());
}
