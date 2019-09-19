#include "Gameplay.h"
#include "Game.h"

// Contructor and intializer list, all assets ================================================================
Gameplay::Gameplay(ResourceManager & t_gameAssets) :
	m_playerCar(t_gameAssets),
	m_predictionCar(t_gameAssets),
	m_map(t_gameAssets),
	m_destinationCarTexture(t_gameAssets.m_gameTextures["Car One"]),
	m_AiCars{ {t_gameAssets}, {t_gameAssets}, {t_gameAssets} },
	m_bgmBuffer(t_gameAssets.m_gameSounds["Race"]),
	m_voiceBadSFXBuffer(t_gameAssets.m_gameSounds["Fall Behind"]),
	m_voiceGoodSFXBuffer(t_gameAssets.m_gameSounds["Pull Ahead"]),
	m_lapBuffer(t_gameAssets.m_gameSounds["Lap"]),
	m_finalLapBuffer(t_gameAssets.m_gameSounds["Final Lap"]),
	m_raceFinishedBuffer(t_gameAssets.m_gameSounds["Race Finished"]),
	m_raceFinishedMusic(t_gameAssets.m_gameSounds["Race Finished Music"]),
	m_barrierOne(t_gameAssets),
	m_barrierTwo(t_gameAssets),
	renderSprite(t_gameAssets.m_gameTextures["Car One"]),
	m_particleTexture(t_gameAssets.m_gameTextures["Particle"]),
	m_drop(t_gameAssets)
{
	// Haze Shader
	setupShader();

	// Thor Particles
	setupParticleSystem();

	// Set Sounds
	m_bgm.setBuffer(m_bgmBuffer);
	m_bgm.setLoop(true);
	m_bgm.stop();
	m_lapSpeaker.stop();
	m_voiceSFX.stop();
}


Gameplay::~Gameplay()
{
}

void Gameplay::initialize()
{
	// Reinitalize Cars ====================================================================
	m_playerCar.intialize();	
	
	for (int i = 0; i < 3; i++)
	{
		m_AiCars[i].intialize();
	}

	// Game Asset Setup ===========================================================================
	m_gameTilesSats = m_map.getTileInfo();											// This gets the Tile map

	m_destinationCarSprite.setTexture(m_destinationCarTexture);
	m_destinationCarSprite.setOrigin((m_destinationCarSprite.getLocalBounds().width / 2), m_destinationCarSprite.getLocalBounds().height / 2);	// Centered
	m_destinationCarSprite.setColor(sf::Color(255, 255, 255, 100));					// slightly transparent

	m_barrierOne.m_barrierBox.setPosition(256 * 8, 256 * 4);
	m_barrierTwo.m_barrierBox.setPosition(256 * 8 + 216, 256 * 4);

	// Player Car setup ===========================================================================

	setupPlayerStats();

	// AI Car Setup ===============================================================================
	setUpAICheckpoints();
	setupAIStats();

	// Game sound ================================================================================
	m_bgm.stop();
	m_delay = 0;
	m_gameTime = 0;
	m_turn = 0;
}



void Gameplay::update(sf::Time t_deltaTime)
{

	// This it catch an upgrades made, forcing a new intialize=====
	if (Game::m_previousMode == GameMode::MainMenu && m_screenChange == true)
	{
		initialize();
		m_screenChange = false;
	}

	// Particle update ==========================================
	const sf::Time frameTime = m_particleClock.restart();
	checkParticleUpdate();

	// In game drop pick up
	checkDropPickUp();


	// Sound update ==============================================

	if (m_drop.getSprite().getGlobalBounds().intersects(m_playerCar.getSprite().getGlobalBounds()))
	{
		// player collided with drop
		m_drop.nextPosition();
		m_dropCollected = true;
	}
	if (m_raceFinished)
	{
		if (m_bgm.getStatus() != sf::Sound::Playing && m_lapSpeaker.getStatus() != sf::Sound::Playing)
		{
			if (Game::MUSIC_BOOL == true)
			{
				m_bgm.play();
			}
		}
	}
	switch (Game::m_gameMode)
	{
	case GameMode::Gameplay:
		if (m_bgm.getStatus() != sf::Sound::Playing)
		{
			if (Game::MUSIC_BOOL == true)
			{
				m_bgm.play();
			}
		}
		break;

	default:
		m_bgm.stop();
		break;
	}
	
	// Check Friction =============================================
	checkFrictionPlayer(m_playerCar, m_map.getOnScreenTiles());
	for (int k = 0; k < 3; k++)
	{
		checkFrictionAI(m_AiCars[k]);
	}

	// Turn Switch Statement ======================================
	switch (m_playersTurnState)
	{
	case GameplayTurnState::INPUT:
		m_predict = true;

		// Check for inputs
		inputState(t_deltaTime);

		// Pick up info
		if (m_dropCollected)
		{
			m_plusOneBool = true;
			m_dropCollected = false;
		}
		break;
	case GameplayTurnState::UPDATE:
		m_predict = false;
		// Update position and infortmation
		updateState(t_deltaTime);

		// Collision checks
		checkBushCollision();
		checkAIToBushCollions();
		checkAItoAICollisions();
		racerPositions(); 

		// Update Particles
		m_emitter.setParticlePosition(m_newVelocity);
		m_particleVelocity.phi = m_playerCar.getDegrees();
		if (m_playerCar.getSpeed() > 200)					// If fast enough
		{
			m_emitter.setEmissionRate(30);
		}
		else
		{
			m_emitter.setEmissionRate(0);
		}
		m_emitter.setParticleVelocity(thor::Distributions::deflect(m_particleVelocity, 30.f));
		m_particleSystem.update(frameTime);

		break;
	default:
		break;
	}

	// Update HUD after Updating the player car ================================================
	m_hud.lapHUD.setLapSprite(m_playerCar.lap.getLap(), 3);
	m_hud.update(t_deltaTime);
	m_hud.speedometer.setSpeedDisplay(m_playerCar.getSpeed() / 6);

	// Update HUD after Updating the player car =================================================
	m_hud.lapHUD.setLapSprite(m_playerCar.lap.getLap(), 3);
	m_hud.update(t_deltaTime);
	m_hud.speedometer.setSpeedDisplay(m_playerCar.getSpeed() / 6);
	m_hud.lapHUD.setLapSprite(m_playerCar.lap.getLap(), m_playerCar.lap.getMaxLaps());

	// Cuts to 2 decimal places ================================================================
	float rounded = ((int)(m_gameTime * 100 + .5) / 100.0);
	m_hud.setTimeText(rounded);

	// set hud to camera center =================================================================
	m_hud.setPosition(Game::m_screenView.getCenter());

	//MiniMap update ===========================================================================
	for (int i = 0; i < 3; i++)
	{
		m_AIPositions[i] = m_AiCars[i].getPosition();
	}

	// Set View to Car ==========================================================================
	Game::m_screenView.setCenter(m_playerCar.getSprite().getPosition());

	// Update Game items 
	m_miniMap.update(t_deltaTime, m_playerCar.getPosition(), m_AIPositions);
	m_drop.update(t_deltaTime);

	// Find players checkpoint and lap info
	setUpPlayerCheckPoints();
	setAICheckpointsAndLap();

	// Set sprite postion for shader
	renderSprite.setPosition(m_playerCar.getPosition() - sf::Vector2f{ 14,14 });
	m_delay++;
	m_makeCount++;
}

void Gameplay::render(sf::RenderWindow & t_window)
{
	// Setting Haze Shader Info
	shader1.setUniform("time", clock.getElapsedTime().asSeconds());
	shader1.setUniform("distortionFactor", distortionFactor);
	shader1.setUniform("riseFactor", riseFactor);

	// Telling shader what to draw on
	renderTexture.clear();
	renderTexture.draw(m_playerCar.getSprite());
	renderTexture.display();

	t_window.clear(sf::Color(46, 139, 87));	// After drawing shader info

	// If under bridge
	// AI
	for (int i = 0; i < 3; i++)
	{
		if (m_AiCars[i].getIsUnder() == true)
		{
			m_AiCars[i].render(t_window);
		}
	}
	// Player
	if (m_playerCar.getIsUnder() == true)
	{
		m_playerCar.render(t_window);
	}

	m_map.render(t_window, m_playerCar.getSprite().getPosition());	// Map
	t_window.draw(m_barrierOne.m_barrierBox);						// Barriers
	t_window.draw(m_barrierTwo.m_barrierBox);
	m_hud.render(t_window);											// Hud
	//for (int i = 0; i < m_lapCheckpoints.size(); i++)
	//{
	//	m_lapCheckpoints.at(i).render(t_window);					// Checkpoints (remove)
	//}

	// If in input mode
	if (m_playersTurnState == GameplayTurnState::INPUT && !m_raceFinished)	// If in input, draw precition circles
	{
		for (int i = 0; i < m_directionCircles.size(); i++)
		{
			t_window.draw(m_directionCircles.at(i));
		}
		t_window.draw(m_destinationCarSprite);	// and predict car
	}

	// If over bridge
	// AI
	for (int i = 0; i < 3; i++)
	{
		if (m_AiCars[i].getIsUnder() != true)
		{
			m_AiCars[i].render(t_window);
		}
	}
	
	// Player
	if (m_playerCar.getIsUnder() != true)
	{
		m_playerCar.render(t_window);
		if ((Game::m_playerAccerating == true || m_playerCar.getSpeed() > 100) && m_playersTurnState == GameplayTurnState::UPDATE)	// If conditions met
		{
			sf::Sprite sprite = m_playerCar.getBackSprite();
			t_window.draw(sprite, &shader1);				// Draw Haze shader
		}
	}
	m_miniMap.render(t_window);

	m_drop.render(t_window);

	t_window.draw(m_particleSystem);			
}
void Gameplay::handleControllerInput()
{
	if (!m_raceFinished)		// If not finished
	{
		// Speed
		if (m_delay > 20)
		{
			m_playerCar.input();		// check for input

			if (INPUT.PressOnce.Start())
			{
				Game::m_previousMode = GameMode::Gameplay;
				Game::m_gameMode = GameMode::Pause;
				m_bgm.stop();
				Game::playSoundTrack();
				m_screenChange = true;
				m_delay = 0;
			}

			if (INPUT.PressOnce.A())
			{
				m_playersTurnState = GameplayTurnState::UPDATE;		// Confirm input
			}

			// Steering
			if (INPUT.Hold.getController().m_currentState.LeftThumbStick.x > 5)
			{
				int tempInput = (INPUT.Hold.getController().m_currentState.LeftThumbStick.x);
				int lastTemp = tempInput % 4;
				if (lastTemp == 2 || lastTemp == 1)		// Dampening, needs fixing
				{
					tempInput--;
				}
				else
				{
					tempInput++;
				}
				float anotherTemp = tempInput / 100.f;
				m_playerCar.inputDirection(anotherTemp);		// input direction
			}
			else if (INPUT.Hold.getController().m_currentState.LeftThumbStick.x < -5)
			{
				int tempInput = (INPUT.Hold.getController().m_currentState.LeftThumbStick.x);
				int lastTemp = tempInput % 4;
				if (lastTemp == 2 || lastTemp == 1)
				{
					tempInput++;
				}
				else
				{
					tempInput--;
				}
				float anotherTemp = tempInput / 100.f;
				m_playerCar.inputDirection(anotherTemp);
			}
			else
			{
				m_playerCar.inputDirection(0);		// If not significant
			}
			// Leaving Game
			if (INPUT.PressOnce.RB())
			{
				initialize();
				m_screenChange = true;
				Game::m_gameMode = GameMode::MainMenu;
				m_delay = 0;
			}
		}
	}
	else
	{
		m_playersTurnState = GameplayTurnState::UPDATE;
	}
}

// Set up points for the AI to go to
void Gameplay::setUpAICheckpoints()
{
	m_lapCheckpoints.clear();
	for (int i = 0; i < 13; i++)
	{
		CheckpointBox a;
		m_lapCheckpoints.push_back(a);
	}
	m_lapCheckpoints.at(0).setPosition(sf::Vector2f{ 670, 640 });
	m_lapCheckpoints.at(1).setPosition(sf::Vector2f{ 2108, 632 });
	m_lapCheckpoints.at(2).setPosition(sf::Vector2f{ 2140, 1200 });
	m_lapCheckpoints.at(3).setPosition(sf::Vector2f{ 2048, 1832 });
	m_lapCheckpoints.at(4).setPosition(sf::Vector2f{ 1208, 1837 });
	m_lapCheckpoints.at(5).setPosition(sf::Vector2f{ 1084, 1656 });
	m_lapCheckpoints.at(6).setPosition(sf::Vector2f{ 690, 1664 });
	m_lapCheckpoints.at(7).setPosition(sf::Vector2f{ 600, 2100 });
	m_lapCheckpoints.at(8).setPosition(sf::Vector2f{ 1052, 2500 });
	m_lapCheckpoints.at(9).setPosition(sf::Vector2f{ 1202, 2861 });
	m_lapCheckpoints.at(10).setPosition(sf::Vector2f{ 2856, 2856 });
	m_lapCheckpoints.at(11).setPosition(sf::Vector2f{ 2876, 1144 });
	m_lapCheckpoints.at(12).setPosition(sf::Vector2f{ 650, 1069 });

	// Game path of the checkpoints for the AI to follow
	int path[13] = { 0,1,2,3,4,5,6,7,8,9,10, 11, 12};
	for (int i = 0; i < m_lapCheckpoints.size(); i++)
	{
		m_lapCheckpoints.at(i).setSize(sf::Vector2f{ 100, 100 });
		m_lapCheckpoints.at(i).setRotation(0);
		m_lapCheckpoints.at(i).setID(i);
	}

}

// Set up AI lap info and checkpoints
void Gameplay::setAICheckpointsAndLap()
{
	for (int i = 0; i < m_map.numberOfCheckPoints; i++)
	{
		for (int index = 0; index < 3; index++)
		{
			bool collision = Collider::collisionPosSize(
				m_AiCars[index].getPosition(), //pos1
				m_AiCars[index].getSize(),	// size 1
				m_map.m_checkPoints[i].getPosition(),	//pos2
				m_map.m_checkPoints[i].getSize()	//size2
			);

			// if collision returns true
			if (collision && m_map.m_checkPoints[i].isRaceCheckPoint() == true)
			{
				// Check that the id is matched to player id and not equal to 8
				if (m_AiCars[index].getCheckPointID() == i + 100 && m_AiCars[index].getCheckPointID() != 108)
				{
					// Increase lap on passing starting line/first check point
					if (m_AiCars[index].getCheckPointID() == 100)
					{
						m_AiCars[index].lap.increaseLap();

						// FINISH
						if (m_AiCars[index].lap.getLap() > 3)
						{
							// End, Lose.
						}
						m_AiCars[index].setIsPastBridge(false);
					}

					m_AiCars[index].setCheckPointID(m_AiCars[index].getCheckPointID() + 1); // increase ID by 1
					if (m_AiCars[index].getCheckPointID() > 103)
					{
						m_AiCars[index].setIsPastBridge(true);
					}

				}
				else if (m_AiCars[index].getCheckPointID() == i + 100 && m_AiCars[index].getCheckPointID() == 108)
				{
					m_AiCars[index].setCheckPointID(100); // set id to first checkpoint id
				}

			}
		} // end for loop index
	} // end for loop i
}

// Set up player Lap info and checkpoints
void Gameplay::setUpPlayerCheckPoints()
{
	for (int i = 0; i < m_map.numberOfCheckPoints; i++)
	{
		bool collision = Collider::collisionPosSize(
			m_playerCar.getPosition(), //pos1
			m_playerCar.getSize(),	// size 1
			m_map.m_checkPoints[i].getPosition(),	//pos2
			m_map.m_checkPoints[i].getSize()	//size2
		);

		// if collision returns true
		if (collision && m_map.m_checkPoints[i].isRaceCheckPoint() == true)
		{
			// Check that the id is matched to player id and not equal to 8
			if (m_playerCar.getCheckPointID() == i + 100 && m_playerCar.getCheckPointID() != 8 + 100)
			{
				if (!m_raceFinished)
				{
					// Increase lap on passing starting line/first check point
					if (m_playerCar.getCheckPointID() == 100)
					{
						m_playerCar.lap.increaseLap();

						if (m_playerCar.lap.getLap() == 3)
						{
							m_lapSpeaker.setBuffer(m_finalLapBuffer);
							m_bgm.setPitch(1.08f);

						}

						// FINISH
						else if (m_playerCar.lap.getLap() > 3)
						{

							m_lapSpeaker.setBuffer(m_raceFinishedBuffer);
							m_raceFinished = true;
							m_bgm.stop();
							m_bgm.setBuffer(m_raceFinishedMusic);
							m_playerCar.makeTarget(m_lapCheckpoints[1].getPosition(), m_lapCheckpoints[1].getSize());
							m_playerCar.setAsPlayerCar(false);
							m_bgm.setPitch(1);
							// End, win.


							// This is how I worte out to the file before, maybe try alter this to write
							// It reads to one line on the yaml, no indents
							/*if (m_targetsHitByPlayer > m_bestScore)
							{
								m_bestScore = m_targetsHitByPlayer;
								YAML::Node config2 = YAML::LoadFile("./resources/levels/level1.yaml");
								std::string string = std::to_string(m_bestScore);
								config2["BestScore"] = string;
								std::ofstream fout2("./resources/levels/level1.yaml");
								writeYamlOrderedMaps(fout2, config2);
							}*/
						}

						else
						{
							m_lapSpeaker.setBuffer(m_lapBuffer);
						}
						m_lapSpeaker.setLoop(false);

						if (Game::EFFECTS_BOOL == true)
						{
							m_lapSpeaker.play();
						}
						//m_pastBridge = false;
						m_playerCar.setIsPastBridge(false);
					}
				}
				m_playerCar.setCheckPointID(m_playerCar.getCheckPointID() + 1); // increase ID by 1

				// Player has reached checkpoint to cull
				if (m_playerCar.getCheckPointID() > 103)
				{
					m_playerCar.setIsPastBridge(true);
				}

			}
			else if (m_playerCar.getCheckPointID() == i + 100 && m_playerCar.getCheckPointID() == 108)
			{
				m_playerCar.setCheckPointID(100); // set id to first checkpoint id
			}
		}
	}
}

// Check AI  Tile friction
void Gameplay::checkFrictionAI(Car & t_car)
{
	// Get here to avoid call the function over and over
	sf::Sprite carSprite = t_car.getSprite();
	carSprite.setPosition(carSprite.getPosition() - sf::Vector2f{30,28 });

	sf::Vector2f carPos = t_car.getPosition();

	t_car.setLateralFriction(100);			// Reset Frictions
	t_car.setGeneralFriction(0.2);
	bool collide = false;
	for (int i = 0; i < 14; i++)			// Tile Columns
	{
		for (int j = 0; j < 14; j++)		// Tile Rows
		{
			if (std::get<1>(m_gameTilesSats->at(i).at(j)).x > (carPos.x - 600)			// Checks the tiles that are in the screen
				&& std::get<1>(m_gameTilesSats->at(i).at(j)).x < (carPos.x + 600)		// Don't check collision if they aren't
				&& std::get<1>(m_gameTilesSats->at(i).at(j)).y >(carPos.y - 400)
				&& std::get<1>(m_gameTilesSats->at(i).at(j)).y < (carPos.y + 400))
			{
				collide = Collider::collisionPosSize(std::get<1>(m_gameTilesSats->at(i).at(j)), // Position
					sf::Vector2f{ 256, 256 },	// Size
					t_car.getSprite().getPosition(),		// Position
					sf::Vector2f{ 30, 14.5 });		// 1/2 car size Size

				if (collide == true)
				{
					if (std::get<0>(m_gameTilesSats->at(i).at(j)) == 0 || std::get<0>(m_gameTilesSats->at(i).at(j)) == 7)		// Grass
					{
						t_car.setLateralFriction(10);
						t_car.setGeneralFriction(3);
					}
					else if (std::get<0>(m_gameTilesSats->at(i).at(j)) == 10)	// Ice
					{
						t_car.setLateralFriction(5);
						t_car.setGeneralFriction(0);
					}
					if (std::get<0>(m_gameTilesSats->at(i).at(j)) == 8 && t_car.getisPastBridge() == true && m_predict != true)		// Tunnel
					{
						t_car.m_indexAi1 = i;
						t_car.m_indexAi2 = j;
						t_car.setIsunder(true);
					}
				}
			}
		}
	}
	if (t_car.getIsUnder() == true && t_car.m_indexAi1 >= 0 && t_car.m_indexAi2 >= 0 && m_predict != true)
	{
		bool anotherCollide = Collider::collisionPosSize(std::get<1>(m_gameTilesSats->at(t_car.m_indexAi1).at(t_car.m_indexAi2)), // Position
			sf::Vector2f{ 256, 256 },	// Size
			t_car.getSprite().getPosition(),		// Position
			sf::Vector2f{ 30, 14.5 });		// Size
		if (anotherCollide != true)
		{
			t_car.setIsunder(false);
			t_car.m_indexAi1 = -1;
			t_car.m_indexAi2 = -1;
		}
	}
}

// Check player Tile Friction
void Gameplay::checkFrictionPlayer(Car & t_playerCar, std::vector<Tile*> & t_onScreenTiles)
{
	// Get here to avoid call the function over and over
	sf::Sprite carSprite = t_playerCar.getSprite();
	carSprite.setPosition(carSprite.getPosition() - sf::Vector2f{ carSprite.getTexture()->getSize().x / 2.f, carSprite.getTexture()->getSize().y / 2.f });

	sf::Vector2f carPos = t_playerCar.getPosition();

	t_playerCar.setLateralFriction(100);			// Reset Frictions
	t_playerCar.setGeneralFriction(0.2);
	bool collide = false;

	if (t_onScreenTiles.size() > 0)
	{
		for (int i = 0; i < t_onScreenTiles.size(); i++)
		{
			collide = Collider::collisionPosSize(t_onScreenTiles.at(i)->getPosition(), // Position
				sf::Vector2f{ 256, 256 },	// Size
				t_playerCar.getSprite().getPosition() - sf::Vector2f{ 30, 14.5 },		// Position
				sf::Vector2f{ 60, 28 });		// Size

			if (collide == true)
			{
				if (t_onScreenTiles.at(i)->getIndex() == 0 || t_onScreenTiles.at(i)->getIndex() == 7)		// Grass
				{
					t_playerCar.setLateralFriction(10);
					t_playerCar.setGeneralFriction(3);
				}
				else if (t_onScreenTiles.at(i)->getIndex() == 10)	// Ice
				{
					t_playerCar.setLateralFriction(1);
					t_playerCar.setGeneralFriction(0);
				}
				if (t_onScreenTiles.at(i)->getIndex() == 8 && m_playerCar.getisPastBridge() == true && m_predict != true)		// Grass
				{
					m_indexPlayer = i;
					m_playerCar.setIsunder(true);
				}
			}
		}
		if (m_playerCar.getIsUnder() == true && m_indexPlayer >= 0 && m_predict != true)
		{
			bool anotherCollide = Collider::collisionPosSize(t_onScreenTiles.at(m_indexPlayer)->getPosition(), // Position
				sf::Vector2f{ 256, 256 },	// Size
				t_playerCar.getSprite().getPosition(),		// Position
				sf::Vector2f{ 30, 14.5 });		// Size
			if (anotherCollide != true)
			{
				m_playerCar.setIsunder(false);
				m_indexPlayer = -1;
			}
		}
	}
}

// If the player is inputting
void Gameplay::inputState(sf::Time t_deltaTime)
{
	handleControllerInput();	// When they confirm, change to UPDATE

	m_predictionCar = m_playerCar;					// Copy of a Car to use for predictions
	m_destinationUpdates = 0;				// reset
	m_directionCircles.clear();					// Clear Circles

	for (m_destinationUpdates = 0; m_destinationUpdates < 60; m_destinationUpdates++)			// 60 updates to mimic a minute
	{
		if (m_destinationUpdates % 2 == 0)				// Every second update ( For performance reasons )
		{
			checkFrictionPlayer(m_predictionCar, m_map.getOnScreenTiles());
		}
		// Run updates on tempCar to find future destinations
		m_predictionCar.update(t_deltaTime);							// Update Temp Car
		if (m_destinationUpdates % 4 == 0)			// To give a dotted effect, spread the dots
		{
			sf::CircleShape tempCircle;
			tempCircle.setPosition(m_predictionCar.getPosition());
			tempCircle.setRadius(5);
			tempCircle.setOrigin(tempCircle.getRadius(), tempCircle.getRadius());
			tempCircle.setFillColor(sf::Color::White);
			m_directionCircles.push_back(tempCircle);					// add a circle along the track for the HUD input view for the player
		}
	}
	m_destinationCarSprite.setPosition(m_predictionCar.getPosition());				// Put the Car at the end for the Player to see final position
	m_destinationCarSprite.setRotation(m_predictionCar.getSprite().getRotation());		// Put the rotation for the player too
}

// If the Game is updating
void Gameplay::updateState(sf::Time t_deltaTime)
{
	int path[13] = { 2,3,4,5,6,7,8,9,10,11,12, 0, 1};
	
	m_turn += t_deltaTime.asSeconds();
	m_gameTime += t_deltaTime.asSeconds();

	// only if race has not yet been finished
	if (!m_raceFinished)
	{
		if (m_turn > 1)		// 1 second
		{
			m_turn = 0;
			m_playersTurnState = GameplayTurnState::INPUT;
			m_playerCar.setSpeed(m_playerCar.getSpeed() * 3 + 100);		// Setting max speed reachable from current		
			if (m_plusOneBool == true)
			{
				m_plusOneBool = false;
			}
		}
	}
	else
	{
		if (m_playerCar.reachedTarget() == true)		// If the AI reaches their target checkpoint
		{
			if (m_playerCar.getWayPointIndex() == 13)		// Reset track when reach the end of the checkpoints
			{
				m_playerCar.setWayPointIndex(0);
			}
			m_playerCar.makeTarget(m_lapCheckpoints[path[m_playerCar.getWayPointIndex()]].getPosition(), m_lapCheckpoints[path[m_playerCar.getWayPointIndex()] ].getSize());	// Next one
			m_playerCar.setWayPointIndex(m_playerCar.getWayPointIndex() + 1);		// Move the index (needs to be adjusted)
		}
		m_playerCar.findTarget();									// Get its new target
	}

	// Update Car =============================================
	m_playerCar.update(t_deltaTime);
	m_emitter.setParticlePosition(thor::Distributions::circle(m_playerCar.getPosition(), 50));   // Emit particles in given circle
	// Update AI ==============================================
	for (int i = 0; i < 3; i++)
	{
		if (m_AiCars[i].reachedTarget() == true)		// If the AI reaches their target checkpoint
		{
				m_makeCount = 0;
				if (m_AiCars[i].getWayPointIndex() == 13)		// Reset track when reach the end of the checkpoints
				{
					m_AiCars[i].setWayPointIndex(0);
				}
				m_AiCars[i].makeTarget(m_lapCheckpoints[path[m_AiCars[i].getWayPointIndex()]].getPosition(), m_lapCheckpoints[path[m_AiCars[i].getWayPointIndex()]].getSize());	// Next one
				m_AiCars[i].setWayPointIndex(m_AiCars[i].getWayPointIndex() + 1);		
		}
		m_AiCars[i].findTarget();
		if (!m_plusOneBool)
		{
			m_AiCars[i].update(t_deltaTime);
		}
	} // end for loop AI
}

// Player info at intialization
void Gameplay::setupPlayerStats()
{
	m_playerCar.setAsPlayerCar(true);
	m_playerCar.setIsPastBridge(false);
	m_playerCar.setIsunder(false);
	m_playerCar.addID(1);						
	m_playerCar.setPosition(sf::Vector2f{ 932.f, 700.f });
	m_playerCar.lap.setLap(1);
	m_playerCar.setCheckPointID(101);
	m_playerCar.setUniqueID(0);
	m_playerCar.setRotation(0);
	m_playerCar.setSteering(2);
	switch (Game::BODY_TYPE)
	{
	case 0:
		m_playerCar.setSprite(0);
		m_predictionCar.setSprite(0);
		break;
	case 1:
		m_playerCar.setSprite(1);
		m_predictionCar.setSprite(1);
		break;
	case 2:
		m_playerCar.setSprite(2);
		m_predictionCar.setSprite(2);
		break;
	default:
		m_playerCar.setSprite(0);
		m_predictionCar.setSprite(0);
		break;
	}
	switch (Game::ENGINE_TYPE)
	{
	case 0:
		m_playerCar.setAcceleration(200);
		break;
	case 1:
		m_playerCar.setAcceleration(300);
		break;
	case 2:
		m_playerCar.setAcceleration(400);
		break;
	default:
		break;
	}
	switch (Game::NITRO_TYPE)
	{
	case 0:
		m_playerCar.setMaxSpeed(500);
		break;
	case 1:
		m_playerCar.setMaxSpeed(600);
		break;
	case 2:
		m_playerCar.setMaxSpeed(700);
		break;
	default:
		break;
	}

	switch (Game::WHEEL_TYPE)
	{
	case 0:
		m_playerCar.setTurnAmount(1);
		break;
	case 1:
		m_playerCar.setTurnAmount(2);
		break;
	case 2:
		m_playerCar.setTurnAmount(3);
		break;
	default:
		break;
	}
}

// AI info at intialization
void Gameplay::setupAIStats()
{
	m_AiCars[0].setPosition(sf::Vector2f{ 932.f, 620.f });
	m_AiCars[0].makeTarget(m_lapCheckpoints[1].getPosition(), m_lapCheckpoints[1].getSize());		// Original aimer point for AI
	m_AiCars[0].setCheckPointID(101);
	m_AiCars[0].setWayPointIndex(1);
	m_AiCars[0].lap.setLap(1);
	m_AiCars[0].setUniqueID(1);
	m_AiCars[0].setMaxSpeed(700);
	m_AiCars[0].setAcceleration(300);
	m_AiCars[0].setSteering(2);
	m_AiCars[0].setRotation(0);
	m_AiCars[0].setSprite(3);

	m_AiCars[1].setPosition(sf::Vector2f{ 932.f, 660.f });
	m_AiCars[1].makeTarget(m_lapCheckpoints[1].getPosition(), m_lapCheckpoints[1].getSize());
	m_AiCars[1].setCheckPointID(101);
	m_AiCars[1].lap.setLap(1);
	m_AiCars[1].setWayPointIndex(1);
	m_AiCars[1].setUniqueID(2);
	m_AiCars[1].setMaxSpeed(500);
	m_AiCars[1].setAcceleration(700);
	m_AiCars[1].setSteering(3);
	m_AiCars[1].setRotation(0);
	m_AiCars[1].setSprite(4);

	m_AiCars[2].setPosition(sf::Vector2f{ 932.f, 580.f });
	m_AiCars[2].makeTarget(m_lapCheckpoints[1].getPosition(), m_lapCheckpoints[1].getSize());
	m_AiCars[2].setCheckPointID(101);
	m_AiCars[2].setWayPointIndex(1);
	m_AiCars[2].lap.setLap(1);
	m_AiCars[2].setUniqueID(3);
	m_AiCars[2].setMaxSpeed(650);
	m_AiCars[2].setAcceleration(500);
	m_AiCars[2].setSteering(4);
	m_AiCars[2].setRotation(0);
	m_AiCars[2].setSprite(5);

}

// Player to bush collisions
void Gameplay::checkBushCollision()
{
	bool collide{ false };
	std::vector<std::pair<sf::Vector2f, sf::Vector2f>> *tempmap = &m_map.getBushes();
	for (int i = 0; i < tempmap->size(); i++)
	{
		collide = Collider::collisionPosSize(tempmap->at(i).first - sf::Vector2f{ 43,43 }, // Position
			tempmap->at(i).second,	// Size
			m_playerCar.getSprite().getPosition(),		// Position
			sf::Vector2f{ 20,9 });		// Size
		if (collide == true)
		{
			std::vector<CheckpointBox> checks = m_map.getCheckpoints();
			for (int i = 0; i < 9; i++)
			{
				int t = checks.at(i).getID() + 1;
				if (m_playerCar.getCheckPointID() == 100)		// Last checkpoint/Reset
				{
					t = 100;
				}
				if ((m_playerCar.getCheckPointID()) == t)
				{
					m_playerCar.stopSpeed();				// Stop the car moving
					m_playerCar.setPosition(checks.at(i).getPosition() + sf::Vector2f{ 200,200 });	// Respawn
					if (checks.at(i).getDirection() == 1)			// 1 - 4 are directions the map is facing
					{
						m_playerCar.setRotation(0);
					}
					else if (checks.at(i).getDirection() == 2)
					{
						m_playerCar.setRotation(90);
					}
					else if (checks.at(i).getDirection() == 3)
					{
						m_playerCar.setRotation(180);
					}
					else if (checks.at(i).getDirection() == 4)
					{
						m_playerCar.setRotation(270);
					}
					m_playersTurnState = GameplayTurnState::INPUT;		// TO input mode
					m_particleSystem.clearParticles();
					m_turn = 0.f;
				}
			}

		}
	}
}

// AI to bush collisions
void Gameplay::checkAIToBushCollions()
{
	bool collide{ false };
	std::vector<std::pair<sf::Vector2f, sf::Vector2f>> *tempmap = &m_map.getFullBushes();

	for (int j = 0; j < 3; j++)
	{
		for (int i = 0; i < tempmap->size(); i++)
		{
			collide = Collider::collisionPosSize(tempmap->at(i).first - sf::Vector2f{ 43,43 }, // Position
				tempmap->at(i).second,	// Size
				m_AiCars[j].getSprite().getPosition(),		// Position
				sf::Vector2f{ 30,14 });		// Size

			if (collide == true)
			{
				std::vector<CheckpointBox> checks = m_map.getCheckpoints();
				for (int i = 0; i < 9; i++)
				{
					int t = checks.at(i).getID() + 1;
					if (m_AiCars[j].getCheckPointID() == 100)		// Last checkpoint/Reset
					{
						t = 100;
					}
					if ((m_AiCars[j].getCheckPointID()) == t)
					{
						//m_AiCars[j].intialize();
						m_AiCars[j].stopSpeed();
						m_AiCars[j].setPosition(checks.at(i).getPosition() + sf::Vector2f{ 200,200 }); //Respawn
						if (checks.at(i).getDirection() == 1)						// Map directions
						{
							m_AiCars[j].setRotation(0);
						}
						else if (checks.at(i).getDirection() == 2)
						{
							m_AiCars[j].setRotation(90);
						}
						else if (checks.at(i).getDirection() == 3)
						{
							m_AiCars[j].setRotation(180);
						}
						else if (checks.at(i).getDirection() == 4)
						{
							m_AiCars[j].setRotation(270);
						}
					}
				}

			}
		}
	}
}

// Checks AI to AI collisions and AI to Player
void Gameplay::checkAItoAICollisions()
{
	bool collide{ false };

	for (int i = 0; i < 3; i++)
	{
		if (i < 2)		// 0-1, 0-2, 1-2 
		{
			collide = m_AiCars[i].getSprite().getGlobalBounds().intersects(m_AiCars[i + 1].getSprite().getGlobalBounds());
			if (collide == true)
			{
				runAvoidance(m_AiCars[i], m_AiCars[i + 1]);
				// AI avoidonce
			}
		}
		if (i < 1)		// 0-1, 0-2, 1-2 
		{
			collide = m_AiCars[i].getSprite().getGlobalBounds().intersects(m_AiCars[i + 2].getSprite().getGlobalBounds());
			if (collide == true)
			{
				runAvoidance(m_AiCars[i], m_AiCars[i + 2]);
				// AI avoidonce
			}
		}
	}
	for(int i = 0; i < 3; i++)
	{
		collide = m_AiCars[i].getSprite().getGlobalBounds().intersects(m_playerCar.getSprite().getGlobalBounds());
		if (collide == true)
		{
			runAvoidance(m_playerCar, m_AiCars[i]);
		}
	}
	
}

// Check the particle is updates
void Gameplay::checkParticleUpdate()
{
	float temp = m_playerCar.getDegrees();
	double radians = temp * 3.14 / 180;		// Into Radians
	float newCos = std::cos(radians);					// Cos, Sin
	float newSin = std::sin(radians);

	float newX = newCos;				// Rotate the vector by the rotationFactor
	float newY = newSin;
	MyVector3 addedDir = { newCos, newSin, 0 };					// New Direction
	addedDir.normalise();							// In unit form
	addedDir = addedDir * 30;
	m_newVelocity = m_playerCar.getPosition() - sf::Vector2f{ (float)addedDir.x, (float)addedDir.y };
}

// Checks pick ups
void Gameplay::checkDropPickUp()
{
	if (m_drop.getSprite().getGlobalBounds().intersects(m_playerCar.getSprite().getGlobalBounds()))
	{
		// player collided with drop
		m_drop.nextPosition();
		m_dropCollected = true;
	}
	if (m_raceFinished)
	{
		if (m_bgm.getStatus() != sf::Sound::Playing && m_lapSpeaker.getStatus() != sf::Sound::Playing)
		{
			m_bgm.play();
		}
	}
}

// deciding once carss collide, which way to avoid each other
void Gameplay::runAvoidance(Car & t_car1, Car & t_car2)
{
	float degrees;
	float slideDirectionV = 0;
	sf::Vector2f target = t_car1.getTarget() - t_car1.getPosition();
	slideDirectionV = atan2(target.y, target.x);		// For this I get inverse Tan y/x

	float degrees2;
	float slideDirectionV2 = 0;
	sf::Vector2f target2 = t_car2.getTarget() - t_car2.getPosition();
	slideDirectionV2 = atan2(target2.y, target2.x);		// For this I get inverse Tan y/x

	degrees = slideDirectionV * (180 / 3.1415926535897932384);     // To Degrees
	degrees2 = slideDirectionV2 * (180 / 3.1415926535897932384);
	while (degrees < 0)
	{
		degrees += 360;
	}
	while (degrees > 360)
	{
		degrees -= 360;
	}
	while (degrees2 < 0)
	{
		degrees2 += 360;
	}
	while (degrees2 > 360)
	{
		degrees2 -= 360;
	}
	float difference = degrees - degrees2;

	if (difference < -180.0f)
		difference += 360.0f;
	if (difference > 180.0f)
		difference -= 360.0f;

	if (difference > 0.0f)
	{
		//std::cout << "Left To Right" << std::endl;
		// Car1 left 
		//// Car2 Right
		if (t_car1.getIsPlayerCar() != true)
		{
			t_car1.runAvoidence(2);
		}
		t_car2.runAvoidence(1);
	}
	if (difference < 0.0f)
	{
		//std::cout << "Right to Left" << std::endl;
		// Car1 Right
		//// Car2 LEft
		if (t_car1.getIsPlayerCar() != true)
		{
			t_car1.runAvoidence(1);
		}
		t_car2.runAvoidence(2);
	}
}

void Gameplay::writeYamlOrderedMaps(std::ostream & out, const YAML::Node & node)
{
	YAML::Emitter emitter;
	writeNode(node, emitter);
	out << emitter.c_str() << std::endl;
}

void Gameplay::writeNode(const YAML::Node & node, YAML::Emitter & emitter)
{
	switch (node.Type())
	{
	case YAML::NodeType::Sequence:
	{
		emitter << YAML::BeginSeq;
		for (size_t i = 0; i < node.size(); i++)
		{
			writeNode(node[i], emitter);
		}
		emitter << YAML::EndSeq;
		break;
	}
	case YAML::NodeType::Map:
	{
		emitter << YAML::BeginMap;

		// First collect all the keys
		std::vector<std::string> keys(node.size());
		int key_it = 0;
		for (YAML::const_iterator it = node.begin(); it != node.end(); ++it)
		{
			keys[key_it++] = it->first.as<std::string>();
		}

		// Then sort them
		std::sort(keys.begin(), keys.end());

		// Then emit all the entries in sorted order.
		for (size_t i = 0; i < keys.size(); i++)
		{
			emitter << YAML::Key;
			emitter << keys[i];
			emitter << YAML::Value;
			writeNode(node[keys[i]], emitter);
		}
		emitter << YAML::EndMap;
		break;
	}
	default:
		emitter << node;
		break;
	}
}

// Finding out player positions
void Gameplay::racerPositions()
{
	Car cars[4] = { m_playerCar,m_AiCars[0],m_AiCars[1],m_AiCars[2] };
	Car temp_carPosition = m_playerCar;
	bool sorted = false;
	int playerPreviousPosition = m_playerCar.racePositon.getCurrentPosition();

	while (!sorted)
	{
		for (int i = 0; i < 4; i++)
		{
			// OUT OF RANGE CHECK
			if (i + 1 != 4)
			{
				// Compare laps
				if (cars[i].lap.getLap() < cars[i + 1].lap.getLap())
				{

					// Swap places
					temp_carPosition = cars[i];
					cars[i] = cars[i + 1];
					cars[i + 1] = temp_carPosition;
					break; // escape for loop


				} // end compare lap less than

				// if on the same lap
				else if (cars[i].lap.getLap() == cars[i + 1].lap.getLap())
				{
					// if the checkpoint id is smaller than the other car checkpoint id
					if (cars[i].getCheckPointID() < cars[i + 1].getCheckPointID())
					{
						// if at position 0 no need for swapping positions
						if (cars[i].getCheckPointID() != 100)
						{
							// Swap places
							temp_carPosition = cars[i];
							cars[i] = cars[i + 1];
							cars[i + 1] = temp_carPosition;
							break; // escape for loop
						}
					} // end checkPoint ID comparison less than

					// If Check Points are the same
					else if (cars[i].getCheckPointID() == cars[i + 1].getCheckPointID())
					{
						int checkPointID = cars[i].getCheckPointID();
						float carDistanceOne = Transform::Distance(cars[i].getPosition(), getCheckPointByID(checkPointID).getPosition());
						float carDistanceTwo = Transform::Distance(cars[i + 1].getPosition(), getCheckPointByID(checkPointID).getPosition());

						// compare distance from checkpoint
						if (carDistanceOne > carDistanceTwo)
						{
							// Swap places
							temp_carPosition = cars[i];
							cars[i] = cars[i + 1];
							cars[i + 1] = temp_carPosition;
							break; // escape for loop
						}// END DISTANCE COMPARISION

					}// END SAME CHECK POINT COMPARISON


				} // END SAME LAP COMPARISON



			} // END OUT OF RANGE CHECK

			// MADE IT TO END WITHOUT ANY SWAPS
			else
			{
				sorted = true; // we can escape from while loop
			}

		} // END FOR LOOP
	}// END WHILE NOT SORTED

	//Set car race positions
	for (int i = 0; i < 4; i++)
	{
		cars[i].racePositon.setCurrentPosition(i + 1);
	}

	// assign positions
	for (int i = 0; i < 4; i++)
	{
		if (cars[i].getUniqueID() == m_playerCar.getUniqueID())
		{
			m_playerCar.racePositon.setCurrentPosition(cars[i].racePositon.getCurrentPosition());
		}
		else if (cars[i].getUniqueID() == m_AiCars[0].getUniqueID())
		{
			m_AiCars[0].racePositon.setCurrentPosition(cars[i].racePositon.getCurrentPosition());
		}
		else if (cars[i].getUniqueID() == m_AiCars[1].getUniqueID())
		{
			m_AiCars[1].racePositon.setCurrentPosition(cars[i].racePositon.getCurrentPosition());
		}
		else if (cars[i].getUniqueID() == m_AiCars[2].getUniqueID())
		{
			m_AiCars[2].racePositon.setCurrentPosition(cars[i].racePositon.getCurrentPosition());
		}
	} // END FOR LOOP



	if (m_voiceSFX.getStatus() != sf::Sound::Playing)
	{
		if (playerPreviousPosition < m_playerCar.racePositon.getCurrentPosition())
		{
			m_voiceSFX.setBuffer(m_voiceBadSFXBuffer);
			m_voiceSFX.setLoop(false);
			if (Game::EFFECTS_BOOL == true)
			{
				m_voiceSFX.play();
			}
		}
		else if (playerPreviousPosition > m_playerCar.racePositon.getCurrentPosition())
		{
			m_voiceSFX.setBuffer(m_voiceGoodSFXBuffer);
			m_voiceSFX.setLoop(false);
			if (Game::EFFECTS_BOOL == true)
			{
				m_voiceSFX.play();
			}
		}
	}
} // END RACER POSIITIONS

// Loading Shader
void Gameplay::setupShader()
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

	const char* fs_src = "#version 130\n"

		"uniform sampler2D currentTexture;" // Our render texture
		"uniform sampler2D distortionMapTexture;" // Our heat distortion map texture

		"uniform float time;" // Time used to scroll the distortion map
		"uniform float distortionFactor;" // Factor used to control severity of the effect
		"uniform float riseFactor;" // Factor used to control how fast air rises

		"void main()"
		"{"
		"vec2 distortionMapCoordinate = gl_TexCoord[0].st;"

		// We use the time value to scroll our distortion texture upwards
		// Since we enabled texture repeating, OpenGL takes care of
		// coordinates that lie outside of [0, 1] by discarding
		// the integer part and keeping the fractional part
		// Basically performing a "floating point modulo 1"
		// 1.1 = 0.1, 2.4 = 0.4, 10.3 = 0.3 etc.
		"distortionMapCoordinate.t -= time * riseFactor;"

		"vec4 distortionMapValue = texture2D(distortionMapTexture, distortionMapCoordinate);"

		// The values are normalized by OpenGL to lie in the range [0, 1]
		// We want negative offsets too, so we subtract 0.5 and multiply by 2
		// We end up with values in the range [-1, 1]
		"vec2 distortionPositionOffset = distortionMapValue.xy;"
		"distortionPositionOffset -= vec2(0.5f, 0.5f);"
		"distortionPositionOffset *= 5.f;"

		// The factor scales the offset and thus controls the severity
		"distortionPositionOffset *= distortionFactor;"

		// The latter 2 channels of the texture are unused... be creative
		"vec2 distortionUnused = distortionMapValue.zw;"

		// Since we all know that hot air rises and cools,
		// the effect loses its severity the higher up we get
		// We use the t (a.k.a. y) texture coordinate of the original texture
		// to tell us how "high up" we are and damp accordingly
		// Remember, OpenGL 0 is at the bottom
		"distortionPositionOffset *= (1.f - gl_TexCoord[0].t);"

		"vec2 distortedTextureCoordinate = gl_TexCoord[0].st + distortionPositionOffset;"

		"gl_FragColor = gl_Color * texture2D(currentTexture, distortedTextureCoordinate);"
		"}";
	if (!shader1.loadFromMemory(vs_src, sf::Shader::Vertex))
	{
		// error...
	}

	// load only the fragment shader
	if (!shader1.loadFromMemory(fs_src, sf::Shader::Fragment))
	{
		// error...
	}
	/*if (!shader1.loadFromFile(vs_src, fs_src))
	{
		sf::err() << "Failed to load shader, exiting..." << std::endl;
	}*/
	shader1.setUniform("currentTexture", sf::Shader::CurrentTexture);
	shader1.setUniform("distortionMapTexture", distortionMap);
}

// Setting up the particles
void Gameplay::setupParticleSystem()
{
	m_emitter.setEmissionRate(30);
	m_emitter.setParticleLifetime(sf::seconds(1.f));

	m_particleSystem.setTexture(m_particleTexture);
	m_particleSystem.addEmitter(thor::refEmitter(m_emitter));

	thor::ColorGradient gradient;
	gradient[0.f] = sf::Color(139, 69, 19);
	gradient[0.5f] = sf::Color(139, 69, 19);
	gradient[1.f] = sf::Color(139, 69, 19);

	// Create color and fade in/out animations
	thor::ColorAnimation colorizer(gradient);
	thor::FadeAnimation fader(0.1f, 0.1f);

	// Add particle affectors
	m_particleSystem.addAffector(thor::AnimationAffector(colorizer));
	m_particleSystem.addAffector(thor::AnimationAffector(fader));
	m_particleSystem.addAffector(thor::TorqueAffector(200.f));
	//system.addAffector(thor::ForceAffector(sf::Vector2f(0.f, 100.f)));

	m_particleVelocity = thor::PolarVector2f(-200.f, 0.f);
}

// Checkpoint Squares
sf::RectangleShape Gameplay::getCheckPointByID(int t_ID)
{
	for (int i = 0; i < m_map.numberOfCheckPoints; i++)
	{
		if (m_map.m_checkPoints[i].getID() == t_ID)
		{
			return m_map.m_checkPoints[i].getShape();
		}
	}
	//std::cout << "Error cannot find Check point with matching ID" << std::endl;
	return sf::RectangleShape();
}
