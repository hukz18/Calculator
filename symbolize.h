#ifndef symbolize
#define symbolize

#include <string>
#include <vector>
#include <algorithm>
using namespace std;
class monomial;
class polynomial;
class fraction;

class monomial             //����ʽ��
{
protected:
	double coefficient;                      //����ϵ��
	string expression;                    //��ĸ���ʽ
public:
	monomial() {};
	monomial (string expression);
	monomial (int coefficient, string expression) :coefficient(coefficient), expression(expression) {};
	monomial (monomial &m) :coefficient(m.coefficient), expression(m.expression) {};
	polynomial operator + (monomial &m2);  //���ص���ʽ�ӷ�
	polynomial operator - (monomial &m2);  //���ص���ʽ����
	monomial operator * (monomial &m2);    //���ص���ʽ�˷���δ������ϵ�����
	fraction operator / (monomial &m2);    //���ص���ʽ����
};

class polynomial : public monomial          //����ʽ��,���м̳е���ʽ����Ϊ����ʽ
{
protected:
	int termNumber;
	vector<monomial> terms;
public:
	polynomial() {};
	polynomial (string expression);
	polynomial (monomial &coefficient, int termNumber, vector<monomial> &terms) :monomial(coefficient),termNumber(termNumber), terms(terms) {};   //�����������ϵ��ȱʡֵΪ1
	polynomial operator +(polynomial &p2);   //���ض���ʽ�ӷ�
	polynomial operator -(polynomial &p2);   //���ض���ʽ����
	polynomial operator *(polynomial &p2);   //���ض���ʽ�˷�
	fraction operator /(polynomial &p2);     //���ض���ʽ����
	polynomial factorize(void);              //�ֽ���ʽ
	polynomial comfactorize(void);           //��ȡ����ʽ
};

class fraction : public polynomial             //��ʽ�࣬���м̳ж���ʽ����Ϊ��ʽ����
{
protected:
	polynomial numerator;
	polynomial denominator;
public:
	fraction() {};
	fraction (string expression);
	fraction (fraction &integrate, fraction &numerator, fraction &denominator) : polynomial(integrate), numerator(numerator), denominator(denominator) {};
	fraction operator +(fraction &f2);        //���ط�ʽ�ӷ�
	fraction operator -(fraction &f2);        //���ط�ʽ����
	fraction operator *(fraction &f2);        //���ط�ʽ�˷�
	fraction operator /(fraction &f2);        //���ط�ʽ����
};

#endif // !symbolize