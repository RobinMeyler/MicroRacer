#include "ControlInfo.h"
#include "Game.h"


ControlInfo::ControlInfo(ResourceManager & t_gameAssets):
	m_font(t_gameAssets.m_gameFonts["carfont1"]),
	border(t_gameAssets.m_gameTextures["Border"]),
	m_a(t_gameAssets.m_gameTextures["XboxA"]),
	m_lt(t_gameAssets.m_gameTextures["XboxLT"]),
	m_rt(t_gameAssets.m_gameTextures["XboxRT"]),
	m_ls(t_gameAssets.m_gameTextures["XboxLS"])
{
	m_rt.setPosition(1000, 150);
	m_lt.setPosition(1000, 300);
	m_ls.setPosition(1000, 450);
	m_a.setPosition(1000, 600);
}

ControlInfo::~ControlInfo()
{
}

void ControlInfo::clearGUI()
{

}

void ControlInfo::initialize()
{
	border.setScale(1, 0.87);
	border.setPosition(0, 0);

	Label *title = new Label(m_font);
	title->setString("--Controls--");
	title->setPosition(sf::Vector2f{ 600, 80 });
	title->setTextSize(80);
	title->setOrigin();
	title->setUnderLined();
	title->setTextColor(sf::Color::White);
	title->setOutline(sf::Color::Black, 2);
	m_gui.addWidget(title);


	Label *item1 = new Label(m_font);
	item1->setString("Press on Right trigger (RT)\nfor different levels of Throttle");
	item1->setPosition(sf::Vector2f{ 50, 150 });
	item1->setTextSize(40);
	//item1->setOrigin();
	item1->setUnderLined();
	item1->setTextColor(sf::Color::White);
	item1->setOutline(sf::Color::Black, 2);
	m_gui.addWidget(item1);

	Label *item2 = new Label(m_font);
	item2->setString("Press on Left trigger (LT)\nfor different levels of Braking");
	item2->setPosition(sf::Vector2f{ 50, 300 });
	item2->setTextSize(40);
	//item2->setOrigin();
	item2->setUnderLined();
	item2->setTextColor(sf::Color::White);
	item2->setOutline(sf::Color::Black, 1.5);
	m_gui.addWidget(item2);

	Label *item3 = new Label(m_font);
	item3->setString("Move the Left Analog (L)\nLeft and Right for turning a degree");
	item3->setPosition(sf::Vector2f{ 50, 450 });
	item3->setTextSize(40);
	//item3->setOrigin();
	item3->setUnderLined();
	item3->setTextColor(sf::Color::White);
	item3->setOutline(sf::Color::Black, 2);
	m_gui.addWidget(item3);

	Label *item4 = new Label(m_font);
	item4->setString("While hold a comination of above\nPress (A) to confrim your action");
	item4->setPosition(sf::Vector2f{ 50, 600 });
	item4->setTextSize(40);
	//item3->setOrigin();
	item4->setUnderLined();
	item4->setTextColor(sf::Color::White);
	item4->setOutline(sf::Color::Black, 2);
	m_gui.addWidget(item4);



	m_gui.setStartFocus(title);
}

void ControlInfo::update(sf::Time t_deltaTime)
{
	handleControllerInput();
	m_gui.update(t_deltaTime);
}

void ControlInfo::render(sf::RenderWindow & t_window)
{
	t_window.clear(sf::Color(220,220,220));
	t_window.draw(border);
	t_window.draw(m_a);
	t_window.draw(m_rt);
	t_window.draw(m_lt);
	t_window.draw(m_ls);
	m_gui.render(t_window);
}

void ControlInfo::handleControllerInput()
{
	if (INPUT.PressOnce.B())
	{
		Game::m_gameMode = GameMode::Options;
	}
	
}

void ControlInfo::runAction(std::string & t_actionString)
{

}
