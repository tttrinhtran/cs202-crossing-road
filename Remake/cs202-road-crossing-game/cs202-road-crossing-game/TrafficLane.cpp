#include "TrafficLane.h"

void TrafficLane::initVariable()
{
	for (int i = 0; i < 5; i++)
	{
		TrafficLight* tmp = new TrafficLight; 
		tmp->setPosition(
			0,
			static_cast<int>(i * (tmp->getShape().getSize().y + 70.f)) + 20.f); 
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
			spawnEnemy();
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
			obs[i]->update(); 
		if (obs[i]->getShape().getPosition().x > window.getSize().x)
		{
			obs.erase(obs.begin() + i); 
			light.erase(light.begin() + i); 
		}
	}
}

void TrafficLane::spawnEnemy() // 
{

}

void TrafficLane::renderObstacle(sf::RenderTarget& target)
{
	for (int i = 0; i < obs.size(); i++)
		obs[i]->render(target);
}

void TrafficLane::renderTrafficLight(sf::RenderTarget& target)
{
	for (int i = 0; i < trafficLight.size(); i++)
		trafficLight[i]->render(target);
}

void TrafficLane::render(sf::RenderTarget& target)
{
	renderObstacle(target);
	renderTrafficLight(target);
}

bool TrafficLane::Collision(sf::FloatRect coll)
{
	for (auto& i : obs)
	{
		if (i->getShape().getGlobalBounds().intersects(coll))
		{
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
