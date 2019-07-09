#ifndef symbolize
#define symbolize

#include <string>
#include <vector>
#include <algorithm>
using namespace std;
class monomial;
class polynomial;
class fraction;

class monomial             //单项式类
{
protected:
	double coefficient;                      //数字系数
	string expression;                    //字母表达式
public:
	monomial() {};
	monomial (string expression);
	monomial (int coefficient, string expression) :coefficient(coefficient), expression(expression) {};
	monomial (monomial &m) :coefficient(m.coefficient), expression(m.expression) {};
	polynomial operator + (monomial &m2);  //重载单项式加法
	polynomial operator - (monomial &m2);  //重载单项式减法
	monomial operator * (monomial &m2);    //重载单项式乘法，未重载与系数相加
	fraction operator / (monomial &m2);    //重载单项式除法
};

class polynomial : public monomial          //多项式类,公有继承单项式类作为公因式
{
protected:
	int termNumber;
	vector<monomial> terms;
public:
	polynomial() {};
	polynomial (string expression);
	polynomial (monomial &coefficient, int termNumber, vector<monomial> &terms) :monomial(coefficient),termNumber(termNumber), terms(terms) {};   //考虑如何设置系数缺省值为1
	polynomial operator +(polynomial &p2);   //重载多项式加法
	polynomial operator -(polynomial &p2);   //重载多项式减法
	polynomial operator *(polynomial &p2);   //重载多项式乘法
	fraction operator /(polynomial &p2);     //重载多项式除法
	polynomial factorize(void);              //分解因式
	polynomial comfactorize(void);           //提取公因式
};

class fraction : public polynomial             //分式类，公有继承多项式类作为整式部分
{
protected:
	polynomial numerator;
	polynomial denominator;
public:
	fraction() {};
	fraction (string expression);
	fraction (fraction &integrate, fraction &numerator, fraction &denominator) : polynomial(integrate), numerator(numerator), denominator(denominator) {};
	fraction operator +(fraction &f2);        //重载分式加法
	fraction operator -(fraction &f2);        //重载分式减法
	fraction operator *(fraction &f2);        //重载分式乘法
	fraction operator /(fraction &f2);        //重载分式除法
};

#endif // !symbolize