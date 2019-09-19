#include "TrackSelection.h"
#include "Game.h"

TrackSelection::TrackSelection(ResourceManager & t_gameAssets) :
	m_mapImage(t_gameAssets.m_gameTextures["Mini Map"])
{
	ptrGameAsstes = &t_gameAssets;
	initialize();
}

TrackSelection::~TrackSelection()
{
}

void TrackSelection::initialize()
{
	m_mapImage.setScale(0.2, 0.2); // scale it to usable size
	m_mapImage.setOrigin(m_mapImage.getLocalBounds().width / 2, m_mapImage.getLocalBounds().height / 2);

	for (int i = 0; i < 6; i++)
	{
		m_mapNames[i].setCharacterSize(30);
		m_mapNames[i].setFont(ptrGameAsstes->m_gameFonts["carfont2"]);
		m_mapNames[i].setFillColor(sf::Color::White);
	}

	// GUI
	Button * firstMap = new Button(ptrGameAsstes->m_gameTextures["Mini Map"], 300, 200);
	firstMap->setPosition(sf::Vector2f(225, 150));
	m_mapNames[0].setPosition(120, 250);
	m_mapNames[0].setString("Rainbow island");

	Button * secondMap = new Button(ptrGameAsstes->m_gameTextures["Mini Map"], 300, 200);
	secondMap->setPosition(sf::Vector2f(600, 150));
	m_mapNames[1].setPosition(480, 250);
	m_mapNames[1].setString("Candy Trail");

	Button * thirdMap = new Button(ptrGameAsstes->m_gameTextures["Mini Map"], 300, 200);
	thirdMap->setPosition(sf::Vector2f(975, 150));
	m_mapNames[2].setPosition(860, 250);
	m_mapNames[2].setString("Miami Strip");

	Button * fourthMap = new Button(ptrGameAsstes->m_gameTextures["Mini Map"], 300, 200);
	fourthMap->setPosition(sf::Vector2f(225, 500));
	m_mapNames[3].setPosition(120, 600);
	m_mapNames[3].setString("Rocky Road");

	Button * fifthMap = new Button(ptrGameAsstes->m_gameTextures["Mini Map"], 300, 200);
	fifthMap->setPosition(sf::Vector2f(600, 500));
	m_mapNames[4].setPosition(480, 600);
	m_mapNames[4].setString("Deputy's Pass");

	Button * sixthMap = new Button(ptrGameAsstes->m_gameTextures["Mini Map"], 300, 200);
	sixthMap->setPosition(sf::Vector2f(975, 500));
	m_mapNames[5].setPosition(860, 600);
	m_mapNames[5].setString("Slip 'n Slide");
	
	firstMap->setAsStarter();

	//set left and rights and up and downs
	firstMap->setRight(secondMap);
	firstMap->setDown(fourthMap);
	secondMap->setLeft(firstMap);
	secondMap->setDown(fifthMap);
	secondMap->setRight(thirdMap);
	thirdMap->setLeft(secondMap);
	thirdMap->setDown(sixthMap);
	fourthMap->setUp(firstMap);
	fourthMap->setRight(fifthMap);
	fifthMap->setLeft(fourthMap);
	fifthMap->setRight(sixthMap);
	fifthMap->setUp(secondMap);
	sixthMap->setLeft(fifthMap);
	sixthMap->setUp(thirdMap);


	m_GUI.setStartFocus(firstMap);
	// add to gui
	m_GUI.addWidget(firstMap);
	m_GUI.addWidget(secondMap);
	m_GUI.addWidget(thirdMap);
	m_GUI.addWidget(fourthMap);
	m_GUI.addWidget(fifthMap);
	m_GUI.addWidget(sixthMap);

}

void TrackSelection::update(sf::Time t_deltaTime)
{
	m_GUI.update(t_deltaTime);
	handleControllerInput();
}

void TrackSelection::render(sf::RenderWindow & t_window)
{
	// draw map image in multiple places and draw
	/*m_mapImage.setPosition(300, 200);
	t_window.draw(m_mapImage);
	m_mapImage.setPosition(600, 200);
	t_window.draw(m_mapImage);
	m_mapImage.setPosition(900, 200);
	t_window.draw(m_mapImage);
	m_mapImage.setPosition(300, 600);
	t_window.draw(m_mapImage);
	m_mapImage.setPosition(600, 600);
	t_window.draw(m_mapImage);
	m_mapImage.setPosition(900, 600);
	t_window.draw(m_mapImage);*/
	for (int i = 0; i < 6; i++)
	{
		t_window.draw(m_mapNames[i]);
	}

	m_GUI.render(t_window);
}

void TrackSelection::handleControllerInput()
{
	if (INPUT.PressOnce.Right())
	{
		m_GUI.moveRight();
	}
	if (INPUT.PressOnce.Left())
	{
		m_GUI.moveLeft();
	}
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
		Game::m_previousMode = GameMode::MainMenu;
		Game::m_gameMode = GameMode::Gameplay;
		//MainMenu::stopMusic();
	}
	if (INPUT.PressOnce.B())
	{
		Game::m_gameMode = GameMode::MainMenu;
	}
}