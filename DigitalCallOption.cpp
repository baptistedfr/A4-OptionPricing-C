#include <iostream>
#include "DigitalCallOption.h"
#include <cmath>
using namespace std;

DigitalCallOption::DigitalCallOption(double expiry, double strike): DigitalOption(expiry, strike) {};; //initial constructor

double DigitalCallOption::payoff(double z) { // the payoff of the digitalcalloption is defined as h(z) = 1(z>=K) with z spot and k strike
    if (z >= _strike) {
        return 1;
    }
    else {
        return 0;
    }
}
optionType DigitalCallOption::GetOptionType() const //override getoptiontype with call
{
    return optionType::call;
}
