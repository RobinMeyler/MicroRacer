/// <summary>
/// Created by Paul O'Callaghan 25/03/19
/// Speedometer for interacting with the HUD
/// No Known Bugs
/// </summary>
#pragma once


#include "ResourceManager.h"	
#include "GUIGlobals.h"

class Speedometer
{
public:
	Speedometer();
	~Speedometer();


	// pass in speed form car for it to set the hud parameters
	void setSpeedDisplay(int t_speed);

	void setPosition(sf::Vector2f t_position);

	/// <summary>
	/// returns the first decimal of a number e.g. 143 the first decimal is 1
	/// </summary>
	/// <param name="t_speed">speed that is to be captured</param>
	/// <returns></returns>
	int digitForFirst(int t_speed);

	/// <summary>
	/// returns the last decimal of a number
	/// </summary>
	/// <param name="t_speed"></param>
	/// <returns></returns>
	int digitForOne(int t_speed);

	// for getting the speedometervalues
	sf::Sprite getLastDigitSprite();
	sf::Sprite getMiddleDigitSprite();
	sf::Sprite getFirstDigitSprite();
	sf::Sprite getMetricSprite();


private:

	// Sprites to display speed
	sf::Sprite one; // 0-9
	sf::Sprite ten;// 10-99
	sf::Sprite hundred;// 100+
	sf::Sprite metricSprite; // kilometers sprite



	// Texture Array of sprites numers 0 - 9
	sf::Texture speedHUDNumbers[10];
	sf::Texture kilometersPerHourTexture;

};
