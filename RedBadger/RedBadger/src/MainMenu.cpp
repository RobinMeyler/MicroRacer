#include "MainMenu.h"
#include "Game.h"



MainMenu::MainMenu(ResourceManager & t_gameAssets) :
	m_font(t_gameAssets.m_gameFonts["Digitial font"]),
	m_wheel(t_gameAssets.m_gameTextures["Menu Wheel"]),
	m_body(t_gameAssets.m_gameTextures["Menu Background"]),
	m_wheelTurnBuffer(t_gameAssets.m_gameSounds["Wheel Turn"]),
	m_confirmBuffer(t_gameAssets.m_gameSounds["Confirm"])
{
	ptrGameAssets = &t_gameAssets;


	// Set up wheel turn sfx
	m_wheelTurnSFX.setBuffer(m_wheelTurnBuffer);
	m_wheelTurnSFX.setVolume(100);
	m_wheelTurnSFX.setLoop(false);
	m_wheelTurnSFX.stop();

	// Set up confirm sound
	m_confirmSFX.setBuffer(m_confirmBuffer);
	m_confirmSFX.setLoop(false);
	m_confirmSFX.stop();

	setupSahder();
}

MainMenu::~MainMenu()
{
}

void MainMenu::clearGUI()
{
	m_gui.clearGUI();
}

void MainMenu::initialize()
{
	m_wheel.setOrigin(406, 400);
	m_wheel.setPosition(600, 400);
	m_body.setPosition(0, 0);

	Label *micro = new Label(m_font);
	micro->setString("Micro");
	micro->setTextSize(90);
	micro->setPosition(sf::Vector2f{ 180, 60 });
	micro->setOrigin();
	micro->setTextColor(sf::Color::Red);
	micro->setOutline(sf::Color::White, 2);
	micro->setUnderLined();
	m_gui.addWidget(micro);

	Label *madness = new Label(m_font);
	madness->setString("Madness");
	madness->setTextSize(90);
	madness->setPosition(sf::Vector2f{ 180, 130 });
	madness->setOrigin();
	madness->setTextColor(sf::Color::Red);
	madness->setOutline(sf::Color::White, 2);
	madness->setUnderLined();
	m_gui.addWidget(madness);

	sf::Color blue = sf::Color(sf::Color::Black);
	Button * PlayButton = new Button(blue, 250, 62);
	PlayButton->setString("Play", 40);
	PlayButton->setTextColor(sf::Color(sf::Color::Red));
	PlayButton->setFont(m_font);
	PlayButton->setPosition(sf::Vector2f(600, 100));
	PlayButton->setOutline(sf::Color(sf::Color::White), 3);
	PlayButton->setHighLightSpeed(6);
	PlayButton->setFlashColor(sf::Color::Green);
	PlayButton->setActionString("Play");
	PlayButton->setRotation(0);
	m_gui.addWidget(PlayButton);

	Button * Optionsbutton = new Button(blue, 250, 62);
	Optionsbutton->setString(" Options ", 40);
	Optionsbutton->setTextColor(sf::Color(sf::Color::Red));
	Optionsbutton->setFont(m_font);
	Optionsbutton->setPosition(sf::Vector2f(900, 400));
	Optionsbutton->setOutline(sf::Color(sf::Color::White), 3);
	Optionsbutton->setHighLightSpeed(1);
	Optionsbutton->setFlashColor(sf::Color(255,180,0));
	Optionsbutton->setActionString("Options");
	Optionsbutton->setRotation(90);
	m_gui.addWidget(Optionsbutton);

	Button * UpgradesButton = new Button(blue, 250, 62);
	UpgradesButton->setString("Upgrades", 40);
	UpgradesButton->setTextColor(sf::Color(sf::Color::Red));
	UpgradesButton->setFont(m_font);
	UpgradesButton->setPosition(sf::Vector2f(300, 400));
	UpgradesButton->setOutline(sf::Color(sf::Color::White), 3);
	UpgradesButton->setHighLightSpeed(1);
	UpgradesButton->setFlashColor(sf::Color(255, 180, 0));
	UpgradesButton->setActionString("Upgrades");
	UpgradesButton->setRotation(-90);
	m_gui.addWidget(UpgradesButton);

	Button * ExitButton = new Button(blue, 250, 62);
	ExitButton->setString("Exit", 40);
	ExitButton->setTextColor(sf::Color(sf::Color::Red));
	ExitButton->setFont(m_font);
	ExitButton->setPosition(sf::Vector2f(600, 700));
	ExitButton->setOutline(sf::Color(sf::Color::White), 3);
	ExitButton->setHighLightSpeed(1);
	ExitButton->setFlashColor(sf::Color(200,0,0));
	ExitButton->setActionString("Exit");
	ExitButton->setRotation(180);
	m_gui.addWidget(ExitButton);

	PlayButton->setRight(Optionsbutton);
	PlayButton->setLeft(UpgradesButton);
	Optionsbutton->setRight(ExitButton);
	Optionsbutton->setLeft(PlayButton);
	ExitButton->setRight(UpgradesButton);
	ExitButton->setLeft(Optionsbutton);
	UpgradesButton->setRight(PlayButton);
	UpgradesButton->setLeft(ExitButton);

	PlayButton->setAsStarter();
	m_gui.setStartFocus(PlayButton);

	m_gui.setTransitionStyle(WidgetTransitionStyle::Rotate);
	m_gui.setRotateInfo(90, 3);
	m_gui.setAnimationStyle(buttonAnimationStyle::FLASH);
}

void MainMenu::update(sf::Time t_deltaTime)
{
	handleControllerInput();
	if (m_gui.getTransitionState() == WidgetTransitionState::INTRO)
	{
		m_wheel.setRotation(m_wheel.getRotation() + m_rotate);
	}
	m_gui.update(t_deltaTime);
	Game::m_screenView.setCenter(600,400);
}

void MainMenu::render(sf::RenderWindow & t_window)
{
	shader1.setUniform("time", clock.getElapsedTime().asSeconds());
	//// For Haze 
	//shader1.setUniform("distortionFactor", distortionFactor);
	//shader1.setUniform("riseFactor", riseFactor);

	// For Lines
	sf::Vector2f res = { 1200,800 };
	shader1.setUniform("resolution", res);
	
	sf::Vector2f mousePos = { 0,0 };
//	shader1.setUniform("mouse", mousePos);

	//renderSprite.setPosition(m_testCar.getPosition() - sf::Vector2f{ 14,14 });
	renderTexture.clear();
	renderTexture.draw(m_body);
	renderTexture.display();

	t_window.clear();
	t_window.draw(m_body, &shader1);
	t_window.draw(m_wheel);
	m_gui.render(t_window);
}

void MainMenu::handleControllerInput()
{
	if (INPUT.Hold.getController().m_currentState.LeftThumbStick.y > 50 || INPUT.Hold.getController().m_currentState.DpadDown == true)
	{

	}
	if (INPUT.PressOnce.A())
	{
		if (Game::EFFECTS_BOOL == true)
		{
			m_confirmSFX.play();
		}
		std::string *m_actionString = m_gui.processInput();
		runAction(*m_actionString);
	}
	if (INPUT.PressOnce.Right())
	{
		if (Game::EFFECTS_BOOL == true)
		{
			m_wheelTurnSFX.play();
		}

		WidgetTransitionState temp = m_gui.getTransitionState();
		if (temp != WidgetTransitionState::INTRO)
		{
			m_gui.moveRight();
			m_gui.rotate(1);
			if (m_rotate > 0)
			{
				m_rotate = -m_rotate;
			}
		}
	}
	if (INPUT.PressOnce.Left())
	{
		if (Game::EFFECTS_BOOL == true)
		{
			m_wheelTurnSFX.play();
		}

		WidgetTransitionState temp = m_gui.getTransitionState();
		if (temp != WidgetTransitionState::INTRO)
		{
			m_gui.moveLeft();
			m_gui.rotate(0);
			if (m_rotate < 0)
			{
				m_rotate = -m_rotate;
			}
		}

	}
}

	

void MainMenu::runAction(std::string & t_actionString)
{
	if (t_actionString != "")
	{
	}

	if (t_actionString == "Play")
	{
		Game::m_gameMode = GameMode::TrackSelection;
		m_gui.clearGUI();
		initialize();
	}
	else if (t_actionString == "Options")
	{
		Game::m_previousMode = GameMode::MainMenu;
		Game::m_gameMode = GameMode::Options;
	}
	else if (t_actionString == "Upgrades")
	{
		Game::m_gameMode = GameMode::Upgrades;
	}

	else if (t_actionString == "Exit")
	{
		Game::m_exitGame = true;
	}


}

void MainMenu::setupSahder()
{
	distortionMap.setRepeated(true);
	distortionMap.setSmooth(true);
	if (!distortionMap.loadFromFile("distortion_map.png"))
	{
		sf::err() << "Failed to load distortion map, exiting..." << std::endl;

	}
	renderTexture.create(14, 14);
	renderSprite.setTexture(renderTexture.getTexture());
	renderSprite.setPosition(100, 150);
	const char* vs_src = "#version 130\n"
		"void main()"
		"{"
		"	gl_Position = gl_ProjectionMatrix * gl_ModelViewMatrix * gl_Vertex;"
		"gl_TexCoord[0] = gl_TextureMatrix[0] * gl_MultiTexCoord0;"
		"gl_FrontColor = gl_Color;"
		"}";


	std::string fragLine, textFrag;

	//std::ifstream inFrag("dataFragShader.txt");				// Spaceish
	//std::ifstream inFrag("townShader.txt");				// Town Moving
	//std::ifstream inFrag("spikeShader.txt");				// Spiral
	//std::ifstream inFrag("cityShader.txt");				// Night City
	//std::ifstream inFrag("pianoShader.txt");				// Random Piano
	//std::ifstream inFrag("cityRacingShader.txt");			// Flying City
	//std::ifstream inFrag("screwShader.txt");				// Flying with screws?
	std::ifstream inFrag("fizzShader.txt");				// Fizz like colors
	//std::ifstream inFrag("fireShader.txt");				// Rising sparks, works with mouse but this is a controller game
	//std::ifstream inFrag("fightClubShader.txt");			// Amazing Fight Club one, hard to see with the wheel

	while (std::getline(inFrag, fragLine))
	{
		textFrag += fragLine + "\n";
	}
	const char* dataFrag = textFrag.c_str();

	if (!shader1.loadFromMemory(vs_src, sf::Shader::Vertex))
	{
		// error...
	}

	// load only the fragment shader
	if (!shader1.loadFromMemory(dataFrag, sf::Shader::Fragment))
	{
		// error...
	}
	/*if (!shader1.loadFromFile(vs_src, fs_src))
	{
		sf::err() << "Failed to load shader, exiting..." << std::endl;
	}*/
	/*shader1.setUniform("currentTexture", sf::Shader::CurrentTexture);
	shader1.setUniform("distortionMapTexture", distortionMap);*/

}
