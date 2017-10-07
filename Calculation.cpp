#include "Calculation.h"
#include <string>
#include <iostream>
#include <cmath>
#include <stack>
#include <sstream> // istringstream 
using namespace std;


const string Calculation::OPERATORS = "+-";
const int Calculation::PRECEDENCE[] = { 8, 8 };

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
	// Get tokens
	while (tokens >> nextChar){
		if (isblank(nextChar))
			break;
		else
			charCount++;
		// if token is a digit push onto stack unless there is two digits in a row
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
			if ((nextChar == '(') || (operatorStack.empty()) || operandMissing)
				if (nextChar == ')')
					throw std::exception(" you Goofed");
				else
					operatorStack.push(nextChar);
			else if ((precedence(nextChar) < findStackPrecedence(operatorStack.top()) || (nextChar == ')'))){
				while (!operatorStack.empty() && (operatorStack.top() != '(') && (precedence(nextChar) <= findStackPrecedence(nextChar))){
					operatorEval(findStackPrecedence(operandStack.top()));
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
	if (holder == operatorStack.top() && ((holder == '!') || (holder == '-') || (holder == '+')))
	{
		operatorStack.push(holder);
		return 9;
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
	switch (prec)
	{
	case 9:
		if (operatorStack.top() == '+')
		{
			calculation = operandStack.top();
			operandStack.pop();
			calculation++;
			operandStack.push(calculation);
			operatorStack.pop();
			operatorStack.pop();
		}
		else if (operatorStack.top() == '-')
		{
			calculation = operandStack.top();
			operandStack.pop();
			calculation--;
			operandStack.push(calculation);
			operatorStack.pop();
			operatorStack.pop();

			
			/*calculation = operandStack.top();
			operandStack.pop();
			if (operatorStack.size() > 1)
			{
				operatorStack.pop();
				if (operatorStack.top() == '-')
				{
					calculation--;
					operandStack.push(calculation);
					operatorStack.pop();
				}
				else
				{
					calculation = calculation * -1;
					operandStack.push(calculation);
				}
			}
			else
			{
				calculation = calculation * -1;
				operandStack.push(calculation);
				operatorStack.pop();
			} */
		}
		break;
	case 8:
		calculation = operandStack.top();
		operandStack.pop();
		calculation = calculation * -1;
		operandStack.push(calculation);
		operatorStack.pop();
		break;
	}

}
	

int Calculation::precedence(char op) const 
{
	
	return PRECEDENCE[OPERATORS.find(op)];

}

/*
string holder = expression;
reverse(holder.begin(), holder.end());
istringstream tokens(holder);
char nextChar;
int operandCount = 0;
int charCount = 0;
bool operandMissing = true;
// Get tokens
while (tokens >> nextChar)
{
	if (isblank(nextChar))
		break;
	else
		charCount++;
	// if token is a digit push onto stack unless there is two digits in a row
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
	else if (is_operator(nextChar))
	{
		if ((nextChar == '(') || (operatorStack.empty()) || operandMissing)
			if (nextChar == ')')
				throw std::exception(" you Goofed");
			else
				operatorStack.push(nextChar);
		else if ((precedence(nextChar) < precedence(operatorStack.top()) || (nextChar == ')')))
		{
			while (!operatorStack.empty() && (operatorStack.top() != '(') && (precedence(nextChar) <= precedence(operatorStack.top())))
			{
				cout << "evaluated";
				operatorStack.pop();
			}
		}
		operandCount = 0;
	}

}
*/