#pragma once
#include <string>
#include <iostream>
#include "Calculation.h"
using namespace std;
class Evaluator
{
public:
	int eval_expression(const string& expression);
private:
	char nextChar;
	bool operandSuccession = false;
	Calculation calculate;
	bool is_operator(char ch) const;
	static const string OPERATORS;
	void errorCheck(string expression);
	string convertString(string expression) const;
};

