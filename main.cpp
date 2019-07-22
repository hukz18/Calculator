#include "tools.h"
#include "symbolize.h"
#include "operation.h"
#include "calculator.h"
#include <iomanip>

bool testOpe(void)
{
	cout << "please input the arithmetic expression:" << endl;
	string test;
	cin >> test;
	opExpression op(test);
	//cout << test << endl;

	/*cout << op.expression << endl;
	for (unsigned int i = 0; i < op.expression.length(); i++)
		if (op.priority[i] != 1e6)
			cout << op.priority[i] << " ";
	cout << endl << "done!" << endl;*/
	cout << "the reselt of the expression is:" << endl;
	cout << calculate(op) << endl;
	cin.get();
	return true;
}

bool testCal(void)
{
	int equNum = 0, varNum = 0;
	double **Auguments;
	vector<string> Equation;
	vector<string> Variable;
	string **Matrix;
	cout << "Input your equations,end with an empty line:" << endl;
	equNum = getEqution(&Equation);
	cout << "Now verify your varitions, seperate by a space:" << endl;
	varNum = getVariable(&Variable);
	Matrix = new string *[equNum];
	Auguments = new double *[equNum];
	for (int i = 0; i < equNum; i++)
	{
		Matrix[i] = new string[varNum + 1];
		Auguments[i] = new double[varNum + 1];
	}
	getMatrix(Equation, Variable, Matrix);
	cout << "The augumented coeffient matrix is:" << endl;
	for (int i = 0; i < equNum; i++)
	{
		for (int j = 0; j < varNum + 1; j++)
		{
			Auguments[i][j] = myStod(Matrix[i][j]);
			cout << setw(4) << Auguments[i][j] << " ";
		}
		cout << endl;
	}
	if (Elimination(Auguments, equNum, varNum))
	{
		cout << "The solutions are as follows:" << endl;
		for (int i = 0; i < varNum; i++)
			cout << Variable[i] << " = " << Auguments[i][varNum] << ",";
	}
	cout << endl << "Done!" << endl;
	cin.get();
	for (int i = 0; i < equNum; i++)
	{
		delete[](Matrix[i]);
		delete[](Auguments[i]);
	}
	delete Matrix;
	delete Auguments;
	return true;
}

//写factorize,重载等于来改写trySymplize,每次操作完调用tryfactorize,注意monomial的指数可能为负带来的问题
//改写所有的分式多项式运算处理前缀问题，编写各自鲁棒的iszero和isdigit(isnull)，改写之前的判定,思考各自的缺省值是否合理
//f2.terms[0].expression[0] != '\0',!f2.terms[0].expression.empty(), !f2.terms.empty()
int main(void)
{
	string test;
	cin >> test;
	opExpression op(test);
	fraction f = calculate(op);
	fraction f0 = f.trySimplify();
	cout << f0 << endl;
	return 0;
}