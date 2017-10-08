#pragma once
#include <string>
#include <iostream>
#include <stack>
using namespace std;
class Calculation
{
public:
	int eval_expression(const string& expression);
private:
	bool is_operator(char ch)const;
	int precedence(char op) const;
	int findStackPrecedence(char op);
	void operatorEval(int prec);
	stack<int> operandStack;
	stack<char> operatorStack;
	static const string OPERATORS;
	static const int PRECEDENCE[];
};

