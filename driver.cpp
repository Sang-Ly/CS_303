
#include "infixEvaluator.h"
#include <iostream>
int main()
{
	infixEvaluator theBest;
	std::cout << theBest.eval("1 + 2");
	return 0;
}