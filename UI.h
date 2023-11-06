#pragma once

#include "Enemy.h"

class UI
{
private:
	sf::RectangleShape hpMaxBar;
	sf::RectangleShape hpCurrentBar;

	//private functions
	void initHpBar();

public:
	//constructor
	UI();
	//deconstructor
	~UI();

	//setters
	void setHpBarPosition(const float x);
	void setHpBarColor(const float current_hp,const float max_hp);
	void setHpBarLength(const float current_hp, const float max_hp);

	//public functions
	void update();
	void render(sf::RenderTarget& target);


};

