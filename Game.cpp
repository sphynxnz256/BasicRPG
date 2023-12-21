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
	this->animator = new Animator(*this->sharedCoinTexture);
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

void Game::initCoins()
{
	this->sharedCoinTexture = std::make_shared<sf::Texture>();
	if (!this->sharedCoinTexture->loadFromFile("textures/coin.png"))
	{
		std::cout << "ERROR::COIN::INITTEXTURE::Failed to load coin.png\n";
	}
}

void Game::initUI()
{
	//create an hp bar and set its position above the enemy
	this->ui = new UI(static_cast<float>(this->window.getSize().x), this->enemy->getGlobalBounds().top,
		this->player->getCoins(), this->player->getDamage(), this->player->getUpgradeCost(),
		this->boss->getGlobalBounds().top);
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
	//check no animations are playing
	if(!this->playDeathAnimation && !this->playEscapeAnimation)
	{
		//if fighting boss, check to see if boss escapes
		if (this->bossActive && this->ui->getTimeLeft() <= 0.f)
		{
			this->playEscapeAnimation = true;
			this->bossEscape();			
		}
		/*this checks to see if the player is attacking and determines how much damage the enemy takes. it then
		also updates the hp bar in the ui*/
		else if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			if (!this->mouseHeld)
			{
				this->mousePosition = sf::Vector2f(static_cast<float>(sf::Mouse::getPosition(this->window).x),
					static_cast<float>(sf::Mouse::getPosition(this->window).y));

				if (this->bossActive && this->boss->getGlobalBounds().contains(this->mousePosition))
				{
					this->mouseHeld = true;
					this->bossTakeDamage();
				}
				//if fighting a regular enemy
				else if (this->enemy->getGlobalBounds().contains(this->mousePosition))
				{
					this->mouseHeld = true;
					this->enemyTakeDamage();
				}
			}
		}
		else
		{
			this->mouseHeld = false;
		}

		//if fighting boss and its dead, play death animation
		if (this->bossActive && this->boss->isDead())
		{
			this->animator->setSprite(this->boss->getSprite());
			this->playDeathAnimation = true;
			this->bossDeath();
		}
		//if fighting regular enemy and its dead, play death animation
		else if (this->enemy->isDead())
		{
			this->animator->setSprite(this->enemy->getSprite());
			this->playDeathAnimation = true;
			this->enemyDeath();
		}
	}
	else if (this->playDeathAnimation)
	{
		if(this->bossActive)
		{
			this->bossDeath();
		}
		else
		{
			this->enemyDeath();
		}
	}
	else
	{
		this->bossEscape();
	}
}

void Game::bossTakeDamage()
{
	//boss takes damage
	this->boss->takeDamage(this->player->getDamage());
	this->ui->setHpBarColor(this->boss->getHpCurrent(), this->boss->getHpMax());
	this->ui->setHpBarLength(this->boss->getHpCurrent(), this->boss->getHpMax());
}

void Game::enemyTakeDamage()
{
	this->enemy->takeDamage(this->player->getDamage());
	this->ui->setHpBarColor(this->enemy->getHpCurrent(), this->enemy->getHpMax());
	this->ui->setHpBarLength(this->enemy->getHpCurrent(), this->enemy->getHpMax());
}

void Game::bossEscape()
{
	//check if animation is finished
	if (this->animator->getAnimationEnd())
	{
		//reset timer
		this->ui->resetTimer();

		//reset animator
		this->animator->resetAnimator();
		this->playEscapeAnimation = false;

		//reset boss
		this->boss->resetBoss();
		this->bossActive = false;

		//set hp bar for next enemy
		this->ui->setHpBarMaxLength(this->bossActive); 
		this->ui->setHpBarLength(this->enemy->getHpCurrent(), this->enemy->getHpMax()); 
		this->ui->setHpBarColor(this->enemy->getHpCurrent(), this->enemy->getHpMax()); 
		this->ui->setHpBarPosition(static_cast<float>(this->window.getSize().x), this->enemy->getGlobalBounds().top);
	}
}

void Game::enemyDeath()
{
	//check if animation is finished
	if (this->animator->getAnimationEnd())
	{
		//update kill count
		this->killCounter++;

		//reset the animator
		this->playDeathAnimation = false;
		this->animator->resetAnimator();

		//set up new random enemy
		this->enemy->resetEnemy();
		this->enemy->setPosition(
			this->window.getSize().x / 2 - this->enemy->getGlobalBounds().width / 2,
			this->window.getSize().y / 2 - this->enemy->getGlobalBounds().height / 2);
		
		//reset health bars for new enemy
		this->ui->setHpBarLength(this->enemy->getHpCurrent(), this->enemy->getHpMax()); 
		this->ui->setHpBarColor(this->enemy->getHpCurrent(), this->enemy->getHpMax());

		//coins drop
		this->dropCoins(this->enemy->getCoinsToDrop(), sf::Vector2f(
			this->enemy->getPosition().x + this->enemy->getGlobalBounds().width / 2,
			this->enemy->getPosition().y + this->enemy->getGlobalBounds().height / 2));

		//check if enough enemies are killed for boss to spawn
		if (this->killCounter >= 10)
		{
			this->setUpBoss();
			this->killCounter = 0;
		}
	}		
}

void Game::dropCoins(std::pair<int, int> coins_to_drop, sf::Vector2f coin_start)
{
	this->coinsToDrop = rng.generateRandomNum(coins_to_drop.first, coins_to_drop.second);
	this->playCoinAnimation = true;
	for (size_t i = 0; i < this->coinsToDrop; i++)
	{
		Coin temp_coin(this->rng, this->window.getSize(), this->sharedCoinTexture);
		//this->animator->startCoinAnimation(coin_start, temp_coin.getPosition());
		this->coinsVector.push_back(Coin(temp_coin));
	}	
}

void Game::setUpBoss()
{
	//active boss
	this->bossActive = true;	

	//set hp bars for boss
	this->ui->setHpBarMaxLength(this->bossActive);
	this->ui->setHpBarPosition(static_cast<float>(this->window.getSize().x), this->boss->getGlobalBounds().top);
	this->ui->setHpBarLength(this->enemy->getHpCurrent(), this->enemy->getHpMax()); 
}

void Game::bossDeath()
{
	//check if animation is finished
	if (this->animator->getAnimationEnd())
	{
		//reset timer
		this->ui->resetTimer();

		//reset animator
		this->animator->resetAnimator();
		this->playDeathAnimation = false;

		//reset boss for next boss fight
		this->bossActive = false;
		this->boss->resetBoss();		
		this->boss->setPosition(
			this->window.getSize().x / 2 - this->boss->getGlobalBounds().width / 2,
			this->window.getSize().y / 2 - this->boss->getGlobalBounds().height / 2);

		//set the hp bar for next enemy
		this->ui->setHpBarMaxLength(this->bossActive);
		this->ui->setHpBarLength(this->boss->getHpCurrent(), this->boss->getHpMax());
		this->ui->setHpBarColor(this->boss->getHpCurrent(), this->boss->getHpMax());
		this->ui->setHpBarPosition(static_cast<float>(this->window.getSize().x), this->enemy->getGlobalBounds().top);

		//coins drop
		this->dropCoins(this->boss->getCoinsToDrop(), sf::Vector2f(
			this->boss->getPosition().x + this->boss->getGlobalBounds().width / 2,
			this->boss->getPosition().y + this->boss->getGlobalBounds().height / 2));
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
		this->upgradeDamage();
	}

	if (this->ui->retreatButtonCLicked(mousePosition))
	{
		this->retreat();
	}

	this->ui->update(this->bossActive, static_cast<float>(this->window.getSize().x), this->boss->getGlobalBounds().top);
}

void Game::upgradeDamage()
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

void Game::retreat()
{
	if (!this->mouseHeld)
	{
		this->mouseHeld = true;
		this->playEscapeAnimation = true;
		this->bossEscape();
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

	if (!this->playDeathAnimation && this->playCoinAnimation)
	{
		this->animator->update("coin");
	}
}

void Game::updateCoins()
{

	static bool click_processed = false;
	if(sf::Mouse::isButtonPressed(sf::Mouse::Left)) 
	{
		if (!click_processed)
		{
			this->mousePosition = sf::Vector2f(static_cast<float>(sf::Mouse::getPosition(this->window).x),
				static_cast<float>(sf::Mouse::getPosition(this->window).y));
				std::vector<Coin> coinsToKeep;
			for (auto& coin : this->coinsVector)
			{	
				if (coin.isMouseOver(this->mousePosition))
				{	
					this->player->addCoins(coin.getCoinValue());
					this->ui->setCoinsText(this->player->getCoins());					
				}
				else
				{
					coinsToKeep.push_back(coin);
				}
			}
			this->coinsVector.swap(coinsToKeep);
			click_processed = true;
		}		 
	}
	else
	{
		click_processed = false; 
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
	this->animator->render(this->window, this->playDeathAnimation, this->playEscapeAnimation,
		this->playCoinAnimation);
}

void Game::renderBackground()
{
	this->window.draw(this->background);
}

void Game::renderCoins()
{
	for (auto coin : this->coinsVector)
	{
		coin.render(this->window);
	}
}

void Game::renderUI()
{
	this->mousePosition = sf::Vector2f(static_cast<float>(sf::Mouse::getPosition(this->window).x),
		static_cast<float>(sf::Mouse::getPosition(this->window).y));
	this->ui->render(this->window, this->mousePosition, this->bossActive, this->playEscapeAnimation, 
		this->playDeathAnimation);
}

//constructor
Game::Game(RNG& rng) : rng(rng)
{
	this->initWindow();
	this->initBackground();
	this->initEnemy();
	this->initBoss();
	this->initPlayer();
	this->initCoins();
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
	this->updateCoins();
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
	this->renderCoins();

	//draw ui
	this->renderUI();

	this->window.display();
}
