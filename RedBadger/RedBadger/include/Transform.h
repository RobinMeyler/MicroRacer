/// <summary>
/// Began 20/03/2019 Paul O'Callaghan
/// </summary>
#pragma once

#include <SFML/Graphics.hpp>

/// <summary>
/// Transform class handles all data concerning vector data for position, rotation and scale. Will also contain functions for manipulating data.
/// </summary>
class Transform
{
public:
	sf::Vector2f position = { 0,0 };

	// Rotation will have 3 vectors for setting angle based on eurler ANGLES
	sf::Vector3f rotation = { 0,0,0 };

	sf::Vector2f scale = { 0,0 };

	
	static float Distance(sf::Vector2f t_pos1, sf::Vector2f t_pos2);
};