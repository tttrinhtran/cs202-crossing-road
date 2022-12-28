#include "Obstacle.h"

sf::RectangleShape Obstacle::getShape()
{
    return shape; 
}

void Obstacle::update()
{
    shape.move(speed.x, speed.y); 
}

void Obstacle::setPosition(sf::Vector2f pos)
{
    shape.setPosition(pos); 
}

void Obstacle::setSpeed(float x, float y)
{
    speed.x = x; 
    speed.y = y; 
}

void Obstacle::render(sf::RenderWindow& window)
{
    window.draw(shape);
}

void Obstacle::setSize(sf::Vector2f size)
{
    shape.setSize(size);
}

void Obstacle::makeSound()
{
    sound.setLoop(0);
    sound.play(); 
    sf::sleep(sf::seconds(1.5f)); 
}
