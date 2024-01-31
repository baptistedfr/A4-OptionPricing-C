#pragma once
#include "Option.h"
#include "BinaryTree.h"


class CRRPricer {

private:
    Option* _option;
    int _depth;
    double _asset_price;
    double _up;
    double _down;
    double _interest_rate;
    double volatility;

public:
    
    CRRPricer(Option* option, int depth, double asset_price, double up, double down, double interest_rate); //constructor with up, down and interest_rate parameters
    double operator()(bool); //additionnal argument (closed_form) in parameter in our function to use the closed-form formula for option pricing
    CRRPricer(Option* option, int depth, double asset_price, double r, double volatility); //constructor without define up, down and interest_rate parameters
    void compute();
    double get(int n, int i); //to obtain the corresponding value of a node in our tree
    double operator()();
    bool getExercise(int, int); //return true if the intrisic value is upper than the continuation else false (for american options)
private:
    BinaryTree<double> _tree;
    bool computed;
    bool efficient;
    BinaryTree<bool> _exercice_condition;
    BinaryTree<double> _payoff_american;
};