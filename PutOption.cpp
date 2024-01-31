#include "PutOption.h"

PutOption::PutOption(double expiry, double strike) : VanillaOption( expiry, strike) {}; //constructor

double PutOption::payoff(double spot) {
	if (spot <= getStrike()) {
		return getStrike() - spot;//if the strike is larger than the spot, we exercise our put. Otherwise, we do not exercise it, our payoff is equal to 0
	}
	else {
		return 0.0;
	}
}

optionType PutOption::GetOptionType() const { //return the type of our option, here it's a put
	return optionType::put;
}