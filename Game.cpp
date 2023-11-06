#include "stdafx.h"
#include "Game.h"

/*the game class runs the game*/

//private initiation functions
void Game::initWindow()
{
	/*create game window*/
	this->window.create(sf::VideoMode(600, 800), "Basic RPG", sf::Style::Close | sf::Style::Titlebar);
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
	this->enemy = new Enemy();
	this->enemy->setPosition(
		this->window.getSize().x /2 - this->enemy->getGlobalBounds().width / 2, 
		this->window.getSize().y / 4 - this->enemy->getGlobalBounds().height / 2);
}

void Game::initAnimator()
{ 
	/*this currently is used to play the enemy death animation when its hp reaches 0*/
	this->animator = new Animator(this->enemy->getSprite());
	this->playAnimation = false;
}

void Game::initUI()
{
	/*this currently sets up a hp bar at the top of the screen so current hp can be seen*/
	this->ui = new UI();
	this->ui->setHpBarPosition(this->window.getSize().x);
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
void Game::updatePlayer()
{
	this->player->update();
}

void Game::updateEnemy()
{
	this->enemy->update();
}

 
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
			if (enemy->getGlobalBounds().contains(mousePosition))
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

	/*when the enemy reaches 0 health, this plays a death animation*/
	if (this->enemy->getHpCurrent() <= 0.f)
	{
		this->playAnimation = true; 
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
			this->window.getSize().y / 4 - this->animator->getGlobalBounds().height / 2);
	}
}

void Game::updateUI()
{
	this->ui->update();
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
	this->ui->render(this->window);
}

//constructor
Game::Game()
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
	this->updatePlayer();
	this->updateEnemy();
	this->updateAnimator();
	this->updateUI();
}

void Game::render()
{
	this->window.clear();

	//draw game
	if(this->enemy->getHpCurrent() > 0.f)
	{
		this->renderEnemy();
	}
	else
	{
		this->renderAnimator();
	}

	//draw ui
	this->renderUI();

	this->window.display();
}
