#pragma once
#include <SFML/Graphics.hpp>
#include "ResourceManager.h"
class Barrier
{
public:
	Barrier(ResourceManager & t_gameAssets);
	~Barrier();
	
	sf::Sprite m_barrierBox;
private:
	
};

