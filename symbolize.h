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
	void arrange(void);                     //将表达式按字母升序排列
	monomial getCoeff(char var) const;            //获取其中某个字母的系数
	monomial changeSign(void) const{ monomial result(*this); result.coefficient *= -1; return result; }                 //改变单项式符号,用于处理减法
	polynomial operator + (monomial const &m2) const;                              //重载单项式互加
	monomial operator * (monomial const &m2) const;                                //重载单项式互乘，未重载与系数相乘
	monomial operator / (monomial const &m2) const;                                //重载单项式互除
	friend ostream &operator <<(ostream &output, monomial const &m);               //重载单项式输出
	/*单项式多项式混合运算*/
	friend polynomial operator +(monomial const &m, polynomial const &p);          //重载单项式加多项式
	friend polynomial operator +(polynomial const &p, monomial const &m);
	friend polynomial operator *(monomial const &m, polynomial const &p);          //重载单项式乘多项式
	friend polynomial operator *(polynomial const &p, monomial const &m);
	friend fraction operator /(monomial const &m, polynomial const &p);            //重载单项式除以多项式
	friend polynomial operator /(polynomial const &p, monomial const &m);          //重载多项式除以单项式
	friend fraction operator +(monomial const &m, fraction const &f);              //重载单项式加分式
	friend fraction operator +(fraction const &f, monomial const &m);
	friend fraction operator *(monomial const &m, fraction const &f);              //重载单项式加分式
	friend fraction operator *(fraction const &f, monomial const &m);
	friend fraction operator /(monomial const &m, fraction const &f);              //重载单项式除以分式
	friend fraction operator /(fraction const &f, monomial const &m);              //重载分式除以单项式
};

class polynomial : public monomial          //多项式类,公有继承单项式类作为公因式
{
public:
	int termNumber = 0;
	vector<monomial> terms;
public:
	polynomial() {};
	polynomial(monomial &m) { termNumber = 1; terms.push_back(m); }  //从单项式构造多项式,项数为1
	polynomial(monomial &coefficient, int termNumber, vector<monomial> &terms) :monomial(coefficient), termNumber(termNumber), terms(terms) {};   //考虑如何设置系数缺省值为1
	virtual bool isZero(void);
	int getLength(void) const;             //获取输出后字符串的长度
	polynomial getConst(char var) const;   //获取对某字母而言的常数项
	polynomial getCoeff(char var, int power) const; //获取对某字母而言最高次幂的系数项
	vector<char> getVar(void) const;       //获取多项式中所含字母
	polynomial changeSign(void) const;
	vector<polynomial> factorize(char var) const;        //递归地分解因式
	polynomial extraction(void) const;                   //提取公因式
	polynomial expansion(void) const;                    //多项式展开
	void orderBy(char a);                    //按字符a降幂排序
	polynomial substitution(char var, polynomial value) const;       //代入并消除同类项
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
	friend fraction operator +(polynomial const &p, fraction const &f);              //重载多项式加分式
	friend fraction operator +(fraction const &f, polynomial const &p);
	friend fraction operator *(polynomial const &p, fraction const &f);              //重载多项式加分式
	friend fraction operator *(fraction const &f, polynomial const &p);
	friend fraction operator /(polynomial const &p, fraction const &f);              //重载多项式除以分式
	friend fraction operator /(fraction const &f, polynomial const &p);              //重载分式除以多项式
	friend ostream &operator <<(ostream &output, polynomial const &p);
};

class fraction : public polynomial             //分式类，公有继承多项式类作为整式部分
{
public:
	polynomial numerator;
	polynomial denominator;
public:
	fraction() {};
	fraction(polynomial &p);                              //从多项式构造分式,分母为1
	fraction (fraction &integrate, fraction &numerator, fraction &denominator) : polynomial(integrate), numerator(numerator), denominator(denominator) {};
	fraction trySimplify(void);                          //调整幂次为正，约去公因子
	fraction operator +(fraction const &f2) const;        //重载分式互加
	fraction operator *(fraction const &f2) const;        //重载分式互乘
	fraction operator /(fraction const &f2) const;        //重载分式互除
	friend ostream &operator <<(ostream &output, fraction const &f);               //重载分式输出
	friend fraction operator +(monomial const &m, fraction const &f);              //重载单项式加分式
	friend fraction operator +(fraction const &f, monomial const &m);
	friend fraction operator *(monomial const &m, fraction const &f);              //重载单项式加分式
	friend fraction operator *(fraction const &f, monomial const &m);
	friend fraction operator /(monomial const &m, fraction const &f);              //重载单项式除以分式
	friend fraction operator /(fraction const &f, monomial const &m);              //重载分式除以单项式
	friend fraction operator +(polynomial const &p, fraction const &f);              //重载多项式加分式
	friend fraction operator +(fraction const &f, polynomial const &p);
	friend fraction operator *(polynomial const &p, fraction const &f);              //重载多项式加分式
	friend fraction operator *(fraction const &f, polynomial const &p);
	friend fraction operator /(polynomial const &p, fraction const &f);              //重载多项式除以分式
	friend fraction operator /(fraction const &f, polynomial const &p);              //重载分式除以多项式
};

#endif // !symbolize