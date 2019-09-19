#include "SoundOptions.h"
#include "Game.h"


SoundOptions::SoundOptions(ResourceManager & t_gameAssets) 
{
	ptrGameAssets = &t_gameAssets;

	m_font = t_gameAssets.m_gameFonts["Speed font"];
	m_digitFont = t_gameAssets.m_gameFonts["Digitial font"];

	initialize();

}


SoundOptions::~SoundOptions()
{
}

void SoundOptions::clearGUI()
{
	m_GUI.clearGUI();
}

void SoundOptions::initialize()
{
	m_GUI.setSoundBuffer(&ptrGameAssets->m_gameSounds["Move Selection"], &Game::EFFECTS_BOOL, &ptrGameAssets->m_gameSounds["Confirm"], 
		&Game::EFFECTS_BOOL, &ptrGameAssets->m_gameSounds["Back"], &Game::EFFECTS_BOOL);

	//Background
	m_bckGroundSprite.setTexture(ptrGameAssets->m_gameTextures["Menu Background"]);
	
	// Volume Level button image
	m_volumeLevelRectangle.setTexture(&ptrGameAssets->m_gameTextures["Button Texture One"]);
	m_volumeLevelRectangle.setSize(sf::Vector2f(100, 75));
	m_volumeLevelRectangle.setPosition(sf::Vector2f(870, 300));
	m_volumeLevelRectangle.setOrigin(m_volumeLevelRectangle.getLocalBounds().width / 2, m_volumeLevelRectangle.getLocalBounds().height / 2);

	//Volume level text
	m_volumeText.setString(std::to_string(Game::MUSIC_VOLUME) + "%");
	m_volumeText.setFont(m_digitFont);
	m_volumeText.setCharacterSize(40);
	m_volumeText.setFillColor(sf::Color::Green);
	m_volumeText.setPosition(sf::Vector2f(840, 270));

	//Volume Knob widget
	VolumeKnob* volumeKnob = new VolumeKnob(ptrGameAssets->m_gameTextures["Volume Knob"]);
	volumeKnob->setPosition(sf::Vector2f(700, 300));
	volumeKnob->setActionString("Knob");
	
	// Title
	Label *title = new Label(m_font);
	title->setString("Sound Options");
	title->setPosition(sf::Vector2f{ 600, 70 });
	title->setTextSize(70);
	title->setOrigin();
	title->setUnderLined();
	title->setOutline(sf::Color::Yellow, 3);
	m_GUI.addWidget(title);

	// Sound Volume button
	sf::Color blue = sf::Color(sf::Color::Blue);
	Button * soundVolume = new Button(blue, 420, 75);
	soundVolume->setString("Sound Volume:", 50);
	soundVolume->setTextColor(sf::Color(sf::Color::Red));
	soundVolume->setFont(m_digitFont);
	soundVolume->setPosition(sf::Vector2f(280, 300));
	soundVolume->setOutline(sf::Color(sf::Color::White), 3);
	soundVolume->setHighLightSpeed(6);
	soundVolume->setFlashColor(sf::Color::Yellow);
	soundVolume->setActionString("Volume Change");

	//Sound effects button
	Button * soundEffects = new Button(blue, 420, 75);
	soundEffects->setString("Sound Effects:", 50);
	soundEffects->setTextColor(sf::Color(sf::Color::Red));
	soundEffects->setFont(m_digitFont);
	soundEffects->setPosition(sf::Vector2f(280, 500));
	soundEffects->setOutline(sf::Color(sf::Color::White), 3);
	soundEffects->setHighLightSpeed(6);
	soundEffects->setFlashColor(sf::Color::Yellow);
	//Check boxs
	CheckBox *check = new CheckBox(40, &Game::MUSIC_BOOL);//&Game::SOUND_EFFECT1);
	check->setFilledTrue();
	check->setPosition(sf::Vector2f{ 950, 525 });
	check->setActionString("Checkbox");
	m_GUI.addWidget(check);

	Label *check1Text = new Label(m_digitFont);
	check1Text->setString("Background Music:");
	check1Text->setPosition(sf::Vector2f{ 550, 500 });
	check1Text->setTextSize(40);
	check1Text->setUnderLined();
	check1Text->setUnderItalic();
	m_GUI.addWidget(check1Text);

	CheckBox *checkTwo = new CheckBox(40, &Game::EFFECTS_BOOL);//&Game::SOUND_EFFECT1);
	checkTwo->setFilledTrue();
	checkTwo->setPosition(sf::Vector2f{ 950, 625 });
	checkTwo->setActionString("Checkbox");
	m_GUI.addWidget(checkTwo);

	Label *check2Text = new Label(m_digitFont);
	check2Text->setString("All Extra Sounds:");
	check2Text->setPosition(sf::Vector2f{ 550, 600 });
	check2Text->setTextSize(40);
	check2Text->setUnderLined();
	check2Text->setUnderItalic();
	m_GUI.addWidget(check2Text);


	soundVolume->setAsStarter();

	//Set Up 'n Downs
	soundVolume->setDown(soundEffects);
	soundVolume->setRight(volumeKnob);
	volumeKnob->setLeft(soundVolume);
	soundEffects->setUp(soundVolume);
	soundEffects->setRight(check);
	check->setLeft(soundEffects);
	check->setDown(checkTwo);
	checkTwo->setUp(check);
	checkTwo->setLeft(soundEffects);

	// Add widgets to gui
	m_GUI.addWidget(soundVolume);
	m_GUI.addWidget(soundEffects);
	m_GUI.addWidget(volumeKnob);

	//Set start focus
	m_GUI.setStartFocus(soundVolume);

}

void SoundOptions::update(sf::Time t_deltaTime)
{
	m_volumeText.setString(std::to_string(Game::MUSIC_VOLUME) + "%");
	m_GUI.update(t_deltaTime);
	handleControllerInput();
}

void SoundOptions::render(sf::RenderWindow & t_window)
{
	t_window.draw(m_bckGroundSprite);
	t_window.draw(m_volumeLevelRectangle);
	t_window.draw(m_volumeText);
	m_GUI.render(t_window);
}


void SoundOptions::handleControllerInput()
{
	if (m_count > 15)
	{
		if (INPUT.PressOnce.Down())
		{
			m_GUI.moveDown();
			m_count = 0;
		}
		if (INPUT.PressOnce.Up())
		{
			m_GUI.moveUp();
			m_count = 0;
		}

		if (INPUT.PressOnce.A())
		{
			m_GUI.moveRight();	// move focus to volume Knob
			if (m_count > 15)
			{
				if (m_GUI.getCurrentWidget()->getActionString() == "Checkbox")
				{
					m_GUI.getCurrentWidget()->action();
					Game::playSoundTrack(); // this is not ideal but best way temporarily
				}
			}
			m_count = 0;
		}
		

		if (m_GUI.getCurrentWidget()->getActionString() == "Knob")	// volumeKnob actionString == Knob
		{
			if (m_count > 15)
			{
				if (INPUT.PressOnce.B())
				{
					m_GUI.moveLeft();	// move focus back to volume button
					m_count = 0;
				}
				else if (INPUT.Hold.Right())
				{
					m_GUI.getCurrentWidget()->increaseRotation();
					m_GUI.getCurrentWidget()->increaseRotation();
					m_GUI.getCurrentWidget()->increaseRotation();
					if (Game::MUSIC_VOLUME < 100)
					{
						Game::MUSIC_VOLUME++;
					}
				}
				else if (INPUT.Hold.Left())
				{
					m_GUI.getCurrentWidget()->decreaseRotation();
					m_GUI.getCurrentWidget()->decreaseRotation();
					m_GUI.getCurrentWidget()->decreaseRotation();
					if (Game::MUSIC_VOLUME > 0)
					{
						Game::MUSIC_VOLUME--;
					}
				}
			}
		}
		else if (m_GUI.getCurrentWidget()->getActionString() == "Checkbox")	// check actionString == checkbox
		{
			if (m_count > 15)
			{
				if (INPUT.PressOnce.B())
				{
					m_GUI.moveLeft();	// move focus back to volume button
					m_count = 0;
				}
			}
		}
		else
		{
			if (INPUT.PressOnce.B())
			{
				Game::m_gameMode = GameMode::Options;			// move focus back to volume button
				m_count = 0;
			}
		}
	}
	m_count++;
}

void SoundOptions::runAction(std::string & t_actionString)
{


}