#include "Licence.h"
#include "Game.h"


Licence::Licence(ResourceManager & t_gameAssets) :
	m_skyTexture(t_gameAssets.m_gameTextures["Sky"]),
	m_cloudTexture(t_gameAssets.m_gameTextures["Clouds"]),
	m_mountainTexture(t_gameAssets.m_gameTextures["Mountain"]),
	m_treeTexture(t_gameAssets.m_gameTextures["Tree"]),
	m_roadTexture(t_gameAssets.m_gameTextures["Road"]),
	m_confirmBuffer(t_gameAssets.m_gameSounds["Confirm"]),
	m_buttonATexture(t_gameAssets.m_gameTextures["Button A"]),
	m_logoTexture(t_gameAssets.m_gameTextures["Logo Game"]),
	m_font(t_gameAssets.m_gameFonts["Digitial font"])
{
	m_skyTexture.setRepeated(true);
	m_cloudTexture.setRepeated(true);
	m_mountainTexture.setRepeated(true);
	m_treeTexture.setRepeated(true);
	m_roadTexture.setRepeated(true);

	m_carSpritesTexture[0].loadFromFile("ASSETS/IMAGES/Licence/1.png");
	m_carSpritesTexture[1].loadFromFile("ASSETS/IMAGES/Licence/2.png");
	m_carSpritesTexture[2].loadFromFile("ASSETS/IMAGES/Licence/3.png");
	m_carSpritesTexture[3].loadFromFile("ASSETS/IMAGES/Licence/4.png");

	m_sky.setTexture(m_skyTexture);
	m_sky.setTextureRect(sf::IntRect(0, 0, 1920, 1080));


	m_cloud.setTexture(m_cloudTexture);
	m_cloud.setTextureRect(sf::IntRect(0, 0, 1920, 1080));


	m_mountain.setTexture(m_mountainTexture);
	m_mountain.setTextureRect(sf::IntRect(0, 0, 1920, 1080));

	m_tree.setTexture(m_treeTexture);
	m_tree.setTextureRect(sf::IntRect(0, 0, 1920, 1080));

	m_road.setTexture(m_roadTexture);
	m_road.setTextureRect(sf::IntRect(0, 0, 1920, 1080));

	m_sky.setPosition(sf::Vector2f(0, 0));
	m_cloud.setPosition(sf::Vector2f(0, 0));
	m_mountain.setPosition(sf::Vector2f(0, 0));
	m_tree.setPosition(sf::Vector2f(0, 0));
	m_road.setPosition(sf::Vector2f(0, 0));

	m_car.setPosition(200, 520);
	m_car.setTexture(m_carSpritesTexture[0]);
	m_car.setScale(.5, .5);

	m_logo.setTexture(m_logoTexture);
	m_logo.setScale(2, 2);
	m_logo.setPosition(sf::Vector2f(350, 100));

	switchScene = false;

	// Set up confirm sound
	m_confirmSFX.setBuffer(m_confirmBuffer);
	m_confirmSFX.setLoop(false);
	m_confirmSFX.stop();

	// Set Up Texture Xbox
	m_buttonA.setTexture(m_buttonATexture);
	m_buttonA.setPosition(600, 600);
	m_buttonA.setOrigin(50, 50);

	m_pressA.setFont(m_font);
	m_pressA.setPosition(600, 400);
	m_pressA.setString("Press A to Continue");
	m_pressA.setCharacterSize(40);
	m_pressA.setOrigin((m_pressA.getGlobalBounds().width) / 2, m_pressA.getGlobalBounds().height / 2);
	m_pressA.setFillColor(sf::Color::Red);
}


Licence::~Licence()
{
}


void Licence::initialize()
{
}

void Licence::update(sf::Time t_deltaTime)
{
	skyX += 0.01;
	m_sky.setTextureRect(sf::IntRect(skyX, 0, 1200, 800));

	cloudX += 0.2;
	m_cloud.setTextureRect(sf::IntRect(cloudX, 0, 1200, 800));

	mountainX += 0.4;
	m_mountain.setTextureRect(sf::IntRect(mountainX, 0, 1200, 800));

	treeX += 0.8;
	m_tree.setTextureRect(sf::IntRect(treeX, 0, 1200, 800));

	roadX += 1.6;
	m_road.setTextureRect(sf::IntRect(roadX, 0, 1200, 800));

	UpdateSprite();

	handleControllerInput();
}

void Licence::render(sf::RenderWindow & t_window)
{


	t_window.clear();
	t_window.draw(m_sky);
	t_window.draw(m_cloud);
	t_window.draw(m_mountain);
	t_window.draw(m_tree);
	t_window.draw(m_road);
	t_window.draw(m_car);
	t_window.draw(m_logo);

	if (!pressedA && ScreenTransitions::isTransitioning() == false)
	{
		t_window.draw(m_buttonA);
		t_window.draw(m_pressA);
	}
	else
	{
		if (m_counterButtonFlash % 2 == 0)
		{

		}
		else
		{
			t_window.draw(m_buttonA);
		}
	}
}

void Licence::handleControllerInput()
{
	if (ScreenTransitions::isTransitioning() == false && !switchScene)
	{
		if (INPUT.PressOnce.A() == true)
		{
			pressedA = true;
			ScreenTransitions::setFadeType(false);

			ScreenTransitions::setFadeSpeed(6);
			switchScene = true;


			m_confirmSFX.play();

		}
	}
	else if (ScreenTransitions::isTransitioning() == false && switchScene)
	{

		Game::m_gameMode = GameMode::MainMenu;
		ScreenTransitions::setFadeType(true);
		ScreenTransitions::setFadeSpeed(6);
	}
}

void Licence::runAction(std::string & t_actionString)
{

}

void Licence::UpdateSprite()
{
	if (m_spriteCount > 4)
	{
		m_spriteTextureIndex++;
		if (m_spriteTextureIndex > 3)
		{
			m_spriteTextureIndex = 0;
		}
		m_car.setTexture(m_carSpritesTexture[m_spriteTextureIndex]);
		m_spriteCount = 0;
	}
	m_spriteCount++;

	carPositionX += 4;

	if (carPositionX > 3000)
	{
		carPositionX = -600;
	}
	m_car.setPosition(carPositionX, m_car.getPosition().y);

	if (!pressedA)
	{
		if (m_increase)
		{
			m_buttonScale += 0.02f;

			if (m_buttonScale > 1)
			{
				m_increase = !m_increase;
			}
		}
		else if (!m_increase)
		{
			m_buttonScale -= 0.02f;

			if (m_buttonScale < 0.5f)
			{
				m_increase = !m_increase;
			}
		}
	}
	else
	{
		m_buttonScale = 1;
	}
	m_buttonA.setScale(m_buttonScale,m_buttonScale);
}
