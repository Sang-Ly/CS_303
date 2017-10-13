#include "Parser.h"
#include <string>
#include <iostream>
#include <sstream> // istringstream 
using namespace std;

const string Evaluator::OPERATORS = "!+=^*%+-|&><=";

bool Evaluator::is_operator(char ch) const {
	return OPERATORS.find(ch) != string::npos;
}

int Evaluator::eval_expression(const string& expression)
{
	errorCheck(expression);

	return 0;
}
void Evaluator::errorCheck(string expression) {
	expression = "( 10 &&&& 993";
	istringstream token(expression);
	int twoOperand = 0;
	string startError = ")|&=><+*/%^";
	int andOp = 0;





	if (!isdigit(expression[0]) && expression[0] != ' ' && expression[0] != '!' && expression[0] != '-' || expression[0] != '(') {
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
			operandSuccession = false;
			if (nextChar == '&') {
				andOp = andOp + 1;
				if (andOp > 2) { throw std::exception("Error"); }
			}
			else andOp = 0;
		}
		else { throw std::exception("Invalid Character"); }
	}






}

string Evaluator::convertString(string expression) const {
	return "";
}