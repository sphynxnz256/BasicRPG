#pragma once
class Animator
{
private:
	//private variables
	sf::Sprite* deathSprite;

	sf::Vector2f currentScale;
	sf::Vector2f targetScale;
	sf::Vector2f newScale;

	sf::Clock dtClock;
	float timeElapsed;
	float frameDuration;
	float deltaTime;

	bool firstFrame;
	bool animationEnd;
	float deathAnimationSpeed;
		

	sf::Texture smokeTextureSheet;
	sf::Sprite smokeSprite;
	sf::IntRect currentFrame;

	//private initation functions
	void initFlags();
	void initSmokeTexture();
	void initSmokeSprite();


	//private update functions
	void updateDeathAnimation();
	void updateEscapeAnimation();

	//private render functions
	void renderDeathAnimation(sf::RenderTarget& target, bool play_death);
	void renderEscapeAnimation(sf::RenderTarget& target, bool play_escape);

public:
	//constructor
	Animator();
	//deconstructor
	~Animator();

	//getters
	const sf::FloatRect& getDeathSpriteGlobalBounds() const;
	const sf::FloatRect& getSmokeSpriteGlobalBounds() const;
	const bool getAnimationEnd() const;

	//setters
	void setDeathSpritePosition(const float x, const float y);
	void setSmokeSpritePosition(const float x, const float y);
	void setSprite(sf::Sprite* sprite);

	//public functions
	void resetAnimator();

	void update(std::string update_this); 
	void render(sf::RenderTarget& target, bool play_death, bool play_escape);
};

