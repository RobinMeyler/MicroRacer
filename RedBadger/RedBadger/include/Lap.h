#pragma once



class Lap
{
public :
	Lap();
	~Lap();

	int getLap();
	void increaseLap();
	int getMaxLaps();
	bool raceFinished();
	void setLap(int t_lap);

private:
	int m_currentLap = 0;
	int m_maxLaps = 3;
	bool m_finished = false;
};