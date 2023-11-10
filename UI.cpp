#include "stdafx.h"
#include "UI.h"

/*the ui class displays info useful to the user*/

//private functions
void UI::initHpBar()
{
	this->hpMaxBar.setSize(sf::Vector2f(200.f, 20.f));
	this->hpMaxBar.setFillColor(sf::Color(200, 200, 200, 100));
	this->hpMaxBar.setOutlineColor(sf::Color(100, 100, 100, 200));
	this->hpMaxBar.setOutlineThickness(1.f);

	this->hpCurrentBar.setSize(hpMaxBar.getSize());
	this->hpCurrentBar.setFillColor(sf::Color::Green);
}

void UI::initFonts()
{
	if (!this->font.loadFromFile("fonts/arial.ttf"))
	{
		std::cout << "ERROR::UI::INITFONTS::Could not load arial.ttf\n";
	}
}

void UI::initText()
{
	//displays the amount of coins the player as earned
	this->coinsText.setFont(font);
	this->coinsText.setCharacterSize(24);
	this->coinsText.setOutlineColor(sf::Color::Black);
	this->coinsText.setOutlineThickness(1.f);
	this->coinsText.setString("Coins: not set");
	this->coinsText.setPosition(20.f, 20.f);
	
	//displays the current damage the player deals
	this->damageText.setFont(font);
	this->damageText.setCharacterSize(24);
	this->damageText.setOutlineColor(sf::Color::Black);
	this->damageText.setOutlineThickness(1.f);
	this->damageText.setString("Damage: not set");
	this->damageText.setPosition(20.f, this->coinsText.getGlobalBounds().height + 40.f);
}

void UI::initUpgradeButton()
{
	//displays the button to upgrade damage
	this->upgradeButton.setSize(sf::Vector2f(100.f, 30.f));
	this->upgradeButton.setFillColor(sf::Color(200, 200, 200, 255));
	this->upgradeButton.setOutlineColor(sf::Color(100, 100, 100, 255));
	this->upgradeButton.setOutlineThickness(5.f);
	this->upgradeButton.setPosition(30.f,
		this->damageText.getGlobalBounds().height + this->damageText.getPosition().y + 40.f);

	this->upgradeButtonText.setFont(font);
	this->upgradeButtonText.setString("upgrade");
	this->upgradeButtonText.setCharacterSize(20);
	this->upgradeButtonText.setOutlineColor(sf::Color::Black);
	this->upgradeButtonText.setFillColor(sf::Color::Black);
	this->upgradeButtonText.setPosition(upgradeButton.getPosition().x + 12, upgradeButton.getPosition().y + 2); //there is a freakin button class. lets use that :/
}



//constructor
UI::UI()
{
	this->initHpBar();
	this->initFonts();
	this->initText();
	this->initUpgradeButton();
}

//deconstructor
UI::~UI()
{
}

sf::FloatRect UI::getUpgradeGlobalBounds()
{
	return this->upgradeButton.getGlobalBounds();
}

//setters
void UI::setHpBarPosition(const float target_x, const float enemy_top)
{
	float x_position = target_x / 2 - this->hpMaxBar.getGlobalBounds().width / 2;
	float y_position = enemy_top - 20.f;
	this->hpMaxBar.setPosition(x_position, y_position);
	this->hpCurrentBar.setPosition(x_position, y_position);
}

void UI::setHpBarColor(const float current_hp, const float max_hp)
{
	if (current_hp > 0.5f * max_hp)
	{
		this->hpCurrentBar.setFillColor(sf::Color(static_cast <int>(255 - (255 * current_hp / max_hp)) * 2, 255, 0, 255));
	}
	else
	{
		this->hpCurrentBar.setFillColor(sf::Color(255, static_cast <int>(255 * (current_hp * 2) / max_hp), 0, 255));
	}
}

void UI::setHpBarLength(const float current_hp, const float max_hp)
{
	this->hpCurrentBar.setSize(sf::Vector2f(this->hpMaxBar.getSize().x * current_hp / max_hp, this->hpMaxBar.getSize().y));
}

void UI::setCoinsText(const int coins)
{
	std::stringstream ss;
	ss << "Coins: " << coins << '\n';
	this->coinsText.setString(ss.str());
}

void UI::setDamageText(const float damage)
{
	std::stringstream ss;
	ss << "Damage: " << static_cast<int>(damage) << '\n';
	this->damageText.setString(ss.str());
}

//public functions
void UI::render(sf::RenderTarget& target, float current_hp) 
{
	if(current_hp > 0)
	{
		target.draw(this->hpMaxBar);
		target.draw(this->hpCurrentBar);
	}
	target.draw(this->coinsText);
	target.draw(this->damageText);
	target.draw(this->upgradeButton);
	target.draw(this->upgradeButtonText);
}
