#include "stdafx.h"
#include "Enemy.h"

/*the enemy holds the enemies state*/

//private functions	
void Enemy::initVariables()
{
	this->hpMax = 10.f;
	this->hpCurrent = this->hpMax;
	this->coinsToDrop = std::make_pair(1, 2);
	this->spriteScale = std::make_pair(0.5f, 0.5f);
}

void Enemy::initTextures()
{
	//store addresses of textures in map	
	this->textureAddressMap[1] = "textures/slime.png";
	this->textureAddressMap[2] = "textures/crab.png";
	this->textureAddressMap[3] = "textures/rat.png";
	this->textureAddressMap[4] = "textures/raven.png";
	this->textureAddressMap[5] = "textures/mushroom monster.png";
	this->textureAddressMap[6] = "textures/spider.png";
	this->textureAddressMap[7] = "textures/wasp.png";
	this->textureAddressMap[8] = "textures/wolf.png";
	this->textureAddressMap[9] = "textures/harpy.png";
	this->textureAddressMap[10] = "textures/horned rabbit.png";

	//preload textures and store them in a map
	for (const auto& pair : textureAddressMap)
	{
		int unique_number = pair.first;
		const std::string& texture_address = pair.second;

		std::shared_ptr<sf::Texture> texture = std::make_shared<sf::Texture>();
		if (texture->loadFromFile(texture_address))
		{
			this->textureMap[unique_number] = texture;
		}
		else
		{
			std::cout << "ERROR::ENEMY::INITTEXTURE::Failed to load " << texture_address << '\n';
		}
	}

	this->texture = *this->textureMap[rng.generateRandomNum(1, 10)];
}

void Enemy::initSprite()
{
	this->sprite.setTexture(this->texture);
	this->sprite.setScale(spriteScale.first, spriteScale.second);
}

//constructor
Enemy::Enemy(RNG& rng) : rng(rng)
{	
	this->initVariables();
	this->initTextures();
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

const float Enemy::getHpMax() const
{
	return this->hpMax;
}

const float Enemy::getHpCurrent() const
{
	return this->hpCurrent;
}

sf::Sprite* Enemy::getSprite()
{
	return &this->sprite;
}

const std::pair<int, int> Enemy::getCoinsToDrop() const
{
	return this->coinsToDrop;
}

//setters
void Enemy::setPosition(const float x, const float y)
{
	this->sprite.setPosition(x, y);
}

void Enemy::takeDamage(const float damage_taken)
{
	this->hpCurrent -= damage_taken;
	if (this->hpCurrent < 0)
	{
		this->hpCurrent = 0;
	}
}

void Enemy::resetEnemy()
{
	this->hpCurrent = this->hpMax;
	this->texture = *this->textureMap[rng.generateRandomNum(1, 10)];
	this->sprite.setTexture(this->texture);
	this->sprite.setScale(spriteScale.first, spriteScale.second);
}

void Enemy::render(sf::RenderTarget& target)
{
	target.draw(this->sprite);
}
