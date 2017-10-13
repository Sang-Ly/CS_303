#pragma once
#include <string>
#include <iostream>
#include "Calculation.h"
using namespace std;
class Parser
{
public:
	int eval_expression(const string& expression);

private:
	Calculation calculator;
	bool is_operator(char ch) const;
	static const string OPERATORS;
	void processOperator(char op, string & converted);
	string convertString(string expression);
	void errorCheck(string expression);
};
