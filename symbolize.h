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
	string expression;                         //字母表达式
public:
	monomial() { coefficient = 1; expression.clear(); }
	monomial(double x) :coefficient(x) { expression.clear(); }
	monomial (string const &expression);
	monomial (double coefficient, string const &expression) :coefficient(coefficient), expression(expression) {};
	monomial (monomial const &m) :coefficient(m.coefficient), expression(m.expression) {};
	void arrange(void);                           //将表达式按字母升序排列
	bool isZero(void) const { return (tools::isZero(coefficient)); }
	monomial getCoeff(char var) const;            //获取其中某个字母的系数
	vector<char> getVar(void) const;              //获取单项式中所含字母
	monomial *split(void) const;                  //将单项式中指数小于零的项拆分
	monomial changeSign(void) const{ monomial result(*this); result.coefficient *= -1; return result; }                 //改变单项式符号,用于处理减法
	polynomial operator + (monomial const &m2) const;                              //重载单项式互加
	monomial operator * (monomial const &m2) const;                                //重载单项式互乘，未重载与系数相乘
	monomial operator / (monomial const &m2) const;                                //重载单项式互除
	bool operator ==(monomial const &m2) const;                                    //重载单项式比较
	friend ostream &operator <<(ostream &output, monomial const &m);               //重载单项式输出
	/*单项式多项式混合运算*/
	friend polynomial operator +(monomial const &m, polynomial const &p);          //重载单项式加多项式
	friend polynomial operator +(polynomial const &p, monomial const &m);
	friend polynomial operator *(monomial const &m, polynomial const &p);          //重载单项式乘多项式
	friend polynomial operator *(polynomial const &p, monomial const &m);
	friend fraction operator /(monomial const &m, polynomial const &p);            //重载单项式除以多项式
	friend fraction operator /(polynomial const &p, monomial const &m);          //重载多项式除以单项式
	friend fraction operator +(monomial const &m, fraction const &f);               //重载单项式加分式
	friend fraction operator +(fraction const &f, monomial const &m);
	friend fraction operator *(monomial const &m, fraction const &f);              //重载单项式加分式
	friend fraction operator *(fraction const &f, monomial const &m);
	friend fraction operator /(monomial const &m, fraction const &f);              //重载单项式除以分式
	friend fraction operator /(fraction const &f, monomial const &m);              //重载分式除以单项式
};
monomial nextValue(int &step, vector<char> const & Coeff, vector<char> const & Const, vector<double> const & value);  //创造一项可能的因式


class polynomial : public monomial          //多项式类,公有继承单项式类作为公因式
{
public:
	int termNumber = 0;
	vector<monomial> terms;
public:
	polynomial() { coefficient = 1; }
	polynomial(string const &expression);  //从字符串构造多项式
	polynomial(monomial const &m) { coefficient = 1; termNumber = 1; terms.push_back(m); }  //从单项式构造多项式,项数为1
	polynomial(monomial &coefficient, int termNumber, vector<monomial> &terms) :monomial(coefficient), termNumber(termNumber), terms(terms) {};   //考虑如何设置系数缺省值为1
	bool isZero(void) const;
	bool isNegative(void) const;           //确认多项式是否"小于零"
	void orderBy(char a);                  //按字符a降幂排序
	int getLength(void) const;             //获取输出后字符串的长度
	char getMainTerm(void) const;          //获取幂次最高的字母
	int getCoeff(void) const;              //获取多项式的公系数
	int factorPower(polynomial const &factor) const;   //获取某多项式因子在另一多项式中的次数
	polynomial getConst(char var) const;   //获取对某字母而言的常数项
	polynomial getCoeff(char var, int power) const; //获取对某字母而言最高次幂的系数项
	vector<char> getVar(void) const;       //获取多项式中所含字母
	polynomial changeSign(void) const;
	vector<polynomial> factorize(char var) const;        //递归地分解因式
	polynomial extraction(void) const;                   //提取公因式
	polynomial expansion(void) const;                    //多项式展开
	bool tryDivide(polynomial const &p);//若整除则除并返回true，否则不改变且返回false
	polynomial DivideWithRemainder(polynomial const &divider);       //带余除法，返回余式
	polynomial substitution(char var, polynomial value) const;       //代入并消除同类项
	polynomial operator +(polynomial const &p2) const;   //重载多项式互加
	polynomial operator *(polynomial const &p2) const;   //重载多项式互乘
	fraction operator /(polynomial const &p2) const;     //重载多项式互除
	bool operator ==(polynomial const &p2) const;        //重载多项式比较

	/*单项式多项式混合运算*/
	friend polynomial operator +(monomial const &m, polynomial const &p);          //重载多项式加单项式
	friend polynomial operator +(polynomial const &p, monomial const &m);
	friend polynomial operator *(monomial const &m, polynomial const &p);          //重载多项式乘单项式
	friend polynomial operator *(polynomial const &p, monomial const &m);
	friend fraction operator /(monomial const &m, polynomial const &p);            //重载单项式除以多项式
	friend fraction operator /(polynomial const &p, monomial const &m);          //重载多项式除以单项式
	friend fraction operator +(polynomial const &p, fraction const &f);              //重载多项式加分式
	friend fraction operator +(fraction const &f, polynomial const &p);
	friend fraction operator *(polynomial const &p, fraction const &f);              //重载多项式加分式
	friend fraction operator *(fraction const &f, polynomial const &p);
	friend fraction operator /(polynomial const &p, fraction const &f);              //重载多项式除以分式
	friend fraction operator /(fraction const &f, polynomial const &p);              //重载分式除以多项式
	friend ostream &operator <<(ostream &output, polynomial const &p);
};
polynomial createTerm(char var, monomial &value, vector<int> &power);                           //创造提取公因式中的一项(x的值为单项式)
polynomial createTerm(char var, fraction &value, vector<int> &power);                           //创造提取公因式中的一项(x的值为分式)，替换下面这个
polynomial createTerm(char var, polynomial const Coeff, int coeffPower, polynomial const Const, int constpower);    //创造提取公因式中的一项
vector<int> nextPower(vector<char> &vars, int *powers, vector<int> *factors,int step);                //获取下一个因式中可能的幂次组合(单项式因子)
vector<int>nextPower(vector<polynomial> &terms, polynomial &Const, polynomial &Coeff);           //获取下一个因式中可能的幂次组合(多项式因子)

class fraction : public polynomial             //分式类，公有继承多项式类作为整式部分
{
public:
	polynomial numerator;
	polynomial denominator=monomial(1);
public:
	fraction() { termNumber = 1; terms.push_back(monomial("1")); }
	fraction(monomial const &m);                                //从单项式构造分式,分母为1
	fraction(polynomial const &p);                              //从多项式构造分式,分母为1
	fraction(fraction const &f) :polynomial(f), numerator(f.numerator), denominator(f.denominator) {};
	fraction (fraction &integrate, fraction &numerator, fraction &denominator) : polynomial(integrate), numerator(numerator), denominator(denominator) {};
	fraction changeSign(void) const;
	bool isZero(void) const{ return numerator.isZero(); }
	bool isDigit(void) const;                            //判断分式是否为数字
	double toDigit(void) const;                          //将是纯数的分式转化为double
	fraction trySimplify(void);                          //调整幂次为正，约去公因子
	friend fraction myPow(fraction const &f, int power);              //求幂运算，用于计算"^"操作符
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
void output(fraction ** const Matrix, int row, int column);         //用于debug的输出
#endif // !symbolize