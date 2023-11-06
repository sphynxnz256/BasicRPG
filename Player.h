#pragma once
class Player
{
private:
	//private variables
	float damage;
	float attackCDMax;
	float attackCD;
	float coins;

	//private functions
	void initVariables();

public:
	//constructor
	Player();
	//deconstructor
	~Player();

	//getters
	const float getDamage() const;
	const float getCoins() const;

	//setters
	void addDamage(float damage_to_add);
	void addCoins(float coins_to_add);

	//public functions
	void update();
};

