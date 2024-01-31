#include "AsianPutOption.h"
#include "AsianOption.h"
#include <vector>

AsianPutOption::AsianPutOption(std::vector<double> ts, double strike) : AsianOption(ts), asian_strike(strike) {}; //constructor
double AsianPutOption::payoff(double average_price)
{
	return (asian_strike -average_price > 0) ? asian_strike - average_price : 0; //payoff of asiancall option is max(k - 1/m * sum(zk); 0) with zk spot and k strike
}