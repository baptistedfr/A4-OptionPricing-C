#include "VanillaOption.h"
#include <stdexcept>
#include <iostream>

using namespace std;

VanillaOption::VanillaOption(double expiry, double strike) : Option(expiry), _strike(strike) {
	if (expiry < 0 || strike < 0) {
		throw std::invalid_argument("Please enter non negative parameters"); //when you enter some negative paremeters, you cannot create a vanilla option
	}
}

double VanillaOption::getStrike() { //get method
	return _strike;
}