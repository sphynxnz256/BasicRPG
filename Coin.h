#pragma once

#include "RNG.h"

class Coin
{
private:
	//private variables
	std::shared_ptr<sf::Texture> texture;
	sf::Sprite sprite;
	RNG& rng;
	int coinValue;

	sf::Clock dtClock;
	float timeElapsed;
	float frameDuration;
	float deltaTime;

	sf::Vector2f startPoint;
	sf::Vector2f endPoint;
	sf::Vector2f controlPoint;
	float animationSpeed;
	float distanceToTravel;
	bool animationEnded;
	bool animationFirstFrame;

	//private functions
	void initVariables(const sf::Vector2u& target_size);
	void initSprite(std::shared_ptr<sf::Texture> shared_texture);
	void initControlPoint();
	void initAnimationSpeed();
	void initDistanceToTravel();
	void initAnimation();
	void updateLocation();

public:
	//constructor
	Coin(RNG& rng, const sf::Vector2u& target_size, std::shared_ptr<sf::Texture> shared_texture,
		sf::Vector2f start_point);

	//getters
	int getCoinValue();
	sf::Vector2f getPosition();

	//public functions
	bool isMouseOver(const sf::Vector2f& mouse_pos);
	bool checkPosition();

	void update();
	void render(sf::RenderTarget& target);
};

