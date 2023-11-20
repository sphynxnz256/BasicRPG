#include "stdafx.h"
#include "Boss.h"

//private functions
void Boss::initVariables()
{
	this->hpMax = 250;
	this->hpCurrent = this->hpMax;
	this->coinsToDrop = std::make_pair(10, 20);
	this->spriteScale = std::make_pair(0.5f, 0.5f);
}

void Boss::initTextures()
{
	if (!this->texture.loadFromFile("textures/enemies/jellyfish.png"))
	{
		std::cout << "ERROR::BOSS::INITTEXTURE::Failed to load jellyfish.png\n";
	}
}

void Boss::initSprite()
{
	this->sprite.setTexture(this->texture);
	this->sprite.setScale(spriteScale.first, spriteScale.second);
}
//constructor
Boss::Boss()
{
	this->initVariables();
	this->initTextures();
	this->initSprite();
}

//deconstructor
Boss::~Boss()
{
}

//getters
const sf::Vector2f Boss::getPosition() const
{
	return sprite.getPosition(); 
}

const sf::FloatRect Boss::getGlobalBounds() const
{
	return sprite.getGlobalBounds(); 
}

const float Boss::getHpMax() const
{
	return this->hpMax; 
}

const float Boss::getHpCurrent() const
{
	return this->hpCurrent;
}

sf::Sprite* Boss::getSprite()
{
	return &this->sprite;
}

const std::pair<int, int> Boss::getCoinsToDrop() const
{
	return this->coinsToDrop;
}

//setters
void Boss::setPosition(const float x, const float y)
{
	this->sprite.setPosition(x, y);
}

void Boss::takeDamage(const float damage_taken)
{
	this->hpCurrent -= damage_taken; 
	if (this->hpCurrent < 0)
	{
		this->hpCurrent = 0;
	}
}

//public functions
void Boss::resetBoss()
{
	this->hpCurrent = this->hpMax;
	this->sprite.setScale(spriteScale.first, spriteScale.second);
}

void Boss::render(sf::RenderTarget& target)
{
	target.draw(this->sprite);
}


