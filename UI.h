#pragma once

#include "Enemy.h"

class UI
{
private:
	sf::RectangleShape hpMaxBar;
	sf::RectangleShape hpCurrentBar;

	sf::Font font;
	sf::Text coins;
	sf::Text damage;



	//private functions
	void initHpBar();
	void initFonts();
	void initText();

public:
	//constructor
	UI();
	//deconstructor
	~UI();

	//setters
	void setHpBarPosition(const float target_x, const float enemy_top);
	void setHpBarColor(const float current_hp,const float max_hp);
	void setHpBarLength(const float current_hp, const float max_hp);

	//public functions
	void update();
	void render(sf::RenderTarget& target);


};

