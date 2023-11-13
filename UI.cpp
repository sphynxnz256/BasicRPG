#include "stdafx.h"
#include "UI.h"

/*the ui class displays info useful to the user*/

//private functions
void UI::initHpBar()
{
	this->hpMaxBar.setSize(sf::Vector2f(130.f, 20.f));
	this->hpMaxBar.setFillColor(sf::Color(200, 200, 200, 100));
	this->hpMaxBar.setOutlineColor(sf::Color::Black);
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
	this->damageText.setPosition(20.f, this->coinsText.getPosition().y + this->coinsText.getGlobalBounds().height + 10.f);

	//displays current cost of upgrade
	this->upgradeCostText.setFont(font); 
	this->upgradeCostText.setCharacterSize(16);
	this->upgradeCostText.setOutlineColor(sf::Color::Black);
	this->upgradeCostText.setOutlineThickness(1.f);
	this->upgradeCostText.setString("Upgrade Cost: not set");
}

void UI::initUpgradeButton()
{
	float pos_x = 20.f;
	float pos_y = this->damageText.getPosition().y + this->damageText.getGlobalBounds().height + 10.f;
	float width = 100.f;
	float height = 30.f;
	sf::Color idle_color = sf::Color(100, 100, 100, 255);
	sf::Color hover_color = sf::Color(50, 50, 50, 255);
	std::string text = "Upgrade";
	int character_size = 20;

	this->upgradeButton = Button(pos_x, pos_y, width, height,
		idle_color, hover_color, text, font, character_size);

	//set upgrade cost text position once upgrade button's position is set
	this->upgradeCostText.setPosition(20.f, this->upgradeButton.getPosition().y + this->upgradeButton.getGlobalBounds().height + 5.f);
}

//constructors
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

void UI::setUpgradeCostText(const int upgrade_cost)
{
	std::stringstream ss;
	ss << "Upgrade Cost: " << upgrade_cost << " coins\n";
	this->upgradeCostText.setString(ss.str());
}

bool UI::upgradeButtonCLicked(sf::Vector2f mouse_pos)
{
	return upgradeButton.isClicked(mouse_pos);
}

//public functions
void UI::render(sf::RenderTarget& target, float current_hp, const sf::Vector2f& mouse_pos)
{
	if(current_hp > 0)
	{
		target.draw(this->hpMaxBar);
		target.draw(this->hpCurrentBar);
	}

	target.draw(this->coinsText);
	target.draw(this->damageText);

	upgradeButton.draw(target, mouse_pos); 
	if(upgradeButton.isMouseOver(mouse_pos))
	{
		target.draw(this->upgradeCostText);
	}
	
}
