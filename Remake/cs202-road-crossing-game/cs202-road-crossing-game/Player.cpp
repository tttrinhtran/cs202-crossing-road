#include "Player.h"

void Player::initVariables()
{
	texture.loadFromFile("pic/santa.png");
	shape.setTexture(&texture); 
	shape.setScale(0.4f, 0.4f); 
	shape.setPosition(sf::Vector2f(600, 600));
	texture.setSmooth(true);
}

Player::Player()
{
	initVariables();
}

Player::~Player(){}

sf::RectangleShape Player::getshape()
{
	return shape; 
}

void Player::reset()
{
	shape.setPosition(600, 600); 
}

void Player::updateInput()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		shape.move(-movementSpeed, 0.f);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		shape.move(movementSpeed, 0.f);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		shape.move(0.f, movementSpeed);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		shape.move(0.f, -movementSpeed);
	}
}

void Player::update(sf::RenderWindow& window)
{
	updateInput(); 
	updateWindowBoundsCollision(window);
}

void Player::render(sf::RenderTarget& target)
{
	target.draw(shape);
}

void Player::updateWindowBoundsCollision(const sf::RenderTarget& target)
{
	// Left 
	if (this->shape.getGlobalBounds().left <= 0.f)
		this->shape.setPosition(0.f, this->shape.getGlobalBounds().top);
	//Right
	if (this->shape.getGlobalBounds().left + this->shape.getGlobalBounds().width >= target.getSize().x)
		this->shape.setPosition(target.getSize().x - this->shape.getGlobalBounds().width, this->shape.getGlobalBounds().top);

	//Top
	if (this->shape.getGlobalBounds().top <= 0.f)
		this->shape.setPosition(this->shape.getGlobalBounds().left, 0.f);
	//Bottom
	if (this->shape.getGlobalBounds().top + this->shape.getGlobalBounds().height >= target.getSize().y)
		this->shape.setPosition(this->shape.getGlobalBounds().left, target.getSize().y - this->shape.getGlobalBounds().height);
}
