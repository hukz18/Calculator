#ifndef calculator
#define calculator

#define maxLength 80

#include <map>
#include <vector>
#include <string>
#include <iostream>
#include <algorithm>

using namespace std;

class Term           //����δ֪������ϵ��
{
private:
	string variable;
	string coefficient;
public:
	Term(string &variable, string &coefficient) :variable(variable), coefficient(coefficient) {};
	Term(const string &variable) :variable(variable), coefficient("1") {};
	bool operator ==(Term &t2) { return variable == t2.variable; }
	bool operator <(Term &t2) { return variable < t2.variable; }
	friend ostream &operator <<(ostream &output, Term &term);
};

int getEqution(vector <string> *equ);     //��ȡ������,����������
int getVariable(vector <Term> *var);  //��ȡδ֪��������������
bool getCoefficient(vector <Term> *var, vector <string> &equ);//��ȡ��δ֪����ϵ���������Ƿ�ɹ�,�ҵ�����Ŀ�ʼ�������erase����

#endif // !calculator.h