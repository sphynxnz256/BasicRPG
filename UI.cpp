#include "stdafx.h"
#include "UI.h"

/*the ui class displays info useful to the user*/

//private functions
void UI::initHpBar()
{
	this->hpMaxBar.setSize(sf::Vector2f(200.f, 20.f));
	this->hpMaxBar.setPosition(20.f, 20.f);
	this->hpMaxBar.setFillColor(sf::Color(200, 200, 200, 100));

	this->hpCurrentBar.setSize(hpMaxBar.getSize());
	this->hpCurrentBar.setPosition(20.f, 20.f);
	this->hpCurrentBar.setFillColor(sf::Color::Green);
}

//constructor
UI::UI()
{
	initHpBar(); 
}

//deconstructor
UI::~UI()
{
}

//setters
void UI::setHpBarPosition(const float x)
{
	float x_position = x / 2 - hpMaxBar.getGlobalBounds().width / 2;
	this->hpMaxBar.setPosition(x_position, 20.f);
	this->hpCurrentBar.setPosition(x_position, 20.f);
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

//public functions
void UI::update()
{
}

void UI::render(sf::RenderTarget& target) 
{
	target.draw(this->hpMaxBar);
	target.draw(this->hpCurrentBar);
}
