#include "stdafx.h"
#include "Player.h"

/*the player class holds the players state*/

//private functions
void Player::initVariables()
{
	this->damage = 1.f;
	this->attackCDMax = 10.f;
	this->attackCD = attackCDMax;
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

//public functions
void Player::update()
{
}
