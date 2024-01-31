#include "AmericanOption.h"
#include <stdexcept>
#include <iostream>

using namespace std;

AmericanOption::AmericanOption(double expiry, double strike) : Option(expiry), _strike(strike) { //constructor
    if (expiry < 0 || strike < 0) {
        throw std::invalid_argument("Please enter non negative parameters"); //checking if parameters arent negatives
    }
}

double AmericanOption::getStrike() { //getter method to obtain the strike
    return _strike;
}

bool AmericanOption::isAmericanOption() {
    return true; //return true because it's an amarican option
}


