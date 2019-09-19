/// <summary>
/// Created 25/03/2019 Paul O'Callaghan
/// 
/// 
/// </summary>
#pragma once
#include "ResourceManager.h"
#include "Transform.h"
#include "GUIGlobals.h"

/// <summary>
/// USed for displaying information about the Steering Wheel during a race on the HUD
/// </summary>
class SteeringWheelHUD
{
private:

	Transform transform;

	sf::Sprite sprite;
	
	sf::Texture texture;

	// limit of degrees of rotation based on euler angles
	float clampSteeringAxis = 45;
	const float TURNING_SPEED = 140; // value for setting the speed the wheel turns

	// used to offset the position of the sprite on the hud
	sf::Vector2f offset = { 390,255 };
public:
	SteeringWheelHUD();
	~SteeringWheelHUD();

	void setSteeringWheelRotation(sf::Time t_deltaTime);
	void setSteeringWheelPosition(sf::Vector2f t_position);
	void offsetChange(sf::Time t_deltaTime);
	sf::Sprite getSprite();
	
};