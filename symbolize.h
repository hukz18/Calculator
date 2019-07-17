#ifndef symbolize
#define symbolize
#include <string>
#include <vector>
#include <iostream>//输出几个提醒
#include <algorithm>

using namespace std;
class monomial;
class polynomial;
class fraction;
 


class monomial             //单项式类
{
public:
	double coefficient;                      //数字系数
	string expression;                    //字母表达式
public:
	monomial() { coefficient = 1; }
	monomial (string const &expression);
	monomial (int coefficient, string const &expression) :coefficient(coefficient), expression(expression) {};
	monomial (monomial const &m) :coefficient(m.coefficient), expression(m.expression) {};
	void arrange(void); //将表达式按字母升序排列
	virtual void changeSign(void) { coefficient *= -1; }                 //改变单项式符号,用于处理减法
	polynomial operator + (monomial const &m2) const;                    //重载单项式互加
	friend polynomial operator +(monomial const &m, polynomial const &p);//重载单项式加多项式
	friend polynomial operator +(polynomial const &p, monomial const &m);
	friend polynomial operator *(monomial const &m, polynomial const &p);//重载单项式乘多项式
	friend polynomial operator *(polynomial const &p, monomial const &m);
	monomial operator * (monomial const &m2) const;    //重载单项式互乘，未重载与系数相乘
	fraction operator / (monomial const &m2) const;    //重载单项式互除
	friend ostream &operator <<(ostream &output, monomial const &m);//重载单项式输出
};

class polynomial : public monomial          //多项式类,公有继承单项式类作为公因式
{
public:
	int termNumber;
	vector<monomial> terms;
public:
	polynomial() {};
	polynomial(string &expression);//先不急着写,也许用不到
	polynomial(monomial &coefficient, int termNumber, vector<monomial> &terms) :monomial(coefficient), termNumber(termNumber), terms(terms) {};   //考虑如何设置系数缺省值为1
	virtual void changeSign(void);//改变多项式符号
	polynomial operator +(polynomial const &p2) const;   //重载多项式互加
	friend polynomial operator +(monomial const &m, polynomial const &p);//重载多项式加单项式
	friend polynomial operator +(polynomial const &p, monomial const &m);
	friend polynomial operator *(monomial const &m, polynomial const &p);//重载多项式乘单项式
	friend polynomial operator *(polynomial const &p, monomial const &m);
	polynomial operator *(polynomial const &p2) const;   //重载多项式互乘
	fraction operator /(polynomial const &p2) const;     //重载多项式互除
	polynomial factorize(void);              //分解因式
	void extraction(void);                   //提取公因式
	void expansion(void);                    //多项式展开
	friend ostream &operator <<(ostream &output, polynomial const &p);
};

class fraction : public polynomial             //分式类，公有继承多项式类作为整式部分
{
protected:
	polynomial numerator;
	polynomial denominator;
public:
	fraction() {};
	fraction (string &expression);
	fraction (fraction &integrate, fraction &numerator, fraction &denominator) : polynomial(integrate), numerator(numerator), denominator(denominator) {};
	fraction operator +(fraction const &f2) const;        //重载分式加法
	fraction operator -(fraction const &f2) const;        //重载分式减法
	fraction operator *(fraction const &f2) const;        //重载分式乘法
	fraction operator /(fraction const &f2) const;        //重载分式除法
};

#endif // !symbolize