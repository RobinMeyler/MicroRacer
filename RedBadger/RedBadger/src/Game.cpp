#include "Game.h"

// Preset Static variables for the whole project
// These span across all screens and can be altered in many ---------------------------------------------------



GameMode Game::m_gameMode{ GameMode::Splash};
GameMode Game::m_previousMode{ GameMode::Splash };
bool Game::m_exitGame{ false };
sf::View Game::m_screenView{ sf::FloatRect(0,0, 1200, 800) };
sf::Vector2f Game::m_mousePos{ 0.0f,0.0f };
bool Game::m_playerAccerating{ false };
int Game::ENGINE_TYPE{ 1 };
int Game::WHEEL_TYPE{ 1 };
int Game::NITRO_TYPE{ 1 };
int Game::BODY_TYPE{ 0 };
int Game::PLAYERS_MONEY{ 5000 };
bool Game::MUSIC_BOOL{ true };
bool Game::EFFECTS_BOOL{ true };
int Game::MUSIC_VOLUME{ 100 };


// Contructor
Game::Game() :
	m_renderWin{ sf::VideoMode{ 1200, 800, 1 }, "Micro Madness" }
{
	int m_currentLevel = 1;
	// Will generate an exception if level loading fails.
	try
	{
		LevelLoader::load(m_currentLevel, m_yamlData);
	}
	catch (std::exception & e)
	{
		std::cout << "Level Loading failure." << std::endl;
		std::cout << e.what() << std::endl;
		throw e;
	}
	catch (...) {
		std::cout << "Default Exception\n";
	}

	intialize();
	ScreenTransitions::init();
}

/// Destructor
Game::~Game()
{
	if (m_rulesScreen != nullptr)				// Don't delete nothing.
	{
		delete m_rulesScreen;					// Delete the heap memory allocated in the initialize
	}
	if (m_licenceScreen != nullptr)				
	{
		delete m_licenceScreen;			
	}
	if (m_soundOptionsScreen != nullptr)		
	{
		delete m_soundOptionsScreen;			
	}
	if (m_splashScreen != nullptr)				
	{
		delete m_splashScreen;					
	}
	if (m_gameplayScreen != nullptr)			
	{
		delete m_gameplayScreen;
	}
	if (m_pauseScreen != nullptr)				// Don't delete nothing.
	{
		delete m_pauseScreen;					// Delete the heap memory allocated in the initialize
	}
	if (m_creditsScreen != nullptr)				
	{
		delete m_creditsScreen;					
	}
	if (m_contrInfoScreen != nullptr)			
	{
		delete m_contrInfoScreen;
	}
	if (m_mainMenuScreen != nullptr)			
	{
		delete m_mainMenuScreen;			
	}
	if (m_upgradeScreen != nullptr)
	{
		delete m_upgradeScreen;
	}
	if (m_trackSelectionScreen != nullptr)
	{
		delete m_trackSelectionScreen;
	}

}

// Loop designed to work at equal speed on all PCs
// If a PC is slower, it will update the same amount of times
// And render less often
void Game::run()
{
	sf::Clock gameClock;											// Game clock
	sf::Time timeTakenForUpdate = sf::Time::Zero;					// No lag on first input
	sf::Time timePerFrame = sf::seconds(1.f / 60.f);				// 60 frames per second
	while (m_renderWin.isOpen())									// Loop
	{
		processInput();												// Check for input
		timeTakenForUpdate += gameClock.restart();					// Returns time take to do the loop
		while (timeTakenForUpdate > timePerFrame)					// Update enough times to catch up on updates missed during the lag time
		{
			timeTakenForUpdate -= timePerFrame;						// Decrement lag
			processInput();											// More checks, the more accurate input to display will be
			update(timePerFrame);									// Update
		}
		render();
	}
}

// Process PC input
void Game::processInput()
{
	sf::Event event;
	while (m_renderWin.pollEvent(event))
	{
		if (sf::Event::Closed == event.type)
		{
			m_renderWin.close();
		}
		if (sf::Event::KeyPressed == event.type)
		{
			if (sf::Keyboard::Escape == event.key.code)
			{
				m_renderWin.close();
			}
		}
		if (event.type == sf::Event::MouseButtonPressed)
		{
			if (event.mouseButton.button == sf::Mouse::Left)
			{
			}
		}
		if (event.type == sf::Event::MouseButtonReleased)
		{
		}
		Game::m_mousePos = sf::Vector2f{ (float)sf::Mouse::getPosition(m_renderWin).x, (float)sf::Mouse::getPosition(m_renderWin).y };
	}
}

// Updates Game
void Game::update(sf::Time t_deltaTime)
{
	if (Game::m_exitGame == true)
	{
		m_renderWin.close();
	}
	ScreenTransitions::Fade();

	switch (m_gameMode)					// Switch to control the screens
	{
	case GameMode::Licence:
		m_licenceScreen->update(t_deltaTime);
		break;
	case GameMode::Splash:
		m_splashScreen->update(t_deltaTime);
		break;
	case GameMode::MainMenu:
		m_mainMenuScreen->update(t_deltaTime);
		break;
	case GameMode::Gameplay:
		m_gameplayScreen->update(t_deltaTime);
		break;
	case GameMode::Options:
		m_optionsScreen->update(t_deltaTime);
		break;
	case GameMode::ControlInfo:
		m_contrInfoScreen->update(t_deltaTime);
		break;
	case GameMode::Rules:
		m_rulesScreen->update(t_deltaTime);
		break;
	case GameMode::SoundOptions:
		m_soundOptionsScreen->update(t_deltaTime);
		break;
	case GameMode::Pause:
		m_pauseScreen->update(t_deltaTime);
		break;
	case GameMode::Credits:
		m_creditsScreen->update(t_deltaTime);
		break;
	case GameMode::Upgrades:
		m_upgradeScreen->update(t_deltaTime);
		break;
	case GameMode::TrackSelection:
		m_trackSelectionScreen->update(t_deltaTime);
		break;
	default:
		break;
	}

	m_soundTrack.setVolume(MUSIC_VOLUME);
	if (MUSIC_BOOL == false || m_gameMode == GameMode::Gameplay || m_gameMode == GameMode::Splash)
	{
		m_soundTrack.stop();
	}

}

// Renders
void Game::render()
{
	m_renderWin.clear();
	m_renderWin.setView(Game::m_screenView);
	switch (m_gameMode)								// Swtich to control the screens
	{
	case GameMode::Licence:
		m_licenceScreen->render(m_renderWin);
		break;
	case GameMode::Splash:
		m_splashScreen->render(m_renderWin);
		break;
	case GameMode::MainMenu:
		m_mainMenuScreen->render(m_renderWin);
		break;
	case GameMode::Gameplay:
		m_gameplayScreen->render(m_renderWin);
		break;
	case GameMode::Options:
		m_optionsScreen->render(m_renderWin);
		break;
	case GameMode::ControlInfo:
		m_contrInfoScreen->render(m_renderWin);
		break;
	case GameMode::Rules:
		m_rulesScreen->render(m_renderWin);
		break;
	case GameMode::SoundOptions:
		m_soundOptionsScreen->render(m_renderWin);
		break;
	case GameMode::Pause:
		m_pauseScreen->render(m_renderWin);
		break;
	case GameMode::Credits:
		m_creditsScreen->render(m_renderWin);
		break;
	case GameMode::Upgrades:
		m_upgradeScreen->render(m_renderWin);
		break;
	case GameMode::TrackSelection:
		m_trackSelectionScreen->render(m_renderWin);
		break;
	default:
		break;
	}

	m_renderWin.draw(ScreenTransitions::getScreenCurtain());

	m_renderWin.display();
}

void Game::playSoundTrack()
{
	if (MUSIC_BOOL == true)
	{
		m_soundTrack.play();
	}
}

void Game::intialize()
{
	ScreenTransitions::setPosition(sf::Vector2f(0, 0));
	// Loading assets to Manager -----------------------------------------------------------
	try
	{
		//Plus One drop
		m_gameAssets.addTexture("Plus One Drop", m_yamlData.m_textures.m_plusOneDrop);

		m_gameAssets.addTexture("Car One", m_yamlData.m_textures.m_carOne);
		m_gameAssets.addTexture("Car One Green", m_yamlData.m_textures.m_carOneGreen);
		m_gameAssets.addTexture("Car One Inferno", m_yamlData.m_textures.m_carOneInferno);
		m_gameAssets.addTexture("Car One Large", m_yamlData.m_textures.m_carOneLarge);
		m_gameAssets.addTexture("Car One Large Green", m_yamlData.m_textures.m_carOneLargeGreen);
		m_gameAssets.addTexture("Car One Large Inferno", m_yamlData.m_textures.m_carOneLargeInferno);
		m_gameAssets.addTexture("Car Two", m_yamlData.m_textures.m_carTwo);
		m_gameAssets.addTexture("Car Three", m_yamlData.m_textures.m_carThree);
		m_gameAssets.addTexture("Car Four", m_yamlData.m_textures.m_carFour);


		// New map
		m_gameAssets.addTexture("Tile Sheet", m_yamlData.m_textures.m_spriteSheetVarious);	// a tile sheet (only used for tree now)
		m_gameAssets.addTexture("Tile Sheet Two", m_yamlData.m_textures.m_spriteSheetDirtRoad);	// the main tile sheet that we use
		m_gameAssets.addTexture("Mini Map", m_yamlData.m_textures.m_miniMap);

		m_gameAssets.addTexture("Raised Road", m_yamlData.m_textures.m_raisedRoad);				// Raised road texture
		m_gameAssets.addTexture("Ice Road", m_yamlData.m_textures.m_iceRoad);					// water road texture
		m_gameAssets.addTexture("Finish Line", "./ASSETS/IMAGES/Dirt road/FinishLine.png");
		m_gameAssets.addTexture("Grass", m_yamlData.m_textures.m_grass);
		m_gameAssets.addTexture("Snow",  m_yamlData.m_textures.m_snow);
		m_gameAssets.addTexture("SnowTreeTile",  m_yamlData.m_textures.m_snowTreeTile);
		m_gameAssets.addTexture("SnowTree", m_yamlData.m_textures.m_snowTree);
		m_gameAssets.addTexture("Big Red Tent", m_yamlData.m_textures.m_bigRedTent);
		m_gameAssets.addTexture("Red Tent", m_yamlData.m_textures.m_redTent);

		m_gameAssets.addTexture("XboxA", m_yamlData.m_textures.m_XboxA);
		m_gameAssets.addTexture("XboxRT", m_yamlData.m_textures.m_XboxRT);
		m_gameAssets.addTexture("XboxLT", m_yamlData.m_textures.m_XboxLT);
		m_gameAssets.addTexture("XboxLS", m_yamlData.m_textures.m_XboxLS);

		//License Screen
		m_gameAssets.addTexture("Sky", m_yamlData.m_textures.m_sky);
		m_gameAssets.addTexture("Clouds", m_yamlData.m_textures.m_clouds);
		m_gameAssets.addTexture("Mountain", m_yamlData.m_textures.m_mountain);
		m_gameAssets.addTexture("Tree", m_yamlData.m_textures.m_tree);
		m_gameAssets.addTexture("Road", m_yamlData.m_textures.m_road);

		m_gameAssets.addTexture("Car Sprite 1", m_yamlData.m_textures.m_carSprite1);
		m_gameAssets.addTexture("Car Sprite 2", m_yamlData.m_textures.m_carSprite2);
		m_gameAssets.addTexture("Car Sprite 3", m_yamlData.m_textures.m_carSprite3);
		m_gameAssets.addTexture("Car Sprite 4", m_yamlData.m_textures.m_carSprite4);
		m_gameAssets.addTexture("Logo Game", m_yamlData.m_textures.m_logoGame);


		// Sound Options Screen Assets
		m_gameAssets.addTexture("Volume Knob", m_yamlData.m_textures.m_volumeKnob);
		m_gameAssets.addTexture("Button Texture One", m_yamlData.m_textures.m_buttonTextureOne);
		m_gameAssets.addTexture("Sound BackGround", m_yamlData.m_textures.m_backGroundSoundOptions);

		m_gameAssets.addTexture("Menu Wheel", m_yamlData.m_textures.m_menuWheel);
		m_gameAssets.addTexture("Menu Background", m_yamlData.m_textures.m_menuBackground);
		m_gameAssets.addTexture("Border", m_yamlData.m_textures.m_border);
		m_gameAssets.addTexture("Bridge Wall", m_yamlData.m_textures.m_bridgeWall);
		m_gameAssets.addTexture("Back Car", m_yamlData.m_textures.m_backCar);
		m_gameAssets.addTexture("Particle", m_yamlData.m_textures.m_particle);

		//Upgrade sceen
		m_gameAssets.addTexture("Upgrade BackGround", m_yamlData.m_textures.m_upgradeBackGround);
		m_gameAssets.addTexture("Green Bar", m_yamlData.m_textures.m_greenBar);
		m_gameAssets.addTexture("Orange Bar", m_yamlData.m_textures.m_orangeBar);
		m_gameAssets.addTexture("Red Bar", m_yamlData.m_textures.m_redBar);

		//FONTS
		m_gameAssets.addFont("Speed font", m_yamlData.m_fonts.m_speed);
		m_gameAssets.addFont("Digitial font", m_yamlData.m_fonts.m_digital);


		m_gameAssets.addFont("carfont1", "./ASSETS/FONTS/FasterOne-Regular.ttf");
		m_gameAssets.addFont("carfont2", "./ASSETS/FONTS/K26SpeechBubble.ttf");
		m_gameAssets.addFont("carfont3", "./ASSETS/FONTS/NightmarePills-DEMO.ttf");
		m_gameAssets.addFont("carfont4", "./ASSETS/FONTS/roadtest.ttf");
		m_gameAssets.addFont("carfont5", "./ASSETS/FONTS/Schilderwald.ttf");
		m_gameAssets.addFont("carfont6", "./ASSETS/FONTS/Speed Freaks.ttf");


		// Transition Curtain
		m_gameAssets.addTexture("Screen Curtain", m_yamlData.m_textures.m_screenCurtain);
		m_gameAssets.addTexture("Logo", m_yamlData.m_textures.m_logo);

		//SOUND
		m_gameAssets.addSoundBuffer("Splash", m_yamlData.m_sounds.m_splash);
		m_gameAssets.addSoundBuffer("Race", m_yamlData.m_sounds.m_raceMusic);
		m_gameAssets.addSoundBuffer("Menu", m_yamlData.m_sounds.m_menuMusic);
		m_gameAssets.addSoundBuffer("Fall Behind", m_yamlData.m_sounds.m_fallBehind);
		m_gameAssets.addSoundBuffer("Pull Ahead", m_yamlData.m_sounds.m_pullAhead);
		m_gameAssets.addSoundBuffer("Lap", m_yamlData.m_sounds.m_lap);
		m_gameAssets.addSoundBuffer("Final Lap", m_yamlData.m_sounds.m_finalLap);
		m_gameAssets.addSoundBuffer("Wheel Turn", m_yamlData.m_sounds.m_wheelTurn);
		m_gameAssets.addSoundBuffer("Confirm", m_yamlData.m_sounds.m_confirm);
		m_gameAssets.addSoundBuffer("Back", m_yamlData.m_sounds.m_back);
		m_gameAssets.addSoundBuffer("Move Selection", m_yamlData.m_sounds.m_moveSelection);
		m_gameAssets.addSoundBuffer("Race Finished", m_yamlData.m_sounds.m_raceFinished);
		m_gameAssets.addSoundBuffer("Race Finished Music", m_yamlData.m_sounds.m_raceResultsMusic);


		// set soundtrack 
		m_soundTrackBuffer = m_gameAssets.m_gameSounds["Menu"];
		m_soundTrack.setBuffer(m_soundTrackBuffer);
		m_soundTrack.setLoop(true);
		//m_soundTrack.play();


		// XBOX BUTTONS

		m_gameAssets.addTexture("Button A", m_yamlData.m_textures.m_buttonA);

	}
	catch (thor::ResourceLoadingException& e)
	{
		std::cout << "Error: " << e.what() << std::endl;
	}

	// Initialize screens
	m_rulesScreen = new Rules(m_gameAssets);
	m_gameplayScreen = new Gameplay(m_gameAssets);
	m_soundOptionsScreen = new SoundOptions(m_gameAssets);
	m_splashScreen = new Splash(m_gameAssets);
	m_licenceScreen = new Licence(m_gameAssets);
	m_contrInfoScreen = new ControlInfo(m_gameAssets);
	m_mainMenuScreen = new MainMenu(m_gameAssets);
	m_pauseScreen = new Pause(m_gameAssets);
	m_optionsScreen = new Options(m_gameAssets);
	m_creditsScreen = new Credits(m_gameAssets);
	m_upgradeScreen = new Upgrades(m_gameAssets);
	m_trackSelectionScreen = new TrackSelection(m_gameAssets);

	// Screen intializing -------------------
	m_rulesScreen->initialize();
	m_gameplayScreen->initialize();
	m_splashScreen->initialize();
	m_contrInfoScreen->initialize();
	m_creditsScreen->initialize();
	m_gameplayScreen->initialize();
	m_mainMenuScreen->initialize();
	m_pauseScreen->initialize();
	m_optionsScreen->initialize();
	m_upgradeScreen->initialize();

	ScreenTransitions::setCurtain(m_gameAssets.m_gameTextures["Screen Curtain"]);
}
