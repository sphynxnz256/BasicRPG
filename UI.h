#pragma once

#include "Enemy.h"

class UI
{
private:
	sf::RectangleShape hpMaxBar;
	sf::RectangleShape hpCurrentBar;	

	sf::Font font;

	sf::Text coinsText;
	sf::Text damageText;

	sf::RectangleShape upgradeButton;
	sf::Text upgradeButtonText;



	//private functions
	void initHpBar();
	void initFonts();
	void initText();
	void initUpgradeButton();

public:
	//constructor
	UI();
	//deconstructor
	~UI();

	//getters
	sf::FloatRect getUpgradeGlobalBounds();

	//setters
	void setHpBarPosition(const float target_x, const float enemy_top);
	void setHpBarColor(const float current_hp,const float max_hp);
	void setHpBarLength(const float current_hp, const float max_hp);
	void setCoinsText(const int coins);
	void setDamageText(const float damage);

	//public functions
	void render(sf::RenderTarget& target, float current_hp);
};

