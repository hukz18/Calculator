#include "symbolize.h"
#include "calculator.h"
#include <iomanip>

int main(void)
{
	int equNum = 0, varNum = 0, **Auguments;
	vector<string> Equation;
	vector<string> Variable;
	string **Matrix;
	int c;
	cin >> c;
	cout << c << endl;
	cout << "Input your equations,end with an empty line:" << endl;
	equNum = getEqution(&Equation);
	cout << "Now verify your varitions, seperate by a space:" << endl;
	varNum = getVariable(&Variable);
	Matrix = new string *[equNum];
	Auguments = new int *[equNum];
	for (int i = 0; i < equNum; i++)
	{
		Matrix[i] = new string[varNum + 1];
		Auguments[i] = new int[varNum + 1];
	}
	getMatrix(Equation, Variable, Matrix);
	for (int i = 0; i < equNum; i++)
	{
		for (int j = 0; j < varNum + 1; j++)
		{
			Auguments[i][j] = stoi(Matrix[i][j]);
			cout << setw(4) << Auguments[i][j] << " ";
		}
		cout << endl;
	}
	cout << "done!" << endl;
	return 0;
}