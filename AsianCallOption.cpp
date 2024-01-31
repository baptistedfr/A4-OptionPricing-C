
#include "AsianCallOption.h"
#include "AsianOption.h"
#include <vector>

AsianCallOption::AsianCallOption(std::vector<double> ts, double strike) :AsianOption(ts), asian_strike(strike) {} //constructor
double AsianCallOption::payoff(double average_price) {
	return (average_price - asian_strike > 0) ? average_price - asian_strike : 0; //payoff of asiancall option is max(1/m * sum(zk) -k ; 0) with zk spot and k strike
}
