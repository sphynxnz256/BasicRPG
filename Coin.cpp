#include "stdafx.h"
#include "Coin.h"

//private functions
void Coin::initSprite(const sf::Vector2u& target_size, std::shared_ptr<sf::Texture> shared_texture)
{
	this->sprite.setTexture(*shared_texture);
	this->sprite.setScale(0.1f, 0.1f);
	this->sprite.setPosition(static_cast<float>(this->rng.generateRandomNum(20, target_size.x - 20)),
		static_cast<float>(target_size.y) - 150.f);
}

//constructor
Coin::Coin(RNG& rng, const sf::Vector2u& target_size, std::shared_ptr<sf::Texture> shared_texture) 
	: rng(rng), texture(shared_texture)
{
	this->initSprite(target_size, shared_texture);
	this->coinValue = 1;
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

void Coin::render(sf::RenderTarget& target)
{
	target.draw(sprite);
}
