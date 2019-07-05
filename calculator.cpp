#include "calculator.h"

ostream & operator<<(ostream & output, Term & term)
{
	output << term.coefficient << term.variable;
	return output;
}

//获取方程组,返回其总数
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

//获取未知数，返回其总数，解决重复bug
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
	sort(var->begin(), var->end());                                 //清除var中可能的重复元素，避免bug
	var->erase(unique(var->begin(), var->end()), var->end());
	return var->size();
}

//获取各未知数的系数，返回是否成功

bool getCoefficient(vector <Term> *var, vector <string> &equ);//获取各未知数的系数，返回是否成功,找到各项的开始与结束，erase变量

