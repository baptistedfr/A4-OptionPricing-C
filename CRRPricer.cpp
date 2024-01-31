#include "CRRPricer.h"
#include "BinaryTree.h"
#include <iostream>

CRRPricer::CRRPricer(Option* option1, int depth, double asset_price, double up, double down, double interest_rate) //constructor
	: _option(option1), _depth(depth), _asset_price(asset_price), _up(up), _down(down), _interest_rate(interest_rate)
{
	efficient = !(up > interest_rate && interest_rate > down);
	std::cout << "Efficient check :" << !efficient << std::endl; //check the arbitrage in our constructor , no arbitrage iif Down < Rate < Up
}

double CRRPricer::get(int n, int i) { //depth=n , index = i 
	return _tree.getNode(n, i); //we just reuse the getNode of our tree class
}

CRRPricer::CRRPricer(Option* _op, int depth, double asset_price, double r, double volatility) //without taking account a up, down and interest rate in our constructor
	: _option(_op), _depth(depth), _asset_price(asset_price), _interest_rate(r), volatility(volatility)
{
	if (_option->isAsianOption()) { //crr pricer doesn't accept asian option
		throw invalid_argument("CRRPricer doesnt accept asian option");
	}
	double h = _option->getExpiry() / (double)depth;
	_up = exp((r + (volatility * volatility) / 2) * h + volatility * sqrt(h)) - 1; //up definition
	_down = exp((r + (volatility*volatility) / 2) * h - volatility * sqrt(h)) - 1; //down definition
	_interest_rate = exp(_interest_rate * h) - 1; //rate definition
}

void CRRPricer::compute()
{
	double q = double(_interest_rate - _down) / double(_up - _down);
	double h_s;
	CRRPricer::_tree.setDepth(_depth);
	if (_option->isAmericanOption()) { // for american option we need to create two news tree : exercise_condition (contains true if intrinsic value > continue value) and payoff_american  (each payoff of each node)
		CRRPricer::_exercice_condition.setDepth(_depth);
		CRRPricer::_payoff_american.setDepth(_depth);
		for (int i = 0; i <= CRRPricer::_payoff_american._depth; i++) {
			for (int j = 0; j < i + 1; j++) {
				double S = _asset_price * pow((1 + _up), j) * pow((1 + _down), i - j); //compute the price of the asset : S(n,i) = S0(1+U)^i (1+D)^(n-i)
				CRRPricer::_payoff_american.setNode(i,j, _option->payoff(S)); //compute the payoff (payoff fonction of the price of the asset) for each node of our tree because american option can be executed at each time
			}
		}
		
	}
	for (int j = 0; j <= CRRPricer::_tree._depth; j++) {
		double S = _asset_price * pow((1 + _up), j) * pow((1 + _down), CRRPricer::_tree._depth - j); 		//S = S0(1+U)^i(1+D)^(n-i), we compute the payoff at the last depth of our tree 
		CRRPricer::_tree.setNode(CRRPricer::_tree._depth, j, _option->payoff(S)); //we do payoff(S), because H(N,i) = h(S(N,i))

	}
	

	for (int n = CRRPricer::_tree._depth - 1; n >= 0; n--) {
		for (int i = n; i >= 0; i--) {
			double value = q * CRRPricer::_tree.getNode(n + 1, i + 1) + (1 - q) * CRRPricer::_tree.getNode(n + 1, i); //compute the continuation value
			value = value / (1 + _interest_rate);
			if (_option->isAmericanOption()) { 
				h_s = _payoff_american.getNode(n,i); //correspond to the instrisic value
				if (h_s >= value) { // if the intrisic value is upper than the continuation, we add true in the exercice_condition tree
					CRRPricer::_exercice_condition.setNode(n, i, true);
					value = h_s; // and in this case, the continuation value take the value of the instrisic value
				}
				else {
					CRRPricer::_exercice_condition.setNode(n, i, false); // else we fix the node with false in the exercice_condition tree
				}	
			}
			CRRPricer::_tree.setNode(n, i, value);
		}
	}
	computed = true;
}

double facto(int n) { //factorial function
	if (n == 0 || n == 1) {
		return 1;
	}
	else {
		return n * facto(n - 1); 
	}
}

double CRRPricer::operator()(bool closed_form) // CRR Method with a closed-form formula
{
	if (!computed) compute(); //we compute the tree if it is not done
	double q = (_interest_rate - _down) / (_up - _down); //define the q 
	_depth = CRRPricer::_tree._depth - 1; //set the depth

	if (closed_form) { //define the H(0,0) instead of the CRR procedure
		double H = 0;
		double q = (_interest_rate - _down) / (_up - _down);
		for (int i = 0; i <= _depth; i++) {
			H += (facto(_depth) / (facto(i) * facto(_depth - i))) * pow(q, i) * pow(1 - q, _depth - i) * get(_depth, i); //sum(N!/(i!)(N-i!) q^i (1-q)^N-i* h (S(N,i))
		}
		H *= 1 / pow((1 + _interest_rate), _depth); //(1/(1+R)^N
		return H;
	}
	else {
		return get(0, 0);
	}
}

double CRRPricer::operator()()
{
	compute(); //return the price of the option
	_depth = CRRPricer::_tree._depth;
	return get(0, 0);
}

bool CRRPricer::getExercise(int n, int j) {
	bool verify = false; // we exercise the option if in our exercise_condition(n,j) tree there is true
	if (_option->isAmericanOption() == false) { // we can't use this function is there is not an american option
		std::cout << "You can't use getExercise function" << endl;
	}
	else {
		return _exercice_condition.getNode(n, j);
	}
	return verify; //else return false
}