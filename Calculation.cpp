#include "Calculation.h"
#include <string>
#include <iostream>
#include <cmath>
#include <stack>
#include <sstream> // istringstream 
using namespace std;


const string Calculation::OPERATORS = "-!^/*%D+";
const int Calculation::PRECEDENCE[] = {8,8,7,6,6,6,5,5};

bool Calculation::is_operator(char ch) const {
	return OPERATORS.find(ch) != string::npos;
}

int Calculation::eval_expression(const string& expression)
{
	istringstream tokens(expression);
	char nextChar;
	int operandCount = 0;
	int charCount = 0;
	bool operandMissing = true;
	while (tokens >> nextChar){
		if (isblank(nextChar))
			break;
		else
			charCount++;
		if (isdigit(nextChar)){
			if (operandCount == 1)
				throw std::exception("Two Operands in a row @ char: " + charCount);
			else{
				tokens.putback(nextChar);
				int value;
				tokens >> value;
				operandStack.push(value);
				operandCount++;
				operandMissing = false;
			}
		}
		else if (is_operator(nextChar)){
			if (operandCount == 1 && nextChar == '-'){
				nextChar = 'D';
			}
			if ((nextChar == '(') || (operatorStack.empty()) || operandMissing)
				if (nextChar == ')')
					throw std::exception(" you Goofed");
				else
					operatorStack.push(nextChar);
			else if ((precedence(nextChar) <= findStackPrecedence(operatorStack.top()) || (nextChar == ')'))){
				while (!operatorStack.empty() && (operatorStack.top() != '(') && (precedence(nextChar) <= findStackPrecedence(operatorStack.top()))){
					operatorEval(findStackPrecedence(operatorStack.top()));
				}
				operatorStack.push(nextChar);
			}
			else{
				operatorStack.push(nextChar);
			}
			operandCount = 0;
		}
	}
	while (!operatorStack.empty()){
		operatorEval(findStackPrecedence(operatorStack.top()));
	}
	int answer;
	answer = operandStack.top();
	return answer;

}

int Calculation::findStackPrecedence(char op)
{
	char holder;
	if (operatorStack.size() <= 1)
	{
			return precedence(op);
	}
	holder = operatorStack.top();
	operatorStack.pop();
	if (holder == operatorStack.top() && ((holder == '-') || (holder == '+')))
	{
		operatorStack.push(holder);
		return 8;
	}
	else if (holder == '=' && ((operatorStack.top() == '<') || (operatorStack.top() == '>')))
	{
		operatorStack.push(holder);
		return 4;
	}
	else if (holder == '=' && ((operatorStack.top() == '=') || (operatorStack.top() == '!')))
	{
		operatorStack.push(holder);
		return 3;
	}
	else if (holder == operatorStack.top() && (operatorStack.top() == '&'))
	{
		operatorStack.push(holder);
		return 2;
	}
	else if (holder == operatorStack.top() && (operatorStack.top() == '|'))
	{
		operatorStack.push(holder);
		return 1;
	}
	else
	{
		operatorStack.push(holder);
		return precedence(op);
	}
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
		break;
	case 3:
		break;
	case 2:
		break;
	case 1:
		break;
	}
}
	

int Calculation::precedence(char op) const 
{
	
	return PRECEDENCE[OPERATORS.find(op)];

}
