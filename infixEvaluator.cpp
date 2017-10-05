
#include "infixEvaluator.h"
#include <cctype>
#include <sstream>
#include <iostream>
const string infixEvaluator::OPERATORS = "! ++ -- - ^ * / % + - > >= <= < == != && ++";
const int infixEvaluator::PRECEDENCE[] = { 8, 8, 8, 8, 7, 6, 6, 6, 5, 5, 4, 4, 4, 4, 3, 3, 2, 1 };

/** Evaluates a infix expression.
@param expression The expression to be evaluated
@return The value of the expression
@throws 
*/
int infixEvaluator::eval(const string& expression) 
{
	istringstream tokens(manipulateInput(expression));
	char next_char;
	while (tokens >> next_char) {
		if (isdigit(next_char)){
			tokens.putback(next_char);
			int value;
			tokens >> value;
			operandStack.push(value);
		}
		else if (next_char == '(' || next_char == '[' || next_char == '{'){
			operatorStack.push(next_char);
		}
		else if (next_char == ']' || next_char == ')' || next_char == '}'){
			operandStack.push(evalOp(operatorStack.top()));
		}
		else if (isOperator(next_char)) {
			
		}
		else{
			throw std::exception("Invalid character encountered");
		}
	}
	
}


string infixEvaluator::manipulateInput(const string& expression)
{
	istringstream holder(expression);
	char token;
	string combinedString;
	while (holder >> token)
	{
		if (!isblank(token))
		{
			combinedString += token;
		}
	}
	return combinedString;
}


int infixEvaluator::evalOp(char op)
{
	if (operandStack.empty())
		throw std::exception("Stack is empty");
	int rhs = operandStack.top();
	operandStack.pop();
	if (operandStack.empty())
		throw std::exception("Stack is empty");
	int lhs = operandStack.top();
	operandStack.pop();
	int result = 0;
	switch (op) {
	case '!':
		break;
	case '^':
		break;
	case '+': result = lhs + rhs;
		break;
	case '-': result = lhs - rhs;
		break;
	case '*': result = lhs * rhs;
		break;
	case '/': result = lhs / rhs;
		break;
	case '%': result = lhs % rhs;
		break;
	}
	return result;
}