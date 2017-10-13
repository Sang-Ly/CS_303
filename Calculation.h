#pragma once
#include <string>
#include <iostream>
#include <stack>
using namespace std;
class Calculation
{
public:
	void eval(int tokenReceived);
	void eval(char tokenReceived);
	int eval_expression(const string& expression);
	int returnAnswer();
private:
	bool is_operator(char ch)const;
	int precedence(char op) const;
	char processOperator(char op, bool opSuccession, bool previousEntry);
	void operatorEval(int prec);
	stack<int> operandStack;
	stack<char> operatorStack;
	static const string OPERATORS;
	static const int PRECEDENCE[];
};

