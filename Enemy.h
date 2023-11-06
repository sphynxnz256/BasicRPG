#pragma once

#include "RNG.h"

class Enemy
{
private:
	//private variables
	sf::Sprite sprite;
	sf::Texture texture;
	RNG& rng;
	std::unordered_map<int, std::string> textureAddressMap;
	std::unordered_map<int, std::shared_ptr<sf::Texture>> textureMap;
	int textureNumber;

	float hpMax;
	float hpCurrent;

	//private functions
	void initVariables();
	void initTextures();
	void initSprite();

public:
	//constructor
	Enemy(RNG& rng);
	//deconstructor
	~Enemy();

	//getters
	const sf::Vector2f getPosition() const;
	const sf::FloatRect getGlobalBounds() const;
	const int getHpMax() const;
	const int getHpCurrent() const;
	const sf::Sprite& getSprite() const;

	//setters
	void setPosition(const float x, const float y);
	void takeDamage(const float damage_taken);
	
	//public functions
	void resetEnemy();
	void dropCoins();

	void update();
	void render(sf::RenderTarget& target);
};

