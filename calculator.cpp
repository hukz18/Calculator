#include "calculator.h"

ostream & operator<<(ostream & output, Term & term)
{
	output << term.coefficient << term.variable;
	return output;
}

//��ȡ������,����������
int getEqution(vector <string> *equ)     
{
	char temp[maxLength];
	int count = 0;
	fgets(temp, maxLength, stdin);
	while (temp[0] != '\n')
	{
		equ->push_back(temp);
		fgets(temp, maxLength, stdin);
		count++;
	}
	return count;
}

//��ȡδ֪��������������������ظ�bug
int getVariable(vector<Term> *var)  
{
	/*char c;
	int count = 0, curTemp = 0, curName = 0;
	char name[20], temp[maxLength];
	fgets(temp, maxLength, stdin);
	c = temp[curTemp];
	while (c != '\n')
	{
		if (c == ' ')
		{
			name[curName] = '\0';
			var->push_back(Term(string(name)));
			curName = 0;count++;
		}
		else
			name[curName++]=c;
		c = temp[++curTemp];
	}*/
	string name;
	cin >> name;
	while (name.size())
	{
		var->push_back(Term(name));
		cin >> name;
	}
	var->push_back(Term(name));
	sort(var->begin(), var->end());                                 //���var�п��ܵ��ظ�Ԫ�أ�����bug
	var->erase(unique(var->begin(), var->end()), var->end());
	return var->size();
}

//��ȡ��δ֪����ϵ���������Ƿ�ɹ�

bool getCoefficient(vector <Term> *var, vector <string> &equ);//��ȡ��δ֪����ϵ���������Ƿ�ɹ�,�ҵ�����Ŀ�ʼ�������erase����

