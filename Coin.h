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

	//private functions
	void initVariables();
	void initSprite(const sf::Vector2u& target_size, std::shared_ptr<sf::Texture> shared_texture);

public:
	Coin(RNG& rng, const sf::Vector2u& target_size, std::shared_ptr<sf::Texture> shared_texture);

	//getters
	sf::FloatRect getGlobalBounds();
	sf::Vector2f getPosition();
	int getCoinValue();

	//public functions
	bool isMouseOver(const sf::Vector2f& mouse_pos);
	bool isClicked(const sf::Vector2f& mouse_pos);

	void render(sf::RenderTarget& target);
};
