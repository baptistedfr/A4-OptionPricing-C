#pragma once
#include "VanillaOption.h"
class CallOption : public VanillaOption // derived from vanilla option class
{
public:
	CallOption(double expiry, double strike); //constructor
	double payoff(double spot) override; //define the payoff of our calloption
	optionType GetOptionType() const override; //overide the getOptionType of vanilla option class
};

