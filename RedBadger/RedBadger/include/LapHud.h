#pragma once

#include "ResourceManager.h"
#include "Transform.h"
#include "GUIGlobals.h"


class LapHUD
{
public:
	LapHUD();
	~LapHUD();
	void setPosition(sf::Vector2f t_position);
	sf::Sprite getCurrentLapSprite();

	/// <summary>
	/// Set sprites for the LapHUD
	/// </summary>
	/// <param name="t_currentLap">pass in the currrent lap player is on</param>
	/// <param name="t_maxLap">pass the max laps of the race track</param>
	void setLapSprite(int t_currentLap, int t_maxLap);

private:
	// Handles textures 0-9
	sf::Texture m_numberTextures[10];
	sf::Sprite m_currentLapSprite;
	sf::Sprite m_maxLapSprite;

};