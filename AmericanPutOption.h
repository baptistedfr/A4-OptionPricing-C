#pragma once
#include "AmericanOption.h"
class AmericanPutOption :
	public AmericanOption //derived class of americanoption
{
public:
	AmericanPutOption(double expiry, double strike); //constructor 
	double payoff(double) override; //compute the payoff of americanputoption
	optionType GetOptionType() const override; //override the getoptiontype

private:
	double strike;
};





