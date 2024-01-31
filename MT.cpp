#include "MT.h"
#include <iostream>
#include <random>

MT MT::generator; //object for a random value
MT::MT() : mt(std::random_device()()){}

MT& MT::getInstance()
{
	return generator; //reference to the single instance of the MT class
}

double MT::rand_unif()
{
	std::uniform_real_distribution<double> distribution(0.0, 1.0); //creates a uniform distribution on the interval [0.0, 1.0]
	return (distribution(MT::getGenerator())); //a random number using the random number generator object
}
double MT::rand_norm()
{
	std::normal_distribution<double> distribution(0.0, 1.0); //creates a normal distribution N(0,1)
	return (distribution(MT::getGenerator())); //a random number using the random number generator object
}

std::mt19937& MT::getGenerator()
{
	return generator.mt; //returns a reference to the mt object contained in the static generator variable
}


