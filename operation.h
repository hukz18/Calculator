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

bool isOpe(char c); //判断一个字符是否为运算符
int prior(char);    //判断一个字符(运算符)的优先级

#endif // !operation