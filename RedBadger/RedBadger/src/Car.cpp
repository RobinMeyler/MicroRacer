#include "Car.h"
#include "Game.h"
#include <ctime>
#include<iostream>

Car::Car()
{
	intialize();
}

Car::Car(ResourceManager & t_gameAssets) :
	assetPtr(&t_gameAssets)
{
	m_backOfCarSprite.setTexture(t_gameAssets.m_gameTextures["Back Car"]);
	m_backOfCarSprite.setOrigin(7, 14);
	intialize();
	srand(time(nullptr));
}

Car::~Car()
{
}

bool Car::getIsUnder()
{
	return m_under;
}

bool Car::getisPastBridge()
{
	return m_pastBridge;
}

void Car::setIsunder(bool t_isUnder)
{
	m_under = t_isUnder;
}

void Car::setIsPastBridge(bool t_isPast)
{
	m_pastBridge = t_isPast;
}

void Car::setSprite(int t_spriteIndex)
{
	switch (t_spriteIndex)
	{
	case 0:
		m_carSprite.setTexture(assetPtr->m_gameTextures["Car One"]);
		break;
	case 1:
		m_carSprite.setTexture(assetPtr->m_gameTextures["Car One Green"]);
		break;
	case 2:
		m_carSprite.setTexture(assetPtr->m_gameTextures["Car One Inferno"]);
		break;
	case 3:
		m_carSprite.setTexture(assetPtr->m_gameTextures["Car Two"]);
		break;
	case 4:
		m_carSprite.setTexture(assetPtr->m_gameTextures["Car Three"]);
		break;
	case 5:
		m_carSprite.setTexture(assetPtr->m_gameTextures["Car Four"]);
		break;
	default:
		m_carSprite.setTexture(assetPtr->m_gameTextures["Car One"]);
		break;
	}
}

void Car::setTurnAmount(float t_turnAmount)
{
	m_directionMove = t_turnAmount;
}

void Car::setMaxSpeed(float t_speed)
{
	MAX_SPEED = t_speed;
}

void Car::setAcceleration(float t_accel)
{
	m_accelerationValue = t_accel;
}

void Car::setSteering(float t_steering)
{
	m_enemySteering = t_steering;
}

void Car::intialize()
{
	m_carSprite.setOrigin(30, 14);	// -10 becuase the centre of gravity in a drift feels back weighted
	m_spriteSize = (sf::Vector2f{ 60,28 });
	m_reachedTarget = false;
	m_pastBridge = false;
	m_under = false;
	// Car 2.0 -----
	// Setups =======================
	m_positionVec = { 100, 400,0 };
	m_carSprite.setPosition(m_positionVec);
	m_acceleration = { 0,0,0 };
	m_VelocityVec = { 0,0,0 };
	m_directionVec = { 10,0,0 };		// Avoid random stuff when at 0,0,0
	temp = m_directionVec;				// Change this var name ---
	m_directionVec.normalise();
	m_steeringAngle = 1;				// Not 0 because of 0 issues
	m_difference = 0;
	// Speed =========================
	m_accelerationValue = 400;			// Factor it accelerates at.

	// Steering ======================
	m_directionMove = 2;				// Turn Amount.
	m_count = 41;
	// Frictions =====================
	laterFrictionFactor = 100;			// 1 = Lots of drift, 100 = no drift.
	generalFrictionFactor = 0.2;		// Bigger = more friction
}

void Car::update(sf::Time t_detlaTime)
{
	// Car 2.0 ===========================================================================================================================================================
	if (rightAvoid == true)
	{
		avoidTimerRight += t_detlaTime.asSeconds();
	}
	if (avoidTimerRight > 0.05)
	{
		avoidTimerRight = 0;
		rightAvoid = false;
		firstTime = false;
		m_target = m_targetStoreWhenAvoiding;
	}
	if (leftAvoid == true)
	{
		avoidTimerLeft += t_detlaTime.asSeconds();
	}
	if (avoidTimerLeft > 0.05)
	{
		avoidTimerLeft = 0;
		leftAvoid = false;
		firstTime = false;
		m_target = m_targetStoreWhenAvoiding;
	}

	steering();

	// Acceleration ===========================================================================================
	if (m_isPlayerCar == true)
	{
		speedCalculator();
	}
	else
	{
		AIinput();
	}
	
	// Friction ===============================================================================================
	getDiffernceVelDir();

	friction();
	// If it is not moving, dont slow it

	// =====================================================================================================
	// Stopping the car if it gets too low and is not accelerating
	
	updatePosition(t_detlaTime);
	m_count++;
}

void Car::setPosition(sf::Vector2f t_position)
{
	m_positionVec = t_position;
	m_carSprite.setPosition(m_positionVec);
	m_backOfCarSprite.setPosition(m_positionVec - sf::Vector2f{ 34,0 });
}

void Car::render(sf::RenderWindow & t_window)
{
	t_window.draw(m_carSprite);
}

void Car::addID(int t_ID)
{
	m_idPassed = t_ID;
}

bool Car::getIsPlayerCar()
{
	return m_isPlayerCar;
}

short Car::getUniqueID()
{
	return m_uniqueCarID;
}

void Car::setUniqueID(short t_ID)
{
	m_uniqueCarID = t_ID;
}

int Car::getID()
{
	return m_idPassed;
}

void Car::setAsPlayerCar(bool t_bool)
{
	m_isPlayerCar = t_bool;
}

float Car::getSpeed()
{
	return m_VelocityVec.length();
}

void Car::setSpeed(float t_speed)
{
	if (t_speed < MAX_SPEED)
	{
		m_currentMaxSpeed = t_speed;
	}
	else
	{
		m_currentMaxSpeed = MAX_SPEED;
	}
}

void Car::increaseSpeed()
{
	if (m_speed < 400)
	{
		m_speed += 4;
	}
}

void Car::decreaseSpeed()
{
	// Assign new vector to = current velocity
	MyVector3 newVelocity = m_VelocityVec;
	// if speed is greater than min speed
	if (m_VelocityVec.length() > 50)
	{
		// assign velocity to a multiple of it's normal minus break power
		if (m_VelocityVec.length() > 450)
		{
			newVelocity = newVelocity * (1 - 15 / m_VelocityVec.length());
		}
		else if (m_VelocityVec.length() > 300)
		{
			newVelocity = newVelocity * (1 - 10 / m_VelocityVec.length());
		}
	}
	// Assign velocity to the newly claculated velocity
	m_VelocityVec = newVelocity;
}

sf::Sprite Car::getSprite()
{
	return m_carSprite;
}

sf::Sprite & Car::getBackSprite()
{
	return m_backOfCarSprite;
}

float Car::getRotation()
{
	return m_rotation;
}

void Car::setRotation(float t_rotation)
{
	m_rotation = t_rotation;
	if (m_rotation != 0)
	{
		double radians = m_rotation * 3.14 / 180;		// Into Radians
		float newCos = std::cos(radians);					// Cos, Sin
		float newSin = std::sin(radians);

		float newX = m_directionVec.x + newCos;				// Rotate the vector by the rotationFactor
		float newY = m_directionVec.y + newSin;
		m_directionVec = { newCos, newSin, 0 };					// New Direction
		m_directionVec.normalise();							// In unit form
	}
	else
	{
		m_directionVec = { 10,0,0 };		// Avoid random stuff when at 0,0,0
		m_directionVec.normalise();
	}
	m_steeringAngle = m_rotation;
	m_carSprite.setRotation(m_rotation);
	m_backOfCarSprite.setRotation(m_rotation);
}

void Car::setLateralFriction(float t_friction)
{
	laterFrictionFactor = t_friction;
}

void Car::setGeneralFriction(float t_friction)
{
	generalFrictionFactor = t_friction;
}

void Car::input()
{
	
	// Acceleration ===========================================================================================
	if (INPUT.Hold.RightTrigger())

	{
		m_accelInput = -(INPUT.Hold.getController().m_currentState.RTrigger / 100);
		doAccerlerate = true;
		Game::m_playerAccerating = true;
		doBrake = false;
	}
	// Decceleration ==========================================================================================
	else if (INPUT.Hold.LeftTrigger())
	{
		m_accelInput = (INPUT.Hold.getController().m_currentState.LTrigger / 100);
		doBrake = true;
		doAccerlerate = false;
		Game::m_playerAccerating = false;
	}
	else
	{
		//m_acceleration = { 0,0,0 };
		Game::m_playerAccerating = false;
		doAccerlerate = false;
		doBrake = false;
	}
	
}

void Car::accelerate()
{
	m_acceleration = m_directionVec * m_accelerationValue;
}

void Car::inputDirection(float t_status)
{
	m_directionInput = t_status;
}

void Car::rotateAroundAxis()
{
	double radians = m_steeringAngle * 3.14 / 180;		// Into Radians
	float newCos = std::cos(radians);					// Cos, Sin
	float newSin = std::sin(radians);

	float newX = m_directionVec.x + newCos;				// Rotate the vector by the rotationFactor
	float newY = m_directionVec.y + newSin;
	m_directionVec = { newCos, newSin, 0 };					// New Direction
	m_directionVec.normalise();							// In unit form
}

void Car::calculateLaterFriction(lateralDirection t_direction)
{
	float rightAngle;
	if (t_direction == lateralDirection::Right)					// If drifting Right
	{
		rightAngle = m_steeringAngle + 90;						// Right Vector
	}
	else if (t_direction == lateralDirection::Left)				// If drifting Left
	{
		rightAngle = m_steeringAngle - 90;						// Left Vector
	}
	
	double radians = rightAngle * 3.14 / 180;					// To radians
	float newCos = std::cos(radians);					// Cos, Sin
	float newSin = std::sin(radians);
	if (m_VelocityVec.length() > 50)
	{
		m_lateralFriction = { newCos, newSin, 0 };				// New Lateral Friction
		m_lateralFriction = m_lateralFriction * (m_difference * laterFrictionFactor);	// Multiplty it by Difference between Velocity and Direction Vector and then by the Drift Factor
	}
	else
	{
		m_lateralFriction = { 0,0,0 };
	}
}

void Car::stopSpeed()
{
	m_acceleration = { 0,0,0 };
	m_VelocityVec = { 0,0,0 };
}

void Car::steering()
{
	float turnValue = m_VelocityVec.length() / 100;
	if (turnValue > 1)
	{
		turnValue = 1;
	}
	m_steeringAngle += m_directionInput * (m_directionMove * turnValue);

	rotateAroundAxis();
}

float Car::getDegrees()
{
	return m_steeringAngle;
}


void Car::speedCalculator()
{
	if (doAccerlerate == true)
	{
		m_acceleration = (m_directionVec * m_accelerationValue) * m_accelInput;
	}
	else if (doBrake == true)
	{
		m_acceleration = (m_directionVec * (-1.0f *m_accelerationValue))* m_accelInput;
	}
	else
	{
		m_acceleration = { 0,0,0 };
	}

}

void Car::getDiffernceVelDir()
{
	if (m_VelocityVec.length() > 0 && m_directionVec.length() > 0)		// Don't divide by 0
	{
		m_difference = m_directionVec.angleBetween(m_VelocityVec);			// Difference between the way the car is moving and the way you are facing
	}
	else
	{
		m_difference = 0;
	}
	if (m_difference < 1)
	{
		m_difference = 0;
	}
}

void Car::friction()
{
	// Getting Degrees of the Vectors ==============================================================
	
	float slideDirectionV = 0;
	// Velocity converted to its degrees.
	if (m_VelocityVec.x != 0)
	{
		slideDirectionV = atan2(m_VelocityVec.y, m_VelocityVec.x);		// For this I get inverse Tan y/x
		directionVel = slideDirectionV * (180 / 3.1415926535897932384);     // To Degrees
	}
	else
	{
		directionVel = 0;
	}
	
	float slideDirectionD = 0;
	// Direction converted to its degrees.
	if (m_directionVec.x != 0)
	{
		slideDirectionD = atan2(m_directionVec.y, m_directionVec.x);		// For this I get inverse Tan y/x
		directionAcceleration = slideDirectionD * (180 / 3.1415926535897932384);		// To Degrees
	}
	else
	{
		directionAcceleration = 0;
	}
	
	// Get into the correct range ----- Absolute Angle
	// This is to ensure it is never outside, though I don't believe it ever is based on the nature of the above 
	while (directionVel < 0)
	{
		directionVel += 360;
	}
	while (directionVel > 359)
	{
		directionVel -= 360;
	}
	while (directionAcceleration < 0)
	{
		directionAcceleration += 360;
	}
	while (directionAcceleration > 359)
	{
		directionAcceleration -= 360;
	}
	if (m_isPlayerCar != true)
	{
		
		float slideDirectionT = 0;
		// Direction converted to its degrees.
		if (m_targetDirectionVector.x != 0)
		{
			slideDirectionT = atan2(m_targetDirectionVector.y, m_targetDirectionVector.x);		// For this I get inverse Tan y/x
			directionTarget = slideDirectionT * (180 / 3.1415926535897932384);		// To Degrees
		}
		else
		{
			directionTarget = 0;
		}
		while (directionTarget < 0)
		{
			directionTarget += 360;
		}
		while (directionTarget > 360)
		{
			directionTarget -= 360;
		}
		if (directionAcceleration != directionTarget)
		{
				if ((((directionAcceleration - directionTarget) > 1) && ((directionAcceleration - directionTarget) < 180)) || ((directionAcceleration - directionTarget) < -180))
				{
					// Right Side of direction
					m_steeringAngle -= m_enemySteering;
				}
				else if ((((directionAcceleration - directionTarget) < -1) && ((directionAcceleration - directionTarget) > -180)) || ((directionAcceleration - directionTarget) > 180))
				{
					// Left side of Direction
					m_steeringAngle += m_enemySteering;
				}
			
			
		}
		// New Direction Vector ======
		if (rightAvoid != true && leftAvoid != true)
		{
			double radians = directionAcceleration * 3.14 / 180;					// To radians
			float newCos = std::cos(radians);					// Cos, Sin
			float newSin = std::sin(radians);
			m_directionVec = { newCos, newSin, 0 };
		}
		else if (rightAvoid == true && leftAvoid != true && firstTime == false)
		{
			m_targetStoreWhenAvoiding = m_target;
			firstTime = true;
			float t = directionAcceleration + 20;
			double radians = t * 3.14 / 180;					// To radians
			float newCos = 1000 * std::cos(radians);					// Cos, Sin
			float newSin = 1000 * std::sin(radians);
			m_target = m_positionVec + MyVector3{ newCos, newSin, 0 };
		}
		else if (leftAvoid == true && rightAvoid != true && firstTime == false)
		{
			m_targetStoreWhenAvoiding = m_target;
			firstTime = true;
			float t = directionAcceleration - 20;
			double radians = t * (3.14 / 180);					// To radians
			float newCos = 1000 * (std::cos(radians));					// Cos, Sin
			float newSin = 1000 * (std::sin(radians));
			m_target = m_positionVec + MyVector3{ newCos, newSin, 0 };
		}




		// This is where you deicide whether the AI should brake or Accelerate.
		float temp = (m_targetDirectionVector).length();
		if (temp < 500 && m_VelocityVec.length() > 350)
		{
			m_aiStates = aiState::braking;
		}
		else
		{
			m_aiStates = aiState::accelerating;
		}
	}

	// Here we solve whether the direction that the car is drifting it Right or left or None
	// Checks the facing direction of the car Minus the direction its moving.
	// It checks if one minus the other is Less than or greater than 0.
	// It checks for coniditions that cross over 0 and reverse the general.
	if ((((directionAcceleration - directionVel) > 0) && ((directionAcceleration - directionVel) < 270)) || ((directionAcceleration - directionVel) < -270))
	{
		// Right Side of direction
		calculateLaterFriction(lateralDirection::Right);
	}
	else if ((((directionAcceleration - directionVel) < 0) && ((directionAcceleration - directionVel) > -270)) || ((directionAcceleration - directionVel) > 270))
	{
		// Left side of Direction
		calculateLaterFriction(lateralDirection::Left);
	}
	else
	{
		// No friction
		m_lateralFriction = { 0,0,0 };
	}

	// General friction
	m_generalFriction = -m_VelocityVec * generalFrictionFactor;

}

void Car::updatePosition(sf::Time t_deltaTime)
{
	// =====================================================================================================
	// Stopping the car if it gets too low and is not accelerating
	if (m_isPlayerCar == true)
	{
		if (m_VelocityVec.length() < 50 && Game::m_playerAccerating == false)
		{
			m_VelocityVec = { 0,0,0 };
			m_lateralFriction = { 0,0,0 };
		}

		// Friction adding =======================================================================================
		if (m_VelocityVec.length() > 50)
		{
			m_VelocityVec = m_VelocityVec + ((m_lateralFriction + m_generalFriction) * t_deltaTime.asSeconds());		// Apply both frictions
		}
		else
		{
			m_VelocityVec = m_VelocityVec + ((m_generalFriction)* t_deltaTime.asSeconds());
		}

	}
	else
	{
		if (m_VelocityVec.length() < 50 && m_aiStates != aiState::accelerating)
		{
			m_VelocityVec = { 0,0,0 };
			m_lateralFriction = { 0,0,0 };
		}
		m_VelocityVec = m_VelocityVec + ((m_lateralFriction + m_generalFriction) * t_deltaTime.asSeconds());		// Apply both frictions
		if ((m_targetDirectionVector).length() < 140)
		{
			m_reachedTarget = true;
		}
	}
	// Velocity =================================================================
	float current_speed = m_VelocityVec.length();
	
	if (current_speed < MAX_SPEED)	// MaxSpeed
	{
		m_VelocityVec = m_VelocityVec + (m_acceleration * t_deltaTime.asSeconds());
	}


	m_positionVec = m_positionVec + (m_VelocityVec * t_deltaTime.asSeconds());
	m_carSprite.setPosition(m_positionVec);
	m_carSprite.setRotation(m_steeringAngle);
	
	m_backOfCarSprite.setPosition(m_positionVec - (m_directionVec*34));
	m_backOfCarSprite.setRotation(m_steeringAngle);
}

void Car::AIinput()
{
	switch (m_aiStates)
	{
	case aiState::accelerating:

		m_acceleration = m_directionVec * m_accelerationValue;
		break;
	case aiState::braking:

		decreaseSpeed();
		break;
	case aiState::Extrabraking:

		decreaseSpeed();
		break;
	case aiState::steady:
		break;
	default:
		break;
	}
}

void Car::runAvoidence(int t_direction)
{
		if (t_direction == 1)
		{
			rightAvoid = true;
		}
		else if (t_direction == 2)
		{
			leftAvoid = true;
		}

}

sf::Vector2f Car::getPosition()
{
	return m_positionVec;
}

sf::Vector2f Car::getSize()
{
	return m_spriteSize;
}

sf::Vector2f Car::getDirection()
{
	return m_directionVec;
}

void Car::setCheckPointID(int t_ID)
{
	m_checkPointID = t_ID;
}

int Car::getCheckPointID()
{
	return m_checkPointID;
}

void Car::makeTarget(sf::Vector2f t_checkPos, sf::Vector2f t_checkSize)
{
	int targetX = rand() % (int)t_checkSize.x;
	int targetY = rand() % (int)t_checkSize.y;
	sf::Vector2f temp = t_checkPos + sf::Vector2f{ (float)targetX , (float)targetY };
	m_target = { temp.x, temp.y, 0 };
	m_reachedTarget = false;
}

void Car::findTarget()
{
	m_targetDirectionVector = (m_target - m_positionVec);
	float tamp = m_targetDirectionVector.length();
}

bool Car::reachedTarget()
{
	return m_reachedTarget;
}

MyVector3 Car::getTarget()
{
	return m_target;
}

int Car::getWayPointIndex()
{
	return m_wayPointIndex;
}

void Car::setWayPointIndex(int t_index)
{
	if (m_count > 40 || t_index == 0)
	{
		m_reachedTarget = false;
		m_wayPointIndex = t_index;
		m_count = 0;
	}
}