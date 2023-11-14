#pragma once

#include "Enemy.h"
#include "Player.h"
#include "Boss.h"
#include "UI.h"
#include "Animator.h"
#include "RNG.h"

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
	bool playAnimation;
	RNG& rng;

	bool mouseHeld;
	sf::Vector2f mousePosition;

	sf::Texture backgroundTexture;
	sf::Sprite background;

	int killCounter;
	bool bossActive;

	//private initiation functions
	void initWindow();
	void initPlayer();
	void initEnemy();
	void initBoss();
	void initAnimator();
	void initBackground();
	void initUI();

	//private update functions
	void polledEvents();
	void updateCombat();
	void updateUI();
	void updateAnimator();

	//private rendering functions
	void renderEnemy();
	void renderBoss();
	void renderAnimator();
	void renderBackground();
	void renderUI();

	//other private functions
	void enemyDeath();
	void bossDeath();

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

