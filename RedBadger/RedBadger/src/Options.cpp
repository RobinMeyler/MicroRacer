#include "Options.h"
#include "Game.h"



Options::Options(ResourceManager & t_gameassets):
	m_font(t_gameassets.m_gameFonts["Digitial font"]),
	m_wheel(t_gameassets.m_gameTextures["Menu Wheel"]),
	m_body(t_gameassets.m_gameTextures["Menu Background"]),
	m_wheelTurnBuffer(t_gameassets.m_gameSounds["Wheel Turn"]),
	m_confirmBuffer(t_gameassets.m_gameSounds["Confirm"]),
	m_backBuffer(t_gameassets.m_gameSounds["Back"])
{
	m_wheelTurnSFX.setBuffer(m_wheelTurnBuffer);
	m_wheelTurnSFX.setVolume(100);
	m_wheelTurnSFX.setLoop(false);
	m_wheelTurnSFX.stop();


	m_confirmSFX.setBuffer(m_confirmBuffer);
	m_confirmSFX.setLoop(false);
	m_confirmSFX.stop();


	m_backSFX.setBuffer(m_backBuffer);
	m_backSFX.setLoop(false);
	m_backSFX.stop();

	setupShader();
}


Options::~Options()
{
}

void Options::clearGUI()
{
	m_gui.clearGUI();
}

void Options::initialize()
{
	m_wheel.setOrigin(406, 400);
	m_wheel.setPosition(600, 400);
	m_body.setPosition(0, 0);

	Label *options = new Label(m_font);
	options->setString("Options");
	options->setTextSize(100);
	options->setPosition(sf::Vector2f{ 180, 90 });
	options->setOrigin();
	options->setTextColor(sf::Color::Red);
	options->setOutline(sf::Color::White, 2);
	options->setUnderLined();
	m_gui.addWidget(options);

	sf::Color blue = sf::Color(sf::Color::Black);
	Button * PlayButton = new Button(blue, 250, 62);
	PlayButton->setString("Sound", 40);
	PlayButton->setTextColor(sf::Color(sf::Color::Red));
	PlayButton->setFont(m_font);
	PlayButton->setPosition(sf::Vector2f(600, 100));
	PlayButton->setOutline(sf::Color(sf::Color::White), 3);
	PlayButton->setHighLightSpeed(6);
	PlayButton->setFlashColor(sf::Color::Green);
	PlayButton->setActionString("Sound");
	PlayButton->setRotation(0);
	m_gui.addWidget(PlayButton);

	Button * Optionsbutton = new Button(blue, 250, 62);
	Optionsbutton->setString("Credits", 40);
	Optionsbutton->setTextColor(sf::Color(sf::Color::Red));
	Optionsbutton->setFont(m_font);
	Optionsbutton->setPosition(sf::Vector2f(900, 400));
	Optionsbutton->setOutline(sf::Color(sf::Color::White), 3);
	Optionsbutton->setHighLightSpeed(6);
	Optionsbutton->setFlashColor(sf::Color::Green);
	Optionsbutton->setActionString("Credits");
	Optionsbutton->setRotation(90);
	m_gui.addWidget(Optionsbutton);

	Button * UpgradesButton = new Button(blue, 250, 62);
	UpgradesButton->setString("Control Info", 40);
	UpgradesButton->setTextColor(sf::Color(sf::Color::Red));
	UpgradesButton->setFont(m_font);
	UpgradesButton->setPosition(sf::Vector2f(300, 400));
	UpgradesButton->setOutline(sf::Color(sf::Color::White), 3);
	UpgradesButton->setHighLightSpeed(6);
	UpgradesButton->setFlashColor(sf::Color::Green);
	UpgradesButton->setActionString("Control Info");
	UpgradesButton->setRotation(-90);
	m_gui.addWidget(UpgradesButton);

	Button * ExitButton = new Button(blue, 250, 62);
	ExitButton->setString("Main Menu", 40);							// Maybe change to Exit later
	ExitButton->setTextColor(sf::Color(sf::Color::Red));
	ExitButton->setFont(m_font);
	ExitButton->setPosition(sf::Vector2f(600, 700));
	ExitButton->setOutline(sf::Color(sf::Color::White), 3);
	ExitButton->setHighLightSpeed(6);
	ExitButton->setFlashColor(sf::Color::Green);
	ExitButton->setActionString("Main Menu");
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
}

void Options::update(sf::Time t_deltaTime)
{
	handleControllerInput();
	if (m_gui.getTransitionState() == WidgetTransitionState::INTRO)
	{
		m_wheel.setRotation(m_wheel.getRotation() + m_rotate);
	}
	m_gui.update(t_deltaTime);
	Game::m_screenView.setCenter(600, 400);
	m_delay++;
}

void Options::render(sf::RenderWindow & t_window)
{
	shader1.setUniform("time", clock.getElapsedTime().asSeconds());
	//// For Haze 
	//shader1.setUniform("distortionFactor", distortionFactor);
	//shader1.setUniform("riseFactor", riseFactor);

	// For Lines
	sf::Vector2f res = { 1200,800 };
	shader1.setUniform("resolution", res);

	sf::Vector2f mousePos = Game::m_mousePos;
	//shader1.setUniform("mouse", mousePos);

	//renderSprite.setPosition(m_testCar.getPosition() - sf::Vector2f{ 14,14 });
	renderTexture.clear();
	renderTexture.draw(m_body);
	renderTexture.display();

	t_window.clear(sf::Color::White);
	t_window.draw(m_body, &shader1);
	t_window.draw(m_wheel);
	m_gui.render(t_window);
}

void Options::handleControllerInput()
{
	if (m_delay > 20)
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
			m_gui.moveUp();
			m_delay = 0;
		}
		if (INPUT.PressOnce.B())
		{

			if (Game::EFFECTS_BOOL == true)
			{
				m_backSFX.play();
			}
			clearGUI();
			initialize();

			if (Game::m_previousMode == GameMode::Pause)
			{
				Game::m_gameMode = GameMode::Pause;
			}
			if (Game::m_previousMode == GameMode::MainMenu)
			{
				Game::m_gameMode = GameMode::MainMenu;
			}
			m_delay = 0;
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
			m_delay = 0;
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
			m_delay = 0;
		}
	}

}

void Options::runAction(std::string & t_actionString)
{
	if (t_actionString != "")
	{
	}

	if (t_actionString == "Sound")
	{
		Game::m_gameMode = GameMode::SoundOptions;
	}
	else if (t_actionString == "Control Info")
	{
		Game::m_gameMode = GameMode::ControlInfo;
	}
	else if (t_actionString == "Main Menu")
	{
		Game::m_gameMode = GameMode::MainMenu;
	}

	else if (t_actionString == "Credits")
	{
		Game::m_gameMode = GameMode::Credits;
	}


}

void Options::setupShader()
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

	std::ifstream inFrag("dataFragShader.txt");				// Spaceish
	//std::ifstream inFrag("townShader.txt");				// Town Moving
	//std::ifstream inFrag("spikeShader.txt");				// Spiral
	//std::ifstream inFrag("cityShader.txt");				// Night City
	//std::ifstream inFrag("pianoShader.txt");				// Random Piano
	//std::ifstream inFrag("cityRacingShader.txt");			// Flying City
	//std::ifstream inFrag("screwShader.txt");				// Flying with screws?
	//std::ifstream inFrag("fizzShader.txt");				// Fizz like colors
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
	//shader1.setUniform("currentTexture", sf::Shader::CurrentTexture);
	//shader1.setUniform("distortionMapTexture", distortionMap);

}
