#pragma once

#include "SFML/Graphics.hpp"
#include "Tile.h"
#include "ResourceManager.h"
#include "Bush.h"
#include "CheckpointBox.h"
#include "LevelEditor.h"
#include <list>
#include "LevelLoader.h"

/// <summary>
/// The class that creates the array of tiles and sets their positions and textures
/// </summary>
class TileMap
{
public:
	TileMap(ResourceManager & t_gameAssets);
	~TileMap();

	void update(sf::Time t_deltaTime);
	void render(sf::RenderWindow &t_window,sf::Vector2f t_playerPosition);
	
	std::vector<std::vector<std::tuple<int, sf::Vector2f, sf::Sprite*>>> m_roadTillArrayVec;	//Stores all tile data
	std::vector<std::vector<std::tuple<int, sf::Vector2f, sf::Sprite*>>> * getTileInfo();		// returns tile data

	static const int NUM_TILES_HORIZONTAL{ 14 };
	static const int NUM_TILES_VERTICAL{ 14 };
	
	std::vector<Tile*>&  getOnScreenTiles();

	void placeBushes();

	void placeCheckPoints();
	

	//LevelEditor levelEditor;
	const static int numberOfCheckPoints = 9;

	//CheckpointBox m_checkPoints[numberOfCheckPoints];
	std::vector<CheckpointBox> m_checkPoints;
	std::vector<CheckpointBox> & getCheckpoints();
	std::vector<std::pair<sf::Vector2f, sf::Vector2f>> & getBushes();
	std::vector<std::pair<sf::Vector2f, sf::Vector2f>> & getFullBushes();
private:
	LevelData m_yamlData;	// this just needed to load in int array for tile map

	const int m_tileWidth{ 256 };

	Tile m_tileArray[NUM_TILES_HORIZONTAL][NUM_TILES_VERTICAL];
	int m_tileIndexArray[NUM_TILES_HORIZONTAL][NUM_TILES_VERTICAL] = {
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0 },	// just a grass textured background
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,3,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0 }
	};

	Tile m_roadTileArray[NUM_TILES_HORIZONTAL][NUM_TILES_VERTICAL];
	int m_roadTileIndexArray[NUM_TILES_HORIZONTAL][NUM_TILES_VERTICAL];// this tile array is loaded through yaml, done in tilemap constructor

	
	const static int numberOfBushes = 179;

	Bush m_bush[numberOfBushes];


protected:
	std::vector<Tile*> m_onScreenTiles;

	std::vector<std::pair<sf::Vector2f, sf::Vector2f>> m_bushInfo;
	std::vector<std::pair<sf::Vector2f, sf::Vector2f>> m_fullBushInfo;

};