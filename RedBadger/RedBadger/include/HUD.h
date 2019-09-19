/// <summary>
/// Created 25/03/2019 Paul O'Callagghan
/// No known bugs
/// Time Spent so far: 2 hours 30 minutes
/// </summary>
#pragma once


#include "ResourceManager.h"	
#include "SteeringWheelHUD.h"
#include "Accelerator.h"
#include "Brake.h"
#include "Speedometer.h"
#include "LapHud.h"

#include <iostream>

class HUD
{
private:


	 

public:
	HUD();
	~HUD();

	// sets the hud position on the screen
	void setPosition(sf::Vector2f t_position);

	void render(sf::RenderWindow & t_window);

	void update(sf::Time t_deltaTime);
	void setTimeText(float t_time);
	// Positon

	// Lap
	LapHUD lapHUD;

	// Speed to show in HUD
	Speedometer speedometer;

	// Accelerator
	Accelerator accelerator;

	// Brake
	Brake brake;
	// Wheel
	SteeringWheelHUD steeringWheel;

	// Text for the speed 
	sf::Text currentSpeedText;
	sf::Font speedFont;
	sf::Text m_gameTime;




};