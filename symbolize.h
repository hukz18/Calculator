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
	monomial() { coefficient = 1; }
	monomial (string const &expression);
	monomial (int coefficient, string const &expression) :coefficient(coefficient), expression(expression) {};
	monomial (monomial const &m) :coefficient(m.coefficient), expression(m.expression) {};
	void arrange(void); //�����ʽ����ĸ��������
	monomial changeSign(void) { coefficient *= -1; return *this; }                 //�ı䵥��ʽ����,���ڴ������
	polynomial operator + (monomial const &m2) const;                              //���ص���ʽ����
	/*����ʽ����ʽ�������*/
	friend polynomial operator +(monomial const &m, polynomial const &p);          //���ص���ʽ�Ӷ���ʽ
	friend polynomial operator +(polynomial const &p, monomial const &m);
	friend polynomial operator *(monomial const &m, polynomial const &p);          //���ص���ʽ�˶���ʽ
	friend polynomial operator *(polynomial const &p, monomial const &m);
	friend fraction operator /(monomial const &m, polynomial const &p);            //���ص���ʽ���Զ���ʽ
	friend polynomial operator /(polynomial const &p, monomial const &m);          //���ض���ʽ���Ե���ʽ
	monomial operator * (monomial const &m2) const;    //���ص���ʽ���ˣ�δ������ϵ�����
	monomial operator / (monomial const &m2) const;    //���ص���ʽ����
	friend ostream &operator <<(ostream &output, monomial const &m);               //���ص���ʽ���
};

class polynomial : public monomial          //����ʽ��,���м̳е���ʽ����Ϊ����ʽ
{
public:
	int termNumber = 0;
	vector<monomial> terms;
public:
	polynomial() {};
	polynomial(string &expression);//�Ȳ�����д,Ҳ���ò���
	polynomial(monomial &coefficient, int termNumber, vector<monomial> &terms) :monomial(coefficient), termNumber(termNumber), terms(terms) {};   //�����������ϵ��ȱʡֵΪ1
	virtual bool isZero(void);
	polynomial changeSign(void);   
	int getLength(void) const;    //��ȡ������ַ����ĳ���
	void factorize(void);                    //�ֽ���ʽ
	polynomial extraction(void) const;                   //��ȡ����ʽ
	polynomial expansion(void) const;                    //����ʽչ��
	void orderBy(char a);                    //���ַ�a��������
	polynomial substitution(char a, char b) const;       //���벢����ͬ����
	polynomial operator +(polynomial const &p2) const;   //���ض���ʽ����
	polynomial operator *(polynomial const &p2) const;   //���ض���ʽ����
	fraction operator /(polynomial const &p2) const;     //���ض���ʽ����
	/*����ʽ����ʽ�������*/
	friend polynomial operator +(monomial const &m, polynomial const &p);          //���ض���ʽ�ӵ���ʽ
	friend polynomial operator +(polynomial const &p, monomial const &m);
	friend polynomial operator *(monomial const &m, polynomial const &p);          //���ض���ʽ�˵���ʽ
	friend polynomial operator *(polynomial const &p, monomial const &m);
	friend fraction operator /(monomial const &m, polynomial const &p);            //���ص���ʽ���Զ���ʽ
	friend polynomial operator /(polynomial const &p, monomial const &m);          //���ض���ʽ���Ե���ʽ

	
	friend ostream &operator <<(ostream &output, polynomial const &p);
};

class fraction : public polynomial             //��ʽ�࣬���м̳ж���ʽ����Ϊ��ʽ����
{
public:
	polynomial numerator;
	polynomial denominator;
public:
	fraction() {};
	fraction (string &expression);                        //Ҳ���ò���
	fraction (fraction &integrate, fraction &numerator, fraction &denominator) : polynomial(integrate), numerator(numerator), denominator(denominator) {};
	fraction substitution(void);                          //�����ݴ�Ϊ����Լȥ������
	fraction operator +(fraction const &f2) const;        //���ط�ʽ����
	fraction operator *(fraction const &f2) const;        //���ط�ʽ����
	fraction operator /(fraction const &f2) const;        //���ط�ʽ����
	friend ostream &operator <<(ostream &output, fraction const &f);
};

#endif // !symbolize