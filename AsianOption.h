#pragma once
#include <vector>
#include "Option.h"

class AsianOption :public Option
{
public:
	AsianOption(std::vector<double> times);
	std::vector<double> getTimeSteps(); //get the points in time associated with the option.
	double payoffPath(std::vector<double> underlying) override; // underlying value
	bool isAsianOption() override; //return true because it's an asian option
private:
	std::vector<double> _ts;
};
