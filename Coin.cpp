#include "stdafx.h"
#include "Coin.h"

//private functions
void Coin::initVariables(const sf::Vector2u& target_size)
{	
	this->coinValue = 1;
	this->endPoint = sf::Vector2f(static_cast<float>(this->rng.generateRandomNum(20, 
		target_size.x - sprite.getGlobalBounds().width - 20)),
		static_cast<float>(target_size.y) - 150.f);
}

void Coin::initSprite(std::shared_ptr<sf::Texture> shared_texture)
{
	this->sprite.setTexture(*shared_texture);
	this->sprite.setScale(0.1f, 0.1f);
	this->sprite.setPosition(sf::Vector2f(this->startPoint.x - this->sprite.getGlobalBounds().width / 2, 
		this->startPoint.y - this->sprite.getGlobalBounds().height / 2));
}

void Coin::initControlPoint()
{
	//set the control point so its on the same side as the coin ends up on
	if (this->endPoint.x > 400.f)
	{
		this->controlPoint = sf::Vector2f(600.f, 200.f);
	}
	else
	{
		this->controlPoint = sf::Vector2f(200.f, 200.f);
	}
}

void Coin::initAnimationSpeed()
{
	//smooth the speed out relative to the center
	if (this->endPoint.x < 100.f || this->endPoint.x > 700.f)
	{
		this->animationSpeed = 600.f;
	}
	else if (this->endPoint.x < 200.f || this->endPoint.x > 600.f)
	{
		this->animationSpeed = 500.f;
	}
	else if (this->endPoint.x < 300.f || this->endPoint.x > 500.f)
	{
		this->animationSpeed = 400.f;
	}
	else
	{
		this->animationSpeed = 300.f;
	}
}

void Coin::initDistanceToTravel()
{
	//calculate distance
	this->distanceToTravel = std::sqrt((this->endPoint.x - this->startPoint.x) *
		(this->endPoint.x - this->startPoint.x) +
		(this->endPoint.y - this->startPoint.y) *
		(this->endPoint.y - this->startPoint.y));
}

void Coin::initAnimation()
{
	this->animationEnded = false;
	this->deltaTime = this->dtClock.restart().asSeconds();
	this->timeElapsed = 0.f;
}

void Coin::updateLocation()
{
	if (!this->animationEnded)
	{
		//plays animation of coin dropping from killed enemy
		this->deltaTime = this->dtClock.restart().asSeconds();
		this->timeElapsed += this->deltaTime;

		//calculate progress based on speed
		float progress = (this->timeElapsed * this->animationSpeed) /
			this->distanceToTravel;


		//check if animation is finished
		if (progress >= 1.f)
		{
			progress = 1.f;
			this->animationEnded = true;
		}

		//calc bezier interpilation
		sf::Vector2f position = (1 - progress) * (1 - progress) * this->startPoint +
			2 * (1 - progress) * progress * this->controlPoint +
			progress * progress * this->endPoint;
		this->sprite.setPosition(position);
	}
}

//constructor
Coin::Coin(RNG& rng, const sf::Vector2u& target_size, std::shared_ptr<sf::Texture> shared_texture,
	sf::Vector2f start_point)
	: rng(rng), texture(shared_texture), startPoint(start_point)
{
	this->initSprite(shared_texture);
	this->initVariables(target_size);
	this->initControlPoint();
	this->initAnimationSpeed();
	this->initDistanceToTravel();
	this->initAnimation();
	
}

//getters
int Coin::getCoinValue()
{
	return coinValue;
}

sf::Vector2f Coin::getPosition()
{
	return this->sprite.getPosition();
}

//public functions
bool Coin::isMouseOver(const sf::Vector2f& mouse_pos)
{
	return sprite.getGlobalBounds().contains(mouse_pos);
}

bool Coin::checkPosition()
{
	if (this->sprite.getPosition() == this->endPoint)
	{
		return true;
	}
	return false;
}

void Coin::update()
{
	this->updateLocation();
}

void Coin::render(sf::RenderTarget& target)
{
	target.draw(sprite);
}
