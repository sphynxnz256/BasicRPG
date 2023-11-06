#include "stdafx.h"
#include "Player.h"

/*the player class holds the players state*/

//private functions
void Player::initVariables()
{
	this->damage = 1.f;
	this->attackCDMax = 10.f;
	this->attackCD = attackCDMax;
	this->coins = 0.f;
}

//constructor
Player::Player()
{
	this->initVariables();
}

//deconstructor
Player::~Player()
{
}

//getters
const float Player::getDamage() const
{
	return this->damage;
}

const float Player::getCoins() const
{
	return this->coins;
}

void Player::addDamage(float damage_to_add)
{
	this->damage += damage_to_add;
}

void Player::addCoins(float coins_to_add)
{
	this->coins += coins_to_add;
}

//public functions
void Player::update()
{
}
