#pragma once
#include "ResourceManager.h"
#include "GUIGlobals.h"
#include "Transform.h"

class FinishLine
{
public:
	FinishLine();
	~FinishLine();

	
	void setCanPass();
	void turnOffCanPass();
private:
	bool m_canPass = false;


};
