#include "BlackScholesPricer.h"
#include <cmath>

using namespace std;
BlackScholesPricer::BlackScholesPricer(VanillaOption* option, double asset_price, double interest_rate, double volatility) :
	_option(option), _asset_price(asset_price), _interest_rate(interest_rate), _volatility(volatility),type_option(true) {}; //constructor with vanillaoption

BlackScholesPricer::BlackScholesPricer(DigitalOption* option, double asset_price, double interest_rate, double volatility) :
	_option_d(option), _asset_price(asset_price), _interest_rate(interest_rate), _volatility(volatility), type_option(false) {}; //constructor with digitaloption

double normalCDF(double x) {
	return 0.5 * (1 + std::erf(x / std::sqrt(2))); //correspond to the cumulative distirbution function of normal law
}
double BlackScholesPricer::operator()() { // compute the price of the option 
	if (type_option) {

		double T = _option->getExpiry(); 
		double K = _option->getStrike();
		optionType type = _option->GetOptionType();
		double d1 = (log(_asset_price / K) + _interest_rate * T + (_volatility * _volatility * T) / 2) / (_volatility * sqrt(T)); //d1 in our formula : 1/(sigma*sqrt(t)) * (log(S0/k)+ (r+(0.5*sigma²)*T)
		double d2 = d1 - (_volatility * sqrt(T)); //d2 is just equal to d1 - sigma*sqrt(T)
		double option_price;

		if (type == optionType::call) { //if the option is a call the price is defined like this
			option_price = _asset_price * std::erfc(-d1 / sqrt(2)) / 2 - K * std::erfc(-d2 / sqrt(2)) / 2 * exp(-_interest_rate * T);
		}
		else { // if the option is a put the price is defined as 
			option_price = K * std::erfc(d2 / sqrt(2)) / 2 * exp(-_interest_rate * T) - _asset_price * std::erfc(d1 / sqrt(2)) / 2;

		}
		return option_price; //return  the final price of our option
	}
	else { //case for the digit options
		double T = _option_d->getExpiry();
		double K = _option_d->getStrike();
		optionType type = _option_d->GetOptionType();
		double d1 = (log(_asset_price / K) + T * (_interest_rate + (_volatility * _volatility / 2))) / (_volatility * sqrt(T));
		double d2 = (log(_asset_price / K) + T * (_interest_rate - (_volatility * _volatility / 2))) / (_volatility * sqrt(T));
		double option_price;
		double Nd1 = normalCDF(d1); //we use the normal law
		double Nd2 = normalCDF(d2);
		double Nd1M = (1 - Nd1);
		double Nd2M = (1 - Nd2);
		
		if (type == optionType::call) {
			//case of digital call
			option_price=exp(-_interest_rate * T)* Nd2;
		}
		else {
			//case of digital put
			option_price = exp(-_interest_rate * T) * Nd2M;
		}
		return option_price;
	}
}

double BlackScholesPricer::delta() {
	if (type_option) {
		double T = _option->getExpiry();
		double K = _option->getStrike();
		optionType type = _option->GetOptionType(); 
		double d1 = (log(_asset_price / K) + _interest_rate * T + (_volatility * _volatility * T) / 2) / (_volatility * sqrt(T)); //compute the same d1 as previous (BlackScholesPricer::operator()())
		double delta;

		if (type == optionType::call) {
			delta = erfc(-d1 / sqrt(2)) / 2; //delta for call option
		}
		else {
			delta = (erfc(-d1 / sqrt(2)) / 2) - 1; //delta for put option
		}
		return delta; // return the final delta
	}
	else { //compute the delta in digit options
		double T = _option_d->getExpiry();
		double K = _option_d->getStrike();
		optionType type = _option_d->GetOptionType();
		double d1 = (log(_asset_price / K) + T * (_interest_rate + (_volatility * _volatility / 2))) / (_volatility * sqrt(T));
		double d2 = d1 - _volatility * sqrt(T);
		double Nd1 = (0.5 * (1 + std::erf(d1 / std::sqrt(2))));
		double Nd2 = (0.5 * (1 + std::erf(d2 / std::sqrt(2))));
		double delta=0;
		//for call digit option
		if (type == optionType::call) {
			delta = exp(_interest_rate * T) * Nd2 / (_volatility * _asset_price * sqrt(T));
		}
		//for put digit option
		else {
			delta = -exp(_interest_rate * T) * Nd2 / (_volatility * _asset_price * sqrt(T));
		}
		return delta;
	}
}
