
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
	std::cout << manipulateInput(" 190823 098f l;akjsdf");
	return 0;
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