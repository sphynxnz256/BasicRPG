#pragma once
class Player
{
private:
	//private variables
	float damage;
	float attackCDMax;
	float attackCD;
	int coins;
	int upgradeCost;

	//private functions
	void initVariables();

public:
	//constructor
	Player();
	//deconstructor
	~Player();

	//getters
	const float getDamage() const;
	const int getCoins() const;
	const int getUpgradeCost() const;

	//setters
	void upgradeDamage();
	void addCoins(int coins_to_add);

	//public functions
	bool canUpgrade();
};

