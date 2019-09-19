#include "LevelEditor.h"

LevelEditor::LevelEditor()
{
	std::string url = "./ASSETS/IMAGES/bush.png";

	if (!bushTexture.loadFromFile(url))
	{
		std::cout << "Could not find file at " << url << std::endl;
	}

	spritePlacing.setTexture(bushTexture);

	spritePlacing.setOrigin(sf::Vector2f(43, 43));
	spritePlacing.setScale(5, 5);
}

LevelEditor::~LevelEditor()
{
}

void LevelEditor::placeObject()
{
	if (INPUT.PressOnce.A())
	{
		setBush(transform.position);
	}
}

void LevelEditor::setBush(sf::Vector2f t_position)
{
	for (int i = 0; i < 200; i++)
	{
		if (!bush[i].isActive())
		{
			bush[i].setPosition(t_position);
			data[i].clear();
			data[i] = std::to_string(t_position.x) + "," + std::to_string(t_position.y);
			bush[i].init();
			bush[i].getSprite().setScale(5, 5);
			bush[i].setActive(true);
			numberOfBushesPlaced++;
			break;
		}
	}
}

void LevelEditor::movePosition()
{
	if (INPUT.Hold.Up())
	{
		transform.position.y -= speed;
	}

	else if (INPUT.Hold.Down())
	{
		transform.position.y += speed;
	}

	if (INPUT.Hold.Left())
	{
		transform.position.x -= speed;
	}

	else if (INPUT.Hold.Right())
	{
		transform.position.x += speed;
	}

	updatePosition();
}

void LevelEditor::performAction()
{
	movePosition();
	savePlacementToFile();
	placeObject();
}

void LevelEditor::updatePosition()
{
	spritePlacing.setPosition(transform.position);
}

sf::Sprite LevelEditor::getSpritePlacing()
{
	return spritePlacing;
}

void LevelEditor::savePlacementToFile()
{	
	if (INPUT.PressOnce.B())
	{

		// Overwrite File
		std::ofstream positionFile("positionFileCheckPoints.txt");


		for (int i = 0; i < numberOfBushesPlaced; i++)
		{

			positionFile << data[i] << std::endl;
		}
		positionFile.close(); // close of file from further editing

	}

}


void LevelEditor::placeBushes()
{
	std::ifstream vectorData("positionFile.txt");
	std::string vecData;


	// iterate through string and add ASCII contents into string
	if (vectorData)
	{
		std::string vectorPosTextContainer((std::istreambuf_iterator<char>(vectorData)),
			std::istreambuf_iterator<char>());

		vecData.clear();
		vecData = vectorPosTextContainer;
	}

	// Initialise and set up bush
	int iBush = 0;

	while (iBush < 180)
	{

		// Strings for storing values from text file
		std::string x_str;
		std::string y_str;


		float x = 0;
		float y = 0;

		bush[iBush].setPosition(sf::Vector2f(x, y));

		bool setX = true;

		x_str.clear();
		y_str.clear();


		for (int i = 0; i < vecData.length(); i++)
		{
			// if data char is not , or ENter
			if (vecData[i] != 44 && vecData[i] != 10)
			{

				if (setX)
				{
					x_str += vecData[i];
				}
				else
				{
					y_str += vecData[i];
				}


			}

			// new line
			else if (vecData[i] == 10)
			{
				setX = true;

				float x = std::stof(x_str);
				float y = std::stof(y_str);

				bush[iBush].setPosition(sf::Vector2f(x, y));
				bush[iBush].setActive(true);
				x_str.clear();
				y_str.clear();
				iBush++;

			}
			// comma ,
			else if (vecData[i] == 44)
			{
				setX = false;
			}
		}


	}
}
