#include "HUD.h"

HUD::HUD()
{
	currentSpeedText.setPosition(80, 80);
	currentSpeedText.setFillColor(sf::Color::Blue);

	if (!speedFont.loadFromFile("./ASSETS/FONTS/BBrick.ttf"))
	{
		std::cout << "Error loading BBrick.ttf font" << std::endl;
	}
	currentSpeedText.setFont(speedFont);
	m_gameTime.setString("Time: ");
	m_gameTime.setFillColor(sf::Color::Blue);
	m_gameTime.setOutlineThickness(2);
	m_gameTime.setOutlineColor(sf::Color::Black);
	m_gameTime.setPosition(80, 80);
	m_gameTime.setFont(speedFont);
	m_gameTime.setCharacterSize(30);
}

HUD::~HUD()
{
}


void HUD::setPosition(sf::Vector2f t_position)
{
	steeringWheel.setSteeringWheelPosition(t_position);
	accelerator.setPosition(t_position);
	brake.setPosition(t_position);
	speedometer.setPosition(t_position);
	lapHUD.setPosition(t_position);
	m_gameTime.setPosition(t_position + sf::Vector2f{ 400, -300 });
}

void HUD::render(sf::RenderWindow & t_window)
{
	t_window.draw(currentSpeedText);

	// Speedometer
	t_window.draw(speedometer.getLastDigitSprite());
	t_window.draw(speedometer.getMiddleDigitSprite());
	t_window.draw(speedometer.getFirstDigitSprite());
	t_window.draw(speedometer.getMetricSprite());

	t_window.draw(steeringWheel.getSprite());
	t_window.draw(accelerator.getSprite());
	t_window.draw(brake.getSprite());

	t_window.draw(lapHUD.getCurrentLapSprite());
	t_window.draw(m_gameTime);
}

void HUD::update(sf::Time t_deltaTime)
{
	steeringWheel.setSteeringWheelRotation(t_deltaTime);
	accelerator.setOpacity(t_deltaTime);
	brake.setOpacity(t_deltaTime);

}

void HUD::setTimeText(float t_time)
{
	m_gameTime.setString("Time: " + std::to_string(t_time));
}


