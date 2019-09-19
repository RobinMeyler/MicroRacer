#include "Accelerator.h"

Accelerator::Accelerator()
{
	// Set up Accerator
	if (!texture.loadFromFile("./ASSETS/IMAGES/HUD/Accelerator.png"))
	{
		std::cout << "Could not find file at " << "./ASSETS/IMAGES/HUD/Accelerator.png" << std::endl;
	}

	sprite.setTexture(texture);

	// Reduce the sixe of the wheel by 2/3
	transform.scale = { .3f,.3f };

	sprite.setScale(transform.scale);

}

Accelerator::~Accelerator()
{
}

void Accelerator::setPosition(sf::Vector2f t_cameraPosition)
{
	transform.position = t_cameraPosition + offset;

	sprite.setPosition(transform.position);
}

sf::Sprite Accelerator::getSprite()
{
	return sprite;
}

void Accelerator::setOpacity(sf::Time t_deltaTime)
{
	if (INPUT.Hold.RightTrigger())
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
