#include "Speedometer.h"

Speedometer::Speedometer()
{

	// Set up number textures
	for (int index = 0; index < 10; index++)
	{
		std::string indexString = std::to_string(index);

		// numbers of images are also there names in the image folder
		std::string url = "./ASSETS/IMAGES/HUD/" + indexString + ".png";

		if (!speedHUDNumbers[index].loadFromFile(url))
		{
			std::cout << "Could not find file at " << url << std::endl;
		}
	}

	// Set up kmph texture
	if (!kilometersPerHourTexture.loadFromFile("./ASSETS/IMAGES/HUD/Kmh.png"))
	{
		std::cout << "Could not find file at " << "./ASSETS/IMAGES/HUD/Kmh.png" << std::endl;
	}

	metricSprite.setTexture(kilometersPerHourTexture);
}

Speedometer::~Speedometer()
{
}


void Speedometer::setSpeedDisplay(int t_speed)
{
	// Convert passed speed to a string 
	std::string currentSpeed = std::to_string(t_speed);

	
	
	// get smallest number
	int digitOne = 0;
	if (t_speed >= 1)
	{
		digitOne = digitForOne(t_speed);
	}

	// create ints for holding data for digits in the tens and initialise to 0
	int digitTens = 0;
	int tens = 0;

	// holds the digits in the hundreds initialise to 0
	int digitHundred = 0;

	// Only if our speed is greated than 100
	if (t_speed > 99)
	{
		// set digitHundred
		digitHundred = digitForFirst(t_speed);

		// get the tens as a seperate number by taking away the hundred value
		tens = t_speed - (digitHundred * 100);

		// Find first number of the 2 digit number
		digitTens = digitForFirst(tens);
	}
	// 
	else
	{
		if (t_speed > 9)
			// just find the first number of the 2 digit number
			digitTens = digitForFirst(t_speed);
	}




	// Set sprites for all the digits
	for (int index = 0; index < 10; index++)
	{
		// 
		if (index == digitOne)
		{
			one.setTexture(speedHUDNumbers[index]);
		}

		if (index == digitTens)
		{
			ten.setTexture(speedHUDNumbers[index]);
		}

		if (index == digitHundred)
		{
			hundred.setTexture(speedHUDNumbers[index]);
		}


	}


} // END SET DISPLAY SPEED HUD

void Speedometer::setPosition(sf::Vector2f t_position)
{
	sf::Vector2f offset = { 450,120 };
	metricSprite.setPosition(sf::Vector2f(t_position.x + offset.x, t_position.y + offset.y));
	one.setPosition(sf::Vector2f(t_position.x - 30 + offset.x, t_position.y + offset.y));
	ten.setPosition(sf::Vector2f(t_position.x - 60 + offset.x, t_position.y + offset.y));
	hundred.setPosition(sf::Vector2f(t_position.x - 90 + offset.x, t_position.y + offset.y));
}


int Speedometer::digitForOne(int t_speed)
{

	return (t_speed % 10);
}

sf::Sprite Speedometer::getLastDigitSprite()
{
	return one;
}

sf::Sprite Speedometer::getMiddleDigitSprite()
{
	return ten;
}

sf::Sprite Speedometer::getFirstDigitSprite()
{
	return hundred;
}

sf::Sprite Speedometer::getMetricSprite()
{
	return metricSprite;
}

int Speedometer::digitForFirst(int t_speed)
{
	while (t_speed >= 10)
	{

		t_speed /= 10;

	}

	return t_speed;

}
