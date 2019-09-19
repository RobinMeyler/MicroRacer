#include "SteeringWheelHUD.h"

SteeringWheelHUD::SteeringWheelHUD()
{
	// Set up steeringWHeel
	if (!texture.loadFromFile("./ASSETS/IMAGES/HUD/steering.png"))
	{
		std::cout << "Could not find file at " << "./ASSETS/IMAGES/HUD/steering.png" << std::endl;
	}

	sprite.setTexture(texture);
	// Reduce the sixe of the wheel by 4/5ths
	transform.scale = { .2f,.2f };

	sprite.setScale(transform.scale);
	
	// Texture size is 231 wide and 208 high
	sprite.setOrigin(231,208);

}


SteeringWheelHUD::~SteeringWheelHUD()
{
}

void SteeringWheelHUD::setSteeringWheelRotation(sf::Time t_deltaTime)
{
	// LEFT
	if (INPUT.Hold.Left())
	{
		if (transform.rotation.z > -clampSteeringAxis)
		{
			transform.rotation.z -= (TURNING_SPEED * t_deltaTime.asSeconds());
		}
		else
		{
			transform.rotation.z = -clampSteeringAxis;
		}
	} // END LEFT

	// RIGHT
	else if (INPUT.Hold.Right())
	{
		if (transform.rotation.z < clampSteeringAxis)
		{
			transform.rotation.z += (TURNING_SPEED * t_deltaTime.asSeconds());
		}
		else
		{
			transform.rotation.z = clampSteeringAxis;
		}
	} // END RIGHT

	// NO INPUT
	else
	{
		if (transform.rotation.z >= -clampSteeringAxis && transform.rotation.z < -5.3f)
		{
			transform.rotation.z += (TURNING_SPEED * t_deltaTime.asSeconds());
		}
		else if (transform.rotation.z <= clampSteeringAxis && transform.rotation.z > 5.3f)
		{
			transform.rotation.z -= (TURNING_SPEED * t_deltaTime.asSeconds());
		}
		else
		{
			transform.rotation.z = 0;
		}
	}// END NO INPUT

	// set sprite roation to z axis rotation
	sprite.setRotation(transform.rotation.z);
}

// Pass the camera position so that the HUD locks to the same position on screen
void SteeringWheelHUD::setSteeringWheelPosition(sf::Vector2f t_cameraPosition)
{
	transform.position = t_cameraPosition + offset;

	sprite.setPosition(transform.position);
}



// used for getting sprite
sf::Sprite SteeringWheelHUD::getSprite()
{
	return sprite;
}





