#include "stdafx.h"
#include "Animator.h"
#include "Enemy.h"

/*the animator class plays animations*/

//private initation functions
void Animator::initVariables()
{
	this->firstFrame = true;
	this->animationEnd = false;
	this->coinAnimationEnded = true;
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

void Animator::initCoinAnimation(sf::Texture& coin_texture)
{
	this->coinSprite.setTexture(coin_texture);
	this->coinSprite.setScale(0.1f, 0.1f);
	this->coinStart = sf::Vector2f(0.f, 0.f);
	this->coinEnd = sf::Vector2f(0.f, 0.f);
	this->coinControlPoint = sf::Vector2f(300.f, 50.f);
	this->coinAnimationSpeed = 400.f;
	this->coinDistance = 0.f;
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
				this->currentFrame = sf::IntRect(0, 0, 150, 150);

			}
		}
	}
}

void Animator::updateCoinAnimation()
{
	if (!this->coinAnimationEnded)
	{
		if (this->firstFrame)
		{
			this->deltaTime = this->dtClock.restart().asSeconds();
			this->firstFrame = false;
		}
		else
		{
			//plays animation of coin dropping from killed enemy
			this->deltaTime = this->dtClock.restart().asSeconds();
			this->timeElapsed += this->deltaTime;

			//calculate progress based on speed
			float progress = (this->timeElapsed * this->coinAnimationSpeed) /
				this->coinDistance;

			


			if (progress >= 1.f)
			{
				progress = 1.f;
				this->coinAnimationEnded = true;
				this->firstFrame = true;
			}

			//cubic bezier curvce interpolation
			float u = 1.f - progress;
			float uu = u * u;
			float uuu = uu * u;
			float tt = progress * progress;
			float ttt = tt * progress;

			sf::Vector2f position = uuu * this->coinStart +
				3.f * uu * u *
				this->coinControlPoint + 3.f * u * tt * this->coinEnd +
				ttt * this->coinEnd;

			this->coinSprite.setPosition(position);
			//std::cout << "current pos: " << position.x << ", " << position.y << '\n';
		}
	}
}

void Animator::renderDeathAnimation(sf::RenderTarget& target, bool play_death)
{
	if (play_death)
	{
		target.draw(*this->deathSprite);
	}
}

void Animator::renderEscapeAnimation(sf::RenderTarget& target, bool play_escape)
{
	if (play_escape)
	{
		target.draw(this->smokeSprite);
	}
}

void Animator::renderCoinAnimation(sf::RenderTarget& target, bool play_coin)
{
	if (play_coin)
	{
		target.draw(this->coinSprite);
	}
}

//constructor
Animator::Animator(sf::Texture& coin_texture)
{
	this->initVariables();
	this->initSmokeTexture();
	this->initSmokeSprite();
	this->initCoinAnimation(coin_texture);
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

void Animator::startCoinAnimation(sf::Vector2f coin_start, sf::Vector2f coin_end)
{
	//resets the clock since its been running a while
	this->deltaTime = this->dtClock.restart().asSeconds();

	this->coinStart = coin_start;
	this->coinEnd = coin_end;

	//calculate distance
	this->coinDistance = std::sqrt((this->coinEnd.x - this->coinStart.x) *
		(this->coinEnd.x - this->coinStart.x) +
		(this->coinEnd.y - this->coinStart.y) *
		(this->coinEnd.y - this->coinStart.y));

	this->coinAnimationEnded = false;
	this->timeElapsed = 0.f;
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

	if (update_this == "coin")
	{
		this->updateCoinAnimation();
	}
}

void Animator::render(sf::RenderTarget& target, bool play_death, bool play_escape,
	bool play_coin)
{
	this->renderDeathAnimation(target, play_death);
	this->renderEscapeAnimation(target, play_escape);
	this->renderCoinAnimation(target, play_coin);
}
