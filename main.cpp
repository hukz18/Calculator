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

//写factorize,重载等于来改写trySymplize,每次操作完调用tryfactorize,注意monomial的指数可能为负带来的问题
//改写所有的分式多项式运算处理前缀问题，编写各自鲁棒的iszero和isdigit(isnull)，改写之前的判定,思考各自的缺省值是否合理
//f2.terms[0].expression[0] != '\0',!f2.terms[0].expression.empty(), !f2.terms.empty()
int main(void)
{
	//testCal();
	/*polynomial a("a^3df^4k -3a^2bdef^3k -a^3df^3gj +3ab^2de^2f^2k +3a^2bdef^2gj -b^3de^3fk -3ab^2de^2fgj -a^3bf^3hk +3a^2b^2ef^2hk -3a^2bcef^2hj -3ab^3e^2fhk +3ab^2ce^2fhj +b^4e^3hk -b^3ce^3hj -a^3cf^4l +3a^2bcef^3l -3ab^2ce^2f^2l +b^3ce^3fl +a^3cf^3hj +a^3bf^3gl -3a^2b^2ef^2gl +3ab^3e^2fgl -b^4e^3gl +b^3de^3gj");
	polynomial b("a^4f^4k -4a^3bef^3k -a^3cf^4i -a^4f^3gj +a^3cef^3j +a^3bf^3gi +6a^2b^2e^2f^2k +3a^2bcef^3i +3a^3bef^2gj -3a^2bce^2f^2j -3a^2b^2ef^2gi -4ab^3e^3fk -3ab^2ce^2f^2i -3a^2b^2e^2fgj +3ab^2ce^3fj +3ab^3e^2fgi +b^4e^4k +b^3ce^3fi +ab^3e^3gj -b^3ce^4j -b^4e^3gi");
	fraction d = a / b;
	vector<polynomial> result=a.factorize('f');
	cout << d << endl << endl << endl;
	fraction f = d.trySimplify();
	cout << f << endl;*/
	polynomial a("3x+6y-3z"), b("a+b"), c("a^3+3a^2b+3ab^2+b^3");
	cout << a.getCoeff() << endl;
	cout << c.factorPower(b) << endl;
	return 0;
}