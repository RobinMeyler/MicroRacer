#pragma once

#include "ResourceManager.h"
#include "GUIGlobals.h"
#include "Bush.h"
#include <fstream>
#include <string>

enum ObjectState
{
	BUSH,
	TREE,
	CHECKPOINT,
	FINISH
};
class LevelEditor
{
public:
	LevelEditor();
	~LevelEditor();


	void setBush(sf::Vector2f t_position);

	Transform transform;
	
	void performAction();

	sf::Sprite getSpritePlacing();
	
	Bush bush[180];
	void placeBushes();
private:
	int numberOfBushesPlaced = 0;

	sf::Texture bushTexture;

	std::string data[999];
	sf::Sprite spritePlacing;

	float speed = 2;

	void updatePosition();
	void placeObject();
	void movePosition();
	void savePlacementToFile();


};
