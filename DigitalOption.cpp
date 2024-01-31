#include <iostream>
#include "DigitalOption.h"
#include <cmath>
using namespace std;
DigitalOption::DigitalOption(double expiry, double strike) : Option(expiry) //constructor
{
    if (expiry >= 0 && strike >= 0)
    {
        _strike = strike; 
    }
    else
    {
        throw invalid_argument("Strike and Expiry can't be negative"); //when strike or expiry given in parameters are negative : it's impossible !
    }
};

double DigitalOption::getStrike() { //getter method
    return _strike;
}

