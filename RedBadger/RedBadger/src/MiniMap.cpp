#include "MiniMap.h"

MiniMap::MiniMap()
{
	initialize();
}

MiniMap::~MiniMap()
{

}

void MiniMap::initialize()
{
	m_miniMapTexture.loadFromFile("./ASSETS/IMAGES/FreshMiniMap.PNG");
	m_miniMap.setTexture(m_miniMapTexture);
	m_miniMap.setScale(0.2,0.2);
	m_miniMap.setColor(sf::Color(sf::Color(255, 255, 255, 200)));

	// PLAYER n AI
	m_player.setFillColor(sf::Color::Green);
	m_player.setRadius(5);
	m_player.setOrigin(m_player.getRadius(), m_player.getRadius());

	for (int i = 0; i < 3; i++)
	{
		m_AI[i].setFillColor(sf::Color::Blue);
		m_AI[i].setRadius(5);
		m_AI[i].setOrigin(m_AI[i].getRadius(), m_AI[i].getRadius());
	}

	// Outline
	m_outline.setSize(sf::Vector2f(1200 * .2, 800 * .2));
	m_outline.setFillColor(sf::Color::Transparent);
	m_outline.setOutlineColor(sf::Color::Black);
	m_outline.setOutlineThickness(3);
}

void MiniMap::update(sf::Time t_deltaTime, sf::Vector2f t_playersPosition, sf::Vector2f t_AIPositions[3])
{
	m_miniMap.setPosition(t_playersPosition.x - 600 + 3, t_playersPosition.y - 400 + 3);
	m_outline.setPosition(m_miniMap.getPosition());

	//set players position
	m_tempXPos = t_playersPosition.x / 3584;
	m_tempXPos = m_tempXPos * (.2 * 1200);
	m_tempXPos = m_miniMap.getPosition().x + m_tempXPos;

	m_tempYPos = t_playersPosition.y / 3584;
	m_tempYPos = m_tempYPos * (.2 * 800);
	m_tempYPos = m_miniMap.getPosition().y + m_tempYPos;

	m_player.setPosition(m_tempXPos, m_tempYPos);

	// set AI positions
	for (int i = 0; i < 3; i++)
	{
		m_tempXPos = t_AIPositions[i].x / 3584;
		m_tempXPos = m_tempXPos * (.2 * 1200);
		m_tempXPos = m_miniMap.getPosition().x + m_tempXPos;

		m_tempYPos = t_AIPositions[i].y / 3584;
		m_tempYPos = m_tempYPos * (.2 * 800);
		m_tempYPos = m_miniMap.getPosition().y + m_tempYPos;

		m_AI[i].setPosition(m_tempXPos, m_tempYPos);
	}
}

void MiniMap::render(sf::RenderWindow & t_window)
{
	t_window.draw(m_miniMap);
	for (int i = 0; i < 3; i++)
	{
		t_window.draw(m_AI[i]);
	}
	t_window.draw(m_player);
	t_window.draw(m_outline);
}
