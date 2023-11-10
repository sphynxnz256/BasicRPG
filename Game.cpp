#include "stdafx.h"
#include "Game.h"

/*the game class runs the game*/

//private initiation functions
void Game::initWindow()
{
	/*create game window*/
	this->window.create(sf::VideoMode(800, 600), "Basic RPG", sf::Style::Close | sf::Style::Titlebar);
}

void Game::initPlayer()
{
	/*this is used to control when the player can attack and holds our player state*/
	this->player = new Player();
	this->mouseHeld = false;
}

void Game::initEnemy()
{
	/*this will hold our enemy state*/
	this->enemy = new Enemy(rng);
	this->enemy->setPosition(
		this->window.getSize().x /2 - this->enemy->getGlobalBounds().width / 2, 
		this->window.getSize().y / 2 - this->enemy->getGlobalBounds().height / 2);
}

void Game::initAnimator()
{ 
	/*this currently is used to play the enemy death animation when its hp reaches 0*/
	this->animator = new Animator();
	this->animator->setSprite(this->enemy->getSprite());
	this->playAnimation = false;
}

void Game::initUI()
{
	//create an hp bar and set its position above the enemy
	this->ui = new UI();
	this->ui->setHpBarPosition(this->window.getSize().x, this->enemy->getGlobalBounds().top);
	this->ui->setCoinsText(this->player->getCoins());
	this->ui->setDamageText(this->player->getDamage());
}

void Game::polledEvents()
{
	/*this lets us close the window using the x button*/
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
	/*this checks to see if the player is attacking and determines how much damage the enemy takes.it then
	also updates the hp bar in the ui*/
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		if (!this->mouseHeld)
		{
			this->mousePosition = sf::Vector2f(static_cast<float>(sf::Mouse::getPosition(this->window).x),
				static_cast<float>(sf::Mouse::getPosition(this->window).y));
			if (this->enemy->getGlobalBounds().contains(this->mousePosition))
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

	if (this->enemy->getHpCurrent() <= 0.f)
	{
		this->enemyDeath();
	}
}

void Game::enemyDeath()
{
	/*when the enemy reaches 0 health, this plays a death animation*/	
	this->playAnimation = true;
	if (this->animator->getAnimationEnd())
	{
		this->enemy->resetEnemy();
		this->enemy->setPosition(
			this->window.getSize().x / 2 - this->enemy->getGlobalBounds().width / 2,
			this->window.getSize().y / 2 - this->enemy->getGlobalBounds().height / 2);
		this->animator->resetAnimator(this->enemy->getSprite());
		this->playAnimation = false;
		this->ui->setHpBarLength(this->enemy->getHpCurrent(), this->enemy->getHpMax());
		this->ui->setHpBarColor(this->enemy->getHpCurrent(), this->enemy->getHpMax());
		this->player->addCoins(rng.generateRandomNum(this->enemy->getCoinsToDrop().first, this->enemy->getCoinsToDrop().second));
		this->ui->setCoinsText(this->player->getCoins());
	}	
}

void Game::updateUI()
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		if (!this->mouseHeld)
		{
			this->mousePosition = sf::Vector2f(static_cast<float>(sf::Mouse::getPosition(this->window).x),
				static_cast<float>(sf::Mouse::getPosition(this->window).y));
			if (this->ui->getUpgradeGlobalBounds().contains(mousePosition))
			{
				this->mouseHeld = true;
				if(this->player->canUpgrade())
				{
					this->player->upgradeDamage();
					this->ui->setDamageText(this->player->getDamage());
					this->ui->setCoinsText(this->player->getCoins());
				}
			}
		}
	}
	else
	{
		this->mouseHeld = false;
	}
}


void Game::updateAnimator()
{
	/*triggered when the enemy reaches 0 hp, play a death animation and make sure the animation sprite stays
	in its correct position*/
	if (playAnimation)
	{
		this->animator->update();
		this->animator->setPosition(this->window.getSize().x / 2 - this->animator->getGlobalBounds().width / 2,
			this->window.getSize().y / 2 - this->animator->getGlobalBounds().height / 2);
	}
}

//private rendering functions
void Game::renderEnemy()
{
	if(!playAnimation)
	{
		this->enemy->render(this->window);
	}
}

void Game::renderAnimator()
{
	if (playAnimation)
	{
		this->animator->render(this->window);
	}
}

void Game::renderUI()
{
	this->ui->render(this->window, this->enemy->getHpCurrent());
}

//constructor
Game::Game(RNG& rng) : rng(rng)
{
	this->initWindow();
	this->initEnemy();
	this->initPlayer();
	this->initAnimator();
	this->initUI();
}

//deconstructor
Game::~Game()
{
	delete this->player;
	delete this->enemy;
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
	this->renderEnemy();
	this->renderAnimator();

	//draw ui
	this->renderUI();

	this->window.display();
}