#pragma once
class Enemy
{
private:
	//private variables
	sf::Sprite sprite;
	sf::Texture texture;

	float hpMax;
	float hpCurrent;

	//private functions
	void initVariables();
	void initTexture();
	void initSprite();

public:
	//constructor
	Enemy();
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

	void update();
	void render(sf::RenderTarget& target);
};

