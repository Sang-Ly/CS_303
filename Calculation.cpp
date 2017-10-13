#include "Calculation.h"
#include <string>
#include <iostream>
#include <cmath>
#include <stack>
#include <sstream> // istringstream 
using namespace std;

int Calculation::precedence(char op) const
{
	switch (op) {
	case '!': case 'U': case 'D': case '-': return 8; break;
	case '^': return 7;	break;
	case '*': case '/': case '%': return 6; break;
	case '+': case 'S': return 5; break;
	case '>': case '<': case 'G': case 'L': return 4; break;
	case '=': return 3; break;
	case '&': return 2; break;
	case '|': return 1; break;
	case '(': case ')': return 0; break;
	}
}

void Calculation::eval(int token)
{
	operandStack.push(token);
}

void Calculation::eval(char token)
{
	if (token == '(' || operatorStack.empty())
		operatorStack.push(token);
	else if (precedence(token) < precedence(operatorStack.top()) || (token == ')')) {
		while (!operatorStack.empty() && (operatorStack.top() != '(') && (precedence(token) <= precedence(operatorStack.top())))
			operatorEval(precedence(operatorStack.top()));
		if (token != ')')
			operatorStack.push(token);
		if (!operatorStack.empty() && operatorStack.top() == '(')
			operatorStack.pop();
	}
	else
		operatorStack.push(token);
}

void Calculation::clearStacks()
{
	while (!operatorStack.empty())
		operatorStack.pop();
	while (!operatorStack.empty())
		operandStack.pop();
}

int Calculation::returnAnswer()
{
	while (!operatorStack.empty())
		operatorEval(precedence(operatorStack.top()));
	return operandStack.top();
}

void Calculation::operatorEval(int prec)
{
	int calculation;
	int lhs;
	int rhs;
	if (prec == 8)
	{
		calculation = operandStack.top();
		operandStack.pop();
		switch (prec)
		{
		case 8:
			if (operatorStack.top() == 'U') {
				calculation++;
				operandStack.push(calculation);
				operatorStack.pop();
			}
			else if (operatorStack.top() == '!')
			{
				if (operandStack.top() != 0) {
					operatorStack.pop();
					operandStack.push(0);
				}
				else {
					operatorStack.pop();
					operandStack.push(1);
				}
			}
			else if (operatorStack.top() == 'D') {
				calculation--;
				operandStack.push(calculation);
				operatorStack.pop();
			}
			else if (operatorStack.top() == '-') {
				calculation = calculation * -1;
				operandStack.push(calculation);
				operatorStack.pop();
			}
			break;
		}
	}
	else
	{
		rhs = operandStack.top();
		operandStack.pop();
		lhs = operandStack.top();
		operandStack.pop();
		switch (prec)
		{

		case 7:
			calculation = pow(lhs, rhs);
			operatorStack.pop();
			operandStack.push(calculation);
			break;
		case 6:
			if (operatorStack.top() == '*') {
				calculation = lhs * rhs;
				operatorStack.pop();
				operandStack.push(calculation);
			}
			else if (operatorStack.top() == '/') {
				calculation = lhs / rhs;
				operatorStack.pop();
				operandStack.push(calculation);
			}
			else if (operatorStack.top() == '%') {
				calculation = lhs % rhs;
				operatorStack.pop();
				operandStack.push(calculation);
			}
			break;
		case 5:
			if (operatorStack.top() == 'S') {
				calculation = lhs - rhs;
				operatorStack.pop();
				operandStack.push(calculation);
			}
			else if (operatorStack.top() == '+') {
				calculation = lhs + rhs;
				operatorStack.pop();
				operandStack.push(calculation);
			}
			break;
		case 4:
			if (operatorStack.top() == 'G') {
				if (lhs >= rhs)
					operandStack.push(1);
				else operandStack.push(0);
			}
			else if (operatorStack.top() == 'L') {
				if (lhs <= rhs)
					operandStack.push(1);
				else operandStack.push(0);
			}
			else if (operatorStack.top() == '>') {
				if (lhs > rhs)
					operandStack.push(1);
				else operandStack.push(0);
			}
			else if (operatorStack.top() == '<') {
				if (lhs < rhs)
					operandStack.push(1);
				else operandStack.push(0);
			}
			operatorStack.pop();
			break;
		case 3:
			if (operatorStack.top() == 'N') {
				if (lhs != rhs)
					operandStack.push(1);
				else
					operandStack.push(0);
			}
			else if (operatorStack.top() == '=') {
				if (lhs == rhs)
					operandStack.push(1);
				else
					operandStack.push(0);
			}
			operatorStack.pop();
			break;
		case 2:
			if (lhs && rhs)
				operandStack.push(1);
			else
				operandStack.push(0);
			operatorStack.pop();
			break;
		case 1:
			if (lhs || rhs)
				operandStack.push(1);
			else
				operandStack.push(0);
			operatorStack.pop();
			break;
		case 0:
			operatorStack.pop();
			break;
		}
	}
}