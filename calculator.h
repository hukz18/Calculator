#ifndef calculator
#define calculator

#define maxLength 80

#include <map>
#include <vector>
#include <string>
#include <iostream>
#include <algorithm>

using namespace std;

class Term           //储存未知数及其系数
{
private:
	string variable;
	string coefficient;
public:
	Term(string &variable, string &coefficient) :variable(variable), coefficient(coefficient) {};
	Term(const string &variable) :variable(variable), coefficient("1") {};
	bool operator ==(Term &t2) { return variable == t2.variable; }
	bool operator <(Term &t2) { return variable < t2.variable; }
	friend ostream &operator <<(ostream &output, Term &term);
};

int getEqution(vector <string> *equ);     //获取方程组,返回其总数
int getVariable(vector <Term> *var);  //获取未知数，返回其总数
bool getCoefficient(vector <Term> *var, vector <string> &equ);//获取各未知数的系数，返回是否成功,找到各项的开始与结束，erase变量

#endif // !calculator.h