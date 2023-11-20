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
	Button retreatButton;

	sf::Text countdownText;
	sf::Clock dtClock;
	float timeLeft;
	bool firstFrame;
	float dt;

	//private initiation functions
	void initHpBar(float target_x, float enemy_top);
	void initFonts();
	void initText(int coins, float damage, int upgrade_cost);
	void initUpgradeButton();
	void initRetreatButton();
	void initCountdown(float target_x, float boss_top);

	//private update functions
	void updateCountdown(float target_x, float boss_top);

	//private render functions
	void renderHpBar(sf::RenderTarget& target, float current_hp, bool boss_escape);
	void renderPlayerStats(sf::RenderTarget& target);
	void renderUpradeButton(sf::RenderTarget& target, const sf::Vector2f& mouse_pos);
	void renderEscapeButton(sf::RenderTarget& target, const sf::Vector2f& mouse_pos,
		bool boss_active, bool boss_escape);
	void renderCountdown(sf::RenderTarget& target, bool boss_active, bool boss_escape);

public:
	//constructor
	UI(float target_x, float enemy_top, int coins, float damage, int upgrade_cost, float boss_top);
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
	void setCountdownPosition(float target_x, float boss_top);

	//public functions
	bool upgradeButtonCLicked(sf::Vector2f& mouse_pos);
	bool retreatButtonCLicked(sf::Vector2f& mouse_pos);
	void resetTimer();
	void update(const bool boss_active, float target_x, float boss_top);
	void render(sf::RenderTarget& target, float current_hp,
		const sf::Vector2f& mouse_pos, bool boss_active, bool boss_escape);
};

