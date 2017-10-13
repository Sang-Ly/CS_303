#include "Calculation.h"
#include <string>
#include <iostream>
#include <cmath>
#include <stack>
#include <sstream> 
using namespace std;
// Check the precedence of the operator
int Calculation::precedence(char op) const
{
	switch (op) {
	case '!': case 'U': case 'D': case '-': return 8; break;		// return precedence value of 8
	case '^': return 7;	break;										// return precedence value of 7
	case '*': case '/': case '%': return 6; break;					// return precedence value of 6
	case '+': case 'S': return 5; break;							// return precedence value of 5
	case '>': case '<': case 'G': case 'L': return 4; break;		// return precedence value of 4
	case '=': return 3; break;										// return precedence value of 3
	case '&': return 2; break;										// return precedence value of 2
	case '|': return 1; break;										// return precedence value of 1
	case '(': case ')': return 0; break;							// return precedence value of 0
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
	// Declare variable
	int calculation;
	int lhs;
	int rhs;
	if (prec == 8)			// when prec value is equal to 8
	{
		calculation = operandStack.top();		// store top of operand stack to calculation variable
		operandStack.pop();						// pop top of operand stack
		switch (prec)
		{
		case 8:
			if (operatorStack.top() == 'U') {		// Operator equal to ++ 
				calculation++;						// Increase calculation by 1
				operandStack.push(calculation);		// Push the value of calculation onto stack
				operatorStack.pop();				// Pop the operator stack
			}
			else if (operatorStack.top() == '!')	// Operator equal to !
			{
				if (operandStack.top() != 0) {		// Check top of operand stack value not equal to zero
					operatorStack.pop();			// Pop operator stack
					operandStack.push(0);			// When top of operand stack value not equal to zero push 0 onto operand stack
				}
				else {
					operatorStack.pop();			// pop operator stack
					operandStack.push(1);			// When top of operand stack is equal to zero, push 1 onto operand stack
				}
			}
			else if (operatorStack.top() == 'D') {	// Operator equal to --
				calculation--;						// Decrease calculation value by 1
				operandStack.push(calculation);		// Store calculation value on operand stack
				operatorStack.pop();				// Pop top of operator stack
			}
			else if (operatorStack.top() == '-') {	// Operator equal to -
				calculation = calculation * -1;		// Multiply calculation by negative 1
				operandStack.push(calculation);		// Push the new value of calculation onto operand stack
				operatorStack.pop();				// Pop top of operator stack
			}
			break;
		}
	}
	else   // When precedence is not 8
	{
		rhs = operandStack.top();					// Store top of operand stack into rhs variable
		operandStack.pop();							// Pop top of operand stack
		lhs = operandStack.top();					// Store the next top of operand stack into lhs variable
		operandStack.pop();							// Pop top of operand stack
		switch (prec)	// check precedence 
		{

		case 7:	// When precedence value equal to 7
			calculation = pow(lhs, rhs);			// Calculate the lhs and rhs operand using power rule
			operatorStack.pop();					// Pop top of operator stack
			operandStack.push(calculation);			// Push the new value of calculation onto operand stack
			break;
		case 6:// When precedence value equal to 6
			if (operatorStack.top() == '*') {		// Check top of operator stack if equal to *
				calculation = lhs * rhs;			// Calculate the lhs and rhs operand using multiplication
				operatorStack.pop();				// Pop top of operator stack 
				operandStack.push(calculation);		// Push the new value of calculation onto operand stack
			}
			else if (operatorStack.top() == '/') {	// Check top of operator Stack if equal to /
				calculation = lhs / rhs;			// Calculate the lhs and rhs operand using division
				operatorStack.pop();				// Pop top of operator stack 
				operandStack.push(calculation);		// Push the new value of calculation onto operand stack
			}
			else if (operatorStack.top() == '%') {
				calculation = lhs % rhs;			// Calculate the lhs and rhs operand using mod
				operatorStack.pop();				// Pop top of operator stack 
				operandStack.push(calculation);		// Push the new value of calculation onto operand stack
			}
			break;
		case 5: // When precedence value equal to 5
			if (operatorStack.top() == 'S') {		// Check if top of operator stack equal to -
				calculation = lhs - rhs;			// Calculate the lhs and rhs operand using subtraction 
				operatorStack.pop();				// Pop top of operator stack 
				operandStack.push(calculation);		// Push the new value of calculation onto operand stack
			}
			else if (operatorStack.top() == '+') {	// Check if top of operator stack equal to + 
				calculation = lhs + rhs;
				operatorStack.pop();				// Pop top of operator stack 
				operandStack.push(calculation);		// Push the new value of calculation onto operand stack
			}
			break;
		case 4: // When precedence value equal to 4
			if (operatorStack.top() == 'G') {		// Check if top of operator stack equal to >=
				if (lhs >= rhs)						// Evaluate lhs if greater than or equal to rhs
					operandStack.push(1);			// Push 1 onto operand stack if true
				else operandStack.push(0);			// Push 0 onto operand stack if false
			}
			else if (operatorStack.top() == 'L') {	// Check if top of operator stack equal to <=
				if (lhs <= rhs)						// Evaluate lhs if less than or equal to rhs
					operandStack.push(1);			// Push 1 onto operand stack if true
				else operandStack.push(0);			// Push 0 onto operand stack if false
			}
			else if (operatorStack.top() == '>') {	// Check if top of operator stack equal to >
				if (lhs > rhs)						// Evaluate lhs if greater than rhs 
					operandStack.push(1);			// Push 1 onto operand stack if true
				else operandStack.push(0);			// Push 0 onto operand stack if false
			}
			else if (operatorStack.top() == '<') {	// Check if top of operator stack equal to <
				if (lhs < rhs)						// Evaluate lhs if less than rhs 
					operandStack.push(1);			// Push 1 onto operand stack if true
				else operandStack.push(0);			// Push 0 onto operand stack if false
			}
			operatorStack.pop();					// Pop top of operator stack 
			break;
		case 3: // When precedence value equal to 3
			if (operatorStack.top() == 'N') {		// Check if top of operator stack equal to !=
				if (lhs != rhs)						// Evaluate lhs if not equal to rhs 
					operandStack.push(1);			// Push 1 onto operand stack if true
				else
					operandStack.push(0);			// push 0 onto operand stack if false
			}
			else if (operatorStack.top() == '=') {	// Check if top of operator stack equal to =
				if (lhs == rhs)						// Evaluate lhs and rhs if they are equal
					operandStack.push(1);			// Push 1 onto operand stack if true
				else
					operandStack.push(0);			// Push 0 onto operand stack if false
			}
			operatorStack.pop();					// Pop top of operator stack 
			break;
		case 2: // When precedence value equal to 2
			if (lhs && rhs)							// Check if top of operator stack equal to &
				operandStack.push(1);				// Push 1 if lhs and rhs are true
			else
				operandStack.push(0);				// Push 0 if lhs and rhs are false
			operatorStack.pop();					// Pop top of operator stack 
			break;		
		case 1: // When precedence value equal to 1
			if (lhs || rhs)							// Check if top of operator stack equal to |
				operandStack.push(1);				// Push 1 if lhs or rhs are true
			else
				operandStack.push(0);				// Push 0 if lhs or rhs are false
			operatorStack.pop();					// Pop top of operator stack 
			break;
		case 0: // When precedence value equal to 0
			operatorStack.pop();					// Pop top of operator stack 
			break;
		}
	}
}