#include "tools.h"
#include "symbolize.h"
#include "operation.h"
#include "calculator.h"
#include "interaction.h"
#include <iomanip>



bool testCal(void)
{
	int equNum = 0, varNum = 0;
	fraction **Auguments;
	vector<string> Equation;
	vector<string> Variable;
	string **Matrix;
	cout << "Input your equations,end with an empty line:" << endl;
	equNum = getEqution(&Equation);
	cout << "Now verify your varitions, seperate by a space:" << endl;
	varNum = getVariable(&Variable);
	Matrix = new string *[equNum];
	Auguments = new fraction *[equNum];
	for (int i = 0; i < equNum; i++)
	{
		Matrix[i] = new string[varNum + 1];
		Auguments[i] = new fraction[varNum + 1];
	}
	getMatrix(Equation, Variable, Matrix);
	cout << "The augumented coeffient matrix is:" << endl;
	for (int i = 0; i < equNum; i++)
	{
		for (int j = 0; j < varNum + 1; j++)
		{
			Auguments[i][j] = fraction(polynomial(Matrix[i][j]));
			cout << setw(4) << Matrix[i][j] << " ";
		}
		cout << endl;
	}
	output(Auguments, rows, cols);
	if (Elimination(Auguments, equNum, varNum))
	{
		cout << "The solutions are as follows:" << endl;
		for (int i = 0; i < varNum; i++)
			if (Auguments[i][varNum].isDigit()) cout << Variable[i] << " = " << endl << Auguments[i][varNum].toDigit() << "," << endl;
			else cout << Variable[i] << " = " << endl << Auguments[i][varNum] << "," << endl;
	}
	cout << endl << "Done!" << endl;
	cin.get();
	for (int i = 0; i < equNum; i++)
	{
		delete[](Matrix[i]);
		delete[](Auguments[i]);
	}
	delete[] Matrix;
	delete[] Auguments;
	return true;
}
//写小数转分数文件用来处理公倍数
//写factorize,重载等于来改写trySymplize,每次操作完调用tryfactorize,注意monomial的指数可能为负带来的问题
//改写所有的分式多项式运算处理前缀问题，编写各自鲁棒的iszero和isdigit(isnull)，改写之前的判定,思考各自的缺省值是否合理
//f2.terms[0].expression[0] != '\0',!f2.terms[0].expression.empty(), !f2.terms.empty()
int main(void)
{
	int option = showMenu();
	while (true)
	{
		switch (option)
		{
		case 1:showInstruction(); option = showMenu(); break;
		case 2:Calculator(); option = showMenu(); break;
		};
	}
	
	
	return 0;
}