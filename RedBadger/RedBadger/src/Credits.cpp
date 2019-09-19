#include "Credits.h"
#include "Game.h"


Credits::Credits(ResourceManager & t_gameAssets) :
	m_font(t_gameAssets.m_gameFonts["Digitial font"])

{
}


Credits::~Credits()
{
}

void Credits::clearGUI()
{
	m_GUI.clearGUI();
}

void Credits::initialize()
{



	//Title
	Label *m_title = new Label(m_font);
	m_title->setFont(m_font);
	m_title->setTextSize(90);
	m_title->setString("Credits");
	m_title->setPosition(sf::Vector2f(600, 75));
	m_title->setOrigin();
	m_title->setUnderLined();

	m_title->setTextColor(sf::Color::Green);
	m_screenOutline.setOutlineColor(sf::Color::Green);
	
	m_title->setTextColor(sf::Color::Red);
	m_screenOutline.setOutlineColor(sf::Color::Red);
	
	// titles
	int numOfTitles = 4;
	for (int i = 0; i < numOfTitles; i++)
	{
		sf::Text temp;
		temp.setFont(m_font);
		temp.setFillColor(sf::Color::Red);
		temp.setFillColor(sf::Color::Green);
		temp.setCharacterSize(0);
		temp.setPosition(200, 200);

		switch (i)
		{
		case 0:
			temp.setString("Producers:");
			break;
		case 1:
			temp.setString("Sound designers:");
			break;
		case 2:
			temp.setString("Artists:");
			break;
		case 3:
			temp.setString("Programmers:");
			break;
		}
		m_titles.push_back(temp);
	}

	// names
	int numOfNames = 12;
	for (int i = 0; i < numOfNames; i++)
	{
		sf::Text temp;
		temp.setFont(m_font);
		temp.setFillColor(sf::Color::Blue);
		temp.setCharacterSize(0);

		switch (i)
		{
		case 0:
			temp.setString("Josh");
			break;
		case 1:
			temp.setString("Robin");
			break;
		case 2:
			temp.setString("Paul");
			break;
		case 3:
			temp.setString("Robin");
			break;
		case 4:
			temp.setString("Josh");
			break;
		case 5:
			temp.setString("Paul");
			break;
		case 6:
			temp.setString("Robin");
			break;
		case 7:
			temp.setString("Josh");
			break;
		case 8:
			temp.setString("Paul");
			break;
		case 9:
			temp.setString("Robin");
			break;
		case 10:
			temp.setString("Josh");
			break;
		case 11:
			temp.setString("Paul");
			break;
		}
		m_names.push_back(temp);
	}

	// Add widgets to GUI
	m_GUI.addWidget(m_title);
}

void Credits::update(sf::Time t_deltaTime)
{
	handleControllerInput();
	shrinkAnimation(&m_titles.at(index), &m_names.at(index * 2), &m_names.at(index * 2) + 1, &m_names.at((index * 2) + 2));

	// Check if animation stage needs changing
	if (m_stage == animationStage::Grow)
	{
		if (m_titles.at(index).getCharacterSize() > 80)
		{
			m_stage = animationStage::Pause;
		}
	}
	else if (m_stage == animationStage::Pause)
	{
		pauseCount++;
		if (pauseCount > 80)
		{
			pauseCount = 0; //  reset
			m_stage = animationStage::ShrinkAway;
		}
	}
	else if (m_stage == animationStage::ShrinkAway)
	{
		if (m_titles.at(index).getCharacterSize() < 1)
		{
			if (index < 3)
			{
				m_titles.at(index).setCharacterSize(0);
				m_names.at(index).setCharacterSize(0);
				index++;
			}
			else
			{
				index = 0;
			}
			m_stage = animationStage::Grow;
		}
	}

}

void Credits::render(sf::RenderWindow & t_window)
{
	t_window.clear(sf::Color::White);
	t_window.draw(m_screenOutline);
	for (int i = 0; i < m_titles.size(); i++)
	{
		if (m_titles.at(i).getCharacterSize() > 0)	// draw if bigger than 0 (because text still visible at 0 for some reason)
			t_window.draw(m_titles.at(i));
	}
	for (int i = 0; i < m_names.size(); i++)
	{
		if (m_names.at(i).getCharacterSize() > 0)
			t_window.draw(m_names.at(i));
	}
	m_GUI.render(t_window);

}

void Credits::handleControllerInput()
{
	if (INPUT.PressOnce.B() == true)
	{
		initialize();
		Game::m_gameMode = GameMode::Options;
	}
}

void Credits::runAction(std::string & t_actionString)
{

}

void Credits::shrinkAnimation(sf::Text * t_title, sf::Text * t_nameOne, sf::Text * t_nameTwo, sf::Text * t_nameThree)
{
	t_nameOne->setPosition(t_title->getPosition().x, t_title->getPosition().y + 80);
	t_nameTwo->setPosition(t_title->getPosition().x, t_title->getPosition().y + 160);
	t_nameThree->setPosition(t_title->getPosition().x, t_title->getPosition().y + 240);
	switch (m_stage)
	{
	case Grow:
		// texts get bigger
		t_title->setCharacterSize(t_title->getCharacterSize() + 2);
		t_nameOne->setCharacterSize(t_nameOne->getCharacterSize() + 2);
		t_nameTwo->setCharacterSize(t_nameTwo->getCharacterSize() + 2);
		t_nameThree->setCharacterSize(t_nameThree->getCharacterSize() + 2);
		break;
	case Pause:
		// dont do anything..
		break;
	case ShrinkAway:
		// texts get smaller
		t_title->setCharacterSize(t_title->getCharacterSize() - 2);
		t_nameOne->setCharacterSize(t_nameOne->getCharacterSize() - 2);
		t_nameTwo->setCharacterSize(t_nameTwo->getCharacterSize() - 2);
		t_nameThree->setCharacterSize(t_nameThree->getCharacterSize() - 2);
		break;
	}
}