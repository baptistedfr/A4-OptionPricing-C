#pragma once
#include <vector>
#include "AsianOption.h"

class AsianPutOption : public AsianOption //derived from asianoption
{
public:
	AsianPutOption(std::vector<double> ts, double strike); //constructor
	double payoff(double) override; //payoff of asianputoption
private:
	double asian_strike;
};

