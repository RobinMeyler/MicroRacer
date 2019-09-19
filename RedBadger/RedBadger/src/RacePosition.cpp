#include "RacePosition.h"

RacePosition::RacePosition()
{
}

RacePosition::~RacePosition()
{
}

int RacePosition::getCurrentPosition()
{
	return m_currentPosition;
}

void RacePosition::setCurrentPosition(int t_position)
{
	m_currentPosition = t_position;
}



//float RacePosition::distanceFromCheckPoint()
//{
//	float dx = std::max(rect.min.x - p.x, 0, p.x - rect.max.x);
//
//	float dy = std::max(rect.min.y - p.y, 0, p.y - rect.max.y);
//
//	return Math.sqrt(dx*dx + dy * dy);
//}
//
//function distance(rect, p) {
//	var dx = Math.max(rect.min.x - p.x, 0, p.x - rect.max.x);
//	var dy = Math.max(rect.min.y - p.y, 0, p.y - rect.max.y);
//	return Math.sqrt(dx*dx + dy * dy);
//}