#include "Upgrades.h"
#include "Game.h"

Upgrades::Upgrades(ResourceManager & t_gameAssets) :
	m_widgetsReference{ m_GUI.getWidgets() }
{
	m_ptrGameAssets = &t_gameAssets;

	m_font = t_gameAssets.m_gameFonts["Digitial font"];
}

Upgrades::~Upgrades()
{
}

void Upgrades::initialize()
{
	m_carImage.setTexture(m_ptrGameAssets->m_gameTextures["Car One Large"]);
	m_carImage.setOrigin(m_carImage.getGlobalBounds().width / 2, m_carImage.getGlobalBounds().height / 2);
	m_carImage.setRotation(90);
	m_carImage.setPosition(900, 500);
	m_carImage.scale(2, 2);
	
	m_bckGround.setTexture(m_ptrGameAssets->m_gameTextures["Upgrade BackGround"]);

	//small car images
	m_smallCarImage[0].setTexture(m_ptrGameAssets->m_gameTextures["Car One"]);
	m_smallCarImage[0].setPosition(620, 245);

	m_smallCarImage[1].setTexture(m_ptrGameAssets->m_gameTextures["Car One Green"]);
	m_smallCarImage[1].setPosition(790, 245);
	m_smallCarImage[1].setColor(sf::Color(sf::Color(255, 255, 255, 100)));

	m_smallCarImage[2].setTexture(m_ptrGameAssets->m_gameTextures["Car One Inferno"]);
	m_smallCarImage[2].setPosition(960, 245);
	m_smallCarImage[2].setColor(sf::Color(sf::Color(255, 255, 255, 100)));

	for (int i = 0; i < 4; i++)
	{
		m_equippedText[i].setFont(m_font);
		m_equippedText[i].setCharacterSize(20);
		m_equippedText[i].setFillColor(sf::Color::Green);
		m_equippedText[i].setString("eqquiped");
		m_eqquipedBools[i] = false; // initially false (not drawn)

		//tHIS FOR LOOP CAN ALSO BE USED TO INITIALIZE STAT BARS
		if (i < 3)
		{
			m_statBars[i].setTexture(&m_ptrGameAssets->m_gameTextures["Green Bar"]);
			m_statBars[i].setPosition(sf::Vector2f(580, 115 + (i * 45)));
			m_statBars[i].setSize(sf::Vector2f(550, 20));
		}
	}

	m_statsDisplay.setSize(sf::Vector2f(700,250));
	m_statsDisplay.setFillColor(sf::Color::Black);
	m_statsDisplay.setPosition(450, 50);
	m_statsDisplay.setOutlineColor(sf::Color::Red);
	m_statsDisplay.setOutlineThickness(4);

	m_statsText.setString("Car statistics: \n\nEngine: \n\nWheels: \n\nNitro: \n\nBody:");
	m_statsText.setFont(m_font);
	m_statsText.setCharacterSize(40);
	m_statsText.setFillColor(sf::Color::Green);
	m_statsText.setPosition(460, 55);

	m_moneyDisplay.setSize(sf::Vector2f(240, 75));
	m_moneyDisplay.setPosition(sf::Vector2f(55, 50));
	m_moneyDisplay.setFillColor(sf::Color::Black);
	m_moneyDisplay.setOutlineColor(sf::Color::Red);
	m_moneyDisplay.setOutlineThickness(4);

	m_moneyText.setCharacterSize(40);
	m_moneyText.setPosition(sf::Vector2f(65, 65));
	m_moneyText.setFont(m_font);
	m_moneyText.setFillColor(sf::Color::Green);
	m_moneyText.setString("Money: " + std::to_string(Game::PLAYERS_MONEY) + "$");

	//GUI
	m_GUI.setSoundBuffer(&m_ptrGameAssets->m_gameSounds["Move Selection"], &Game::EFFECTS_BOOL, &m_ptrGameAssets->m_gameSounds["Confirm"],
		&Game::EFFECTS_BOOL, &m_ptrGameAssets->m_gameSounds["Back"], &Game::EFFECTS_BOOL);
	//Engine==============================================================================================================
	Button * engineUpgradeButton = new Button(m_ptrGameAssets->m_gameTextures["Button Texture One"], 320, 75);
	engineUpgradeButton->setString("Engine", 40);
	engineUpgradeButton->setTextColor(sf::Color(sf::Color::Red));
	engineUpgradeButton->setFont(m_font);
	engineUpgradeButton->setPosition(sf::Vector2f(200, 400));
	//engineUpgradeButton->setOutline(sf::Color(sf::Color::White), 3);
	engineUpgradeButton->setHighLightSpeed(6);
	engineUpgradeButton->setFlashColor(sf::Color::Yellow);
	engineUpgradeButton->setActionString("Upgrade Button");

	//Sub Buttons Engine
	Button * engineUpgradeStandard = new Button(m_ptrGameAssets->m_gameTextures["Button Texture One"], 320, 75);
	engineUpgradeStandard->setString("Standard  0$", 40);
	engineUpgradeStandard->setTextColor(sf::Color(sf::Color::Red));
	engineUpgradeStandard->setFont(m_font);
	engineUpgradeStandard->setPosition(sf::Vector2f(200, 400));
	//engineUpgradeStandard->setOutline(sf::Color(sf::Color::White), 3);
	engineUpgradeStandard->setHighLightSpeed(6);
	engineUpgradeStandard->setFlashColor(sf::Color::Yellow);
	engineUpgradeStandard->setActionString("Sub Button Engine");
	engineUpgradeStandard->setButtonAsTransparent();
	m_equippedEngine = engineUpgradeStandard; // set initial equipped

	Button * engineUpgradeSuper = new Button(m_ptrGameAssets->m_gameTextures["Button Texture One"], 320, 75);
	engineUpgradeSuper->setString("Super  500$", 40);
	engineUpgradeSuper->setTextColor(sf::Color(sf::Color::Red));
	engineUpgradeSuper->setFont(m_font);
	engineUpgradeSuper->setPosition(sf::Vector2f(200, 400));
	//engineUpgradeSuper->setOutline(sf::Color(sf::Color::White), 3);
	engineUpgradeSuper->setHighLightSpeed(6);
	engineUpgradeSuper->setFlashColor(sf::Color::Yellow);
	engineUpgradeSuper->setActionString("Sub Button Engine");
	engineUpgradeSuper->setButtonAsTransparent();

	Button * engineUpgradeUltra = new Button(m_ptrGameAssets->m_gameTextures["Button Texture One"], 320, 75);
	engineUpgradeUltra->setString("Ultra  1000$", 40);
	engineUpgradeUltra->setTextColor(sf::Color(sf::Color::Red));
	engineUpgradeUltra->setFont(m_font);
	engineUpgradeUltra->setPosition(sf::Vector2f(200, 400));
	//engineUpgradeUltra->setOutline(sf::Color(sf::Color::White), 3);
	engineUpgradeUltra->setHighLightSpeed(6);
	engineUpgradeUltra->setFlashColor(sf::Color::Yellow);
	engineUpgradeUltra->setActionString("Sub Button Engine");
	engineUpgradeUltra->setButtonAsTransparent();


	//Wheels=================================================================================================================================
	Button * wheelsUpgradeButton = new Button(m_ptrGameAssets->m_gameTextures["Button Texture One"], 320, 75);
	wheelsUpgradeButton->setString("Wheels", 40);
	wheelsUpgradeButton->setTextColor(sf::Color(sf::Color::Red));
	wheelsUpgradeButton->setFont(m_font);
	wheelsUpgradeButton->setPosition(sf::Vector2f(200, 475));
	//wheelsUpgradeButton->setOutline(sf::Color(sf::Color::White), 3);
	wheelsUpgradeButton->setHighLightSpeed(6);
	wheelsUpgradeButton->setFlashColor(sf::Color::Yellow);
	wheelsUpgradeButton->setActionString("Upgrade Button");

	//Sub Buttons 
	Button * wheelsUpgradeStandard = new Button(m_ptrGameAssets->m_gameTextures["Button Texture One"], 320, 75);
	wheelsUpgradeStandard->setString("Standard  0$", 40);
	wheelsUpgradeStandard->setTextColor(sf::Color(sf::Color::Red));
	wheelsUpgradeStandard->setFont(m_font);
	wheelsUpgradeStandard->setPosition(sf::Vector2f(200, 475));
	//wheelsUpgradeStandard->setOutline(sf::Color(sf::Color::White), 3);
	wheelsUpgradeStandard->setHighLightSpeed(6);
	wheelsUpgradeStandard->setFlashColor(sf::Color::Yellow);
	wheelsUpgradeStandard->setActionString("Sub Button Wheel");
	wheelsUpgradeStandard->setButtonAsTransparent();
	m_equippedWheel = wheelsUpgradeStandard; // set initial equipped

	Button * wheelsUpgradeGrippy = new Button(m_ptrGameAssets->m_gameTextures["Button Texture One"], 320, 75);
	wheelsUpgradeGrippy->setString("Grippy  500$", 40);
	wheelsUpgradeGrippy->setTextColor(sf::Color(sf::Color::Red));
	wheelsUpgradeGrippy->setFont(m_font);
	wheelsUpgradeGrippy->setPosition(sf::Vector2f(200, 475));
	//wheelsUpgradeGrippy->setOutline(sf::Color(sf::Color::White), 3);
	wheelsUpgradeGrippy->setHighLightSpeed(6);
	wheelsUpgradeGrippy->setFlashColor(sf::Color::Yellow);
	wheelsUpgradeGrippy->setActionString("Sub Button Wheel");
	wheelsUpgradeGrippy->setButtonAsTransparent();

	Button * wheelsUpgradeExtraGrippy = new Button(m_ptrGameAssets->m_gameTextures["Button Texture One"], 320, 75);
	wheelsUpgradeExtraGrippy->setString("Extra Grippy 1000$", 40);
	wheelsUpgradeExtraGrippy->setTextColor(sf::Color(sf::Color::Red));
	wheelsUpgradeExtraGrippy->setFont(m_font);
	wheelsUpgradeExtraGrippy->setPosition(sf::Vector2f(200, 475));
	//wheelsUpgradeExtraGrippy->setOutline(sf::Color(sf::Color::White), 3);
	wheelsUpgradeExtraGrippy->setHighLightSpeed(6);
	wheelsUpgradeExtraGrippy->setFlashColor(sf::Color::Yellow);
	wheelsUpgradeExtraGrippy->setActionString("Sub Button Wheel");
	wheelsUpgradeExtraGrippy->setButtonAsTransparent();

	//Nitro=======================================================================================================================================
	Button * nitroUpgradeButton = new Button(m_ptrGameAssets->m_gameTextures["Button Texture One"], 320, 75);
	nitroUpgradeButton->setString("Nitro", 40);
	nitroUpgradeButton->setTextColor(sf::Color(sf::Color::Red));
	nitroUpgradeButton->setFont(m_font);
	nitroUpgradeButton->setPosition(sf::Vector2f(200, 550));
	//nitroUpgradeButton->setOutline(sf::Color(sf::Color::White), 3);
	nitroUpgradeButton->setHighLightSpeed(6);
	nitroUpgradeButton->setFlashColor(sf::Color::Yellow);
	nitroUpgradeButton->setActionString("Upgrade Button");

	//Sub Buttons 
	Button * nitroUpgradeStandard = new Button(m_ptrGameAssets->m_gameTextures["Button Texture One"], 320, 75);
	nitroUpgradeStandard->setString("Standard  0$", 40);
	nitroUpgradeStandard->setTextColor(sf::Color(sf::Color::Red));
	nitroUpgradeStandard->setFont(m_font);
	nitroUpgradeStandard->setPosition(sf::Vector2f(200, 550));
	//nitroUpgradeStandard->setOutline(sf::Color(sf::Color::White), 3);
	nitroUpgradeStandard->setHighLightSpeed(6);
	nitroUpgradeStandard->setFlashColor(sf::Color::Yellow);
	nitroUpgradeStandard->setActionString("Sub Button Nitro");
	nitroUpgradeStandard->setButtonAsTransparent();
	m_equippedNitro = nitroUpgradeStandard;

	Button * nitroUpgradeFast = new Button(m_ptrGameAssets->m_gameTextures["Button Texture One"], 320, 75);
	nitroUpgradeFast->setString("Fast  500$", 40);
	nitroUpgradeFast->setTextColor(sf::Color(sf::Color::Red));
	nitroUpgradeFast->setFont(m_font);
	nitroUpgradeFast->setPosition(sf::Vector2f(200, 550));
	//nitroUpgradeFast->setOutline(sf::Color(sf::Color::White), 3);
	nitroUpgradeFast->setHighLightSpeed(6);
	nitroUpgradeFast->setFlashColor(sf::Color::Yellow);
	nitroUpgradeFast->setActionString("Sub Button Nitro");
	nitroUpgradeFast->setButtonAsTransparent();

	Button * nitroUpgradeLightning = new Button(m_ptrGameAssets->m_gameTextures["Button Texture One"], 320, 75);
	nitroUpgradeLightning->setString("Lightning  1000$", 40);
	nitroUpgradeLightning->setTextColor(sf::Color(sf::Color::Red));
	nitroUpgradeLightning->setFont(m_font);
	nitroUpgradeLightning->setPosition(sf::Vector2f(200, 550));
	//nitroUpgradeExtraGluck->setOutline(sf::Color(sf::Color::White), 3);
	nitroUpgradeLightning->setHighLightSpeed(6);
	nitroUpgradeLightning->setFlashColor(sf::Color::Yellow);
	nitroUpgradeLightning->setActionString("Sub Button Nitro");
	nitroUpgradeLightning->setButtonAsTransparent();

	//Body==========================================================================================================
	Button * bodyUpgradeButton = new Button(m_ptrGameAssets->m_gameTextures["Button Texture One"], 320, 75);
	bodyUpgradeButton->setString("Body", 40);
	bodyUpgradeButton->setTextColor(sf::Color(sf::Color::Red));
	bodyUpgradeButton->setFont(m_font);
	bodyUpgradeButton->setPosition(sf::Vector2f(200, 625));
	//bodyUpgradeButton->setOutline(sf::Color(sf::Color::White), 3);
	bodyUpgradeButton->setHighLightSpeed(6);
	bodyUpgradeButton->setFlashColor(sf::Color::Yellow);
	bodyUpgradeButton->setActionString("Upgrade Button");

	//Sub Buttons 
	Button * bodyUpgradeStandard = new Button(m_ptrGameAssets->m_gameTextures["Button Texture One"], 320, 75);
	bodyUpgradeStandard->setString("Standard  0$", 40);
	bodyUpgradeStandard->setTextColor(sf::Color(sf::Color::Blue));
	bodyUpgradeStandard->setFont(m_font);
	bodyUpgradeStandard->setPosition(sf::Vector2f(200, 625));
	//bodyUpgradeStandard->setOutline(sf::Color(sf::Color::White), 3);
	bodyUpgradeStandard->setHighLightSpeed(6);
	bodyUpgradeStandard->setFlashColor(sf::Color::Yellow);
	bodyUpgradeStandard->setActionString("Sub Button Body");
	bodyUpgradeStandard->setButtonAsTransparent();
	m_equippedBody = bodyUpgradeStandard;

	Button * bodyUpgradeGreen = new Button(m_ptrGameAssets->m_gameTextures["Button Texture One"], 320, 75);
	bodyUpgradeGreen->setString("Green  500$", 40);
	bodyUpgradeGreen->setTextColor(sf::Color(sf::Color::Green));
	bodyUpgradeGreen->setFont(m_font);
	bodyUpgradeGreen->setPosition(sf::Vector2f(200, 625));
	//bodyUpgradeFast->setOutline(sf::Color(sf::Color::White), 3);
	bodyUpgradeGreen->setHighLightSpeed(6);
	bodyUpgradeGreen->setFlashColor(sf::Color::Yellow);
	bodyUpgradeGreen->setActionString("Sub Button Body");
	bodyUpgradeGreen->setButtonAsTransparent();

	Button * bodyUpgradeInferno = new Button(m_ptrGameAssets->m_gameTextures["Button Texture One"], 320, 75);
	bodyUpgradeInferno->setString("Inferno  1000$", 40);
	bodyUpgradeInferno->setTextColor(sf::Color(sf::Color::Red));
	bodyUpgradeInferno->setFont(m_font);
	bodyUpgradeInferno->setPosition(sf::Vector2f(200, 625));
	//bodyUpgradeGluck->setOutline(sf::Color(sf::Color::White), 3);
	bodyUpgradeInferno->setHighLightSpeed(6);
	bodyUpgradeInferno->setFlashColor(sf::Color::Yellow);
	bodyUpgradeInferno->setActionString("Sub Button Body");
	bodyUpgradeInferno->setButtonAsTransparent();

	//Set Right 'n Lefts
	//Engine===============================================
	engineUpgradeButton->setRight(engineUpgradeStandard);
	engineUpgradeStandard->setLeft(engineUpgradeButton);
	engineUpgradeStandard->setDown(engineUpgradeSuper);
	engineUpgradeSuper->setUp(engineUpgradeStandard);
	engineUpgradeSuper->setDown(engineUpgradeUltra);
	engineUpgradeUltra->setUp(engineUpgradeSuper);
	//Wheels===============================================
	wheelsUpgradeButton->setRight(wheelsUpgradeStandard);
	wheelsUpgradeStandard->setLeft(wheelsUpgradeButton);
	wheelsUpgradeStandard->setDown(wheelsUpgradeGrippy);
	wheelsUpgradeGrippy->setUp(wheelsUpgradeStandard);
	wheelsUpgradeGrippy->setDown(wheelsUpgradeExtraGrippy);
	wheelsUpgradeExtraGrippy->setUp(wheelsUpgradeGrippy);
	//Nitro=================================================
	nitroUpgradeButton->setRight(nitroUpgradeStandard);
	nitroUpgradeStandard->setLeft(nitroUpgradeButton);
	nitroUpgradeStandard->setDown(nitroUpgradeFast);
	nitroUpgradeFast->setUp(nitroUpgradeStandard);
	nitroUpgradeFast->setDown(nitroUpgradeLightning);
	nitroUpgradeLightning->setUp(nitroUpgradeFast);
	//Body=================================================
	bodyUpgradeButton->setRight(bodyUpgradeStandard);
	bodyUpgradeStandard->setLeft(bodyUpgradeButton);
	bodyUpgradeStandard->setDown(bodyUpgradeGreen);
	bodyUpgradeGreen->setUp(bodyUpgradeStandard);
	bodyUpgradeGreen->setDown(bodyUpgradeInferno);
	bodyUpgradeInferno->setUp(bodyUpgradeGreen);

	//Set Up 'n Downs
	engineUpgradeButton->setDown(wheelsUpgradeButton);
	wheelsUpgradeButton->setUp(engineUpgradeButton);
	wheelsUpgradeButton->setDown(nitroUpgradeButton);
	nitroUpgradeButton->setUp(wheelsUpgradeButton);
	nitroUpgradeButton->setDown(bodyUpgradeButton);
	bodyUpgradeButton->setUp(nitroUpgradeButton);

	// Add widgets to gui
	//Engine Stuff
	m_GUI.addWidget(engineUpgradeUltra);
	m_GUI.addWidget(engineUpgradeSuper);
	m_GUI.addWidget(engineUpgradeStandard);
	m_GUI.addWidget(engineUpgradeButton);
	//wheel stuff
	m_GUI.addWidget(wheelsUpgradeExtraGrippy);
	m_GUI.addWidget(wheelsUpgradeGrippy);
	m_GUI.addWidget(wheelsUpgradeStandard);
	m_GUI.addWidget(wheelsUpgradeButton);
	// nitro stuff
	m_GUI.addWidget(nitroUpgradeLightning);
	m_GUI.addWidget(nitroUpgradeFast);
	m_GUI.addWidget(nitroUpgradeStandard);
	m_GUI.addWidget(nitroUpgradeButton);
	//body stuff
	m_GUI.addWidget(bodyUpgradeInferno);
	m_GUI.addWidget(bodyUpgradeGreen);
	m_GUI.addWidget(bodyUpgradeStandard);
	m_GUI.addWidget(bodyUpgradeButton);
	

	//Set start focus
	m_GUI.setStartFocus(engineUpgradeButton);
	engineUpgradeButton->setAsStarter();
	m_GUI.setAnimationStyle(buttonAnimationStyle::SHRINK);


	m_widgetsReference = m_GUI.getWidgets();
}

void Upgrades::update(sf::Time t_deltaTime)
{
	m_moneyText.setString("Money: " + std::to_string(Game::PLAYERS_MONEY) + "$");
	m_GUI.update(t_deltaTime);
	handleControllerInput();
	setEquipedTextPositions();
}

void Upgrades::render(sf::RenderWindow & t_window)
{
	t_window.draw(m_bckGround);
	t_window.draw(m_carImage);
	t_window.draw(m_statsDisplay);
	t_window.draw(m_statsText);
	t_window.draw(m_moneyDisplay);
	t_window.draw(m_moneyText);

	t_window.draw(m_smallCarImage[0]);
	t_window.draw(m_smallCarImage[1]);
	t_window.draw(m_smallCarImage[2]);

	for (int i = 0; i < 4; i++)
	{
		if (i < 3)
		t_window.draw(m_statBars[i]);

		if (m_eqquipedBools[i])
		t_window.draw(m_equippedText[i]);
	}
	m_GUI.render(t_window);
}

void Upgrades::handleControllerInput()
{
	//std::cout << m_count << std::endl;
	if (m_count > 10)
	{
		if (m_GUI.getCurrentWidget()->getActionString() == "Upgrade Button")
		{
			if (INPUT.PressOnce.A())
			{
				fadeButtons();	// function that fades all buttons exept the current

				m_GUI.moveRight();
				m_subButtonState = subButtonState::SlideOut;
				m_count = 0;
			}

			if (INPUT.PressOnce.Down())
			{
				m_GUI.moveDown();
				m_count = 0;
			}
			if (INPUT.PressOnce.Up())
			{
				m_GUI.moveUp();
				m_count = 0;
			}
			if (INPUT.PressOnce.B())
			{
				Game::m_gameMode = GameMode::MainMenu;
				m_count = 0;
			}
		}
	}


	if (sf::Keyboard::isKeyPressed(sf::Keyboard::M))
	{
		Game::PLAYERS_MONEY += 5000;
	}


	if (m_GUI.getCurrentWidget()->getActionString() == "Upgrade Button")
	{
		if (INPUT.PressOnce.A())
		{
			fadeButtons();	// function that fades all buttons exept the current

			m_GUI.moveRight();
			m_subButtonState = subButtonState::SlideOut;
			m_count = 0;
		}

		if (INPUT.PressOnce.Down())
		{
			m_GUI.moveDown();
			m_count = 0;
		}
		if (INPUT.PressOnce.Up())
		{
			m_GUI.moveUp();
			m_count = 0;
		}
		if (INPUT.PressOnce.B())
		{
			Game::m_gameMode = GameMode::MainMenu;
		}
	}



	// sub button movement
	if (m_GUI.getCurrentWidget()->getActionString() == "Sub Button Engine" || m_GUI.getCurrentWidget()->getActionString() == "Sub Button Wheel" || m_GUI.getCurrentWidget()->getActionString() == "Sub Button Nitro" || m_GUI.getCurrentWidget()->getActionString() == "Sub Button Body")
	{
		if (INPUT.PressOnce.A())
		{
			if (m_GUI.getCurrentWidget()->getActionString() == "Sub Button Engine") // engine upgrade attempt
			{
				if (m_GUI.getCurrentWidget()->getText() == "Standard  0$")
				{
					//change to standard
					Game::ENGINE_TYPE = 0;
					m_statBars[0].setTexture(&m_ptrGameAssets->m_gameTextures["Green Bar"]);

				}
				else if (m_GUI.getCurrentWidget()->getText() == "Super  500$")
				{
					//check money and do appropriate actions
					if (Game::PLAYERS_MONEY >= 500)
					{
						Game::PLAYERS_MONEY -= 500;
						Game::ENGINE_TYPE = 1;
						m_statBars[0].setTexture(&m_ptrGameAssets->m_gameTextures["Orange Bar"]);
					}
				}
				else if (m_GUI.getCurrentWidget()->getText() == "Ultra  1000$")
				{
					//check money and do appropriate actions
					if (Game::PLAYERS_MONEY >= 1000)
					{
						Game::PLAYERS_MONEY -= 1000;
						Game::ENGINE_TYPE = 2;
						m_statBars[0].setTexture(&m_ptrGameAssets->m_gameTextures["Red Bar"]);
					}
				}
			}
			else if (m_GUI.getCurrentWidget()->getActionString() == "Sub Button Wheel") // wheel upgrade attempt
			{
				if (m_GUI.getCurrentWidget()->getText() == "Standard  0$")
				{
					//change to standard
					Game::WHEEL_TYPE = 0;
					m_statBars[1].setTexture(&m_ptrGameAssets->m_gameTextures["Green Bar"]);
				}
				else if (m_GUI.getCurrentWidget()->getText() == "Grippy  500$")
				{
					//check money and do appropriate actions
					if (Game::PLAYERS_MONEY >= 500)
					{
						Game::PLAYERS_MONEY -= 500;
						Game::WHEEL_TYPE = 1;
						m_statBars[1].setTexture(&m_ptrGameAssets->m_gameTextures["Orange Bar"]);
					}
				}
				else if (m_GUI.getCurrentWidget()->getText() == "Extra Grippy 1000$")
				{
					//check money and do appropriate actions
					if (Game::PLAYERS_MONEY >= 1000)
					{
						Game::PLAYERS_MONEY -= 1000;
						Game::WHEEL_TYPE = 2;
						m_statBars[1].setTexture(&m_ptrGameAssets->m_gameTextures["Red Bar"]);
					}
				}
			}
			else if (m_GUI.getCurrentWidget()->getActionString() == "Sub Button Nitro") // nitro upgrade attempt
			{
				if (m_GUI.getCurrentWidget()->getText() == "Standard  0$")
				{
					//change to standard
					Game::NITRO_TYPE = 0;
					m_statBars[2].setTexture(&m_ptrGameAssets->m_gameTextures["Green Bar"]);
				}
				else if (m_GUI.getCurrentWidget()->getText() == "Fast  500$")
				{
					//check money and do appropriate actions
					if (Game::PLAYERS_MONEY >= 500)
					{
						Game::PLAYERS_MONEY -= 500;
						Game::NITRO_TYPE = 1;
						m_statBars[2].setTexture(&m_ptrGameAssets->m_gameTextures["Orange Bar"]);
					}
				}
				else if (m_GUI.getCurrentWidget()->getText() == "Lightning  1000$")
				{
					//check money and do appropriate actions
					if (Game::PLAYERS_MONEY >= 1000)
					{
						Game::PLAYERS_MONEY -= 1000;
						Game::NITRO_TYPE = 2;
						m_statBars[2].setTexture(&m_ptrGameAssets->m_gameTextures["Red Bar"]);
					}
				}
			}
			else if (m_GUI.getCurrentWidget()->getActionString() == "Sub Button Body") // Body upgrade attempt
			{
				if (m_GUI.getCurrentWidget()->getText() == "Standard  0$")
				{
					//change to standard
					Game::BODY_TYPE = 0;
					m_smallCarImage[0].setColor(sf::Color(sf::Color(255, 255, 255, 255)));
					m_smallCarImage[1].setColor(sf::Color(sf::Color(255, 255, 255, 100)));
					m_smallCarImage[2].setColor(sf::Color(sf::Color(255, 255, 255, 100)));
					m_carImage.setTexture(m_ptrGameAssets->m_gameTextures["Car One Large"]);
				}
				else if (m_GUI.getCurrentWidget()->getText() == "Green  500$")
				{
					//check money and do appropriate actions
					if (Game::PLAYERS_MONEY >= 500)
					{
						Game::PLAYERS_MONEY -= 500;
						Game::BODY_TYPE = 1;
						m_smallCarImage[0].setColor(sf::Color(sf::Color(255, 255, 255, 100)));
						m_smallCarImage[1].setColor(sf::Color(sf::Color(255, 255, 255, 255)));
						m_smallCarImage[2].setColor(sf::Color(sf::Color(255, 255, 255, 100)));
						m_carImage.setTexture(m_ptrGameAssets->m_gameTextures["Car One Large Green"]);
					}
				}
				else if (m_GUI.getCurrentWidget()->getText() == "Inferno  1000$")
				{
					//check money and do appropriate actions
					if (Game::PLAYERS_MONEY >= 1000)
					{
						Game::PLAYERS_MONEY -= 1000;
						Game::BODY_TYPE = 2;
						m_smallCarImage[0].setColor(sf::Color(sf::Color(255, 255, 255, 100)));
						m_smallCarImage[1].setColor(sf::Color(sf::Color(255, 255, 255, 100)));
						m_smallCarImage[2].setColor(sf::Color(sf::Color(255, 255, 255, 255)));
						m_carImage.setTexture(m_ptrGameAssets->m_gameTextures["Car One Large Inferno"]);
					}
				}
			}

		}


		if (INPUT.PressOnce.B() && m_subButtonState == subButtonState::DoNothing)
		{
			m_subButtonState = subButtonState::ReverseDropDown;
		}
		if (INPUT.PressOnce.Down())
		{
			m_GUI.moveDown();
		}
		if (INPUT.PressOnce.Up())
		{
			m_GUI.moveUp();
		}

		if (m_GUI.getCurrentWidget()->getActionString() == "Sub Button Engine")
		{
			m_eqquipedBools[0] = true; // set eqquipped to draw
		}
		else if (m_GUI.getCurrentWidget()->getActionString() == "Sub Button Wheel")
		{
			m_eqquipedBools[1] = true; // set eqquipped to draw
		}
		else if (m_GUI.getCurrentWidget()->getActionString() == "Sub Button Nitro")
		{
			m_eqquipedBools[2] = true; // set eqquipped to draw
		}
		else if (m_GUI.getCurrentWidget()->getActionString() == "Sub Button Body")
		{
			m_eqquipedBools[3] = true; // set eqquipped to draw
		}

		subButtonMovement();
	}
	else
	{
		for (int i = 0; i < 4; i++)
		{
			m_eqquipedBools[i] = false;
		}
	}
}

void Upgrades::runAction(std::string & t_actionString)
{

}

void Upgrades::fadeButtons()
{
	Widget * previousWidget = m_GUI.getCurrentWidget();
	for (int i = 0; i < 4; i++)
	{
		m_GUI.moveUp();
		m_GUI.getCurrentWidget()->setButtonAsFaded();
	}
	for (int i = 0; i < 4; i++)
	{
		m_GUI.moveDown();
		m_GUI.getCurrentWidget()->setButtonAsFaded();
		m_GUI.getCurrentWidget()->notHightlighted();	// to stop button thinking its in focus
	}
	m_GUI.setStartFocus(previousWidget);
	previousWidget->setAsStarter();
	m_GUI.getCurrentWidget()->setButtonAsNormal();
}

void Upgrades::unFadeButtons()
{
	Widget * previousWidget = m_GUI.getCurrentWidget();
	for (int i = 0; i < 4; i++)
	{
		m_GUI.moveUp();
		m_GUI.getCurrentWidget()->setButtonAsNormal();
	}
	for (int i = 0; i < 4; i++)
	{
		m_GUI.moveDown();
		m_GUI.getCurrentWidget()->setButtonAsNormal();
		m_GUI.getCurrentWidget()->notHightlighted();	// to stop button thinking its in focus
	}
	m_GUI.setStartFocus(previousWidget);
	previousWidget->setAsStarter();
	m_GUI.getCurrentWidget()->setButtonAsNormal();
}

void Upgrades::subButtonMovement()
{
	switch (m_subButtonState)
	{
	case Upgrades::subButtonState::Normal:
		for (auto widget : m_widgetsReference)
		{
			if (widget->getActionString() == firstSubButton->getActionString())
			{
				// set all to transparent
				widget->setButtonAsTransparent();
			}
		}
		m_GUI.setStartFocus(firstSubButton);
		m_GUI.moveLeft();	// set back to upgrade button
		unFadeButtons(); //unfade the buttons
		break;
	case Upgrades::subButtonState::SlideOut:
		for (auto widget : m_widgetsReference)
		{
			if (widget->getActionString() == m_GUI.getCurrentWidget()->getActionString())
			{
				// set all to normal so can be seen
				widget->setButtonAsNormal();
				widget->setPosition(m_GUI.getCurrentWidget()->getPosition());
			}
		}

		if (m_GUI.getCurrentWidget()->getPosition().x < 520)
		{
			//move it right
			m_GUI.getCurrentWidget()->setPosition(sf::Vector2f(m_GUI.getCurrentWidget()->getPosition().x + (m_slideSpeed * 1.5), m_GUI.getCurrentWidget()->getPosition().y));
		}
		else
		{
			firstSubButton = m_GUI.getCurrentWidget();
			m_subButtonState = subButtonState::DropDown;
		}
		break;
	case Upgrades::subButtonState::DropDown:

		for (auto widget : m_widgetsReference)
		{
			if (widget->getActionString() == firstSubButton->getActionString())
			{
				if (widget->getText() == "Super  500$" || widget->getText() == "Grippy  500$" || widget->getText() == "Fast  500$" || widget->getText() == "Green  500$")
				{
					if (widget->getPosition().y < firstSubButton->getPosition().y + 75)
					{
						widget->setPosition(sf::Vector2f(widget->getPosition().x, widget->getPosition().y + m_slideSpeed));
					}
					else
					{
						widget->setPosition(sf::Vector2f(widget->getPosition().x, firstSubButton->getPosition().y + 75));
					}
				}
				else if (widget->getText() == "Ultra  1000$" || widget->getText() == "Extra Grippy 1000$" || widget->getText() == "Lightning  1000$" || widget->getText() == "Inferno  1000$")
				{
					if (widget->getPosition().y < firstSubButton->getPosition().y + 150)
					{
						widget->setPosition(sf::Vector2f(widget->getPosition().x, widget->getPosition().y + m_slideSpeed));
					}
					else
					{
						widget->setPosition(sf::Vector2f(widget->getPosition().x, firstSubButton->getPosition().y + 150));
						m_GUI.getCurrentWidget()->notHightlighted();
						m_GUI.setStartFocus(firstSubButton);
						firstSubButton->setAsStarter();
						m_subButtonState = subButtonState::DoNothing;
					}
				}
			}
		}
		break;
	case Upgrades::subButtonState::DoNothing:
		break;
	case Upgrades::subButtonState::ReverseDropDown:

		for (auto widget : m_widgetsReference)
		{
			if (widget->getActionString() == firstSubButton->getActionString())
			{
				if (widget->getPosition().y > firstSubButton->getPosition().y)
				{
					widget->setPosition(sf::Vector2f(widget->getPosition().x, widget->getPosition().y - m_slideSpeed));
				}
				else
				{
					widget->setPosition(firstSubButton->getPosition());
				}

				if (widget->getText() == "Ultra  1000$" || widget->getText() == "Extra Grippy 1000$" || widget->getText() == "Lightning  1000$" || widget->getText() == "Inferno  1000$")
				{
					if (widget->getPosition().y <= firstSubButton->getPosition().y)
					{
						m_subButtonState = subButtonState::SlideIn;
					}
				}
			}
		}
		break;
	case Upgrades::subButtonState::SlideIn:

		for (auto widget : m_widgetsReference)
		{
			if (widget->getActionString() == firstSubButton->getActionString())
			{
				if (widget->getPosition().x > 205)
				{
					widget->setPosition(sf::Vector2f(widget->getPosition().x - (m_slideSpeed * 1.5), widget->getPosition().y));
				}
				else
				{
					m_subButtonState = subButtonState::Normal;
				}
			}
		}
		break;
	default:
		break;
	}
}

void Upgrades::setEquipedTextPositions()
{
	for (auto widget : m_widgetsReference)
	{
		switch (Game::ENGINE_TYPE) // switch to set engines current eqquiped widget
		{
		case 0:
			if (widget->getActionString() == "Sub Button Engine" && widget->getText() == "Standard  0$")
			{
				m_equippedEngine = widget;
			}
			break;
		case 1:
			if (widget->getActionString() == "Sub Button Engine" && widget->getText() == "Super  500$")
			{
				m_equippedEngine = widget;
			}
			break;
		case 2:
			if (widget->getActionString() == "Sub Button Engine" && widget->getText() == "Ultra  1000$")
			{
				m_equippedEngine = widget;
			}
			break;
		default:
			break;
		}

		switch (Game::WHEEL_TYPE)
		{
		case 0:
			if (widget->getActionString() == "Sub Button Wheel" && widget->getText() == "Standard  0$")
			{
				m_equippedWheel = widget;
			}
			break;
		case 1:
			if (widget->getActionString() == "Sub Button Wheel" && widget->getText() == "Grippy  500$")
			{
				m_equippedWheel = widget;
			}
			break;
		case 2:
			if (widget->getActionString() == "Sub Button Wheel" && widget->getText() == "Extra Grippy 1000$")
			{
				m_equippedWheel = widget;
			}
			break;
		default:
			break;
		}

		switch (Game::NITRO_TYPE)
		{
		case 0:
			if (widget->getActionString() == "Sub Button Nitro" && widget->getText() == "Standard  0$")
			{
				m_equippedNitro = widget;
			}
			break;
		case 1:
			if (widget->getActionString() == "Sub Button Nitro" && widget->getText() == "Fast  500$")
			{
				m_equippedNitro = widget;
			}
			break;
		case 2:
			if (widget->getActionString() == "Sub Button Nitro" && widget->getText() == "Lightning  1000$")
			{
				m_equippedNitro = widget;
			}
			break;
		default:
			break;
		}

		switch (Game::BODY_TYPE)
		{
		case 0:
			if (widget->getActionString() == "Sub Button Body" && widget->getText() == "Standard  0$")
			{
				m_equippedBody = widget;
			}
			break;
		case 1:
			if (widget->getActionString() == "Sub Button Body" && widget->getText() == "Green  500$")
			{
				m_equippedBody = widget;
			}
			break;
		case 2:
			if (widget->getActionString() == "Sub Button Body" && widget->getText() == "Inferno  1000$")
			{
				m_equippedBody = widget;
			}
			break;
		default:
			break;
		}
	}

	m_equippedText[0].setPosition(sf::Vector2f(m_equippedEngine->getPosition().x + 170, m_equippedEngine->getPosition().y));
	m_equippedText[1].setPosition(sf::Vector2f(m_equippedWheel->getPosition().x + 170, m_equippedWheel->getPosition().y));
	m_equippedText[2].setPosition(sf::Vector2f(m_equippedNitro->getPosition().x + 170, m_equippedNitro->getPosition().y));
	m_equippedText[3].setPosition(sf::Vector2f(m_equippedBody->getPosition().x + 170, m_equippedBody->getPosition().y));
}
