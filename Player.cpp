#include "stdafx.h"
#include "Player.h"

/*the player class holds the players state*/

//private functions
void Player::initVariables()
{
	this->damage = 1.f;
	this->attackCDMax = 10.f;
	this->attackCD = attackCDMax;
	this->coins = 0;
	this->upgradeCost = 10;
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

const int Player::getCoins() const
{
	return this->coins;
}

const int Player::getUpgradeCost() const
{
	return this->upgradeCost;
}

void Player::upgradeDamage()
{
	this->damage *= 2.f;
	this->coins -= upgradeCost;
	this->upgradeCost *= 2;
}

void Player::addCoins(int coins_to_add)
{
	this->coins += coins_to_add;
}

//public functions
bool Player::canUpgrade()
{
	if (this->coins >= this->upgradeCost)
	{
		return true;
	}
	return false;
}
