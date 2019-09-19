#pragma once

#include <sstream>
#include <fstream>
#include <iostream>
#include "yaml-cpp/yaml.h"


/// <summary>
/// @brief A struct to store int array information for tilemap.
/// 
/// </summary>
struct Int
{
	// int array
	int m_int;
};

/// <summary>
/// @brief A struct to store all fonts information.
/// 
/// </summary>
struct Fonts
{
	//File names for fonts
	std::string m_speed;
	std::string m_digital;

};

/// <summary>
/// Struct that stores all sounds and sound effects
/// </summary>
struct Sounds
{
	// Sound Effects
	std::string m_splash;
	std::string m_select;
	std::string m_return;

	std::string m_lap;
	std::string m_finalLap;

	std::string m_win;
	std::string m_place;
	std::string m_lose;

	std::string m_wheelTurn;
	std::string m_confirm;
	std::string m_back;
	std::string m_moveSelection;

	std::string m_pullAhead;
	std::string m_fallBehind;

	std::string m_raceFinished;

	//BGM
	std::string m_menuMusic;
	std::string m_raceMusic;
	std::string m_raceResultsMusic;



};

/// <summary>
/// @brief A struct to store all texture information.
/// 
/// </summary>
struct Textures
{
	//File names for textures
	std::string m_backGroundSoundOptions;
	std::string m_buttonTextureOne;
	std::string m_volumeKnob;

	std::string m_spriteSheetDirtRoad;
	std::string m_spriteSheetVarious;

	std::string m_raisedRoad;
	std::string m_iceRoad;

	std::string m_carOne;
	std::string m_carTwo;
	std::string m_carThree;
	std::string m_carFour;
	std::string m_carOneGreen;
	std::string m_carOneInferno;
	std::string m_carOneLarge;
	std::string m_carOneLargeGreen;
	std::string m_carOneLargeInferno;
	std::string m_plusOneDrop;
	std::string m_miniMap;
	std::string m_grass;
	std::string m_snow;
	std::string m_snowTreeTile;
	std::string m_snowTree;
	std::string m_bigRedTent;
	std::string m_redTent;
	std::string m_XboxA;
	std::string m_XboxRT;
	std::string m_XboxLT;
	std::string m_XboxLS;
	std::string m_finishLine;
	std::string m_menuWheel;
	std::string m_menuBackground;
	std::string m_border;
	std::string m_bridgeWall;
	std::string m_backCar;
	std::string m_particle;
	std::string m_upgradeBackGround;
	std::string m_greenBar;
	std::string m_orangeBar;
	std::string m_redBar;

	std::string m_screenCurtain;
	std::string m_logo;

	//Licence
	std::string m_sky;
	std::string m_clouds;
	std::string m_mountain;
	std::string m_tree;
	std::string m_road;
	std::string m_carSprite1;
	std::string m_carSprite2;
	std::string m_carSprite3;
	std::string m_carSprite4;
	std::string m_logoGame;

	// Xbox Icons
	std::string m_buttonA;
};

/// <summary>
/// @brief A struct representing all the Level Data.
/// 
/// Obstacles may be repeated and are therefore stored in a container.
/// </summary>
struct LevelData
{
	Textures m_textures;
	Fonts m_fonts;
	Sounds m_sounds;
	std::vector<int> m_intContainer;

	/*BackgroundData m_background;
	TankData m_tank;
	std::vector<ObstacleData> m_obstacles;
	std::vector<TargetData> m_target;*/
};


/// <summary>
/// @brief A class to manage level loading.
/// 
/// This class will manage level loading using YAML.
/// </summary>
class LevelLoader
{
public:

	/// <summary>
	/// @brief No-op default constructor.
	/// 
	/// </summary>
	LevelLoader() = default;

	/// <summary>
	/// @brief Loads and parses the yaml level file.
	/// The level file is identified by a number and is assumed to have
	/// the following format: "level" followed by number followed by .yaml extension
	/// E.g. "level1.yaml"
	/// The level information is stored in the specified LevelData object.
	/// If the filename is not found or the file data is invalid, an exception
	/// is thrown.
	/// </summary>
	/// <param name="t_fileNumber">The file number</param>
	/// <param name="level">A reference to the LevelData object</param>
	static void load(int t_fileNumber, LevelData& level);

};