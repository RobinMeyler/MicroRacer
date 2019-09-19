#include "Pause.h"
#include "Game.h"


Pause::Pause(ResourceManager & t_gameAssets) :
	m_backGround(t_gameAssets.m_gameTextures["Menu Background"])
{
	ptrGameAsstes = &t_gameAssets;
	initialize();
}


Pause::~Pause()
{
}

void Pause::clearGUI()
{
	
}

void Pause::initialize()
{
	//Title
	Label *m_title = new Label(ptrGameAsstes->m_gameFonts["carfont2"]);
	m_title->setTextSize(60);
	m_title->setString("Pause");
	m_title->setPosition(sf::Vector2f(600, 100));
	m_title->setTextColor(sf::Color::Green);
	m_title->setOrigin();
	m_title->setUnderLined();

	// Buttons

	Button *continueButton = new Button(ptrGameAsstes->m_gameTextures["Button Texture One"], 200, 60);
	continueButton->setPosition(sf::Vector2f(200, 300));
	continueButton->setString("Continue", 25);
	continueButton->setFont(ptrGameAsstes->m_gameFonts["carfont2"]);
	continueButton->setActionString("Continue");

	Button *restartButton = new Button(ptrGameAsstes->m_gameTextures["Button Texture One"], 200, 60);
	restartButton->setPosition(sf::Vector2f(200, 370));
	restartButton->setString("Restart", 25);
	restartButton->setFont(ptrGameAsstes->m_gameFonts["carfont2"]);
	restartButton->setActionString("Restart");

	Button *optionsButton = new Button(ptrGameAsstes->m_gameTextures["Button Texture One"], 200, 60);
	optionsButton->setPosition(sf::Vector2f(200, 440));
	optionsButton->setString("Options", 25);
	optionsButton->setFont(ptrGameAsstes->m_gameFonts["carfont2"]);
	optionsButton->setActionString("Options");

	Button *menuButton = new Button(ptrGameAsstes->m_gameTextures["Button Texture One"], 200, 60);
	menuButton->setPosition(sf::Vector2f(200, 510));
	menuButton->setString("Main Menu", 25);
	menuButton->setFont(ptrGameAsstes->m_gameFonts["carfont2"]);
	menuButton->setActionString("Main Menu");

	Button *exitButton = new Button(ptrGameAsstes->m_gameTextures["Button Texture One"], 200, 60);
	exitButton->setPosition(sf::Vector2f(200, 580));
	exitButton->setString("Exit", 25);
	exitButton->setFont(ptrGameAsstes->m_gameFonts["carfont2"]);
	exitButton->setActionString("Exit");

	


	//SET UP N DOWNS
	continueButton->setDown(restartButton);
	restartButton->setUp(continueButton);
	restartButton->setDown(optionsButton);
	optionsButton->setUp(restartButton);
	optionsButton->setDown(menuButton);
	menuButton->setUp(optionsButton);
	menuButton->setDown(exitButton);
	exitButton->setUp(menuButton);

	m_GUI.addWidget(m_title);
	m_GUI.addWidget(continueButton);
	m_GUI.addWidget(restartButton);
	m_GUI.addWidget(optionsButton);
	m_GUI.addWidget(menuButton);
	m_GUI.addWidget(exitButton);
	m_GUI.setStartFocus(continueButton);
	m_GUI.setAnimationStyle(buttonAnimationStyle::SHRINK);
	continueButton->setAsStarter();
}

void Pause::update(sf::Time t_deltaTime)
{
	m_GUI.update(t_deltaTime);
	handleControllerInput();
	Game::m_screenView.setCenter(600, 400);
}

void Pause::render(sf::RenderWindow & t_window)
{
	t_window.draw(m_backGround);
	m_GUI.render(t_window);
}

void Pause::handleControllerInput()
{
	
	if (INPUT.PressOnce.Up())
	{
		m_GUI.moveUp();
	}
	if (INPUT.PressOnce.Down())
	{
		m_GUI.moveDown();
	}

	if (INPUT.PressOnce.A())
	{
		std::string m_actionStringTemp = m_GUI.getCurrentWidget()->getActionString();
		std::string *m_actionString = &m_actionStringTemp;
		runAction(*m_actionString);
	}

}

void Pause::runAction(std::string & t_actionString)
{
	if (t_actionString == "Continue")
	{
		Game::m_gameMode = GameMode::Gameplay;
		Game::m_previousMode = GameMode::Pause;
	}
	else if (t_actionString == "Restart")
	{
		Game::m_previousMode = GameMode::MainMenu;
		Game::m_gameMode = GameMode::Gameplay;
	}
	else if (t_actionString == "Options")
	{
		Game::m_previousMode = GameMode::Pause;
		Game::m_gameMode = GameMode::Options;
	}
	else if (t_actionString == "Main Menu")
	{
		Game::m_gameMode = GameMode::MainMenu;
	}
	else if (t_actionString == "Exit")
	{
		Game::m_exitGame = true;
	}
}
