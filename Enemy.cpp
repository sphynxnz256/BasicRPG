#include "stdafx.h"
#include "Enemy.h"

/*the enemy holds the enemies state*/

//private functions	
void Enemy::initVariables()
{
	hpMax = 10.f;
	hpCurrent = hpMax;
}

void Enemy::initTexture()
{
	if (!this->texture.loadFromFile("textures/slime.png"))
	{
		std::cout << "ERROR::ENEMY::INITSPRITE::Failed to load " << "textures/slime.png" << "!/n";
	}
}

void Enemy::initSprite()
{
	this->sprite.setTexture(this->texture);
	this->sprite.setScale(0.5f, 0.5f);
}

//constructor
Enemy::Enemy()
{	
	this->initVariables();
	this->initTexture();
	this->initSprite();
}

//deconstructor
Enemy::~Enemy()
{
}

//getters
const sf::Vector2f Enemy::getPosition() const
{
	return sprite.getPosition();
}

const sf::FloatRect Enemy::getGlobalBounds() const
{
	return sprite.getGlobalBounds();
}

const int Enemy::getHpMax() const
{
	return this->hpMax;
}

const int Enemy::getHpCurrent() const
{
	return this->hpCurrent;
}

const sf::Sprite& Enemy::getSprite() const
{
	return this->sprite;
}

//setters
void Enemy::setPosition(const float x, const float y)
{
	this->sprite.setPosition(x, y);
}

void Enemy::takeDamage(const float damage_taken)
{
	this->hpCurrent -= damage_taken;
	if (hpCurrent < 0)
	{
		hpCurrent = 0;
	}
}

//public functions
void Enemy::update()
{
}

void Enemy::render(sf::RenderTarget& target)
{
	target.draw(this->sprite);
}
