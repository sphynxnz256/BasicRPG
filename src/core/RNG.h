#pragma once
class RNG
{
private:
	std::mt19937 generator; // Mersenne Twister 19937 engine

public:
	//constructor
	RNG();

	//public functions
	int generateRandomNum(int min, int max);
};

