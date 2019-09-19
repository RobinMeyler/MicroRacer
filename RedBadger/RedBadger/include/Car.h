#pragma once

#include "Transform.h"
#include "ResourceManager.h"
#include "MyVector3.h"
#include "GUIGlobals.h"
#include "RacePosition.h"
#include "LevelEditor.h"

enum class aiState
{
	accelerating,
	braking,
	Extrabraking,
	steady
};

class Car
{
private:

	aiState m_aiStates{ aiState::accelerating };
	ResourceManager * assetPtr{ nullptr };

	sf::Sprite m_carSprite;
	sf::Sprite m_backOfCarSprite;

	MyVector3 m_acceleration;
	MyVector3 m_directionVec;
	MyVector3 m_lateralFriction;
	MyVector3 m_generalFriction;
	MyVector3 m_VelocityVec;
	MyVector3 m_positionVec;
	MyVector3 temp;
	MyVector3 m_target;
	MyVector3 m_targetStoreWhenAvoiding;
	MyVector3 m_targetDirectionVector;

	sf::Vector2f m_spriteSize;

	float MAX_SPEED{ 600 };
	float m_enemySteering{ 2 };
	float avoidTimerRight;
	float avoidTimerLeft;
	float m_accelInput;
	float m_brakePower = 2.8f;
	float directionVel{ 0 };
	float directionAcceleration{ 0 };
	float directionTarget{ 0 };
	float laterFrictionFactor;
	float generalFrictionFactor;
	float m_steeringAngle{ 0 };
	float m_directionMove{ 1 };
	float m_directionInput{ 0 };
	float m_difference{ 0 };
	float m_speed{ 10 };
	float m_rotation{ 0 };
	float m_accelerationValue{ 0 };
	float m_currentMaxSpeed{ 0 };

	int m_Ainput{ 0 };
	int count{ 0 };
	int m_wayPointIndex;
	int m_idPassed;
	int m_checkPointID{1};
	int m_count{ 41 };
	short m_uniqueCarID;

	bool m_pastBridge;
	bool m_under;
	bool isAlive;
	bool m_isPlayerCar{ false };
	bool m_reachedTarget{ false };
	bool doAccerlerate = false;
	bool doBrake = false;
	bool leftAvoid{ false };
	bool rightAvoid{ false };
	bool firstTime{ false };

public:
	Car();
	Car(ResourceManager & t_gameAssets);
	~Car();

	bool getIsUnder();
	bool getisPastBridge();
	
	int m_indexAi1{ -1 };
	int m_indexAi2{ -1 };

	
	void intialize();
	void update(sf::Time t_detlaTime);
	void setPosition(sf::Vector2f t_position);
	void render(sf::RenderWindow & t_window);
	void addID(int t_ID);

	void makeTarget(sf::Vector2f t_checkPos, sf::Vector2f t_checkSize);
	void findTarget();
	bool reachedTarget();
	MyVector3 getTarget();

	short getUniqueID();
	void setUniqueID(short t_ID);

	int getID();
	float getSpeed();
	bool getIsPlayerCar();
	int getCheckPointID();
	sf::Vector2f getPosition();
	sf::Vector2f getSize();
	sf::Vector2f getDirection();

	void setCheckPointID(int t_ID);
	void setIsunder(bool t_isUnder);
	void setIsPastBridge(bool t_isPast);
	void setSprite(int t_spriteIndex);
	void setTurnAmount(float t_turnAmount);
	void setMaxSpeed(float t_speed);
	void setAcceleration(float t_accel);
	void setSteering(float t_steering);
	void setAsPlayerCar(bool t_bool);
	void setSpeed(float t_speed);
	void setRotation(float t_rotation);
	void setLateralFriction(float t_friction);
	void setGeneralFriction(float t_friction);
	void setWayPointIndex(int t_index);

	void increaseSpeed();
	void decreaseSpeed();
	sf::Sprite getSprite();
	sf::Sprite & getBackSprite();

	float getRotation();
	void input();
	void accelerate();
	void inputDirection(float t_status);
	void rotateAroundAxis();
	void calculateLaterFriction(lateralDirection t_direction);
	int getWayPointIndex();

	void stopSpeed();
	void steering();
	float getDegrees();
	void speedCalculator();
	void getDiffernceVelDir();
	void friction();
	void updatePosition(sf::Time deltaTime);
	void AIinput();
	void runAvoidence(int t_direction);		// 1 = right, 2 = left

	// For use durning track races
	RacePosition racePositon;

	Lap lap;
};

