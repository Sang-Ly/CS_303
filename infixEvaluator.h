#ifndef INFIX_EVALUATOR_H_
#define INFIX_EVAULATOR_H_

#include <stack>
#include <string>
using namespace std;

class infixEvaluator {
	// Public member functions
public:
	/** Evaluates a postfix expression.
	@param expression The expression to be evaluated
	@return The value of the expression
	@throws Syntax_Error if a syntax error is detected
	*/
	int eval(const string& expression);

	// Private member functions
private:
	/** Evaluates the current operator.
	This function pops the two operands off the operand
	stack and applies the operator.
	@param op A character representing the operator
	@throws Syntax_Error if top is attempted on an empty stack
	*/
	int evalOp(char op);

	/** Determines whether a character is an operator.
	@param ch The character to be tested
	@return true if the character is an operator
	*/
	bool isOperator(char ch) const {
		return OPERATORS.find(ch) != string::npos;
	}

	// Data fields
	string OPERATORS;
	stack<int> operandStack;
	stack<char> operatorStack;
};
#endif
