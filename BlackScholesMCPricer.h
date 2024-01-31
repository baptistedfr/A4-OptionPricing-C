#pragma once

#include "Option.h";
class BlackScholesMCPricer
{
private:
	Option* _option;
	double initial_price;
	double _interest_rate;
	double _volatility;
	double NbPaths;
	double _sumpayoff;
	double _sumpayoff2; //sum of our payoffs to the power of 2
public:
	BlackScholesMCPricer(Option* option, double initial_price, double interest_rate, double volatility); //constructor 
	double getNbPaths(); //method that counts the number of paths already generated since the beginning of the program to estimate the price of the option
	double generate(int); //generates a certain number of paths and returns the average payoff calculated to estimate the option price
	std::vector<double> confidenceInterval(); //returns a vector of doubles that represents the confidence interval for the option price estimate
	double operator()(); 

};