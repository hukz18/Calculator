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
	cout << "��ӭʹ�÷��ŷ��̼�����ver1.0��" << endl;
	cout << endl << "                   ***���ܼ��***" << endl;
	cout << "��������֧�����ּ���ĸ���ʽ��ļӼ��˳����˷�����" << endl;
	cout << "	*��2�������ģʽ���ɽ��б��ʽ��Լ�֣����򼰼��㣬ͬʱ֧�����ŵ������ȼ�" << endl;
	cout << "	*��3����ⷽ��ģʽ" << endl;
	cout << "		-��������Ҫ������֪�ĵ�ʽ������δ֪����ϵ������Ϊ��ĸ������" << endl;
	cout << "		-�����Ӧ��ָ����ʽ����Щ��ĸΪ�������������Ὣ������ĸ��Ϊ����" << endl;
	cout << "		-�������ķ��̺�δ֪�������̿��ܻ��޽�������Ӧ�ĸ�" << endl;
	cout << "	*����������4���鿴���ڳ������߼����ⷴ���ĸ�����Ϣ" << endl;
	cout << endl << "                   ***ע������***" << endl;
	cout << "���������ʽ����ʽʱӦע�������﷨����" << endl;
	cout << "	1.���ɽ���ĸ/��������ĸ/���ż�����������������ʾ�˷�" << endl;
	cout << "	2.����������ĸ���ʽ�ĳ˷�ʱ����ȷ�����ݴ�Ϊ����" << endl;
	cout << "	3.�ⷽ�̹��ܵ�ǰֻ��Զ�Ԫһ�η����飬��������δ֪���������ߵĵ�ʽ" << endl;
	cout << "����֮�⣬��ֻ�谴����ѧ����ϰ�����뼴�ɣ�ף��ʹ����죡" << endl;
	cout << endl << "�밴������������˵�..." << endl;
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
	cout << "�����������ı��ʽ����������Է������˵�:" << endl;
	getline(cin, expression);
	while (!expression.empty())
	{
		for (int i = 0; i < expression.length(); i++)
			if (!isLegal(expression[i]))
			{ cout << "�������뺬�Ƿ��ַ�" << expression[i] << ",����������" << endl; flag = false; break; }
		if (flag == true)
		{
			pos = 0;//��ȥ�����еĿո�
			while ((pos = expression.find(' ', pos)) != string::npos)
				expression.erase(pos, 1);
			pos = 0;//��ȥ�����еĳ˺�(ǰ���Ϊ���ֳ���)
			while (((pos = expression.find('*', pos)) != string::npos) && (!((isdigit(expression[pos - 1])) && (isdigit(expression[pos + 1])))))
				expression.erase(pos, 1);
			result = calculate(expression);
			result.trySimplify();
			cout << "������Ϊ:" << endl;
			cout << result << endl;
		}
		cout << "�����������ı��ʽ����������Է������˵�:" << endl;
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
	cout << "���������ķ��̣��ÿ��н�β��" << endl;
	equNum = getEqution(&Equation);
	cout << "������ȷ�����ı������ÿո���" << endl;
	varNum = getVariable(&Variable);
	Matrix = new string *[equNum];
	Auguments = new fraction *[equNum];
	for (int i = 0; i < equNum; i++)
	{
		Matrix[i] = new string[varNum + 1];
		Auguments[i] = new fraction[varNum + 1];
	}
	getMatrix(Equation, Variable, Matrix);
	cout << "���ķ��̵�ϵ������Ϊ:" << endl;
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
		cout << "������Ľ�����:" << endl;
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
	cout << "��ĸϵ���ⷽ�̼�����ver1.0" << endl;
	cout << "    ���ڵĸ���ʱ�ڣ������������г������ֵĶ�Ԫһ�η����飬" << endl;
	cout << "�ұ��ϣ�������ܽⷽ�̵ĳ��򣬵���������֧��" << endl;
	cout << "�ģ�����������ϵ������Ԫ���ڷ����飬���ֱ�����б�ҵ" << endl;
	cout << "��Ҳδ����Ը���ڴ�ѧ�����˽⵽matlab���еķ��ż���������" << endl;
	cout << "Ҳ�������Ҷ�����������Ȥ������һ���������" << endl;
	cout << "רע���ݵķ��Žⷽ�̳����ɴ˳�Ϊ�ҵ�Ŀ�ꡣ������" << endl;
	cout << "Ӧ���׼ȷ�����õ��ص㣬֧�ֶ��ַ�����дϰ�ߵ��������룬" << endl;
	cout << "�����ܶԽ�����������ʽ�ֽ�Ȼ��������ͬʱ���ֺ���" << endl;
	cout << "�ļ����ٶȡ�" << endl;
	cout << "    ���ڱ���������ޣ���򵥵ĳ���һ������಻�㣬Ҳ�����" << endl;
	cout << "����Ĺ���δ��ʵ�֡���ϣ������Ҫ��;���ϣ���Ӧ���ҵı��ˮƽһͬ����" << endl;
	cout << "������һ������������������˵�" << endl;
	cout << "������Ҫ�ļ��������˹��Ԫ���У�����෽��Ч���Բ��ߡ�" << endl;
	cout << "����㷢����һЩbug�����ǶԳ����ʵ���и��õ��뷨��" << endl;
	cout << "��ӭ��ϵ�����ߣ��ҵ�������hukz18@mails.tsinghua.edu.cn," << endl;
	cout << "ͬʱ����ĿҲ��github�Ͽ�Դ����ӭ������ĿSymbolicCalculator��ע������չ" << endl;
	cin.sync();
	system("cls");
}

