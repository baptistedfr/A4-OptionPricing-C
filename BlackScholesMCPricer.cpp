#include "BlackScholesMCPricer.h"
#include "MT.h"
#include "AsianOption.h"
#include <iostream>


using namespace std;

BlackScholesMCPricer::BlackScholesMCPricer(Option* option, double initial_price, double interest_rate, double volatility) : //constructor
	_option(option), initial_price(initial_price), _interest_rate(interest_rate), _volatility(volatility), NbPaths(0),_sumpayoff(0),_sumpayoff2(0) {};


double BlackScholesMCPricer::getNbPaths() { //getter method for obtain the number of paths
	return NbPaths;
}

double BlackScholesMCPricer::generate(int nb_paths) {

	if (nb_paths < 0) {
		throw std::invalid_argument("0 added paths");
	}//if no path, I don't execute anything

	std::vector<double> T(nb_paths);
	if (_option->isAsianOption()) { // case of asian option

		AsianOption* asianOption = dynamic_cast<AsianOption*>(_option); //I redefined the option as Asian
		vector<double> St(asianOption->getTimeSteps().size()); //creates a new vector for all St (price of asian option)
		vector<double> z(asianOption->getTimeSteps().size()); //creates a new vector for spot price of underlying
		for (int i = 0; i < nb_paths; i++) {
			for (int j = 0; j < asianOption->getTimeSteps().size(); j++) {
				z[j] = MT::rand_norm(); //generates a random value for Z at each time
				if (j != 0) {
					St[j] = (St[j - 1]) * exp((_interest_rate - _volatility * _volatility / 2) * (asianOption->getTimeSteps()[j] - asianOption->getTimeSteps()[j - 1]) + _volatility * (sqrt(asianOption->getTimeSteps()[j] - asianOption->getTimeSteps()[j - 1])) * z[j]);
				}
				else { //for St[0]
					St[0] = (initial_price * exp((_interest_rate - _volatility * _volatility / 2) * asianOption->getTimeSteps()[0] + _volatility * sqrt(asianOption->getTimeSteps()[0]) * z[0]));
				}
			}
			NbPaths++; //little by little I update NbPath so that at the end it corresponds to nb_paths (initially entered as parameter)
			//// we therefore have a sequence (St1...., Stm) and we will add h(St1...., Stm) to our final variable _sum
			_sumpayoff += asianOption->payoffPath(St); //add h(St1, St2, ..., Stm) to the _sumpayoff variable
			_sumpayoff2 += asianOption->payoffPath(St) * asianOption->payoffPath(St); //Add h(St1, St2, ..., Stm)^2 to the variable _sumpayoff2 (useful for confidence intervals)
		}
	}
	else { //case of european options
		double Z = MT::rand_norm(); //generate a random value for Z
		double T = _option->getExpiry(); //the S corresponds only to maturity m =1
		//because we can execute the european option only at the maturity
		for (int i = 0; i < nb_paths; i++) {
			Z = MT::rand_norm();
			double S1 = initial_price * exp((_interest_rate - (_volatility * _volatility) / 2)*T + (_volatility * sqrt(T) *Z)); //calculation of the price of the underlying S at maturity T using the Black-Scholes model
			NbPaths++;
			_sumpayoff += _option->payoff(S1);//add h(St1) to the _sumpayoff variable
			_sumpayoff2 += _option->payoff(S1) * _option->payoff(S1); // add h(St1)^2 to the variable_sumpayoff2
		}
	}
}
double BlackScholesMCPricer::operator()() {  //operator compute the final price estimation
	if (NbPaths != 0) { //check if NbPaths is non-zero
		double maturity = _option->getExpiry(); //obtain the maturity of the option
		return (1 / NbPaths) * exp(-_interest_rate * maturity) * _sumpayoff; //calculates the final price estimate using the Black-Scholes model formula
	}
	else
	{
		throw std::invalid_argument("_price no find ");
	}
}

std::vector<double> BlackScholesMCPricer::confidenceInterval() { 
	vector<double> CI(2); //confidence interval vector
	double q = 1.96; //1.96 is the quantile at the 95% level of the normal distribution
	double price = BlackScholesMCPricer::operator()(); //obtain the estimation of the price
	double sigma = sqrt(_sumpayoff2 / NbPaths - (_sumpayoff / NbPaths) * (_sumpayoff / NbPaths)); //sigma calculation (standard deviation)
	CI[0] = price-q* (sigma/ sqrt(NbPaths)); //calculating the lower value of the interval
	CI[1] = price + q * (sigma / sqrt(NbPaths)); //calculating the upper value of the interval
	return CI;
}
