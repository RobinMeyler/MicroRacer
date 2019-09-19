#pragma once
#include "SFML/Graphics.hpp"

class CheckpointBox
{
private:
	sf::RectangleShape m_checkBox;
	sf::Vector2f m_size;
	int m_ID{ 0 };
	int m_direction{ 1 };
	bool m_raceCheckpoint{ false };

public:
	CheckpointBox();
	CheckpointBox(sf::Vector2f t_size, sf::Vector2f t_position, float t_rotation);
	~CheckpointBox();


	void update(sf::Time deltaTime);
	void render(sf::RenderWindow & t_window);

	void setDirection(int t_direction);
	int getDirection();
	sf::Vector2f getPosition();
	sf::Vector2f getSize();
	void setPosition(sf::Vector2f t_size);
	void setSize(sf::Vector2f t_position);
	void setRotation(float t_rotation);
	void setID(int t_ID);
	void setOpacity(float t_alpha);
	int getID();
	void setAsRaceCheckPoint(bool t_raceCheckPoint);
	bool isRaceCheckPoint();

	sf::RectangleShape getShape();
};

