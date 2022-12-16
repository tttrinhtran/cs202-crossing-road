#include "Player.h"

void Player::initSanta()
{
	texture.loadFromFile("pic/santa.png"); 
	sprite.setTexture(texture); 
	sprite.setScale(0.4f, 0.4f);
}

void Player::initVariables()
{
	movementSpeed = 5.f; 
	hpMax = 3; 
	hp = hpMax; 
}

Player::Player()
{
	initSanta();
	initVariables();
}

Player::~Player()
{

}

const int& Player::getHP() const
{
	// TODO: insert return statement here
	return hp; 
}

const int& Player::getHPMax() const
{
	// TODO: insert return statement here
	return hpMax;
}

void Player::updateInput()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		sprite.move(-movementSpeed, 0.f);
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		sprite.move(movementSpeed, 0.f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		sprite.move(0.f, movementSpeed);
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		sprite.move(0.f, -movementSpeed);
}

void Player::updateWindowBoundsCollision(const sf::RenderTarget& target)
{
	//Left 
	if (sprite.getGlobalBounds().left <= 0.f)
		sprite.setPosition(0.f, sprite.getGlobalBounds().top); 

	//Right
	if (sprite.getGlobalBounds().left + sprite.getGlobalBounds().width >= target.getSize().x)
		sprite.setPosition(target.getSize().x - sprite.getGlobalBounds().width, sprite.getGlobalBounds().top); 

	//Top
	if (sprite.getGlobalBounds().top <= 0.f)
		sprite.setPosition(sprite.getGlobalBounds().left, 0.f);

	//Bottom 
	if (sprite.getGlobalBounds().top + sprite.getGlobalBounds().height >= target.getSize().y)
		sprite.setPosition(sprite.getGlobalBounds().left, target.getSize().y - sprite.getGlobalBounds().height);
}

void Player::update(sf::RenderTarget& target)
{
	updateInput();
	updateWindowBoundsCollision(target);
}

void Player::render(sf::RenderTarget& target)
{
	target.draw(sprite);
}
