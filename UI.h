#pragma once

#include "Enemy.h"
#include "Button.h"

class UI
{
private:
	sf::RectangleShape hpMaxBar;
	sf::RectangleShape hpCurrentBar;	

	sf::Font font;

	sf::Text coinsText;
	sf::Text damageText;
	sf::Text upgradeCostText;

	Button upgradeButton;

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

	//setters
	void setHpBarPosition(const float target_x, const float enemy_top);
	void setHpBarColor(const float current_hp,const float max_hp);
	void setHpBarLength(const float current_hp, const float max_hp);
	void setCoinsText(const int coins);
	void setDamageText(const float damage);
	void setUpgradeCostText(const int upgrade_cost);

	//public functions
	bool upgradeButtonCLicked(sf::Vector2f mouse_pos);
	void render(sf::RenderTarget& target, float current_hp, const sf::Vector2f& mouse_pos);
};

