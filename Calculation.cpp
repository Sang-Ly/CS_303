#include "Calculation.h"
#include <string>
#include <iostream>
#include <cmath>
#include <stack>
#include <sstream> // istringstream 
using namespace std;


const string Calculation::OPERATORS = "-!^/*%D+GL<>N=&|()";
const int Calculation::PRECEDENCE[] = {8,8,7,6,6,6,5,5,4,4,4,4,3,3,2,1,0,0};

bool Calculation::is_operator(char ch) const {
	return OPERATORS.find(ch) != string::npos;
}

int Calculation::eval_expression(const string& expression)
{
	while (!operatorStack.empty())
		operatorStack.pop();
	while (!operatorStack.empty())
		operandStack.pop();
	istringstream tokens(expression);
	char nextChar;
	int operandSuccessionCount = 0;
	int charCount = 0;
	bool operandMissing = true;
	while (tokens >> nextChar){
		if (isblank(nextChar))
			break;
		else
			charCount++;
		if (isdigit(nextChar)){
			if (operandSuccessionCount == 1)
				throw std::exception("Two Operands in a row @ char: " + charCount);
			else{
				tokens.putback(nextChar);
				int value;
				tokens >> value;
				operandStack.push(value);
				operandSuccessionCount++;
				operandMissing = false;
			}
		}
		else if (is_operator(nextChar)){
			if ((operandSuccessionCount == 1 && nextChar == '-'))
				nextChar = 'D';
			else if (!operatorStack.empty() && operatorStack.top() == '!' && nextChar == '='){
				operatorStack.pop();
				nextChar = 'N';
			}
			else if (!operatorStack.empty() && operatorStack.top() == '>' && nextChar == '='){
				operatorStack.pop();
				nextChar = 'G';
			}
			else if (!operatorStack.empty() && operatorStack.top() == '<' && nextChar == '='){
				operatorStack.pop();
				nextChar = 'L';
			}
			if ((nextChar == '(') || (operatorStack.empty()) || operandMissing)
				if (nextChar == ')')
					throw std::exception(" you Goofed");
				else
					operatorStack.push(nextChar);
			else if ((precedence(nextChar) < findStackPrecedence(operatorStack.top()) || (nextChar == ')'))){
				while (!operatorStack.empty() && (operatorStack.top() != '(') && (precedence(nextChar) <= findStackPrecedence(operatorStack.top())))
					operatorEval(findStackPrecedence(operatorStack.top()));
				if (nextChar != ')')
					operatorStack.push(nextChar);
				if (!operatorStack.empty() && operatorStack.top() == '(')
					operatorStack.pop();
			}
			else
				operatorStack.push(nextChar);
			operandSuccessionCount = 0;
		}
	}
	while (!operatorStack.empty())
		operatorEval(findStackPrecedence(operatorStack.top()));
	int answer;
	answer = operandStack.top();
	return answer;

}

int Calculation::findStackPrecedence(char op)
{
	char top;
	char underTop;
	if (operatorStack.size() <= 1)
		return precedence(op);
	top = operatorStack.top();
	operatorStack.pop();
	underTop = operatorStack.top();
	operatorStack.push(top);
	if ((top == underTop) && ((top == '-') || (top == '+')))
		return 8;
	else if (top == underTop && (underTop == '&'))
		return 2;
	else if (top == underTop && (underTop == '|'))
		return 1;
	else
		return precedence(op);
}

void Calculation::operatorEval(int prec)
{
	int calculation;
	int lhs;
	int rhs;
	switch (prec)
	{
	case 8:
		if (operatorStack.top() == '+')
		{
			calculation = operandStack.top();
			operandStack.pop();
			calculation++;
			operandStack.push(calculation);
			operatorStack.pop();
			operatorStack.pop();
		}
		else if (operatorStack.top() == '!')
		{
			if (operandStack.top() != 0)
			{
				operatorStack.pop();
				operandStack.push(0);
			}
			else
			{
				operatorStack.pop();
				operandStack.push(1);
			}
		}
		else if (operatorStack.top() == '-')
		{
			int remainder;
			int count = 0;
			while ((!operatorStack.empty() && (operatorStack.top() == '-')))
			{
				count = count + 1;
				operatorStack.pop();
			}
			calculation = operandStack.top();
			operandStack.pop();
			calculation = calculation - (count / 2);
			remainder = count % 2;
			if (remainder == 1)
			{
				calculation = calculation * -1;
			}
			operandStack.push(calculation);
		}
		break;
	case 7:
		rhs = operandStack.top();
		operandStack.pop();
		lhs = operandStack.top();
		operandStack.pop();
		calculation = pow(lhs, rhs);
		operatorStack.pop();
		operandStack.push(calculation);
		break;
	case 6:
		if (operatorStack.top() == '*')
		{
			rhs = operandStack.top();
			operandStack.pop();
			lhs = operandStack.top();
			operandStack.pop();
			calculation = lhs * rhs;
			operatorStack.pop();
			operandStack.push(calculation);
			break;
		}
		else if (operatorStack.top() == '/')
		{
			rhs = operandStack.top();
			operandStack.pop();
			lhs = operandStack.top();
			operandStack.pop();
			calculation = lhs / rhs;
			operatorStack.pop();
			operandStack.push(calculation);
			break;
		}
		else if (operatorStack.top() == '%')
		{
			rhs = operandStack.top();
			operandStack.pop();
			lhs = operandStack.top();
			operandStack.pop();
			calculation = lhs % rhs;
			operatorStack.pop();
			operandStack.push(calculation);
		}
		break;
	case 5:
		if (operatorStack.top() == 'D')
		{
			rhs = operandStack.top();
			operandStack.pop();
			lhs = operandStack.top();
			operandStack.pop();
			calculation = lhs - rhs;
			operatorStack.pop();
			operandStack.push(calculation);
		}
		else if (operatorStack.top() == '+')
		{
			rhs = operandStack.top();
			operandStack.pop();
			lhs = operandStack.top();
			operandStack.pop();
			calculation = lhs + rhs;
			operatorStack.pop();
			operandStack.push(calculation);
		}
		break;
	case 4:
		rhs = operandStack.top();
		operandStack.pop();
		lhs = operandStack.top();
		operandStack.pop();
		if (operatorStack.top() == 'G')
		{
			if (lhs >= rhs)
				operandStack.push(1);
			else operandStack.push(0);
		}
		else if (operatorStack.top() == 'L')
		{
			if (lhs <= rhs)
				operandStack.push(1);
			else operandStack.push(0);
		}
		else if (operatorStack.top() == '>')
		{
			if (lhs > rhs)
				operandStack.push(1);
			else operandStack.push(0);
		}
		else if (operatorStack.top() == '<')
		{
			if (lhs < rhs)
				operandStack.push(1);
			else operandStack.push(0);
		}
		operatorStack.pop();
		break;
	case 3:
		rhs = operandStack.top();
		operandStack.pop();
		lhs = operandStack.top();
		operandStack.pop();
		if (operatorStack.top() == 'N')
		{
			if (lhs != rhs)
				operandStack.push(1);
			else
				operandStack.push(0);
		}
		else if (operatorStack.top() == '=')
		{
			if (lhs == rhs)
				operandStack.push(1);
			else
				operandStack.push(0);
			operatorStack.pop();
		}
		operatorStack.pop();
		break;
	case 2:
		rhs = operandStack.top();
		operandStack.pop();
		lhs = operandStack.top();
		operandStack.pop();
		if (lhs && rhs)
			operandStack.push(1);
		else
			operandStack.push(0);
		operatorStack.pop();
		operatorStack.pop();
		break;
	case 1:
		rhs = operandStack.top();
		operandStack.pop();
		lhs = operandStack.top();
		operandStack.pop();
		if (lhs || rhs)
			operandStack.push(1);
		else
			operandStack.push(0);
		operatorStack.pop();
		operatorStack.pop();
		break;
	case 0:
		operatorStack.pop();
		break;


	/*
	int calculation;
	int lhs;
	int rhs;
	switch (prec)
	{
	case 8:
		if (operatorStack.top() == '+')
		{
			calculation = operandStack.top();
			operandStack.pop();
			calculation++;
			operandStack.push(calculation);
			operatorStack.pop();
			operatorStack.pop();
		}
		else if (operatorStack.top() == '!')
		{
			if (operandStack.top() != 0)
			{
				operatorStack.pop();
				operandStack.push(0);
			}
			else
			{
				operatorStack.pop();
				operandStack.push(1);
			}
		}
		else if (operatorStack.top() == '-')
		{
			int remainder;
			int count=0;
			while ((!operatorStack.empty() && (operatorStack.top() == '-')))
			{
				count = count + 1;
				operatorStack.pop();
			}
			calculation = operandStack.top();
			operandStack.pop();
			calculation = calculation - (count / 2);
			remainder = count % 2;
			if (remainder == 1)
			{
				calculation = calculation * -1;
			}
			operandStack.push(calculation);
		}
		break;
	case 7:
		rhs = operandStack.top();
		operandStack.pop();
		lhs = operandStack.top();
		operandStack.pop();
		calculation = pow(lhs, rhs);
		operatorStack.pop();
		operandStack.push(calculation);
		break;
	case 6:
		if (operatorStack.top() == '*')
		{
			rhs = operandStack.top();
			operandStack.pop();
			lhs = operandStack.top();
			operandStack.pop();
			calculation = lhs * rhs;
			operatorStack.pop();
			operandStack.push(calculation);
			break;
		}
		else if (operatorStack.top() == '/')
		{
			rhs = operandStack.top();
			operandStack.pop();
			lhs = operandStack.top();
			operandStack.pop();
			calculation = lhs / rhs;
			operatorStack.pop();
			operandStack.push(calculation);
			break;
		}
		else if (operatorStack.top() == '%')
		{
			rhs = operandStack.top();
			operandStack.pop();
			lhs = operandStack.top();
			operandStack.pop();
			calculation = lhs % rhs;
			operatorStack.pop();
			operandStack.push(calculation);
		}
		break;
	case 5:
		if (operatorStack.top() == 'D')
		{
			rhs = operandStack.top();
			operandStack.pop();
			lhs = operandStack.top();
			operandStack.pop();
			calculation = lhs - rhs;
			operatorStack.pop();
			operandStack.push(calculation);
		}
		else if (operatorStack.top() == '+')
		{
			rhs = operandStack.top();
			operandStack.pop();
			lhs = operandStack.top();
			operandStack.pop();
			calculation = lhs + rhs;
			operatorStack.pop();
			operandStack.push(calculation);
		}
		break;
	case 4:
		rhs = operandStack.top();
		operandStack.pop();
		lhs = operandStack.top();
		operandStack.pop();
		if (operatorStack.top() == '=')
		{
			operatorStack.pop();
			if (operatorStack.top() == '>')
			{
				if (lhs >= rhs)
					operandStack.push(1);
			}
			else if (operatorStack.top() == '<')
			{
				if (lhs <= rhs)
					operandStack.push(1);
			}
			else operandStack.push(0);
		}
		if (operatorStack.top() == '>')
		{
			if (lhs > rhs)
				operandStack.push(1);
			else operandStack.push(0);
		}
		else if (operatorStack.top() == '<')
		{
			if (lhs < rhs)
				operandStack.push(1);
			else operandStack.push(0);
		}
		operatorStack.pop();
		break;
	case 3:
		rhs = operandStack.top();
		operandStack.pop();
		lhs = operandStack.top();
		operandStack.pop();
		if (operatorStack.top() == 'N')
		{
			if (lhs != rhs)
				operandStack.push(1);
			else
				operandStack.push(0);
		}
		else if (operatorStack.top() == '=')
		{
			if (lhs == rhs)
				operandStack.push(1);
			else
				operandStack.push(0);
			operatorStack.pop();
		}
		operatorStack.pop();
		break;
	case 2:
		rhs = operandStack.top();
		operandStack.pop();
		lhs = operandStack.top();
		operandStack.pop();
		if (lhs && rhs)
			operandStack.push(1);
		else
			operandStack.push(0);
		operatorStack.pop();
		operatorStack.pop();
		break;
	case 1:
		rhs = operandStack.top();
		operandStack.pop();
		lhs = operandStack.top();
		operandStack.pop();
		if (lhs || rhs)
			operandStack.push(1);
		else
			operandStack.push(0);
		operatorStack.pop();
		operatorStack.pop();
		break;
	case 0:
		operatorStack.pop();
		break;*/
	}
}
	

int Calculation::precedence(char op) const 
{
	
	return PRECEDENCE[OPERATORS.find(op)];

}
