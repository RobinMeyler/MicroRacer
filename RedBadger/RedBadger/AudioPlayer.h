#pragma once
#include "ResourceManager.h"
#include "GUI.h"

class AudioPlayer
{
public:
	AudioPlayer();
	~AudioPlayer();
	void PlayOnce(sf::Sound t_sound);
	void PlayLoop(sf::Sound t_sound);
private:
	float volumeSFX = 0.6f;
	float volumeMusic = 0.6f;
	GUI * gui;

	

};