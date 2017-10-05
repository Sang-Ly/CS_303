#include "Calculation.h"
#include <string>
#include <iostream>
#include <cmath>
#include <stack>
#include <sstream> // istringstream 
using namespace std;

const string Calculation::OPERATORS = "! ^ * / % + - > = < & |";
const string Calculation::special = "! < >";
const int Calculation::PRECEDENCE[] = { 8, 8, 7, 6, 6, 6, 5, 5, 4, 4, 4, 4, 2, 1 };

bool Calculation::is_operator(char ch) const {
	return OPERATORS.find(ch) != string::npos;
}

/*string Calculation::remove_spaces(string& expression) {

	string temp;
	for (int i = 0; i < expression.size(); i++) {
		if (expression[i] != ' ') {
			temp += expression[i];
		}
	}
	expression = temp;
	cout << expression << endl;
	return expression;
}*/


int Calculation::eval_expression(const string& expression)
{
	istringstream tokens(expression);
	char nextChar;
	int operandCount = 0;
	int operatorCount = 0;
	int charCount = 0;
	bool isUnary = false;
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
				if (isUnary) {
					//evaluate.
				}
			}

		}
		else if (is_operator(nextChar)){
			
		}


		// Check if Operator
}

/*int Calculation::eval_expression(const string& expression) {
	istringstream tokens(expression);
	char nextChar;
	int operandCount = 0;
	int operatorCount = 0;
	int charCount = 0;
	bool isUnary = false;
	// Get tokens
	while (tokens >> nextChar) {
		if (isblank(nextChar))
			break;
		else
			charCount++;
		// if token is a digit push onto stack unless there is two digits in a row
		if (isdigit(nextChar)) {
			if (operandCount == 1)
				throw std::exception("Two Operands in a row @ char: " + charCount);
			else {
				tokens.putback(nextChar);
				int value;
				tokens >> value;
				operandStack.push(value);
				operandCount++;
				if (isUnary) {
					//evaluate.
				}
			}

		}

		// Check if Operator
		else if (is_operator(nextChar)) {
			//if previous token was operator check to see if is a two character operator
			if (operatorCount >=1) {

				if (operatorStack.top() == nextChar) {
					isUnary = true;

					switch (nextChar) {
					case 'D':
						operatorStack.pop();
						operatorStack.push('-');
						operatorStack.push('D');
						break;
					case 'I':
						operatorStack.pop();
						operatorStack.push('+');
						operatorStack.push('I');
						break;
					case '+':
						operatorStack.pop();
						operatorStack.push('I');
						break;
					case '-':
						operatorStack.pop();
						operatorStack.push('D');
						break;
					case '!': 
						operatorStack.push(nextChar);
						break;
					}
				}
				else if (nextChar == '=') {
					switch (operatorStack.top()) {
					case '!':
						operatorStack.pop();
						operatorStack.push('E');
						break;
					case '>':
						operatorStack.pop();
						operatorStack.push('G');
						break;
					case '<':
						operatorStack.pop();
						operatorStack.push('L');
						break;
					default:
						break;
					}
				}
				else if (operatorStack.top() == '-') {
					operatorStack.pop();
					operatorStack.push('N');
				} else {
					throw std::exception("Two operators in a row");
				}
			}
			else if (nextChar == '-') {
				operatorStack.push('N');
			} 
			throw std::exception("");

		}


	}


		throw std::exception("Invalid Character");

	}
	*/
	
	char next_char;


	/*while (tokens >> next_char) {
		if (isdigit(next_char)) {
			tokens.putback(next_char);
			int value;
			tokens >> value;
			operandStack.push(value);

		}
		else if (next_char == '(' || next_char == '[' || next_char == '{') {
			operatorStack.push(next_char);
		}
		else if (next_char == ']' || next_char == ')' || next_char == '}') {
			operandStack.push(evalOp(operatorStack.top()));
		}
		else if (isOperator(next_char)) {
		}
		else {
			throw std::exception("Invalid character encountered");
		}
	}
	return 0;*/
}

int Calculation::precedence(char op) const {

	return PRECEDENCE[OPERATORS.find(op)];

}