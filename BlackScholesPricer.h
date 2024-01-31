#pragma once
#include "VanillaOption.h"
#include "DigitalOption.h"

class BlackScholesPricer
{
private:
	VanillaOption* _option; 
	DigitalOption* _option_d;
	bool type_option;
	double _asset_price;
	double _interest_rate;
	double _volatility;
public:
	BlackScholesPricer(VanillaOption* option, double asset_price, double interest_rate, double volatility); //constructor with a vanillaoption in parameters
	BlackScholesPricer(DigitalOption* option, double asset_price, double interest_rate, double volatility); //constructor with a digitaloption in parameters
	double operator()(); //returns the price of the option
	double delta(); //compute the delta  of our the option
};

