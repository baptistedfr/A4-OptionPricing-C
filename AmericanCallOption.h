#pragma once
#include "AmericanOption.h"
class AmericanCallOption :
	public AmericanOption //dervied from americanoption
{
public:
	AmericanCallOption(double expiry, double strike); //constructor
	double payoff(double) override; //compute the payoff of the americancallotpion
	optionType GetOptionType() const override; //equal to call

private:
	double strike;
};

