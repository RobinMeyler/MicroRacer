#include "Brake.h"

Brake::Brake()
{
	// Set up Brake sprite and textures
	if (!texture.loadFromFile("./ASSETS/IMAGES/HUD/Brake.png"))
	{
		std::cout << "Could not find file at " << "./ASSETS/IMAGES/HUD/Brake.png" << std::endl;
	}

	sprite.setTexture(texture);

	// Reduce the sixe of the wheel by 2/3
	transform.scale = { .3f,.3f };

	sprite.setScale(transform.scale);
}

Brake::~Brake()
{
}

void Brake::setPosition(sf::Vector2f t_cameraPosition)
{
	transform.position = t_cameraPosition + offset;

	sprite.setPosition(transform.position);
}

sf::Sprite Brake::getSprite()
{
	return sprite;
}

void Brake::setOpacity(sf::Time t_deltaTime)
{
	if (INPUT.Hold.LeftTrigger())
	{
		if (currentAlpha < ALPHA_MAX)
		{
			currentAlpha += CHANGE_SPEED * t_deltaTime.asSeconds();
		}
		else
		{
			currentAlpha = 255;
		}
	}
	else
	{
		if (currentAlpha > ALPHA_MIN)
		{
			currentAlpha -= CHANGE_SPEED * t_deltaTime.asSeconds();
		}
	}

	// set the NEW values to sprite
	sprite.setColor(sf::Color(255, 255, 255, currentAlpha));
}
