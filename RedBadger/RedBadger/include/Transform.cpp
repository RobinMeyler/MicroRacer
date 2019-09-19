#include "Transform.h"

/// <summary>
/// Gets distance of two objects from one another
/// </summary>
/// <param name="t_pos1">1st object position</param>
/// <param name="t_pos2">2nd object position</param>
/// <returns></returns>
float Transform::Distance(sf::Vector2f t_pos1, sf::Vector2f t_pos2)
{
	return std::sqrtf((t_pos1.x - t_pos2.x)*(t_pos1.x - t_pos2.x) + (t_pos1.y - t_pos2.y)*(t_pos1.y - t_pos2.y));
}
