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
	opExpression(string &exp);
	~opExpression();
};

bool isOpe(char c); //�ж�һ���ַ��Ƿ�Ϊ�����
int prior(char);    //�ж�һ���ַ�(�����)�����ȼ�

#endif // !operation