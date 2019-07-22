#ifndef symbolize
#define symbolize
#include <string>
#include <vector>
#include <sstream> //�����������
#include <iostream>//�����������
#include <algorithm>

using namespace std;
class monomial;
class polynomial;
class fraction;
 


class monomial             //����ʽ��
{
public:
	double coefficient=1;                      //����ϵ��
	string expression;                    //��ĸ���ʽ
public:
	monomial() { coefficient = 1; expression.clear(); }
	monomial(double x) :coefficient(x) { expression.clear(); }
	monomial (string const &expression);
	monomial (double coefficient, string const &expression) :coefficient(coefficient), expression(expression) {};
	monomial (monomial const &m) :coefficient(m.coefficient), expression(m.expression) {};
	void arrange(void);                     //�����ʽ����ĸ��������
	monomial getCoeff(char var) const;            //��ȡ����ĳ����ĸ��ϵ��
	monomial *split(void) const;                  //������ʽ��ָ��С���������
	monomial changeSign(void) const{ monomial result(*this); result.coefficient *= -1; return result; }                 //�ı䵥��ʽ����,���ڴ������
	polynomial operator + (monomial const &m2) const;                              //���ص���ʽ����
	monomial operator * (monomial const &m2) const;                                //���ص���ʽ���ˣ�δ������ϵ�����
	monomial operator / (monomial const &m2) const;                                //���ص���ʽ����
	bool operator ==(monomial const &m2) const;                                    //���ص���ʽ�Ƚ�
	friend ostream &operator <<(ostream &output, monomial const &m);               //���ص���ʽ���
	/*����ʽ����ʽ�������*/
	friend polynomial operator +(monomial const &m, polynomial const &p);          //���ص���ʽ�Ӷ���ʽ
	friend polynomial operator +(polynomial const &p, monomial const &m);
	friend polynomial operator *(monomial const &m, polynomial const &p);          //���ص���ʽ�˶���ʽ
	friend polynomial operator *(polynomial const &p, monomial const &m);
	friend fraction operator /(monomial const &m, polynomial const &p);            //���ص���ʽ���Զ���ʽ
	friend fraction operator /(polynomial const &p, monomial const &m);          //���ض���ʽ���Ե���ʽ
	friend fraction operator +(monomial const &m, fraction const &f);               //���ص���ʽ�ӷ�ʽ
	friend fraction operator +(fraction const &f, monomial const &m);
	friend fraction operator *(monomial const &m, fraction const &f);              //���ص���ʽ�ӷ�ʽ
	friend fraction operator *(fraction const &f, monomial const &m);
	friend fraction operator /(monomial const &m, fraction const &f);              //���ص���ʽ���Է�ʽ
	friend fraction operator /(fraction const &f, monomial const &m);              //���ط�ʽ���Ե���ʽ
};

class polynomial : public monomial          //����ʽ��,���м̳е���ʽ����Ϊ����ʽ
{
public:
	int termNumber = 0;
	vector<monomial> terms;
public:
	polynomial() { coefficient = 1; }
	polynomial(string const &expression);  //���ַ����������ʽ
	polynomial(monomial const &m) { coefficient = 1; termNumber = 1; terms.push_back(m); }  //�ӵ���ʽ�������ʽ,����Ϊ1
	polynomial(monomial &coefficient, int termNumber, vector<monomial> &terms) :monomial(coefficient), termNumber(termNumber), terms(terms) {};   //�����������ϵ��ȱʡֵΪ1
	virtual bool isZero(void) const;
	void orderBy(char a);                  //���ַ�a��������
	int getLength(void) const;             //��ȡ������ַ����ĳ���
	polynomial getConst(char var) const;   //��ȡ��ĳ��ĸ���Եĳ�����
	polynomial getCoeff(char var, int power) const; //��ȡ��ĳ��ĸ������ߴ��ݵ�ϵ����
	vector<char> getVar(void) const;       //��ȡ����ʽ��������ĸ
	polynomial changeSign(void) const;
	vector<polynomial> factorize(char var) const;        //�ݹ�طֽ���ʽ
	polynomial extraction(void) const;                   //��ȡ����ʽ
	polynomial expansion(void) const;                    //����ʽչ��
	polynomial DivideWithRemainder(polynomial &divider);       //���������������ʽ
	polynomial substitution(char var, polynomial value) const;       //���벢����ͬ����
	polynomial operator +(polynomial const &p2) const;   //���ض���ʽ����
	polynomial operator *(polynomial const &p2) const;   //���ض���ʽ����
	fraction operator /(polynomial const &p2) const;     //���ض���ʽ����
	bool operator ==(polynomial const &p2) const;        //���ض���ʽ�Ƚ�

	/*����ʽ����ʽ�������*/
	friend polynomial operator +(monomial const &m, polynomial const &p);          //���ض���ʽ�ӵ���ʽ
	friend polynomial operator +(polynomial const &p, monomial const &m);
	friend polynomial operator *(monomial const &m, polynomial const &p);          //���ض���ʽ�˵���ʽ
	friend polynomial operator *(polynomial const &p, monomial const &m);
	friend fraction operator /(monomial const &m, polynomial const &p);            //���ص���ʽ���Զ���ʽ
	friend fraction operator /(polynomial const &p, monomial const &m);          //���ض���ʽ���Ե���ʽ
	friend fraction operator +(polynomial const &p, fraction const &f);              //���ض���ʽ�ӷ�ʽ
	friend fraction operator +(fraction const &f, polynomial const &p);
	friend fraction operator *(polynomial const &p, fraction const &f);              //���ض���ʽ�ӷ�ʽ
	friend fraction operator *(fraction const &f, polynomial const &p);
	friend fraction operator /(polynomial const &p, fraction const &f);              //���ض���ʽ���Է�ʽ
	friend fraction operator /(fraction const &f, polynomial const &p);              //���ط�ʽ���Զ���ʽ
	friend ostream &operator <<(ostream &output, polynomial const &p);
};


class fraction : public polynomial             //��ʽ�࣬���м̳ж���ʽ����Ϊ��ʽ����
{
public:
	polynomial numerator;
	polynomial denominator;
public:
	fraction() { termNumber = 1; terms.push_back(monomial("1")); }
	fraction(monomial const &m);                                //�ӵ���ʽ�����ʽ,��ĸΪ1
	fraction(polynomial const &p);                              //�Ӷ���ʽ�����ʽ,��ĸΪ1
	fraction(fraction const &f) :polynomial(f), numerator(f.numerator), denominator(f.denominator) {};
	fraction (fraction &integrate, fraction &numerator, fraction &denominator) : polynomial(integrate), numerator(numerator), denominator(denominator) {};
	fraction changeSign(void) const;
	bool isZero(void) const{ return numerator.isZero(); }
	bool isDigit(void) const;                            //�жϷ�ʽ�Ƿ�Ϊ����
	double toDigit(void) const;                          //���Ǵ����ķ�ʽת��Ϊdouble
	fraction trySimplify(void);                          //�����ݴ�Ϊ����Լȥ������
	friend fraction myPow(fraction const &f, int power);              //�������㣬���ڼ���"^"������
	fraction operator +(fraction const &f2) const;        //���ط�ʽ����
	fraction operator *(fraction const &f2) const;        //���ط�ʽ����
	fraction operator /(fraction const &f2) const;        //���ط�ʽ����
	friend ostream &operator <<(ostream &output, fraction const &f);               //���ط�ʽ���
	friend fraction operator +(monomial const &m, fraction const &f);              //���ص���ʽ�ӷ�ʽ
	friend fraction operator +(fraction const &f, monomial const &m);
	friend fraction operator *(monomial const &m, fraction const &f);              //���ص���ʽ�ӷ�ʽ
	friend fraction operator *(fraction const &f, monomial const &m);
	friend fraction operator /(monomial const &m, fraction const &f);              //���ص���ʽ���Է�ʽ
	friend fraction operator /(fraction const &f, monomial const &m);              //���ط�ʽ���Ե���ʽ
	friend fraction operator +(polynomial const &p, fraction const &f);              //���ض���ʽ�ӷ�ʽ
	friend fraction operator +(fraction const &f, polynomial const &p);
	friend fraction operator *(polynomial const &p, fraction const &f);              //���ض���ʽ�ӷ�ʽ
	friend fraction operator *(fraction const &f, polynomial const &p);
	friend fraction operator /(polynomial const &p, fraction const &f);              //���ض���ʽ���Է�ʽ
	friend fraction operator /(fraction const &f, polynomial const &p);              //���ط�ʽ���Զ���ʽ
};

#endif // !symbolize