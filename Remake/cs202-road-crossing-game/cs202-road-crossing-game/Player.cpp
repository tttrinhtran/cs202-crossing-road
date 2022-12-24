#include "Player.h"

void Player::initVariables()
{
    texturebg.loadFromFile("pic/levelbackground.png");
    bg.setTexture(texturebg);
	shape.setSize(sf::Vector2f(100.0f, 100.0f));
	shape.setPosition(sf::Vector2f(600, 600));
	texture.loadFromFile("pic/santa.png");
	shape.setTexture(&texture);
	texture.setSmooth(true);
}

Player::Player()
{
	initVariables();
}

Player::~Player() {}

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
	if (clock.getElapsedTime() > time)
	{
		updateInput();
		updateWindowBoundsCollision(window);
		clock.restart();
	}
}

void Player::render(sf::RenderWindow& window)
{
    window.draw(bg);
	window.draw(shape);
}

void Player::updateWindowBoundsCollision(const sf::RenderWindow& window)
{
	// Left 
	if (this->shape.getGlobalBounds().left <= 0.f)
		this->shape.setPosition(0.f, this->shape.getGlobalBounds().top);
	//Right
	if (this->shape.getGlobalBounds().left + this->shape.getGlobalBounds().width >= window.getSize().x)
		this->shape.setPosition(window.getSize().x - this->shape.getGlobalBounds().width, this->shape.getGlobalBounds().top);

	//Top
	if (this->shape.getGlobalBounds().top <= 0.f)
		this->shape.setPosition(this->shape.getGlobalBounds().left, 0.f);
	//Bottom
	if (this->shape.getGlobalBounds().top + this->shape.getGlobalBounds().height >= window.getSize().y)
		this->shape.setPosition(this->shape.getGlobalBounds().left, window.getSize().y - this->shape.getGlobalBounds().height);
}
