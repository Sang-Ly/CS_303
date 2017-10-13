#include "parser.h"
#include <string>
#include <iostream>
#include <sstream>
using namespace std;

const string Parser::OPERATORS = "UD-!^/*%S+GL<>N=&|()";

bool Parser::is_operator(char ch) const {
	return OPERATORS.find(ch) != string::npos;
}

int Parser::eval_expression(const string& expression)
{
	calculator.clearStacks();
	errorCheck(expression);
	char token;
	string converted = convertString(expression);
	istringstream stream(converted);
	while (stream >> token)
	{
		if (isdigit(token))
		{
			stream.putback(token);
			int value;
			stream >> value;
			calculator.eval(value);
		}
		else
			calculator.eval(token);
	}
	return calculator.returnAnswer();
}

void Parser::processOperator(char op, string& converted)
{
	if ((converted.back() == ')' || !is_operator(converted.back())) && op == '-')
		converted += 'S';
	else if (converted.back() == '-' && op == '-')
		converted.back() = 'D';
	else if (converted.back() == '+'  && op == '+')
		converted.back() = 'U';
	else if (converted.back() == '<' && op == '=')
		converted.back() = 'L';
	else if (converted.back() == '>' && op == '=')
		converted.back() = 'G';
	else if (converted.back() == '!' && op == '=')
		converted.back() = 'N';
	else if (converted.back() == '=' && op == '=')
		converted.back() = '=';
	else if (converted.back() == '&' && op == '&')
		converted.back() = '&';
	else if (converted.back() == '|' && op == '|')
		converted.back() = '|';
	else
		converted += op;
}

void Parser::errorCheck(string expression)
{
	string temp;
	bool operandSuccession = false;
	char nextChar;
	istringstream token(expression);
	int twoOperand = 0;
	string unaryOP = "UD-!";
	string binaryOP = "!/*%S+GL<>N=&|";
	int andOp = 0;
	if (expression[0] == '+' && expression[1] != '+') { cout << "error"; }
	if (!isdigit(expression[0]) && expression[0] != ' ' && expression[0] != '!' && expression[0] != '+' && expression[0] != '-' && expression[0] != '(') {
		throw std::exception("Invalid Character");
	}
	while (token >> nextChar) {
		if (isblank(nextChar)) break;
		if (isdigit(nextChar)) {
			if (operandSuccession == true)
				throw std::exception("Two Operands in a row");
			else {
				token.putback(nextChar);
				int value;
				token >> value;
				operandSuccession = true;
			}
		}
		else if (is_operator(nextChar)) {
			temp += nextChar;
			operandSuccession = false;

			if (nextChar == '&') {
				andOp = andOp + 1;
				if (andOp > 2) { throw std::exception("Error"); }
			}
			else andOp = 0;
			
			if (nextChar == '/') {
				char look_next;
				token >> look_next;
				if (look_next == '0') { throw std::exception("Can't divide by zero"); }
				else token.putback(look_next);
			}
		}
		else { throw std::exception("Invalid Character"); }
	}
	
	temp = convertString(expression);
	for (int i = 0; i < temp.size(); i++) {
		temp[i] != unaryOP.string::npos;

		if (unaryOP.find(temp[i]) != string::npos) {
			if (binaryOP.find(temp[i + 1]) != string::npos) {
				throw std::exception("error");
			}
		}
	}
}

string Parser::convertString(string expression)
{
	string converted = "";
	string temp = "";
	for (int k = 0; k < expression.size(); k++)
	{
		if (converted.empty())
			converted = expression[k];
		else if (!is_operator(expression[k]) && expression[k] != ' ')
			converted += expression[k];
		else if (is_operator(expression[k]))
			processOperator(expression[k], converted);
	}
	return converted;
}