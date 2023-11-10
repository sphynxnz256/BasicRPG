#pragma once

#include "Enemy.h"
#include "Player.h"
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
	UI* ui;
	Animator* animator;
	bool playAnimation;
	RNG& rng;

	bool mouseHeld;
	sf::Vector2f mousePosition;

	//private initiation functions
	void initWindow();
	void initPlayer();
	void initEnemy();
	void initAnimator();
	void initUI();

	//private update functions
	void polledEvents();
	void updateCombat();
	void enemyDeath();
	void updateUI();
	void updateAnimator();

	//private rendering functions
	void renderEnemy();
	void renderAnimator();
	void renderUI();

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

