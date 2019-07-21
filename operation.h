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
	opExpression(string &exp);            //���첢���������������ȼ�����ͬ��ε����ȼ����1000��ȷ�������໥���ţ����ڿ�����Ϊһ��level��
	opExpression(opExpression &exp);                              //���ƹ��죺���
	opExpression(opExpression &exp, int begin, int length = 0);   //��ȡһ�������ȼ����ʽ
	~opExpression();                      //�������ͷ��ڴ�
};


bool isOpe(char c);   //�ж�һ���ַ��Ƿ�Ϊ�����
int prior(char);      //�ж�һ���ַ�(�����)�����ȼ�
opExpression *split(opExpression exp);     //�������ȼ��ָ���ʽ
fraction calculate(opExpression exp);        //�ݹ������ʽ��ֵ��Ŀǰ�ȷ���double(���ڷ��ط�ʽ)

#endif // !operation