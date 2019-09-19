#include "LapHud.h"

LapHUD::LapHUD()
{
	// Set up number textures
	for (int index = 0; index < 10; index++)
	{
		std::string indexString = std::to_string(index);

		// numbers of images are also there names in the image folder
		std::string url = "./ASSETS/IMAGES/HUD/" + indexString + ".png";

		if (!m_numberTextures[index].loadFromFile(url))
		{
			std::cout << "Could not find file at " << url << std::endl;
		}
	}
}

LapHUD::~LapHUD()
{
}

void LapHUD::setPosition(sf::Vector2f t_position)
{
		sf::Vector2f offset = { 450,-120 };
		m_currentLapSprite.setPosition(sf::Vector2f(t_position.x + offset.x, t_position.y + offset.y));
		m_currentLapSprite.setPosition(sf::Vector2f(t_position.x + offset.x + 50, t_position.y + offset.y));
	
}

sf::Sprite LapHUD::getCurrentLapSprite()
{
	return m_currentLapSprite;
}

void LapHUD::setLapSprite(int t_currentLap, int t_maxLap)
{
	
		if (t_currentLap <= t_maxLap)
		{
			m_currentLapSprite.setTexture(m_numberTextures[t_currentLap]);
		}

		m_maxLapSprite.setTexture(m_numberTextures[t_maxLap]);
}
