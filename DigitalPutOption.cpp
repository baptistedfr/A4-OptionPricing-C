#include <iostream>
#include "DigitalPutOption.h"
#include <cmath>
using namespace std;

DigitalPutOption::DigitalPutOption(double expiry, double strike) : DigitalOption(expiry, strike) {}; //initial constructor
double DigitalPutOption::payoff(double z) { //payoff of DigitalPutOption is defined as h(z) = 1(Z=<K) with Z = spot and K = strike
    if (_strike >= z) {
        return 1;
    }
    else {
        return 0;
    }
}
optionType DigitalPutOption::GetOptionType() const //it's is a put here
{
    return optionType::put;
}



