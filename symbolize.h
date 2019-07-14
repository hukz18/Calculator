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
 


class monomial             //����ʽ��
{
public:
	double coefficient;                      //����ϵ��
	string expression;                    //��ĸ���ʽ
public:
	monomial() { coefficient = 1; }
	monomial (string const &expression);
	monomial (int coefficient, string const &expression) :coefficient(coefficient), expression(expression) {};
	monomial (monomial const &m) :coefficient(m.coefficient), expression(m.expression) {};
	void arrange(void); //�����ʽ����ĸ��������
	virtual void changeSign(void) { coefficient *= -1; }                 //�ı䵥��ʽ����,���ڴ������
	polynomial operator + (monomial const &m2) const;                    //���ص���ʽ����
	friend polynomial operator +(monomial const &m, polynomial const &p);//���ص���ʽ�Ӷ���ʽ
	friend polynomial operator +(polynomial const &p, monomial const &m) { return m + p; }//���ض���ʽ�ӵ���ʽ
	friend polynomial operator *(monomial const &m, polynomial const &p);//���ص���ʽ�˶���ʽ
	friend polynomial operator *(polynomial const &p, monomial const &m) { return m * p; }//���ض���ʽ�˵���ʽ
	monomial operator * (monomial const &m2) const;    //���ص���ʽ���ˣ�δ������ϵ�����
	fraction operator / (monomial const &m2) const;    //���ص���ʽ����
	friend ostream &operator <<(ostream &output, monomial const &m);//���ص���ʽ���
};

class polynomial : public monomial          //����ʽ��,���м̳е���ʽ����Ϊ����ʽ
{
public:
	int termNumber;
	vector<monomial> terms;
public:
	polynomial() {};
	polynomial(string &expression);//�Ȳ�����д,Ҳ���ò���
	polynomial(monomial &coefficient, int termNumber, vector<monomial> &terms) :monomial(coefficient), termNumber(termNumber), terms(terms) {};   //�����������ϵ��ȱʡֵΪ1
	virtual void changeSign(void);//�ı����ʽ����
	polynomial operator +(polynomial const &p2) const;   //���ض���ʽ����
	friend polynomial operator +(monomial const &m, polynomial const &p);//���ص���ʽ�Ӷ���ʽ
	friend polynomial operator +(polynomial const &p, monomial const &m);//���ض���ʽ�ӵ���ʽ
	friend polynomial operator *(monomial const &m, polynomial const &p);//���ص���ʽ�˶���ʽ
	friend polynomial operator *(polynomial const &p, monomial const &m);//���ض���ʽ�˵���ʽ
	polynomial operator *(polynomial const &p2) const;   //���ض���ʽ����
	fraction operator /(polynomial const &p2) const;     //���ض���ʽ����
	polynomial factorize(void);              //�ֽ���ʽ
	void extractCom(void);           //��ȡ����ʽ
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