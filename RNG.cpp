#include "stdafx.h"
#include "RNG.h"

//constructor
RNG::RNG() : generator(std::random_device()()) {}

//public functions
int RNG::generateRandomNum(int min, int max)
{
	std::uniform_int_distribution<int> distribution(min, max);
	return distribution(this->generator);
}



