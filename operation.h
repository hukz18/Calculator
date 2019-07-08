#ifndef operation
#define operation

#include <vector>
#include <string>
#include <iostream>

using namespace std;

class opExpression
{
public:
	string expression;
	double *priority;
	opExpression() {};
	opExpression(string &exp);
	opExpression(opExpression &exp, int begin, int length = 0);
	~opExpression();
};


bool isOpe(char c); //�ж�һ���ַ��Ƿ�Ϊ�����
int prior(char);    //�ж�һ���ַ�(�����)�����ȼ�
opExpression *split(opExpression exp);     //�������ȼ��ָ���ʽ
double calculate(opExpression exp);        //�ݹ������ʽ��ֵ��Ŀǰ�ȷ���double(���ڷ��ط�ʽ)

#endif // !operation