#include "AsianOption.h"
#include <vector>
AsianOption::AsianOption(std::vector<double> times) : Option(times.back()), _ts(times){}; //constructor
std::vector<double> AsianOption::getTimeSteps()
{
	return _ts; //function returns the vector _ts which contains the moments in time associated with the option
}
double AsianOption::payoffPath(std::vector<double> underlying) //an underlying parameter of type std::vector<double>, which represents the underlying values associated with the option
{
	double sum = 0;
	for (int k = 0; k < getTimeSteps().size(); k++) {
		sum += underlying[k]; //calculates the sum of underlying values
	}
	return payoff((1.0 / getTimeSteps().size()) * sum); //returns the corresponding payoff using the payoff member function of the mean 
}

bool AsianOption::isAsianOption() //it is an asian option here
{
	return true;
}