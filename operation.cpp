#include "operation.h"

opExpression::opExpression(string & exp)
{
	int length = exp.length();
	priority = new double[length];
	for (int i = 0; i < length ; i++)
		this->priority[i] = 0;
	//处理括号相连表示的乘法
	for (int i = 0; i < length; i++)
		if (((exp[i] == ')') && (exp[i + 1] == '(')) || ((!(isOpe(exp[i]))) && (exp[i + 1] == '(')))
			exp.insert(i+1, 1, '*');
	//开始计算优先级
	length = exp.length();
	int cur = 0;
	int level = 0;                        //进出括号的层数
	double orderAS = 0, orderMD = 0;      //位置导致的同级运算符的先后调整
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
	default:return 100; //该字符为数字则设为最大优先级，避免在数字处分段
	}
}
