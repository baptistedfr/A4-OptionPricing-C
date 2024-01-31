#pragma once
#include "Option.h"
#include <stdio.h>
#include <stdexcept>
#include "VanillaOption.h"

using namespace std;
class DigitalOption : public Option //digitalOption is an option derived class

{
protected:
    double _strike;
public:
    DigitalOption(double expiry, double strike); //constructor of digitalOption
    virtual optionType GetOptionType() const = 0; //virtual function that need to be implemented in derived class.
    friend class BlackScholesPricer; //blackscholes pricer is declared as a friend class of the "DigitalOption" class. 
    //"BlackScholesPricer" will have access to private and protected members of the "DigitalOption" class.
    virtual double payoff(double spot) = 0; //virtual function 
    double getStrike();
};
