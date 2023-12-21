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

	sf::Sprite coinSprite;
	sf::Vector2f coinStart;
	sf::Vector2f coinEnd;
	sf::Vector2f coinControlPoint;
	float coinAnimationSpeed;
	float coinDistance;
	bool coinAnimationEnded;
	bool coinFirstFrame;

	//private initation functions
	void initVariables();
	void initSmokeTexture();
	void initSmokeSprite();
	void initCoinAnimation(sf::Texture& coin_texture); 

	//private update functions
	void updateDeathAnimation();
	void updateEscapeAnimation();
	void updateCoinAnimation();

	//private render functions
	void renderDeathAnimation(sf::RenderTarget& target, bool play_death);
	void renderEscapeAnimation(sf::RenderTarget& target, bool play_escape);
	void renderCoinAnimation(sf::RenderTarget& target, bool play_coin);

public:
	//constructor
	Animator(sf::Texture& coin_texture);
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
	//void startDeathAnimation();
	//void startEscapeAnimation();
	void startCoinAnimation(sf::Vector2f coin_start, sf::Vector2f coin_end);
	void resetAnimator();

	void update(std::string update_this); 
	void render(sf::RenderTarget& target, bool play_death, bool play_escape,
		bool play_coin);
};

