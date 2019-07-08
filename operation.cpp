#include "operation.h"

opExpression::opExpression(string & exp)
{
	int length = exp.length();
	priority = new double[length];
	for (int i = 0; i < length ; i++)
		this->priority[i] = 0;
	//��������������ʾ�ĳ˷�
	for (int i = 0; i < length; i++)
		if (((exp[i] == ')') && (exp[i + 1] == '(')) || ((!(isOpe(exp[i]))) && (exp[i + 1] == '(')))
			exp.insert(i+1, 1, '*');
	//��ʼ�������ȼ�
	length = exp.length();
	int cur = 0;
	int level = 0;                        //�������ŵĲ���
	double orderAS = 0, orderMD = 0;      //λ�õ��µ�ͬ����������Ⱥ����
	for (int i = 0; i < length; i++)
	{
		if (exp[i] == '(')
			level += 100;
		if (exp[i] == ')')
			level -= 100;
		if (exp[i] != '('&&exp[i] != ')')
		{
			if (isOpe(exp[i]))
				priority[cur] = level + prior(exp[i]);
			else priority[cur] = 100;
			expression.append(1, exp[i]);
			cur++;
		}
	}
	for (int i = expression.length() - 1; i >= 0; i--)
	{
		if (expression[i] == '+' || expression[i] == '-')
		{
			priority[i] += orderAS;
			orderAS += 0.01;
		}

		if (expression[i] == '*' || expression[i] == '/')
		{
			priority[i] += orderMD;
			orderMD += 0.01;
		}
	}
}

opExpression::~opExpression()
{
	delete[]this->priority;
}



bool isOpe(char c)
{
	if (c == '+' || c == '-' || c == '*' || c == '/')
		return true;
	else return false;
}

int prior(char c)
{
	switch (c)
	{
	case '+':return 1;
	case '-':return 1;
	case '*':return 2;
	case '/':return 2;
	default:return 100; //���ַ�Ϊ��������Ϊ������ȼ������������ִ��ֶ�
	}
}
