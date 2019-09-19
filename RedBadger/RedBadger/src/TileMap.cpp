#include "TileMap.h"
#include <tuple>
#include <fstream>
#include <iostream>

TileMap::TileMap(ResourceManager & t_gameAssets)
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

	// populate index array
	for (int i = 0; i < NUM_TILES_HORIZONTAL; i++)		// 14
	{
		for (int j = 0; j < NUM_TILES_VERTICAL; j++)			// 14
		{
			m_roadTileIndexArray[j][i] = m_yamlData.m_intContainer.at(i+(14*j));
		}
	}


	for (int i = 0; i < NUM_TILES_HORIZONTAL; i++)		// 14
	{
		for (int j = 0; j < NUM_TILES_VERTICAL; j++)			// 14
		{
			//initialize game assets pointer for tiles
			m_tileArray[i][j].initialize(t_gameAssets);
			m_roadTileArray[i][j].initialize(t_gameAssets);

			// BackGround========================================================================

			m_tileArray[i][j].setPosition(sf::Vector2f{ (float)j * 256,(float)i * 256 });

			m_tileArray[i][j].setTexture(m_tileIndexArray[i][j]);

			// Road =============================================================================
			m_roadTileArray[i][j].setPosition(sf::Vector2f{ (float)j * 256,(float)i * 256 });

			m_roadTileArray[i][j].setTexture(m_roadTileIndexArray[i][j]);

		}
	}

	for (int i = 0; i < 14; i++)		// 14
	{
		std::vector<std::tuple<int, sf::Vector2f, sf::Sprite*>> innerTemp;
		for (int j = 0; j < 14; j++)			// 14
		{
			std::tuple<int, sf::Vector2f, sf::Sprite*> pairTemp;
			pairTemp = std::make_tuple(m_roadTileArray[i][j].getIndex(), m_roadTileArray[i][j].getPosition(), m_roadTileArray[i][j].getSprite());
			innerTemp.push_back(pairTemp);
		}
		m_roadTillArrayVec.push_back(innerTemp);
	}


	for (int i = 0; i < numberOfBushes; i++)
	{
		m_bush[i].init();
	}


	// Set up checkpoints 
	for (int i = 0; i < numberOfCheckPoints; i++)
	{
		CheckpointBox check;
		check.setSize(sf::Vector2f(400, 400));
		check.getShape().setOrigin(200, 200);
		check.getShape().setFillColor(sf::Color::Yellow);
		check.setOpacity(40.0f);

		check.setID(i + 100);
		check.setAsRaceCheckPoint(true); // set as a race checkpoint
		m_checkPoints.push_back(check);

	}
	m_checkPoints.at(0).setDirection(1);
	m_checkPoints.at(1).setDirection(2);
	m_checkPoints.at(2).setDirection(2);
	m_checkPoints.at(3).setDirection(3);
	m_checkPoints.at(4).setDirection(2);

	m_checkPoints.at(5).setDirection(1);
	m_checkPoints.at(6).setDirection(4);
	m_checkPoints.at(7).setDirection(4);
	m_checkPoints.at(8).setDirection(4);


	placeBushes();
	placeCheckPoints();

	for (int i = 0; i < numberOfBushes; i++)
	{
		sf::Vector2f pos = m_bush[i].getSprite().getPosition();
		std::pair<sf::Vector2f, sf::Vector2f> tempPair;
		tempPair.first = pos;
		tempPair.second = sf::Vector2f{ 83,83 };
		m_fullBushInfo.push_back(tempPair);
	}
}

TileMap::~TileMap()
{

}

void TileMap::update(sf::Time t_deltaTime)
{

}

void TileMap::render(sf::RenderWindow & t_window, sf::Vector2f t_playerPosition)
{
	if (m_onScreenTiles.size() > 0)
	{
		m_onScreenTiles.clear(); // clear every time, repopulated below
	}
	for (int i = 0; i < NUM_TILES_HORIZONTAL; i++)		// 14
	{
		for (int j = 0; j < NUM_TILES_VERTICAL; j++)			// 14
		{
			// IF statement for culling (only render if on screen)
			if (m_tileArray[i][j].getPosition().x > (t_playerPosition.x - (600 + m_tileWidth)) &&
				m_tileArray[i][j].getPosition().x < (t_playerPosition.x + (600)) &&
				m_tileArray[i][j].getPosition().y >(t_playerPosition.y - (400 + m_tileWidth)) &&
				m_tileArray[i][j].getPosition().y < (t_playerPosition.y + (400)))
			{
				m_tileArray[i][j].render(t_window);
			}
		}
	}
	for (int i = 0; i < NUM_TILES_HORIZONTAL; i++)		// 14
	{
		for (int j = 0; j < NUM_TILES_VERTICAL; j++)			// 14
		{
			// IF statement for culling (only render if on screen)
			if (m_roadTileArray[i][j].getPosition().x >(t_playerPosition.x - (600 + m_tileWidth)) &&
				m_roadTileArray[i][j].getPosition().x < (t_playerPosition.x + (600)) &&
				m_roadTileArray[i][j].getPosition().y >(t_playerPosition.y - (400 + m_tileWidth)) &&
				m_roadTileArray[i][j].getPosition().y < (t_playerPosition.y + (400)))
			{
				m_roadTileArray[i][j].render(t_window);
				m_onScreenTiles.push_back(&m_roadTileArray[i][j]);
			}
		}
	}

	// Bushes
	m_bushInfo.clear();
	for (int i = 0; i < numberOfBushes; i++)
	{
		// culling
		if (m_bush[i].getSprite().getPosition().x > (t_playerPosition.x - (600 + m_tileWidth)) &&
			m_bush[i].getSprite().getPosition().x < (t_playerPosition.x + (600 + m_tileWidth)) &&
			m_bush[i].getSprite().getPosition().y >(t_playerPosition.y - (400 + m_tileWidth)) &&
			m_bush[i].getSprite().getPosition().y < (t_playerPosition.y + (400 + m_tileWidth)))
		{

			sf::Vector2f pos = m_bush[i].getSprite().getPosition();
			std::pair<sf::Vector2f, sf::Vector2f> tempPair;
			tempPair.first = pos;
			tempPair.second = sf::Vector2f{ 83,83 };
			m_bushInfo.push_back(tempPair);
			m_bush[i].render(t_window);
		}
	}

	//for (int i = 0; i < numberOfCheckPoints; i++)
	//{
	//	t_window.draw(m_checkPoints[i].getShape());
	//}

}

std::vector<std::vector<std::tuple<int, sf::Vector2f, sf::Sprite*>>>* TileMap::getTileInfo()
{
	return &m_roadTillArrayVec;
}

std::vector<Tile*>& TileMap::getOnScreenTiles()
{
	return m_onScreenTiles;
}

void TileMap::placeBushes()
{
	std::ifstream vectorData("positionFile.txt");
	std::string vecData;


	// iterate through string and add ASCII contents into string
	if (vectorData)
	{
		std::string vectorPosTextContainer((std::istreambuf_iterator<char>(vectorData)),
			std::istreambuf_iterator<char>());

		vecData.clear();
		vecData = vectorPosTextContainer;
	}

	// Initialise and set up bush
	int iBush = 0;

	while (iBush < numberOfBushes)
	{
		// Strings for storing values from text file
		std::string x_str;
		std::string y_str;


		float x = 0;
		float y = 0;

		//bush.setPosition(sf::Vector2f(x, y));

		bool setX = true;

		x_str.clear();
		y_str.clear();


		for (int i = 0; i < vecData.length(); i++)
		{
			// if data char is not , or ENter
			if (vecData[i] != 44 && vecData[i] != 10)
			{

				if (setX)
				{
					x_str += vecData[i];
				}
				else
				{
					y_str += vecData[i];
				}


			}

			// new line
			else if (vecData[i] == 10)
			{
				setX = true;

				float x = std::stof(x_str);
				float y = std::stof(y_str);

				m_bush[iBush].setPosition(sf::Vector2f(x, y));
				x_str.clear();
				y_str.clear();

				iBush++;
				if (iBush >= numberOfBushes)
				{
					break;
				}

			}
			// comma ,
			else if (vecData[i] == 44)
			{
				setX = false;
			}
		}


	}

}

void TileMap::placeCheckPoints()
{
	std::ifstream vectorData("positionFileCheckPoints.txt");
	std::string vecData;


	// iterate through string and add ASCII contents into string
	if (vectorData)
	{
		std::string vectorPosTextContainer((std::istreambuf_iterator<char>(vectorData)),
			std::istreambuf_iterator<char>());

		vecData.clear();
		vecData = vectorPosTextContainer;
	}

	// Initialise and set up checkPoint
	int checkIndex = 0;

	while (checkIndex < numberOfCheckPoints)
	{
		// Strings for storing values from text file
		std::string x_str;
		std::string y_str;


		float x = 0;
		float y = 0;

		//bush.setPosition(sf::Vector2f(x, y));

		bool setX = true;

		x_str.clear();
		y_str.clear();


		for (int i = 0; i < vecData.length(); i++)
		{
			// if data char is not , or ENter
			if (vecData[i] != 44 && vecData[i] != 10)
			{

				if (setX)
				{
					x_str += vecData[i];
				}
				else
				{
					y_str += vecData[i];
				}


			}

			// new line
			else if (vecData[i] == 10)
			{
				setX = true;

				float x = std::stof(x_str) - 200;
				float y = std::stof(y_str) - 200;

				// set as an racecheck piont
				m_checkPoints[checkIndex].setAsRaceCheckPoint(setX);
				m_checkPoints[checkIndex].setPosition(sf::Vector2f(x, y));
				x_str.clear();
				y_str.clear();

				checkIndex++;

				if (checkIndex >= numberOfCheckPoints)
				{
					break;
				}

			}
			// comma ,
			else if (vecData[i] == 44)
			{
				setX = false;
			}
		}


	}
}

std::vector<CheckpointBox>& TileMap::getCheckpoints()
{
	return m_checkPoints;
}

std::vector<std::pair<sf::Vector2f, sf::Vector2f>>& TileMap::getBushes()
{
	return m_bushInfo;
}

std::vector<std::pair<sf::Vector2f, sf::Vector2f>>& TileMap::getFullBushes()
{
	return m_fullBushInfo;
}
