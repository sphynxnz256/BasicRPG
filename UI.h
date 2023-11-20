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

	sf::Text countdownText;
	sf::Clock dtClock;
	float timeLeft;
	bool firstFrame;
	float dt;

	//private functions
	void initHpBar();
	void initFonts();
	void initText();
	void initUpgradeButton();
	void initCountdown();

	void updateCountdown();

public:
	//constructor
	UI();
	//deconstructor
	~UI();

	//getters
	const float getTimeLeft();

	//setters
	void setHpBarPosition(const float target_x, const float enemy_top);
	void setHpBarColor(const float current_hp,const float max_hp);
	void setHpBarLength(const float current_hp, const float max_hp);
	void setHpBarMaxLength(const bool boss_active);
	void setCoinsText(const int coins);
	void setDamageText(const float damage);
	void setUpgradeCostText(const int upgrade_cost);
	void setCountdownPosition(const float x_pos);

	//public functions
	bool upgradeButtonCLicked(sf::Vector2f mouse_pos);
	void resetTimer();
	void update(const bool boss_active);
	void render(sf::RenderTarget& target, float current_hp,
		const sf::Vector2f& mouse_pos, bool boss_active, bool boss_escape);
};

