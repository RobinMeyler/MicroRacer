#pragma once


#include "Transform.h"
#include "ResourceManager.h"
#include "SFML/Graphics.hpp"

class Checkpoint
{
public:
	Checkpoint();
	~Checkpoint();

	Transform transform;


	void setCanPass();
	void turnOffCanPass();
private:
	bool m_canPass = false;

};