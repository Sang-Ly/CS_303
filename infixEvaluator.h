#ifndef INFIX_EVALUATOR_H_
#define INFIX_EVAULATOR_H_

#include <stack>
#include <string>
using namespace std;


class infixEvaluator {
	// Public member functions
public:
	/** Evaluates an infix expression.
	@param expression The expression to be evaluated
	@return The value of the expression
	*/
	int eval(const string& expression);

	// Private member functions
private:
	/** Evaluates the current operator.
	This function pops the two operands off the operand
	stack and applies the operator.
	@param op A character representing the operator
	*/
	int evalOp(char op);

	string manipulateInput(const string& expression);

	/** Determines whether a character is an operator.
	@param ch The character to be tested
	@return true if the character is an operator
	*/
	bool isOperator(char ch) const {
		return OPERATORS.find(ch) != string::npos;
	}

	int precedence(char op) const {
		return PRECEDENCE[OPERATORS.find(op)];
	}

	// Data fields
	static const string OPERATORS;
	static const int PRECEDENCE[];
	stack<int> operandStack;
	stack<char> operatorStack;
};
#endif
