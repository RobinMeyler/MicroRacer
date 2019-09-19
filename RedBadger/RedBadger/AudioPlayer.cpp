#include "AudioPlayer.h"

AudioPlayer::AudioPlayer()
{
}

AudioPlayer::~AudioPlayer()
{
}

void AudioPlayer::PlayOnce(sf::Sound t_sound)
{
}

void AudioPlayer::PlayLoop(sf::Sound t_sound)
{
	
	t_sound.setLoop(true);
}
