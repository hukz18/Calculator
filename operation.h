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


bool isOpe(char c); //判断一个字符是否为运算符
int prior(char);    //判断一个字符(运算符)的优先级
opExpression *split(opExpression exp);     //依据优先级分割算式
double calculate(opExpression exp);        //递归地求算式的值，目前先返回double(后期返回分式)

#endif // !operation