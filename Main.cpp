#include <iostream>
#include "Calculation.h"

using namespace std;

int main()
{
	Calculation finder;
	int expression = finder.eval_expression("++- --7");
	cout << expression;


}
