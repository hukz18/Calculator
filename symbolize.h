#ifndef symbolize
#define symbolize
#include <string>
#include <vector>
#include <iostream>//�����������
#include <algorithm>

using namespace std;
class monomial;
class polynomial;
class fraction;
 
int getPower(string const &str, int pos);
int getPower(string const &str, char var);
bool changePower(string &str, int pos, int power);
bool changePower(string &str, char var, int power);

double getGCF(double a, double b);   //��ʵΪ�����򷵻��������

class monomial             //����ʽ��
{
private:
	double coefficient;                      //����ϵ��
	string expression;                    //��ĸ���ʽ
public:
	monomial() {};
	monomial (string &expression);
	monomial (int coefficient, string &expression) :coefficient(coefficient), expression(expression) {};
	monomial (monomial const &m) :coefficient(m.coefficient), expression(m.expression) {};
	void arrange(void); //�����ʽ����ĸ��������
	polynomial operator + (monomial const &m2) const;  //���ص���ʽ�ӷ�
	polynomial operator - (monomial const &m2) const;  //���ص���ʽ����
	monomial operator * (monomial const &m2) const;    //���ص���ʽ�˷���δ������ϵ�����
	fraction operator / (monomial const &m2) const;    //���ص���ʽ����
	friend ostream &operator <<(ostream &output, monomial const &m);
};

class polynomial : public monomial          //����ʽ��,���м̳е���ʽ����Ϊ����ʽ
{
public:
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
	friend ostream &operator <<(ostream &output, polynomial const &m);
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