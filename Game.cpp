#include "stdafx.h"
#include "Game.h"

//the game class runs the game

//private initiation functions
void Game::initWindow()
{
	//creates the game window
	this->window.create(sf::VideoMode(800, 600), "Basic RPG", sf::Style::Close | sf::Style::Titlebar);
}

void Game::initPlayer()
{
	//holds player state
	this->player = new Player();
	this->mouseHeld = false;
}

void Game::initEnemy()
{
	//stores enemy state
	this->enemy = new Enemy(rng);
	this->enemy->setPosition(
		this->window.getSize().x /2 - this->enemy->getGlobalBounds().width / 2, 
		this->window.getSize().y / 2 - this->enemy->getGlobalBounds().height / 2);
}

void Game::initBoss()
{
	this->killCounter = 0;
	this->boss = new Boss();
	this->boss->setPosition( 
		this->window.getSize().x / 2 - this->boss->getGlobalBounds().width / 2, 
		this->window.getSize().y / 2 - this->boss->getGlobalBounds().height / 2); 
	this->bossActive = false;
}

void Game::initAnimator()
{ 
	//plays the enemy death animation when its hp reaches 0
	this->animator = new Animator();
	this->playDeathAnimation = false;
	this->playEscapeAnimation = false;
	this->animator->setSmokeSpritePosition(
		this->window.getSize().x / 2 - this->animator->getSmokeSpriteGlobalBounds().width / 2,
		this->window.getSize().y / 2 - this->animator->getSmokeSpriteGlobalBounds().height / 2);
}

void Game::initBackground()
{
	//sets the background
	if (!this->backgroundTexture.loadFromFile("textures/backgrounds/beach.png"))
	{
		std::cout << "ERROR::GAME::INITBACKGROUND::Can't load beach.png";
	}
	this->background.setTexture(backgroundTexture);
}

void Game::initUI()
{
	//create an hp bar and set its position above the enemy
	this->ui = new UI();
	this->ui->setHpBarPosition(this->window.getSize().x, this->enemy->getGlobalBounds().top);
	this->ui->setCoinsText(this->player->getCoins());
	this->ui->setDamageText(this->player->getDamage());
	this->ui->setUpgradeCostText(this->player->getUpgradeCost());
}

void Game::polledEvents()
{
	//this lets us close the window using the x button
	while (this->window.pollEvent(this->event))
	{
		if (this->event.type == sf::Event::Closed)
		{
			window.close();
		}
	}
}

//private update functions
void Game::updateCombat()
{
	//if fighting boss, check to see if boss escapes
	if (this->bossActive && this->ui->getTimeLeft() <= 0.f)
	{
		this->bossEscape();
	}

	/*this checks to see if the player is attacking and determines how much damage the enemy takes. it then
	also updates the hp bar in the ui*/
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		if (!this->mouseHeld)
		{
			this->mousePosition = sf::Vector2f(static_cast<float>(sf::Mouse::getPosition(this->window).x),
				static_cast<float>(sf::Mouse::getPosition(this->window).y));

			//if fighting a boss
			if (this->bossActive && this->boss->getGlobalBounds().contains(this->mousePosition))
			{
				this->mouseHeld = true;
				this->boss->takeDamage(this->player->getDamage());
				this->ui->setHpBarColor(this->boss->getHpCurrent(), this->boss->getHpMax());
				this->ui->setHpBarLength(this->boss->getHpCurrent(), this->boss->getHpMax());
			}
			//if fighting a regular enemy
			else if (this->enemy->getGlobalBounds().contains(this->mousePosition))
			{				
				this->mouseHeld = true;
				this->enemy->takeDamage(this->player->getDamage());
				this->ui->setHpBarColor(this->enemy->getHpCurrent(), this->enemy->getHpMax());
				this->ui->setHpBarLength(this->enemy->getHpCurrent(), this->enemy->getHpMax());
			}
		}
	}
	else
	{
		this->mouseHeld = false;
	}

	//if fighting boss and its dead, play death animation
	if (this->bossActive && this->boss->getHpCurrent() <= 0.f)
	{
		this->animator->setSprite(this->boss->getSprite());
		this->ui->resetTimer();
		this->bossDeath();
	}
	//if fighting regular enemy and its dead, play death animation
	else if (this->enemy->getHpCurrent() <= 0.f)		
	{
		this->animator->setSprite(this->enemy->getSprite());
		this->enemyDeath();
	}
}

void Game::bossEscape()
{
	this->playEscapeAnimation = true;
	if (this->animator->getAnimationEnd())
	{
		this->ui->resetTimer();
		this->boss->resetBoss();
		this->bossActive = false;
		this->ui->setHpBarMaxLength(this->bossActive); 
		this->ui->setHpBarLength(this->enemy->getHpCurrent(), this->enemy->getHpMax()); 
		this->ui->setHpBarColor(this->enemy->getHpCurrent(), this->enemy->getHpMax()); 
		this->ui->setHpBarPosition(this->window.getSize().x, this->enemy->getGlobalBounds().top); 
		this->animator->resetAnimator();
		this->playEscapeAnimation = false;
	}
}

void Game::enemyDeath()
{
	//plays an animation for enemy death
	this->playDeathAnimation = true;
	if (this->animator->getAnimationEnd())
	{
		this->killCounter++;
		std::cout << "kill count: " << killCounter << '\n';
		this->enemy->resetEnemy(); //this sets up a new random enemy
		this->enemy->setPosition(
			this->window.getSize().x / 2 - this->enemy->getGlobalBounds().width / 2,
			this->window.getSize().y / 2 - this->enemy->getGlobalBounds().height / 2);
		this->animator->resetAnimator();
		this->playDeathAnimation = false;
		this->ui->setHpBarLength(this->enemy->getHpCurrent(), this->enemy->getHpMax()); 
		this->ui->setHpBarColor(this->enemy->getHpCurrent(), this->enemy->getHpMax()); 
		this->player->addCoins(rng.generateRandomNum(this->enemy->getCoinsToDrop().first, this->enemy->getCoinsToDrop().second));
		this->ui->setCoinsText(this->player->getCoins());

		if (this->killCounter >= 10)
		{
			this->setUpBoss();
			this->killCounter = 0;
		}
	}		
}

void Game::setUpBoss()
{
	//setup boss fight	
	this->bossActive = true;		
	this->ui->setHpBarMaxLength(this->bossActive);
	this->ui->setHpBarPosition(this->window.getSize().x, this->boss->getGlobalBounds().top);
	this->ui->setHpBarLength(this->enemy->getHpCurrent(), this->enemy->getHpMax()); 
	this->ui->setCountdownPosition(this->window.getSize().x);
}

void Game::bossDeath()
{
	//plays an animation for boss death
	this->playDeathAnimation = true;
	if (this->animator->getAnimationEnd())
	{
		this->boss->resetBoss();
		this->bossActive = false;
		this->boss->setPosition(
			this->window.getSize().x / 2 - this->boss->getGlobalBounds().width / 2,
			this->window.getSize().y / 2 - this->boss->getGlobalBounds().height / 2);
		this->animator->resetAnimator();
		this->ui->setHpBarMaxLength(this->bossActive);
		this->playDeathAnimation = false;
		this->ui->setHpBarLength(this->boss->getHpCurrent(), this->boss->getHpMax());
		this->ui->setHpBarColor(this->boss->getHpCurrent(), this->boss->getHpMax());
		this->player->addCoins(rng.generateRandomNum(this->boss->getCoinsToDrop().first, this->boss->getCoinsToDrop().second));
		this->ui->setCoinsText(this->player->getCoins());
		this->ui->setHpBarPosition(this->window.getSize().x, this->enemy->getGlobalBounds().top);
	}
}

void Game::updateUI()
{
	/*when clicked and when the player has enough coins, upgrade the players damage and set the UI
	to reflect this*/
	this->mousePosition = sf::Vector2f(static_cast<float>(sf::Mouse::getPosition(this->window).x),
		static_cast<float>(sf::Mouse::getPosition(this->window).y));
	if (this->ui->upgradeButtonCLicked(mousePosition))
	{
		if (!this->mouseHeld)
		{
			this->mouseHeld = true;
			if (this->player->canUpgrade())
			{
				this->player->upgradeDamage();
				this->ui->setDamageText(this->player->getDamage());
				this->ui->setCoinsText(this->player->getCoins());
				this->ui->setUpgradeCostText(this->player->getUpgradeCost());
			}
		}
		else
		{
			this->mouseHeld = false;
		}
	}
	this->ui->update(this->bossActive);
	this->ui->setCountdownPosition(this->window.getSize().x);
}

void Game::updateAnimator()
{
	/*triggered when the enemy reaches 0 hp, play a death animation and make sure the animation sprite stays
	in its correct position*/
	if (this->playDeathAnimation)
	{
		this->animator->update("death");
		this->animator->setDeathSpritePosition(this->window.getSize().x / 2 - this->animator->getDeathSpriteGlobalBounds().width / 2,
			this->window.getSize().y / 2 - this->animator->getDeathSpriteGlobalBounds().height / 2);
	}
	if (this->playEscapeAnimation)
	{
		this->animator->update("escape");
	}
}

//private rendering functions
void Game::renderEnemy()
{
	if(!this->playDeathAnimation && !this->bossActive)
	{
		this->enemy->render(this->window);
	}
}

void Game::renderBoss()
{
	if (this->bossActive && !playEscapeAnimation && !playDeathAnimation)
	{
		this->boss->render(this->window);
	}
}

void Game::renderAnimator()
{
	this->animator->render(this->window, this->playDeathAnimation, this->playEscapeAnimation);
}

void Game::renderBackground()
{
	this->window.draw(this->background);
}

void Game::renderUI()
{
	this->mousePosition = sf::Vector2f(static_cast<float>(sf::Mouse::getPosition(this->window).x),
		static_cast<float>(sf::Mouse::getPosition(this->window).y));
	this->ui->render(this->window, this->enemy->getHpCurrent(), this->mousePosition, this->bossActive, 
		this->playEscapeAnimation);
}

//constructor
Game::Game(RNG& rng) : rng(rng)
{
	this->initWindow();
	this->initBackground();
	this->initEnemy();
	this->initBoss();
	this->initPlayer();
	this->initAnimator();
	this->initUI();
}

//deconstructor
Game::~Game()
{
	delete this->player;
	delete this->enemy;
	delete this->boss;
	delete this->ui;
}

//getters
const sf::RenderWindow& Game::getWindow() const
{
	return this->window;
}

//public functions
void Game::update()
{
	this->polledEvents();
	this->updateCombat();
	this->updateAnimator();
	this->updateUI();
}

void Game::render()
{
	this->window.clear();

	//draw game
	this->renderBackground();
	this->renderEnemy();
	this->renderBoss();
	this->renderAnimator();
	

	//draw ui
	this->renderUI();

	this->window.display();
}
