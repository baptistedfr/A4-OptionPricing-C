#pragma once
#include "VanillaOption.h"
class PutOption : public VanillaOption
{
public:
	PutOption(double expiry, double strike); //constructor
	double payoff(double spot) override;//define the payoff of our putoption
	optionType GetOptionType() const override;//override the getOptionType of vanilla option class
};

