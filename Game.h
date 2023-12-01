#pragma once

#include "Enemy.h"
#include "Player.h"
#include "Boss.h"
#include "UI.h"
#include "Animator.h"
#include "RNG.h"
#include "Coin.h"

class Game
{
private:
	//private variables
	sf::RenderWindow window;
	sf::Event event;

	Player* player;
	Enemy* enemy;
	Boss* boss;
	UI* ui;

	Animator* animator;
	bool playDeathAnimation;
	bool playEscapeAnimation;
	bool playCoinAnimation;

	RNG& rng;

	bool mouseHeld;
	sf::Vector2f mousePosition;

	sf::Texture backgroundTexture;
	sf::Sprite background;

	int killCounter;
	bool bossActive;
	int coinsToDrop;
	std::vector<Coin> coinsVector;
	std::shared_ptr<sf::Texture> sharedCoinTexture;
	sf::Vector2f coinStart;
	sf::Vector2f coinEnd;

	//private initiation functions
	void initWindow();
	void initPlayer();
	void initEnemy();
	void initBoss();
	void initAnimator();
	void initBackground();
	void initCoins();
	void initUI();

	//private update functions
	void polledEvents();
	void updateCombat();
	void updateUI();
	void updateAnimator();
	void updateCoins();

	//private rendering functions
	void renderEnemy();
	void renderBoss();
	void renderAnimator();
	void renderBackground();
	void renderCoins();
	void renderUI();

	//other private functions
	void bossTakeDamage();
	void enemyTakeDamage();
	void bossEscape();
	void enemyDeath();
	void dropCoins(std::pair<int, int> coins_to_drop, sf::Vector2f coin_start);
	void setUpBoss();
	void bossDeath();
	void upgradeDamage();
	void retreat();

public:
	//constructor
	Game(RNG& rng);
	//deconstuctor
	~Game();

	//getters
	const sf::RenderWindow& getWindow() const;

	//public functions	
	void update();
	void render();
};

