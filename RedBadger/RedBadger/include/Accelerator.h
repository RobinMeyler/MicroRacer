#pragma once

#include "GUIGlobals.h"
#include "ResourceManager.h"
#include "Transform.h"

class Accelerator
{
public:
	Accelerator();
	~Accelerator();
	/// <summary>
	/// sets position of the accelerator relative to the camera position
	/// </summary>
	/// <param name="t_cameraPosition"> The camera position the HUD is following on screen</param>
	void setPosition(sf::Vector2f t_cameraPosition);
	sf::Sprite getSprite();
	void setOpacity(sf::Time t_deltaTime);
private:
	// Min , max alpha/opacity values
	const float ALPHA_MIN = 100.0f, ALPHA_MAX = 254.0f;
	float currentAlpha = 100.0f;
	const float CHANGE_SPEED = 400.0f;

	sf::Vector2f offset = { 390,305 };
	sf::Sprite sprite;
	sf::Texture texture;
	Transform transform;
};