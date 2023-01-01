#include "Snowfall.h"

Snow::Snow()
{
	shape.setSize(sf::Vector2f(20.0f, 20.0f));
	texture.loadFromFile("pic/snow.png");
	shape.setTexture(&texture);
	texture.setSmooth(true);
}

void Snowfall::spawn()
{
	int k = rand() % 24 + 1;
	Snow* tmp = new Snow;
	tmp->setPosition(sf::Vector2f(k * 50, 0));
	tmp->setSize(sf::Vector2f(45.0f, 45.0f));
	snow.push_back(tmp);
}

void Snowfall::render(sf::RenderWindow& window)
{
	for (auto& s : snow)
		window.draw(s->getShape());
}

void Snowfall::update(sf::RenderWindow& window)
{
	std::cout << "Snow size: " << snow.size() << '\n';
	if (snow.size() < 70)
	{
		if (timer >= timeSpawning)
		{
			spawn();
			timer = 0.f;
		}
		else
			timer += 2.0f;
	}

	for (int i = 0; i < snow.size(); i++)
	{
		snow[i]->setSpeed(0.0f, 3.0f);

		if (clock.getElapsedTime() >= sf::seconds(2))
		{
			clock.restart();
		}
		snow[i]->update();

		if (snow[i]->getShape().getPosition().y > window.getSize().y)
		{
			std::cout << "erase\n";
			snow.erase(snow.begin() + i);
		}
	}
}
