#include "stdafx.h"
#include "Animator.h"
#include "Enemy.h"

/*the animator class plays animations*/

//private initation functions
void Animator::initFlags()
{
	this->firstFrame = true;
	this->animationEnd = false;
}

void Animator::updateAnimation()
{	
	if (this->firstFrame)
	{
		/*a hack to fix first frame issue where first calculation
		of dt is too large*/
		this->firstFrame = false;
		this->dt = dtClock.restart().asSeconds();
	}
	else if(this->sprite->getScale().x > 0.001)
	{
		/*death animation. shrinks the enemy to nothing*/
		this->speed = 10.f;

		this->dt = dtClock.restart().asSeconds();
		this->currentScale = this->sprite->getScale();
		this->newScale = currentScale - currentScale * dt * speed;

		this->sprite->setScale(newScale);
	}
	else
	{
		this->sprite->setScale(0.f, 0.f);
		this->animationEnd = true;
	}
}

//constructor
Animator::Animator()
{
	this->initFlags();
}

//deconstructor
Animator::~Animator()
{
}

//getters
const sf::FloatRect& Animator::getGlobalBounds() const
{
		return this->sprite->getGlobalBounds();
}

const bool Animator::getAnimationEnd() const
{
	return this->animationEnd;
}

//setters
void Animator::setPosition(float x, float y)
{
	this->sprite->setPosition(x, y);
}

void Animator::setSprite(sf::Sprite* sprite)
{
	this->sprite = sprite;
}

//public functions
void Animator::resetAnimator()
{
	this->animationEnd = false;
	this->firstFrame = true;
}

void Animator::update()
{
	this->updateAnimation();
}

void Animator::render(sf::RenderTarget& target)
{
	target.draw(*this->sprite);
}
