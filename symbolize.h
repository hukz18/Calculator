#ifndef symbolize
#define symbolize
#include <string>
#include <vector>
#include <sstream> //计算输出长度
#include <iostream>//输出几个提醒
#include <algorithm>

using namespace std;
class monomial;
class polynomial;
class fraction;
 


class monomial             //单项式类
{
public:
	double coefficient=1;                      //数字系数
	string expression;                    //字母表达式
public:
	monomial() { coefficient = 1; }
	monomial (string const &expression);
	monomial (int coefficient, string const &expression) :coefficient(coefficient), expression(expression) {};
	monomial (monomial const &m) :coefficient(m.coefficient), expression(m.expression) {};
	void arrange(void); //将表达式按字母升序排列
	monomial changeSign(void) { coefficient *= -1; return *this; }                 //改变单项式符号,用于处理减法
	polynomial operator + (monomial const &m2) const;                              //重载单项式互加
	/*单项式多项式混合运算*/
	friend polynomial operator +(monomial const &m, polynomial const &p);          //重载单项式加多项式
	friend polynomial operator +(polynomial const &p, monomial const &m);
	friend polynomial operator *(monomial const &m, polynomial const &p);          //重载单项式乘多项式
	friend polynomial operator *(polynomial const &p, monomial const &m);
	friend fraction operator /(monomial const &m, polynomial const &p);            //重载单项式除以多项式
	friend polynomial operator /(polynomial const &p, monomial const &m);          //重载多项式除以单项式
	monomial operator * (monomial const &m2) const;    //重载单项式互乘，未重载与系数相乘
	monomial operator / (monomial const &m2) const;    //重载单项式互除
	friend ostream &operator <<(ostream &output, monomial const &m);               //重载单项式输出
};

class polynomial : public monomial          //多项式类,公有继承单项式类作为公因式
{
public:
	int termNumber = 0;
	vector<monomial> terms;
public:
	polynomial() {};
	polynomial(string &expression);//先不急着写,也许用不到
	polynomial(monomial &coefficient, int termNumber, vector<monomial> &terms) :monomial(coefficient), termNumber(termNumber), terms(terms) {};   //考虑如何设置系数缺省值为1
	virtual bool isZero(void);
	polynomial changeSign(void);   
	int getLength(void) const;    //获取输出后字符串的长度
	void factorize(void);                    //分解因式
	polynomial extraction(void) const;                   //提取公因式
	polynomial expansion(void) const;                    //多项式展开
	void orderBy(char a);                    //按字符a降幂排序
	polynomial substitution(char a, char b) const;       //代入并消除同类项
	polynomial operator +(polynomial const &p2) const;   //重载多项式互加
	polynomial operator *(polynomial const &p2) const;   //重载多项式互乘
	fraction operator /(polynomial const &p2) const;     //重载多项式互除
	/*单项式多项式混合运算*/
	friend polynomial operator +(monomial const &m, polynomial const &p);          //重载多项式加单项式
	friend polynomial operator +(polynomial const &p, monomial const &m);
	friend polynomial operator *(monomial const &m, polynomial const &p);          //重载多项式乘单项式
	friend polynomial operator *(polynomial const &p, monomial const &m);
	friend fraction operator /(monomial const &m, polynomial const &p);            //重载单项式除以多项式
	friend polynomial operator /(polynomial const &p, monomial const &m);          //重载多项式除以单项式

	
	friend ostream &operator <<(ostream &output, polynomial const &p);
};

class fraction : public polynomial             //分式类，公有继承多项式类作为整式部分
{
public:
	polynomial numerator;
	polynomial denominator;
public:
	fraction() {};
	fraction (string &expression);                        //也许用不到
	fraction (fraction &integrate, fraction &numerator, fraction &denominator) : polynomial(integrate), numerator(numerator), denominator(denominator) {};
	fraction substitution(void);                          //调整幂次为正，约去公因子
	fraction operator +(fraction const &f2) const;        //重载分式互加
	fraction operator *(fraction const &f2) const;        //重载分式互乘
	fraction operator /(fraction const &f2) const;        //重载分式互除
	friend ostream &operator <<(ostream &output, fraction const &f);
};

#endif // !symbolize