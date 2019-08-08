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
	opExpression(string &exp);            //构造并计算各运算符的优先级，不同层次的优先级相差1000倍确保不会相互干扰，后期考虑设为一个level类
	opExpression(opExpression &exp);                              //复制构造：深复制
	opExpression(opExpression &exp, int begin, int length = 0);   //截取一部分优先级表达式
	~opExpression();                      //析构并释放内存
};



int prior(char);      //判断一个字符(运算符)的优先级
opExpression *split(opExpression exp);     //依据优先级分割算式
fraction calculate(opExpression exp);        //递归地求算式的值，目前先返回double(后期返回分式)

#endif // !operation