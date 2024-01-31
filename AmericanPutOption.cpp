#include "AmericanPutOption.h"

AmericanPutOption::AmericanPutOption(double expiry, double strike) : AmericanOption(expiry, strike) {}; //constructor

double AmericanPutOption::payoff(double spot) { //compute the payoff of the americanputoption
	if (spot <= getStrike()) {
		return getStrike() - spot; // the payoff is equal of strike - spot like classical put option
	}
	else {
		return 0.0;
	}
};

optionType AmericanPutOption::GetOptionType() const { // here it's an put so optionType is equal to put
	return optionType::put;
}

