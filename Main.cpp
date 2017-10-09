#include <iostream>
#include "Calculation.h"

using namespace std;

int main()
{
	Calculation finder;
	//<< finder.eval_expression("1+2*3") << endl;
	cout << finder.eval_expression("1+2*3") << endl;
	cout << finder.eval_expression("2+2^2*3") << endl;
	cout << finder.eval_expression("1==2") << endl;
	cout << finder.eval_expression("1+3>2") << endl;
	cout << finder.eval_expression("(4>=4)&&0") << endl;
	cout << finder.eval_expression("(1+2) * 3 ") << endl;
	cout << finder.eval_expression("++++2-5*(3^2)") << endl;
	

}
