#pragma once

class Boss
{
private:
	//private variables
	sf::Sprite sprite;
	sf::Texture texture;

	float hpMax;
	float hpCurrent;
	std::pair<float, float> spriteScale;

	std::pair<int, int> coinsToDrop;

	//private functions
	void initVariables();
	void initTextures();
	void initSprite();

public:
	//constructor
	Boss();
	//deconstructor
	~Boss();

	//getters
	const sf::Vector2f getPosition() const;
	const sf::FloatRect getGlobalBounds() const;
	const float getHpMax() const;
	const float getHpCurrent() const;
	sf::Sprite* getSprite();
	const std::pair<int, int> getCoinsToDrop() const;

	//setters
	void setPosition(const float x, const float y);
	void takeDamage(const float damage_taken);

	//public functions
	void resetBoss();

	void render(sf::RenderTarget& target);
};

