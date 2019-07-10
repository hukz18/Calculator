#ifndef symbolize
#define symbolize
//��ҪisZero��
#include <string>
#include <vector>
#include <iostream>//�����������
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
	monomial (string &expression);
	monomial (int coefficient, string &expression) :coefficient(coefficient), expression(expression) {};
	monomial (monomial const &m) :coefficient(m.coefficient), expression(m.expression) {};
	polynomial operator + (monomial const &m2) const;  //���ص���ʽ�ӷ�
	polynomial operator - (monomial const &m2) const;  //���ص���ʽ����
	monomial operator * (monomial const &m2) const;    //���ص���ʽ�˷���δ������ϵ�����
	fraction operator / (monomial const &m2) const;    //���ص���ʽ����
	friend ostream &operator <<(ostream &output, monomial const &m);
};

class polynomial : public monomial          //����ʽ��,���м̳е���ʽ����Ϊ����ʽ
{
protected:
	int termNumber;
	vector<monomial> terms;
public:
	polynomial() {};
	polynomial (string &expression);//�Ȳ�����д,Ҳ���ò���
	polynomial (monomial &coefficient, int termNumber, vector<monomial> &terms) :monomial(coefficient),termNumber(termNumber), terms(terms) {};   //�����������ϵ��ȱʡֵΪ1
	polynomial operator +(polynomial const &p2) const;   //���ض���ʽ�ӷ�
	polynomial operator -(polynomial const &p2) const;   //���ض���ʽ����
	polynomial operator *(polynomial const &p2) const;   //���ض���ʽ�˷�
	fraction operator /(polynomial const &p2) const;     //���ض���ʽ����
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
	fraction (string &expression);
	fraction (fraction &integrate, fraction &numerator, fraction &denominator) : polynomial(integrate), numerator(numerator), denominator(denominator) {};
	fraction operator +(fraction const &f2) const;        //���ط�ʽ�ӷ�
	fraction operator -(fraction const &f2) const;        //���ط�ʽ����
	fraction operator *(fraction const &f2) const;        //���ط�ʽ�˷�
	fraction operator /(fraction const &f2) const;        //���ط�ʽ����
};

#endif // !symbolize