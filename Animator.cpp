#include "stdafx.h"
#include "Animator.h"
#include "Enemy.h"

/*the animator class plays animations*/

//private initation functions
void Animator::initFlags()
{
	this->firstFrame = true;
	this->animationEnd = false;
	this->timeElapsed = 0.f;
	this->deathAnimationSpeed = 10.f;
	this->frameDuration = 0.05f;
}

void Animator::initSmokeTexture()
{
	if (!this->smokeTextureSheet.loadFromFile("textures/smoke_sheet.png"))
	{
		std::cout << "ERROR::ANIMATOR::INITSMOKETEXTURE::Couldn't load smoke_sheet.png\n";
	}
}

void Animator::initSmokeSprite()
{
	this->smokeSprite.setTexture(this->smokeTextureSheet);
	this->currentFrame = sf::IntRect(0, 0, 150, 150);
	this->smokeSprite.setTextureRect(sf::IntRect(0, 0, 150, 150));
	this->smokeSprite.setScale(2.f, 2.f);
}

void Animator::updateDeathAnimation()
{	
	if (this->firstFrame)
	{
		//resets the clock since its been running a while
		this->firstFrame = false;
		this->deltaTime = this->dtClock.restart().asSeconds();
	}
	else if(this->deathSprite->getScale().x > 0.001)
	{
		//death animation. shrinks the enemy to nothing
		this->deltaTime = this->dtClock.restart().asSeconds();

		this->currentScale = this->deathSprite->getScale();
		this->newScale = this->currentScale - this->currentScale 
			* this->deltaTime * this->deathAnimationSpeed;
		this->deathSprite->setScale(this->newScale);
	}
	else
	{
		this->deathSprite->setScale(0.f, 0.f);
		this->animationEnd = true;
	}
}

void Animator::updateEscapeAnimation()
{
	if (this->firstFrame)
	{
		//resets the clock since its been running a while
		this->firstFrame = false;
		this->deltaTime = this->dtClock.restart().asSeconds();
	}
	else
	{
		//plays a puff of smoke when enemy escapes
		this->deltaTime = this->dtClock.restart().asSeconds();
		this->timeElapsed += this->deltaTime;

		if(this->timeElapsed >= this->frameDuration)
		{
			this->timeElapsed = 0.f;
			if (this->currentFrame.left < 1050)
			{
				this->currentFrame.left += 150;
				this->smokeSprite.setTextureRect(this->currentFrame);
			}
			else
			{
				this->animationEnd = true;
				this->timeElapsed = 0.f;

			}
		}
	}
}

//constructor
Animator::Animator()
{
	this->initFlags();
	this->initSmokeTexture();
	this->initSmokeSprite();
}

//deconstructor
Animator::~Animator()
{
}

//getters
const sf::FloatRect& Animator::getDeathSpriteGlobalBounds() const
{
		return this->deathSprite->getGlobalBounds();
}

const sf::FloatRect& Animator::getSmokeSpriteGlobalBounds() const
{
	return this->smokeSprite.getGlobalBounds();
}

const bool Animator::getAnimationEnd() const
{
	return this->animationEnd;
}

//setters
void Animator::setDeathSpritePosition(const float x, const float y)
{
	this->deathSprite->setPosition(x, y);
}

void Animator::setSmokeSpritePosition(const float x, const float y)
{
	this->smokeSprite.setPosition(x, y);
}

void Animator::setSprite(sf::Sprite* sprite)
{
	this->deathSprite = sprite;
}

//public functions
void Animator::resetAnimator()
{
	this->animationEnd = false;
	this->firstFrame = true;
}

void Animator::update(std::string update_this)
{
	if(update_this == "death")
	{
		this->updateDeathAnimation();
	}

	if(update_this == "escape")
	{
		this->updateEscapeAnimation();
	}
}

void Animator::render(sf::RenderTarget& target, bool play_death, bool play_escape)
{
	if(play_death)
	{
		target.draw(*this->deathSprite);
	}

	if(play_escape)
	{
		target.draw(this->smokeSprite);
	}
}
