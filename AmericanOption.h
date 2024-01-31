#pragma once
#include "Option.h"
#include "VanillaOption.h"

class AmericanOption :
	public Option //derived from option
{
private:
	double _strike;
	friend class BlackScholesPricer; //friend class of blackscholespricers 

public:
	AmericanOption(double expiry, double strike); //constructor
	virtual optionType GetOptionType() const = 0; //must be implemented in derived classes and it returns the type of the option
	virtual double payoff(double spot) = 0; //must also be implemented in derived classes and it calculates the payoff of the option based on the price of the underlying
	double getStrike(); //getter method
	bool isAmericanOption() override; //overrides the option base class function and returns true to indicate that the option is of american type
};




