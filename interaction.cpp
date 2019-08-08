#include "tools.h"
#include "symbolize.h"
#include "operation.h"
#include "calculator.h"
#include "interaction.h"

int showMenu(void)
{
	int option = 0;
	cout << "******Symbolized  Matrix  Solver******" << endl;
	cout << "                                --ver1.0" << endl;
	cout << "              Function Menu" << endl << endl;
	cout << "1.************************Instructions" << endl;
	cout << "2.**************************Calculator" << endl;
	cout << "3.**********************Eqution Solver" << endl;
	cout << "4.*******************************About" << endl;
	cout << "5.********************************Quit" << endl;
	cout << endl<< "Please input the correspond fuction number:";
	while ((!(cin >> option)) || option < 1 || option > 5)
	{
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "Please input an integer between 1 and 4" << endl;
		cout << "Now please input the correspond fuction number:";
	}
	cin.sync();
	system("cls");
	return option;
}

void ShowInstruction(void)
{
	cout << "欢迎使用符号方程计算器ver1.0！" << endl;
	cout << endl << "                   ***功能简介***" << endl;
	cout << "本计算器支持数字及字母表达式间的加减乘除、乘方运算" << endl;
	cout << "	*按2进入计算模式，可进行表达式的约分，化简及计算，同时支持括号调整优先级" << endl;
	cout << "	*按3进入解方程模式" << endl;
	cout << "		-首先您需要输入已知的等式，其中未知数的系数可以为字母或数字" << endl;
	cout << "		-其次您应当指定等式中哪些字母为变量，计算机则会将其余字母视为常量" << endl;
	cout << "		-根据您的方程和未知数，方程可能会无解或给出相应的根" << endl;
	cout << "	*您还可输入4来查看关于程序、作者及问题反馈的更多信息" << endl;
	cout << endl << "                   ***注意事项***" << endl;
	cout << "您在输入等式或算式时应注意以下语法规则：" << endl;
	cout << "	1.您可将字母/数字与字母/括号及括号与括号相连表示乘法" << endl;
	cout << "	2.当您输入字母表达式的乘方时，请确保其幂次为整数" << endl;
	cout << "	3.解方程功能当前只针对多元一次方程组，请勿输入未知数次数过高的等式" << endl;
	cout << "除此之外，您只需按照数学表达的习惯输入即可，祝您使用愉快！" << endl;
	cout << endl << "请按任意键返回主菜单..." << endl;
	_getche();
	cin.sync();
	system("cls");
	return;
}

void Calculator(void)
{
	int pos = 0;
	fraction result;
	bool flag = true;
	string expression;
	cout << "                 **Calculator**" << endl;
	cout << "请输入待化简的表达式，输入空行以返回主菜单:" << endl;
	getline(cin, expression);
	while (!expression.empty())
	{
		for (int i = 0; i < expression.length(); i++)
			if (!isLegal(expression[i]))
			{ cout << "您的输入含非法字符" << expression[i] << ",请重新输入" << endl; flag = false; break; }
		if (flag == true)
		{
			pos = 0;//除去代码中的空格
			while ((pos = expression.find(' ', pos)) != string::npos)
				expression.erase(pos, 1);
			pos = 0;//除去代码中的乘号(前后均为数字除外)
			while (((pos = expression.find('*', pos)) != string::npos) && (!((isdigit(expression[pos - 1])) && (isdigit(expression[pos + 1])))))
				expression.erase(pos, 1);
			result = calculate(expression);
			result.trySimplify();
			cout << "化简结果为:" << endl;
			cout << result << endl;
		}
		cout << "请输入待化简的表达式，输入空行以返回主菜单:" << endl;
		getline(cin, expression);
	}
	cin.sync();
	system("cls");
	return;
}

void EqutionSolver(void)
{
	int equNum = 0, varNum = 0;
	fraction **Auguments;
	vector<string> Equation;
	vector<string> Variable;
	string **Matrix;
	cout << "                 **Equation Solver**" << endl;
	cout << "请输入您的方程，用空行结尾：" << endl;
	equNum = getEqution(&Equation);
	cout << "现在请确认您的变量，用空格间隔" << endl;
	varNum = getVariable(&Variable);
	Matrix = new string *[equNum];
	Auguments = new fraction *[equNum];
	for (int i = 0; i < equNum; i++)
	{
		Matrix[i] = new string[varNum + 1];
		Auguments[i] = new fraction[varNum + 1];
	}
	getMatrix(Equation, Variable, Matrix);
	cout << "您的方程的系数矩阵为:" << endl;
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
		cout << "方程组的解如下:" << endl;
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
	cin.sync();
	system("cls");
}

void About(void)
{
	cout << "                        **About**" << endl;
	cout << "字母系数解方程计算器ver1.0" << endl;
	cout << "    还在的高中时期，面对物理大题中常常出现的多元一次方程组，" << endl;
	cout << "我便会希望出现能解方程的程序，但计算器所支持" << endl;
	cout << "的，仅仅是数字系数的四元以内方程组，因此直到高中毕业" << endl;
	cout << "我也未能如愿。在大学，我了解到matlab具有的符号计算能力，" << endl;
	cout << "也激发了我对这个问题的兴趣，创造一款更轻量、" << endl;
	cout << "专注与便捷的符号解方程程序由此成为我的目标。这款程序" << endl;
	cout << "应兼具准确与易用的特点，支持多种符合手写习惯的自由输入，" << endl;
	cout << "并且能对结果进行消项、因式分解等化简操作，同时保持合理" << endl;
	cout << "的计算速度。" << endl;
	cout << "    由于编程能力有限，这简单的程序一定有诸多不足，也有许多" << endl;
	cout << "设想的功能未能实现。我希望它不要半途而废，而应与我的编程水平一同进步" << endl;
	cout << "，终有一天可以真正帮助到别人到" << endl;
	cout << "程序主要的计算借助高斯消元进行，但许多方法效率仍不高。" << endl;
	cout << "如果你发现了一些bug，或是对程序的实现有更好的想法，" << endl;
	cout << "欢迎联系开发者，我的邮箱是hukz18@mails.tsinghua.edu.cn," << endl;
	cout << "同时本项目也在github上开源，欢迎搜索项目SymbolicCalculator关注后续进展" << endl;
	cin.sync();
	system("cls");
}

