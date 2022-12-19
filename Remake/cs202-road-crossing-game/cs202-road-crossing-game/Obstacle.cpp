#include "Obstacle.h"

sf::RectangleShape Obstacle::getShape()
{
    return shape; 
}

void Obstacle::update()
{
    shape.move(speed.x, speed.y); 
}

void Obstacle::setSpeed(float x, float y)
{
    speed.x = x; 
    speed.y = y; 
}

void Obstacle::render(sf::RenderTarget& target)
{
    target.draw(shape);
}
