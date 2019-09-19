#pragma once


// Extra ----------------------------
#include <iostream>
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include "GUIGlobals.h"
#include "MyVector3.h"
#include "Xbox360Controller.h"
#include "Collider.h"
#include <String>
#include <ctime>

// Screens -------------------------
#include "Licence.h"
#include "Splash.h"
#include "MainMenu.h"
#include "Gameplay.h"
#include "Options.h"
#include "ControlInfo.h"
#include "Rules.h"
#include "SoundOptions.h"
#include "Pause.h"
#include "Credits.h"
#include "Upgrades.h"
#include "TrackSelection.h"

// GUI -----------------------------
#include "CharacterInput.h"
#include "CheckBox.h"
#include "HorizontalSlider.h"
#include "VerticalSlider.h"
#include "Button.h"
#include "RadioButton.h"
#include "GUI.h"

#include "Thor/Resources.hpp"
#include "ResourceManager.h"
#include "LevelLoader.h"	// for loading yaml info

static sf::Sound m_soundTrack;

static GameMode m_previousScreen;
class Game
{
public:
	Game();
	~Game();
	void run();
	// Intialized and commented in cpp -------------------------
	static GameMode m_gameMode;
	static GameMode m_previousMode;
	static bool m_exitGame;
	static bool m_playerAccerating;
	thor::ResourceHolder<sf::Texture, std::string> holder;

	//CURRENCY
	static int PLAYERS_MONEY;

	//Upgrade Stats
	static int ENGINE_TYPE;
	static int WHEEL_TYPE;
	static int NITRO_TYPE;
	static int BODY_TYPE;
	// Sound 
	static bool MUSIC_BOOL;
	static bool EFFECTS_BOOL;
	static int MUSIC_VOLUME;

	sf::SoundBuffer m_soundTrackBuffer;
	static void playSoundTrack();
	static sf::View m_screenView;
	static sf::Vector2f m_mousePos;

protected:
	void intialize();
	void update(sf::Time t_deltaTime);
	void processInput();
	void render();
	
	sf::RenderWindow m_renderWin;
	sf::Font m_font;

	/*Screens*/
	Licence* m_licenceScreen{ nullptr }; // josh is using this screen for testing
	Splash *m_splashScreen{ nullptr };
	MainMenu *m_mainMenuScreen{ nullptr };
	Gameplay *m_gameplayScreen{ nullptr };
	Options *m_optionsScreen{ nullptr };
	ControlInfo *m_contrInfoScreen{ nullptr };
	Rules* m_rulesScreen{ nullptr };
	SoundOptions* m_soundOptionsScreen{nullptr};
	Pause *m_pauseScreen{ nullptr };
	Credits *m_creditsScreen{ nullptr };
	Upgrades *m_upgradeScreen{ nullptr };
	TrackSelection *m_trackSelectionScreen{ nullptr };
	ResourceManager m_gameAssets;

	LevelData m_yamlData;
};

