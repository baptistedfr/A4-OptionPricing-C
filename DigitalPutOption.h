#pragma once
#include "DigitalOption.h"


class DigitalPutOption : public DigitalOption
{
public:
    DigitalPutOption(double expiry, double strike); //constructor

    double payoff(double z); //compute the payoff of digitalputoption
    optionType GetOptionType() const override; //override the getoptionType with put
};