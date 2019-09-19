#pragma once

#include <iostream>
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include "GUIGlobals.h"

#include "GUI.h"
#include "Xbox360Controller.h"
#include "ResourceManager.h"

class Upgrades
{
public:
	Upgrades(ResourceManager & t_gameAssets);
	~Upgrades();

	void initialize();
	void update(sf::Time t_deltaTime);
	void render(sf::RenderWindow & t_window);
	void handleControllerInput();
	void runAction(std::string & t_actionString);

	void fadeButtons();
	void unFadeButtons();
	void subButtonMovement();
	void setEquipedTextPositions();

private:
	ResourceManager * m_ptrGameAssets;
	GUI m_GUI;
	enum class subButtonState{ Normal,SlideOut, DropDown, DoNothing, ReverseDropDown,SlideIn};
	subButtonState m_subButtonState{ subButtonState::SlideIn };
	Widget * firstSubButton; // a pointer to keep track of the first sub button
	std::vector<Widget*>& m_widgetsReference;
	Widget * m_equippedEngine; // a pointer to keep track of the equipped button
	Widget * m_equippedWheel; // a pointer to keep track of the equipped button
	Widget * m_equippedNitro; // a pointer to keep track of the equipped button
	Widget * m_equippedBody; // a pointer to keep track of the equipped button

	sf::Font m_font;

	sf::Sprite m_carImage;
	sf::Sprite m_smallCarImage[3];

	sf::Sprite m_bckGround;

	sf::RectangleShape m_statsDisplay;
	sf::Text m_statsText;
	sf::RectangleShape m_statBars[3];

	sf::RectangleShape m_moneyDisplay;
	sf::Text m_moneyText;

	sf::Text m_equippedText[4];
	bool m_eqquipedBools[4]; // these are used to know if the eqquipped text should be drawn

	int m_count{ 0 };

	int m_slideSpeed{10};

	bool m_reInitialised = false;
};