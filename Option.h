#pragma once
#include <iostream>
#include <vector>

class Option
{
private:
	double _expiry;
public:
	Option(double expiry);	//constructor
	virtual double payoffPath(std::vector<double> vect); //contains h(St1,.....,Stm) (useful for asianoption)
	virtual double payoff(double spot) = 0;	//pure virtual method
	double getExpiry() const;	//get method
	virtual bool isAsianOption(); //return true if it's an asian option
	virtual bool isAmericanOption(); // return true if it's an american option

};

