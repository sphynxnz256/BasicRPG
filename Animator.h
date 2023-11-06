#pragma once
class Animator
{
private:
	//private variables
	sf::Sprite sprite;

	sf::Vector2f currentScale;
	sf::Vector2f targetScale;
	sf::Vector2f newScale;

	sf::Clock dtClock;
	float dt;

	bool firstFrame;
	float speed;

	//private initation functions
	void initSrite(sf::Sprite sprite);
	void initFlags();

	//private update functions
	void updateAnimation();

public:
	//constructor
	Animator(sf::Sprite sprite);
	//deconstructor
	~Animator();

	//getters
	const sf::FloatRect& getGlobalBounds() const;

	//setters
	void setPosition(float x, float y);

	//public functions
	void update();
	void render(sf::RenderTarget& target);
};

