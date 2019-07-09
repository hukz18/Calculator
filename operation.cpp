#include "operation.h"


//���첢���������������ȼ�����ͬ��ε����ȼ����1000��ȷ�������໥���ţ����ڿ�����Ϊһ��level��
opExpression::opExpression(string & exp)
{
	int length = exp.length();
	priority = new double[length];
	for (int i = 0; i < length ; i++)
		this->priority[i] = 0;
	for (int i = 0; i < length; i++)                  //��������������ʾ�ĳ˷�
		if (((exp[i] == ')') && (exp[i + 1] == '(')) || ((!(isOpe(exp[i]))) && (exp[i + 1] == '(')))
			exp.insert(i+1, 1, '*');
	length = exp.length();                            //��ʼ�������ȼ�
	int cur = 0, level = 0;
	double orderOffset = 0;
	for (int i = 0; i < length; i++)                  //����������ŵĲ���
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
	for (int i = expression.length() - 1; i >= 0; i--)//����λ�õ��µ�ͬ����������Ⱥ����
	{
		if (isOpe(expression[i]))
		{
			priority[i] += orderOffset;
			orderOffset += 0.001;
		}
	}
}

opExpression::opExpression(opExpression & exp)
{
	int length = exp.expression.length();
	expression = exp.expression;
	priority = new double[length];
	for(int i=0;i<length;i++)
		priority[i] = exp.priority[i];
}

opExpression::opExpression(opExpression & exp, int begin, int length)
{
	if(length)//!=0
		expression = exp.expression.substr(begin, begin + length);
	else expression = exp.expression.substr(begin);
	priority = new double[length];
	for (int i = 0; i < length; i++)
		priority[i] = exp.priority[i];
}

opExpression::~opExpression()
{
	cout << "deleting" << expression << endl;
	delete[]this->priority;
};


//��������ȼ��Ĳ�����Ϊ�磬��һ�α��ʽ�ָ�Ϊ����
opExpression * split(opExpression exp)
{
	int minPos, length;
	double prior = exp.priority[0];
	opExpression *split = new opExpression[3];
	length = exp.expression.length();
	for(int i=0;i<length;i++)                                //�ҵ����ȼ���С��
		if (exp.priority[i] < prior)
		{
			minPos = i;
			prior = exp.priority[i];
		}
	//opExpression *split = new opExpression[3]{ opExpression(exp,0,minPos),opExpression(exp,minPos,1),opExpression(exp,minPos + 1) };
	split[0].expression = exp.expression.substr(0, minPos);  //�ָ�ǰһ����ʽ
	length = split[0].expression.length();
	split[0].priority = new double[length];
	for (int i = 0; i < length; i++)
		split[0].priority[i] = exp.priority[i];
	split[1].expression = string(1,exp.expression[minPos]);  //�ָ������
	split[1].priority = new double[1];
	split[1].priority[0] = exp.priority[minPos];
	split[2].expression = exp.expression.substr(minPos+1);     //�ָ��һ����ʽ
	length = split[2].expression.length();
	split[2].priority = new double[length];
	for (int i = 0; i < length; i++)
		split[2].priority[i] = exp.priority[minPos+1+i];
	return split;
}


//�ݹ������ʽ��ֵ��Ŀǰ�ȷ���double(���ڷ��ط�ʽ)
double calculate(opExpression exp)
{
	bool flag = false;                //�ݹ��յ�:��ʽ���Ƿ������
	for(int i=0;i<exp.expression.length();i++)
		if (isOpe(exp.expression[i]))
		{
			flag = true; break;
		}
	if (flag == true)                    //������������ݹ�ָ�
	{
		opExpression *splition = split(exp);
		opExpression split0 = splition[0];
		opExpression split1 = splition[1];
		opExpression split2 = splition[2];
		delete[]splition;
		switch (split1.expression[0])
		{
		case '+':return calculate(split0) + calculate(split2);
		case '-':return calculate(split0) - calculate(split2);
		case '*':return calculate(split0) * calculate(split2);
		case '/':return calculate(split0) / calculate(split2);
		case '^':return pow(calculate(split0), calculate(split2));
		default:return 0;
		}
	}
	else if (exp.expression.empty())
		return 0;
	else return stod(exp.expression);
}



bool isOpe(char c)
{
	if (c == '+' || c == '-' || c == '*' || c == '/' || c == '^')
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
	case '^':return 3;
	default:return 1e6; //���ַ�Ϊ��������Ϊ������ȼ������������ִ��ֶ�
	}
}


