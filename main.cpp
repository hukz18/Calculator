#include "symbolize.h"
#include "calculator.h"

int main(void)
{
	int equ_num = 0, var_num = 0;
	vector<Term> Varition;
	vector<string> Equation;
	cout << "Input your equations,end with an empty line:" << endl;
	equ_num = getEqution(&Equation);
	cout << "Now verify your varitions, seperate by a space:" << endl;
	var_num = getVariable(&Varition);
	cout << "done!" << endl;
	return 0;
}