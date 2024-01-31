#include "AmericanCallOption.h"


AmericanCallOption::AmericanCallOption(double expiry, double strike) : AmericanOption(expiry, strike) {}; //constructor
double AmericanCallOption::payoff(double spot) {
	if (spot >= getStrike()) { //compute the payoff of americancalloption
		return spot - getStrike(); // equal to spot - strike like call option
	}
	else {
		return 0.0;
	}
};
optionType AmericanCallOption::GetOptionType() const { // optionType is equal to call
	return optionType::call;
}

