#pragma once
#include "Option.h"

enum class optionType { //optionType can be a call (buy) or put (sell)
	call, put
};

class VanillaOption : public Option {
private:
	double _strike; //the strike (price of exercise) of our option
	friend class BlackScholesPricer; 
public:
	VanillaOption(double expiry, double strike);
	virtual optionType GetOptionType() const = 0; //need to be implemented in our derived classes
	virtual double payoff(double spot) = 0; //also a virtual method that must be implemented in our derived classes
	double getStrike();
};

