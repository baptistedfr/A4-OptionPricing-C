#include "CallOption.h"

CallOption::CallOption(double expiry, double strike) : VanillaOption(expiry, strike) {} //constructor

double CallOption::payoff(double spot)
{
	if (spot >= getStrike()) {
		return spot - getStrike(); //if the spot is larger than the strike, we exercise our call. Otherwise, we do not exercise it, our payoff is equal to 0
	}
	else {
		return 0.0;
	}
};

optionType CallOption::GetOptionType() const {
	return optionType::call;  //return the type of our option, here it's a call
}