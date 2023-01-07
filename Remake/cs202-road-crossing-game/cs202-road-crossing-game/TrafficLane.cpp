#include "TrafficLane.h"
#include "Candy.h"
#include "Ginger.h"
#include "Reindeer.h"
#include "PineTree.h"
#include "Wood.h"
void TrafficLane::initVariable()
{
	for (int i = 0; i < 5; i++)
	{
		TrafficLight* tmp = new TrafficLight; 
		tmp->setPosition(0,40 + i*110.f);
		trafficLight.push_back(tmp); 
	}
}

TrafficLane::TrafficLane()
{
	initVariable();
}

TrafficLane::~TrafficLane()
{
	for (int i = 0; i < obs.size(); i++)
		delete obs[i];
	for (int i = 0; i < 5; i++)
		delete trafficLight[i];
}

bool TrafficLane::canMove(int lane)
{
	if (traffic[lane]) return 0; 
	return 1; 
}

void TrafficLane::update(sf::RenderWindow& window, int level)
{
	for (int i = 0; i < 5; i++)
		trafficLight[i]->update(!canMove(i)); 
	if (obs.size() < 10 + level)
	{
		if (timer >= timeSpawning)
		{
			spawnEnemy(window);
			timer = 0.f;
		}
		else
			timer += 0.5f + float(level) / 5; 
	}

	for (int i = 0; i < obs.size(); i++)
	{
		obs[i]->setSpeed(float(5 + level), 0.f); 
		
		if (clock.getElapsedTime() >= sf::seconds(1 + rand() % 5))
		{
			srand(time(NULL));
			for (int i = 0; i < 5; i++)
				traffic[i] = rand() % 2; 
			clock.restart(); 
		}
		
		if (canMove(light[i]))
		{
			obs[i]->update();
		}
		else
		{
			if (obs[i]->checkType())
				obs[i]->update();
		}
		if (obs[i]->getShape().getPosition().x > window.getSize().x)
		{
			obs.erase(obs.begin() + i); 
			light.erase(light.begin() + i); 
		}
	}
}

void TrafficLane::spawnEnemy(sf::RenderWindow& window)
{
	int k = rand() % 5;
	if (k != lane) lane = k;
	else if (k == lane) lane = (k + 1) % 5;

	if (canMove(lane))
	{
		int t = rand() % 5;
		Obstacle* tmp = nullptr;
		if (t == 0)
			tmp = new Wood;
		else if (t == 1)
			tmp = new Candy;
		else if (t == 2)
			tmp = new Reindeer;
		else if (t == 3)
			tmp = new PineTree;
		else if (t == 4)
			tmp = new Ginger;
		std::cout << "Lane: " << lane << '\n';
		tmp->setPosition(sf::Vector2f(0, lane * 110 + 13));

		obs.push_back(tmp);
		light.push_back(lane);
	}
}

void TrafficLane::renderObstacle(sf::RenderWindow& window)
{
	for (auto& o : obs)
	{
		window.draw(o->getShape());
	}
}

void TrafficLane::renderTrafficLight(sf::RenderWindow& window)
{
	for (int i = 0; i < trafficLight.size(); i++)
		trafficLight[i]->render(window);
}

void TrafficLane::render(sf::RenderWindow& window)
{
	renderObstacle(window);
	renderTrafficLight(window);
}

bool TrafficLane::Collision(sf::FloatRect coll)
{
	for (auto& i : obs)
	{
		if (i->getShape().getGlobalBounds().intersects(coll))
		{
			i->makeSound(); 
			// make sound; 
			return true; 
		}
	}
	return false; 
}

void TrafficLane::resetTimer()
{
	clock.restart();
}
