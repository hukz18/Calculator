#include "tools.h"
#include "symbolize.h"
#include "operation.h"


//构造并计算各运算符的优先级，不同层次的优先级相差1000倍确保不会相互干扰，后期考虑设为一个level类
opExpression::opExpression(string & exp)
{
	int length = exp.length();
	priority = new double[length];
	for (int i = 0; i < length ; i++)
		this->priority[i] = 0;
	for (int i = 0; i < length - 1; i++)                  //处理括号相连及指数相连表示的乘法
	{
		if (((exp[i] == ')') && (exp[i + 1] == '(')) || ((!(isOpe(exp[i]))) && (exp[i + 1] == '(')))
			exp.insert(i + 1, 1, '*');
		if ((exp[i] == '^') && (isdigit(exp[i + 1])))
		{
			int j = i + 1;
			while (j < length - 1 && isdigit(exp[j])) j++;
			if (isalpha(exp[j])) exp.insert(j, 1, '*');
		}
	}
	length = exp.length();                            //开始计算优先级
	int cur = 0, level = 0;
	double orderOffset = 0;
	for (int i = 0; i < length; i++)                  //计算进出括号的层数
	{
		if (exp[i] == '(')
			level += 1000;
		if (exp[i] == ')')
			level -= 1000;
		if (exp[i] != '('&&exp[i] != ')')
		{
			if (isOpe(exp[i]))
				priority[cur] = level + prior(exp[i]);
			else priority[cur] = 1e6;
			expression.append(1, exp[i]);
			cur++;
		}
	}
	if (level)
		cout << "the \"(\"and\")\"aren't matching,please recheck your input" << endl;
	/*计算位置导致的同级运算符的先后调整*/
	for (int i = expression.length() - 1; i >= 0; i--)
	{
		if (isOpe(expression[i]))
		{
			priority[i] += orderOffset;
			orderOffset += 0.001;
		}
	}
}

//复制构造：深复制
opExpression::opExpression(opExpression & exp)
{
	int length = exp.expression.length();
	expression = exp.expression;
	priority = new double[length];
	for(int i=0;i<length;i++)
		priority[i] = exp.priority[i];
}

//截取一部分优先级表达式
opExpression::opExpression(opExpression & exp, int begin, int length)
{
	if(length)//!=0
		expression = exp.expression.substr(begin, begin + length);
	else expression = exp.expression.substr(begin);
	priority = new double[length];
	for (int i = 0; i < length; i++)
		priority[i] = exp.priority[i];
}

//析构并释放内存
opExpression::~opExpression()
{
	delete[]this->priority;
};


//以最低优先级的操作符为界，将一段表达式分割为两段
opExpression * split(opExpression exp)
{
	int minPos, length;
	double prior = exp.priority[0];
	opExpression *split = new opExpression[3];
	length = exp.expression.length();
	for(int i=0;i<length;i++)                                //找到优先级最小处
		if (exp.priority[i] < prior)
		{
			minPos = i;
			prior = exp.priority[i];
		}
	//opExpression *split = new opExpression[3]{ opExpression(exp,0,minPos),opExpression(exp,minPos,1),opExpression(exp,minPos + 1) };
	split[0].expression = exp.expression.substr(0, minPos);  //分割前一半表达式
	length = split[0].expression.length();
	split[0].priority = new double[length];
	for (int i = 0; i < length; i++)
		split[0].priority[i] = exp.priority[i];
	split[1].expression = string(1,exp.expression[minPos]);  //分割运算符
	split[1].priority = new double[1];
	split[1].priority[0] = exp.priority[minPos];
	split[2].expression = exp.expression.substr(minPos+1);     //分割后一半表达式
	length = split[2].expression.length();
	split[2].priority = new double[length];
	for (int i = 0; i < length; i++)
		split[2].priority[i] = exp.priority[minPos+1+i];
	return split;
}


//递归地求算式的值，目前先返回double(后期返回分式)
fraction calculate(opExpression exp)
{
	bool flag = false;                //递归终点:算式中是否含运算符
	for(int i=0;i<exp.expression.length();i++)
		if (isOpe(exp.expression[i]))
		{
			flag = true; break;
		}
	if (flag == true)                    //含有运算符，递归分割
	{
		opExpression *splition = split(exp);
		opExpression split0 = splition[0];
		opExpression split1 = splition[1];
		opExpression split2 = splition[2];
		delete[]splition;
		switch (split1.expression[0])
		{
		case '+':return calculate(split0) + calculate(split2);
		case '-':return calculate(split0) + calculate(split2).changeSign();
		case '*':return calculate(split0) * calculate(split2);
		case '/':return calculate(split0) / calculate(split2);
		case '^':
		{
			if (calculate(split0).isDigit() && calculate(split2).isDigit())
			{
				int power = pow(calculate(split0).toDigit(), calculate(split2).toDigit());
				return (fraction(monomial(power)));
			}
			else if (calculate(split2).isDigit() && isZero(calculate(split2).toDigit() - (int)calculate(split2).toDigit()))
				return myPow(calculate(split0), (int)calculate(split2).toDigit());
			else return monomial("0");
		}
		default:return monomial("0");
		}
	}
	else if (exp.expression.empty())
		return monomial("0");
	else return monomial(exp.expression);
}

//判断一个字符是否为运算符
bool isOpe(char c)
{
	if (c == '+' || c == '-' || c == '*' || c == '/' || c == '^')
		return true;
	else return false;
}

//判断一个字符(运算符)的优先级
int prior(char c)
{
	switch (c)
	{
	case '+':return 1;
	case '-':return 1;
	case '*':return 2;
	case '/':return 2;
	case '^':return 3;
	default:return 1000000; //该字符为数字则设为最大优先级，避免在数字处分段
	}
}