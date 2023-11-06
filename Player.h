#pragma once
class Player
{
private:
	//private variables
	float damage;
	float attackCDMax;
	float attackCD;	

	//private functions
	void initVariables();

public:
	//constructor
	Player();
	//deconstructor
	~Player();

	//getters
	const float getDamage() const;
	void update();
};

