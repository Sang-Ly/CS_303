#include "Calculation.h"
#include <string>
#include <iostream>
#include <cmath>
#include <stack>
#include <sstream> // istringstream 
using namespace std;

//const string Calculation::OPERATORS = "UD-!^/*%S+GL<>N=&|()";
//const int Calculation::PRECEDENCE[] = {8, 8, 8, 8, 7, 6, 6, 6, 5, 5, 4, 4, 4, 4, 3, 3, 2, 1, 0, 0 };




/*
bool Calculation::is_operator(char ch) const {
	return OPERATORS.find(ch) != string::npos;
}
*/
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
	else if (precedence(token) < precedence(operatorStack.top()) || (token == ')')){
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
	

/*
int Calculation::eval_expression(const string& expression)
{
	while (!operatorStack.empty())
		operatorStack.pop();
	while (!operatorStack.empty())
		operandStack.pop();

		/
	istringstream tokens(expression);
	char nextChar;
	int charCount = 0;
	int previousEntryOperand = false;
	bool operandSuccession = false;
	bool evaluationBefore = false; 
	bool operandMissing = true;
	while (tokens >> nextChar){
		if (isblank(nextChar))
			break;
		else
			charCount++;
		if (isdigit(nextChar)){
			if (operandSuccession == true)
				throw std::exception("Two Operands in a row @ char: " + charCount);
			else{
				tokens.putback(nextChar);
				int value;
				tokens >> value;
				operandStack.push(value);
				evaluationBefore = true;
				operandSuccession = true;
				operandMissing = false;
				previousEntryOperand = true;
			}
		}
		else if (is_operator(nextChar)){
			nextChar = processOperator(nextChar, evaluationBefore, previousEntryOperand);
			if ((nextChar == '(') || (operatorStack.empty()) || operandMissing)
				if (nextChar == ')')
					throw std::exception(" you Goofed");
				else
					operatorStack.push(nextChar);
			else if ((precedence(nextChar) < precedence(operatorStack.top()) || (nextChar == ')'))){
				while (!operatorStack.empty() && (operatorStack.top() != '(') && (precedence(nextChar) <= precedence(operatorStack.top())))
					operatorEval(precedence(operatorStack.top()));
				if (nextChar != ')')
					operatorStack.push(nextChar);
				else
					evaluationBefore = true;
				if (!operatorStack.empty() && operatorStack.top() == '(')
					operatorStack.pop();
			}
			else{
				evaluationBefore = false;
				operatorStack.push(nextChar);
			}
			operandSuccession = false;
			previousEntryOperand = false;
		}
	}
	while (!operatorStack.empty())
		operatorEval(precedence(operatorStack.top()));
	return operandStack.top();
}

char Calculation::processOperator(char op, bool opSuccession, bool previousEntryOperand)
{
	if ((opSuccession == true && op == '-')){
		return 'S';
	}
	else if (!operatorStack.empty() && operatorStack.top() == '!' && op == '='){
		operatorStack.pop();
		return'N';
	}
	else if (!operatorStack.empty() && operatorStack.top() == '>' && op == '='){
		operatorStack.pop();
		return'G';
	}
	else if (!operatorStack.empty() && operatorStack.top() == '<' && op == '='){
		operatorStack.pop();
		return'L';
	}
	else if (!operatorStack.empty() && (operatorStack.top() == '-' || operatorStack.top() == 'S') && op == '-' && previousEntryOperand == false){
		operatorStack.pop();
		return 'D';
	}
	else if (!operatorStack.empty() && (operatorStack.top() == '+') && op == '+' && previousEntryOperand == false){
		operatorStack.pop();
		return 'U';
	}
	else
		return op;
}
*/
int Calculation::returnAnswer()
{
	return 0;
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
			if (operatorStack.top() == 'U'){
				calculation++;
				operandStack.push(calculation);
				operatorStack.pop();
			}
			else if (operatorStack.top() == '!')
			{
				if (operandStack.top() != 0){
					operatorStack.pop();
					operandStack.push(0);
				}
				else{
					operatorStack.pop();
					operandStack.push(1);
				}
			}
			else if (operatorStack.top() == 'D'){
				calculation--;
				operandStack.push(calculation);
				operatorStack.pop();
			}
			else if (operatorStack.top() == '-'){
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
			if (operatorStack.top() == '*'){
				calculation = lhs * rhs;
				operatorStack.pop();
				operandStack.push(calculation);
			}
			else if (operatorStack.top() == '/'){
				calculation = lhs / rhs;
				operatorStack.pop();
				operandStack.push(calculation);
			}
			else if (operatorStack.top() == '%'){
				calculation = lhs % rhs;
				operatorStack.pop();
				operandStack.push(calculation);
			}
			break;
		case 5:
			if (operatorStack.top() == 'S'){
				calculation = lhs - rhs;
				operatorStack.pop();
				operandStack.push(calculation);
			}
			else if (operatorStack.top() == '+'){
				calculation = lhs + rhs;
				operatorStack.pop();
				operandStack.push(calculation);
			}
			break;
		case 4:
			if (operatorStack.top() == 'G'){
				if (lhs >= rhs)
					operandStack.push(1);
				else operandStack.push(0);
			}
			else if (operatorStack.top() == 'L'){
				if (lhs <= rhs)
					operandStack.push(1);
				else operandStack.push(0);
			}
			else if (operatorStack.top() == '>'){
				if (lhs > rhs)
					operandStack.push(1);
				else operandStack.push(0);
			}
			else if (operatorStack.top() == '<'){
				if (lhs < rhs)
					operandStack.push(1);
				else operandStack.push(0);
			}
			operatorStack.pop();
			break;
		case 3:
			if (operatorStack.top() == 'N'){
				if (lhs != rhs)
					operandStack.push(1);
				else
					operandStack.push(0);
			}
			else if (operatorStack.top() == '='){
				if (lhs == rhs)
					operandStack.push(1);
				else
					operandStack.push(0);
				operatorStack.pop();
			}
			operatorStack.pop();
			break;
		case 2:
			if (lhs && rhs)
				operandStack.push(1);
			else
				operandStack.push(0);
			operatorStack.pop();
			operatorStack.pop();
			break;
		case 1:
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
		}
	}
}
	
