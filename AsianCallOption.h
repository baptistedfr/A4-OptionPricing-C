#pragma once
#include "AsianOption.h"

class AsianCallOption : public AsianOption { //derived from asianoption
public:
	AsianCallOption(std::vector<double> ts, double strike); //constructor
	double payoff(double) override; //compute the payoff of asiancalloption
private:
	double asian_strike;

};