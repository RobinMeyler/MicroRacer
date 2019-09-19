#include "CheckpointBox.h"
#include <iostream>


CheckpointBox::CheckpointBox()
{
	m_checkBox.setFillColor(sf::Color::Red);
}

CheckpointBox::CheckpointBox(sf::Vector2f t_size, sf::Vector2f t_position, float t_rotation):
	m_size(t_size)		// Instead of call getSize every time
{
	m_checkBox.setPosition(t_position);
	m_checkBox.setSize(t_size);
	m_checkBox.setRotation(t_rotation);
	m_checkBox.setFillColor(sf::Color::Red);
}

CheckpointBox::~CheckpointBox()
{
}

void CheckpointBox::update(sf::Time deltaTime)
{
}

void CheckpointBox::render(sf::RenderWindow & t_window)
{
	t_window.draw(m_checkBox);
}

void CheckpointBox::setDirection(int t_direction)
{
	m_direction = t_direction;
}

int CheckpointBox::getDirection()
{
	return m_direction;
}

sf::Vector2f CheckpointBox::getPosition()
{
	return m_checkBox.getPosition();
}

sf::Vector2f CheckpointBox::getSize()
{
	return m_size;
}

void CheckpointBox::setPosition(sf::Vector2f t_position)
{
	m_checkBox.setPosition(t_position);
}

void CheckpointBox::setSize(sf::Vector2f t_size)
{
	m_checkBox.setSize(t_size);
	m_size = t_size;
}

void CheckpointBox::setRotation(float t_rotation)
{
	m_checkBox.setRotation(t_rotation);
}

void CheckpointBox::setID(int t_ID)
{
	m_ID = t_ID;
}

void CheckpointBox::setOpacity(float t_alpha)
{
	m_checkBox.setFillColor(sf::Color(m_checkBox.getFillColor().r, m_checkBox.getFillColor().g, m_checkBox.getFillColor().b, t_alpha));
}

int CheckpointBox::getID()
{
	return m_ID;
}

void CheckpointBox::setAsRaceCheckPoint(bool t_raceCheckPoint)
{
	m_raceCheckpoint = t_raceCheckPoint;
}

bool CheckpointBox::isRaceCheckPoint()
{
	return m_raceCheckpoint;
}

sf::RectangleShape CheckpointBox::getShape()
{
	return m_checkBox;
}
