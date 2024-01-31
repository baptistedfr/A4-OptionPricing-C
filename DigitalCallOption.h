#pragma once
#include "DigitalOption.h"

class DigitalCallOption : public DigitalOption //derived from digitaloption
{
public:
    DigitalCallOption(double expiry, double strike); //constructor
    double payoff(double z); //defined the payoff of the digitalcalloption
    optionType GetOptionType() const override; //override the getoptiontype with call
}; 