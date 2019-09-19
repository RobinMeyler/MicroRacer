#pragma once

#include <iostream>
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include "GUIGlobals.h"
#include "GUI.h"
#include "Label.h"
#include <ctime>
#include "Xbox360Controller.h"
#include "TileMap.h"

#include "Thor/Resources.hpp"
#include "Thor/Particles.hpp"
#include "Thor/Animations.hpp"
#include "Thor/Vectors/PolarVector2.hpp"
#include "Thor/Math/Distributions.hpp"

#include "Thor/Math.hpp"
#include "ResourceManager.h"
#include "Car.h"
#include "HUD.h"
#include "Barrier.h"
#include "CheckpointBox.h"
#include "MiniMap.h"
#include "PlusOneDrop.h"

class Gameplay
{
public:
	Gameplay(ResourceManager & t_gameAssets);
	~Gameplay();

	// General ========================================================================
	void initialize();
	void update(sf::Time t_deltaTime);
	void render(sf::RenderWindow & t_window);
	void handleControllerInput();

	// Game setup =======================================================================
	void setUpPlayerCheckPoints();
	void setUpAICheckpoints();
	void setupPlayerStats();
	void setupAIStats();
	void setupShader();
	void setupParticleSystem();

	// Updates ==========================================================================
	void inputState(sf::Time t_deltaTime);
	void updateState(sf::Time t_deltaTime);

	// Game Checks ======================================================================
	void checkFrictionAI(Car & t_car);
	void checkFrictionPlayer(Car & t_playerCar, std::vector<Tile*> & t_onScreenTiles);	// different functions for player and AI friction because players needs to be more effi
	void checkBushCollision();
	void checkAIToBushCollions();
	void checkAItoAICollisions();
	void checkParticleUpdate();
	void checkDropPickUp();

	// Game Actions ======================================================================
	sf::RectangleShape getCheckPointByID(int t_ID);
	void setAICheckpointsAndLap();
	void racerPositions();
	void runAvoidance(Car & t_car1, Car & t_car2);

	void writeYamlOrderedMaps(std::ostream& out, const YAML::Node& node);
	void writeNode(const YAML::Node& node, YAML::Emitter& emitter);

private:
	// Variables used for the Haze shader on the back fo the car ====================================
	sf::Sprite renderSprite;
	sf::RenderTexture renderTexture;
	sf::Texture distortionMap;
	sf::Shader shader1;
	float riseFactor = 1.25;
	float distortionFactor = 0.13;
	sf::Clock clock;

	// Variables used for the Mud particle effect =================================================
	sf::Clock m_particleClock;
	sf::Texture m_particleTexture;
	thor::ParticleSystem m_particleSystem;
	thor::UniversalEmitter m_emitter;
	thor::PolarVector2f m_particleVelocity;

	// Game pick up, get a free second variables ==================================================
	PlusOneDrop m_drop;
	bool m_dropCollected{ false };				// two bools are needed for this to work properly
	bool m_plusOneBool{false};
	bool m_screenChange{ true };

	// Bridge barrier sides ==========================================================
	Barrier m_barrierOne;
	Barrier m_barrierTwo;

	// Game Cars ====================================================================
	Car m_playerCar;
	Car m_AiCars[3];
	Car m_predictionCar;

	// Map Items ====================================================================
	TileMap m_map;
	MiniMap m_miniMap;
	HUD m_hud;

	GameplayTurnState m_playersTurnState{ GameplayTurnState::INPUT };

	// Variables and Collections of Variables ====================================================
	std::vector<sf::CircleShape> m_directionCircles;
	std::vector<std::vector<std::tuple<int, sf::Vector2f, sf::Sprite*>>> *m_gameTilesSats;
	std::vector<CheckpointBox> m_lapCheckpoints;

	sf::Texture m_destinationCarTexture;
	sf::Sprite m_destinationCarSprite;

	sf::Vector2f m_AIPositions[3];				// ai positions needed for mini map
	sf::Vector2f m_newVelocity;

	const static int s_numberOfCheckPoints = 9;		// Amount of checkpoints

	float m_turn;						// Counts to 1 second then changes state
	float m_gameTime{ 0.f };			// Overall game time
	
	int m_destinationUpdates{ 0 };		// Counts to 60 and repeats
	int m_indexPlayer{ -1 };			// Helps the Player know if they are under the bridge still
	int m_delay{ 0 };
	int m_makeCount{ 10 };

	bool m_predict{ false };			// If in predicting state or not
	bool m_raceFinished{ false };		// Race completed or not

	// Sound ==============================================================================
	sf::Sound m_bgm;
	sf::Sound m_voiceSFX;
	sf::Sound m_lapSpeaker;
	sf::SoundBuffer m_bgmBuffer;
	sf::SoundBuffer m_voiceBadSFXBuffer;
	sf::SoundBuffer m_voiceGoodSFXBuffer;
	sf::SoundBuffer m_finalLapBuffer;
	sf::SoundBuffer m_lapBuffer;
	sf::SoundBuffer m_raceFinishedBuffer;
	sf::SoundBuffer m_raceFinishedMusic;
};