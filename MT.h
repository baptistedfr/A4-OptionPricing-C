#pragma once
#include <random>
#include <iostream>
using namespace std;

class MT //for random number
{
public:
	MT(const MT&) = delete; //destructor
	static MT& getInstance(); //reference to a single instance of class "MT"
	static std::mt19937& getGenerator(); //random number generator
	static double rand_unif(); //random number generated according to a uniform distribution on the interval [0, 1]
	static double rand_norm(); //returns a random number generated according to a normal gaussian distribution N(0,1)
private:
	MT();
	mt19937 mt;
	static MT generator;
};
