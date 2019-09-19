#pragma once
#include "Lap.h"
#include <array>

class RacePosition
{
public:
	RacePosition();
	~RacePosition();

	/// <summary>
	/// Get current race position
	/// </summary>
	/// <returns></returns>
	int getCurrentPosition();

	/// <summary>
	/// Set's the position of the car to t_position
	/// </summary>
	/// <param name="t_position"></param>
	void setCurrentPosition(int t_position);
	Lap lap;
private:
	int m_currentPosition = 1;
};
