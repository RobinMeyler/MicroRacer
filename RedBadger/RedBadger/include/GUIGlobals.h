#pragma once

// Made by: Robin Meyler, Josh Browne
// Date: Feburary - march 2019
// Time taken: ~ 40 hours


#include <iostream>
#include "Thor/Resources.hpp"
#include "InputManager.h"
#include "ScreenTransitions.h"

enum class lateralDirection
{
	Left,
	Right,
	None
};

enum class GameMode
{
	Licence,
	Splash,
	MainMenu,
	Gameplay,
	LeaderBoard,
	Credits,
	Options,
	ControlInfo,
	Rules,
	SoundOptions,
	ArtOptions,
	Pause,
	Winning,
	CutScene,
	Upgrades,
	TrackSelection
};

enum class GUItype
{ 
	Widget,
	Button,
	Switch,
	Label,
	CheckBox,
	Radio,
	SideSlider,
	CharacterSelect
};

enum class PositionSetState
{
	DECIMAL,
	PERCENTAGE,
	EXACT
};

enum class buttonStyle
{
	NORMAL,
	SWITCH,
	FADED,
	TRANSPARENT
};

enum class buttonVisual
{
	RECTANGLE,
	TEXTURE
};

enum class buttonAnimationStyle
{
	FLASH,
	SHRINK, 
	HIGHLIGHT
};

enum class Sort
{
	STRING,
	VALUE
};

enum class WidgetTransitionState
{
	SETUP,
	INTRO,
	DISPLAY,
	EXIT,
	FINISH
};

enum class WidgetTransitionStyle
{
	VerticalMove,
	HorizontalMove,
	Rotate
};

enum class highLightState
{
	NotHighlighted,
	UnHighlighted,
	Highlighting,
	FullyHighlighted,
	UnHighlighting
};

enum class GameplayTurnState
{
	INPUT,		// read in players input
	UPDATE,		// update car movement with players input
};

static const int SCREEN_WIDTH = 800;
static const int SCREEN_HEIGHT = 800;
//static Xbox360Controller GAME_CONTROLLER;

static InputManager INPUT;
