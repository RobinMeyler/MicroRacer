#include "Lap.h"

Lap::Lap()
{
}

Lap::~Lap()
{
}

int Lap::getLap()
{
	return m_currentLap;
}

void Lap::increaseLap()
{
	m_currentLap += 1;
}

int Lap::getMaxLaps()
{
	return m_maxLaps;
}

bool Lap::raceFinished()
{
	return m_finished;
}

void Lap::setLap(int t_lap)
{
	m_currentLap = t_lap;
}
