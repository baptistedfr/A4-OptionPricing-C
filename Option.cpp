#include "Option.h"
#include <iostream>
#include <vector>

Option::Option(double expiry) : _expiry(expiry) {};	//constructor

double Option::getExpiry() const {	//get method
	return _expiry;
}


double Option::payoffPath(std::vector<double> vect)
{
	return payoff(vect.back()); //return the last payoff of the tree
}

bool Option::isAsianOption() {
	return false; //by default equal to false
}
bool Option::isAmericanOption() {
	return false; //by default equel to false
}