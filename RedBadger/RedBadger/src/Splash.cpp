#include "Splash.h"
#include "Game.h"


Splash::Splash(ResourceManager & t_gameAssets) :
	m_redLogoTexture(t_gameAssets.m_gameTextures["Logo"]),
	m_soundBuffer(t_gameAssets.m_gameSounds["Splash"])
{
	m_redLogo.setTexture(m_redLogoTexture);
	m_redLogo.setPosition(-200, 350);
	ScreenTransitions::setFadeType(true);
	//MainMenu::stopMusic();
	m_sound.setBuffer(m_soundBuffer);
	m_sound.setLoop(false);
	m_sound.play();
	ScreenTransitions::setFadeSpeed(2.0f);

	m_redLogo.setScale(1.3,1.3);

}


Splash::~Splash()
{
}

void Splash::initialize()
{
	
}

void Splash::update(sf::Time t_deltaTime)
{
	handleControllerInput();
}

void Splash::render(sf::RenderWindow & t_window)
{
	t_window.clear(sf::Color::White);
	t_window.draw(m_redLogo);
}

void Splash::handleControllerInput()
{
	if (m_count > 180 && m_count < 200)
	{
		ScreenTransitions::setFadeType(false);
	}

	else if (m_count > 300)
	{
		if (ScreenTransitions::isTransitioning() == false)
		{
			if (m_sound.getStatus() == sf::Sound::Stopped)
			{
				ScreenTransitions::setFadeType(true);

			
				Game::m_gameMode = GameMode::Licence;
				m_count = 0;
				Game::playSoundTrack();
				//MainMenu::playMusic();
				ScreenTransitions::setFadeSpeed(2);
			}
		}
	}
	m_redLogo.setPosition(m_redLogo.getPosition().x + 5, 300);
	m_count++;
}

void Splash::runAction(std::string & t_actionString)
{
	
}

void Splash::displayLogo()
{
	
}
