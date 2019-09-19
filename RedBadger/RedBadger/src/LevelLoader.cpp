#include "LevelLoader.h"



/// <summary>
/// @brief Extracts the int array info for the game tile map.
/// 
/// </summary>
/// <param name="backgroundNode">A YAML node</param>
/// <param name="background">A simple struct to store background related data</param>
////////////////////////////////////////////////////////////
void operator >> (const YAML::Node& mapNode, Int& tileArray)
{
	tileArray.m_int = mapNode.as<int>();
}

/// <summary>
/// @brief Extracts the filename for the game textures.
/// 
/// </summary>
/// <param name="backgroundNode">A YAML node</param>
/// <param name="background">A simple struct to store background related data</param>
////////////////////////////////////////////////////////////
void operator >> (const YAML::Node& texturessNode, Textures& textures)
{
	textures.m_backGroundSoundOptions = texturessNode["SoundOptionsBackGround"]["file"].as<std::string>();
	textures.m_buttonTextureOne = texturessNode["buttonTextureOne"]["file"].as<std::string>();
	textures.m_volumeKnob = texturessNode["volumeKnob"]["file"].as<std::string>();
	textures.m_spriteSheetDirtRoad = texturessNode["dirtRoadSpriteSheet"]["file"].as<std::string>();
	textures.m_spriteSheetVarious = texturessNode["variousAssetsSpriteSheet"]["file"].as<std::string>();
	textures.m_raisedRoad = texturessNode["raisedRoad"]["file"].as<std::string>();
	textures.m_iceRoad = texturessNode["iceRoad"]["file"].as<std::string>();
	textures.m_carOne = texturessNode["carOne"]["file"].as<std::string>();
	textures.m_carTwo = texturessNode["carTwo"]["file"].as<std::string>();
	textures.m_carThree = texturessNode["carThree"]["file"].as<std::string>();
	textures.m_carFour = texturessNode["carFour"]["file"].as<std::string>();
	textures.m_screenCurtain = texturessNode["screenCurtain"]["file"].as<std::string>();
	textures.m_logo = texturessNode["logo"]["file"].as<std::string>();
	textures.m_logoGame = texturessNode["logoGame"]["file"].as<std::string>();
	textures.m_plusOneDrop = texturessNode["plusOneDrop"]["file"].as<std::string>();
	textures.m_miniMap = texturessNode["miniMap"]["file"].as<std::string>();
	textures.m_grass = texturessNode["grass"]["file"].as<std::string>();
	textures.m_snow = texturessNode["snow"]["file"].as<std::string>();
	textures.m_snowTreeTile = texturessNode["snowTreeTile"]["file"].as<std::string>();
	textures.m_snowTree = texturessNode["snowTree"]["file"].as<std::string>();
	textures.m_bigRedTent = texturessNode["bigRedTent"]["file"].as<std::string>();
	textures.m_redTent = texturessNode["redTent"]["file"].as<std::string>();
	textures.m_XboxA = texturessNode["XboxA"]["file"].as<std::string>();
	textures.m_XboxRT = texturessNode["XboxRT"]["file"].as<std::string>();
	textures.m_XboxLT = texturessNode["XboxLT"]["file"].as<std::string>();
	textures.m_XboxLS = texturessNode["XboxLS"]["file"].as<std::string>();

	textures.m_menuWheel = texturessNode["menuWheel"]["file"].as<std::string>();
	textures.m_menuBackground = texturessNode["menuBackground"]["file"].as<std::string>();
	textures.m_border = texturessNode["border"]["file"].as<std::string>();
	textures.m_bridgeWall = texturessNode["bridgeWall"]["file"].as<std::string>();
	textures.m_backCar = texturessNode["backCar"]["file"].as<std::string>();
	textures.m_particle = texturessNode["particle"]["file"].as<std::string>();
	textures.m_upgradeBackGround = texturessNode["upgradeBackGround"]["file"].as<std::string>();
	textures.m_greenBar = texturessNode["greenBar"]["file"].as<std::string>();
	textures.m_orangeBar = texturessNode["orangeBar"]["file"].as<std::string>();
	textures.m_redBar = texturessNode["redBar"]["file"].as<std::string>();


	textures.m_carOneGreen = texturessNode["carOneGreen"]["file"].as<std::string>();
	textures.m_carOneInferno = texturessNode["carOneInferno"]["file"].as<std::string>();
	textures.m_carOneLarge = texturessNode["carOneLarge"]["file"].as<std::string>();
	textures.m_carOneLargeGreen = texturessNode["carOneLargeGreen"]["file"].as<std::string>();
	textures.m_carOneLargeInferno = texturessNode["carOneLargeInferno"]["file"].as<std::string>();

	// Licence Textures
	textures.m_sky = texturessNode["sky"]["file"].as<std::string>();
	textures.m_clouds = texturessNode["clouds"]["file"].as<std::string>();
	textures.m_mountain = texturessNode["mountain"]["file"].as<std::string>();
	textures.m_tree = texturessNode["tree"]["file"].as<std::string>();
	textures.m_road = texturessNode["road"]["file"].as<std::string>();

	textures.m_carSprite1 = texturessNode["carLicence1"]["file"].as<std::string>();
	textures.m_carSprite2 = texturessNode["carLicence2"]["file"].as<std::string>();
	textures.m_carSprite3 = texturessNode["carLicence3"]["file"].as<std::string>();
	textures.m_carSprite4 = texturessNode["carLicence4"]["file"].as<std::string>();

	// Xbox Buttons
	textures.m_buttonA = texturessNode["buttonA"]["file"].as<std::string>();
}

/// <summary>
/// @brief Extracts the filename for the game textures.
/// 
/// </summary>
/// <param name="backgroundNode">A YAML node</param>
/// <param name="background">A simple struct to store background related data</param>
////////////////////////////////////////////////////////////
void operator >> (const YAML::Node& fontsNode, Fonts& fonts)
{
	fonts.m_speed = fontsNode["speed"]["file"].as<std::string>();
	fonts.m_digital = fontsNode["digital"]["file"].as<std::string>();
}

void operator >> (const YAML::Node& soundsNode, Sounds& sounds)
{
	sounds.m_splash = soundsNode["splash"]["file"].as<std::string>();
	sounds.m_raceMusic = soundsNode["race"]["file"].as<std::string>();
	sounds.m_menuMusic = soundsNode["opening"]["file"].as<std::string>();
	sounds.m_fallBehind = soundsNode["fallBehind"]["file"].as<std::string>();
	sounds.m_pullAhead = soundsNode["pullAhead"]["file"].as<std::string>();
	sounds.m_finalLap = soundsNode["finalLap"]["file"].as<std::string>();
	sounds.m_lap = soundsNode["lap"]["file"].as<std::string>();
	sounds.m_wheelTurn = soundsNode["wheelTurn"]["file"].as<std::string>();
	sounds.m_confirm = soundsNode["confirm"]["file"].as<std::string>();
	sounds.m_back = soundsNode["back"]["file"].as<std::string>();
	sounds.m_moveSelection = soundsNode["moveSelection"]["file"].as<std::string>();
	sounds.m_raceFinished = soundsNode["finish"]["file"].as<std::string>();
	sounds.m_raceResultsMusic = soundsNode["result"]["file"].as<std::string>();
}

/// <summary>
/// @brief Top level function that extracts various game data from the YAML data stucture.
/// 
/// Invokes other functions to extract the background etc...
/// </summary>
////////////////////////////////////////////////////////////
void operator >> (const YAML::Node& levelNode, LevelData& level)
{
	levelNode["Textures"] >> level.m_textures;
	levelNode["Fonts"] >> level.m_fonts;
	levelNode["Sounds"] >> level.m_sounds;

	const YAML::Node& mapNode = levelNode["Map"].as<YAML::Node>();
	for (unsigned i = 0; i < mapNode.size(); i++)
	{
		Int temp;
		mapNode[i] >> temp;
		level.m_intContainer.push_back(temp.m_int);
	}
}


void LevelLoader::load(int t_fileNumber, LevelData & level)
{
	// make a stringstream with a name of a yaml file (in this case level1.yaml)
	std::stringstream ss;
	ss << "./ASSETS/YAML/file";
	ss << t_fileNumber;
	ss << ".yaml";

	try
	{
		YAML::Node baseNode = YAML::LoadFile(ss.str());
		if (baseNode.IsNull())
		{
			std::string message("File: " + ss.str() + " not found");
			throw std::exception(message.c_str());
		}
		baseNode >> level;
	}
	catch (YAML::ParserException& e)
	{
		std::string message(e.what());
		message = "YAML Parser Error: " + message;
		throw std::exception(message.c_str());
	}
	catch (std::exception& e)
	{
		std::string message(e.what());
		message = "Unexpected Error: " + message;
		throw std::exception(message.c_str());
	}
	catch (...) {
		std::cout << "Default Exception\n";
	}

}

