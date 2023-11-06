#pragma once

#include "Enemy.h"
#include "Player.h"
#include "UI.h"
#include "Animator.h"

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
	void updatePlayer();
	void updateEnemy();
	void updateCombat();
	void updateAnimator();
	void updateUI();

	//private rendering functions
	void renderEnemy();
	void renderAnimator();
	void renderUI();

public:
	//constructor
	Game();
	//deconstuctor
	~Game();

	//getters
	const sf::RenderWindow& getWindow() const;

	//public functions	
	void update();
	void render();
};

