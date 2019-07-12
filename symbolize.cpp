#include "tool.h"
#include "symbolize.h"


double getGCF(double a, double b)
{
	int i,x = a, y = b, gcf = 1, m = min(x, y);
	if (!isZero(a - x)) return 1;
	if (!isZero(b - y)) return 1;
	for (i = 1; i <= m; i++)
		if ((!(x%i)) && (!(y%i))) gcf = i;
	return i;
}

int getPower(string const & str, int pos)
{
	if(!isalpha(str[pos])) return 0;
	if (str[pos + 1] == '^')
		return stoi(str.substr(pos + 2));
	else return 1;
}

int getPower(string const & str, char var)
{
	int pos = str.find(string(1, var));
	if (pos == string::npos) return 0;
	else if (str[pos + 1] != '^') return 1;
	else return stoi(str.substr(pos + 2));
}

bool changePower(string & str, int pos, int target)
{
	int power = getPower(str, pos);
	if (target == 0)
		if (power == 1) str.erase(pos, 1);
		else
		{
			str.erase(pos, 3);//将可能的符号也删去
			while (isdigit(str[pos])) str.erase(pos, 1);
		}
	else if (target == 1)
	{
		if (power == 1) return true;
		str.erase(pos + 1, 2);
		while (isdigit(str[pos + 1])) str.erase(pos + 1, 1);
	}
	else
	{
		if (power == 1)
		{
			str.insert(pos+1, 1, '^');
			str.insert(pos + 2, to_string(target));
		}
		else
		{
			str.erase(pos + 2, 1);
			while (isdigit(str[pos + 2])) str.erase(pos + 2, 1);
			str.insert(pos + 2, to_string(target));
		}
	}
	return true;
}

bool changePower(string & str, char var, int target)
{
	int pos = str.find(string(1, var));
	if (pos != string::npos)
		return(changePower(str, pos, target));
	else if (target == 0) return true;
	else if (target == 1) str.append(1, var);
	else
	{
		str.append(1, var);
		str.append(1, '^');
		str.append(to_string(target));
	}
	return true;
}



//将表达式按字母升序排列
void monomial::arrange(void)
{
	string temp;
	vector<string> strings;
	int length = expression.length();
	temp.append(1, expression[0]);
	for (int i = 1; i < length; i++)
	{
		if (isalpha(expression[i]))
		{
			strings.push_back(temp);
			temp.erase();
		}
		temp.append(1, expression[i]);
	}
	strings.push_back(temp);
	temp.erase();
	sort(strings.begin(), strings.end());
	for (vector<string>::iterator iter = strings.begin(); iter < strings.end(); iter++)
		temp.append(*iter);
	expression = temp;
}

//从字符串构造单项式并合并指数
monomial::monomial(string &exp)
{
	string expression;
	int power0, power1, length = exp.length();
	coefficient = stod(exp);
	for (int i = 0; i < length; i++)
	{
		if (power1 = getPower(exp, i))
		{
			if (power0=getPower(expression,exp[i]))
				cout << "you have input repeated letter " << exp[i] << "!" << endl;
			changePower(expression, exp[i], power0 + power1);
		}
	}
	this->expression = expression;
	this->arrange();
}


polynomial monomial::operator+(monomial const & m2) const
{
	polynomial result;
	monomial p1 = *this, p2 = m2;
	int m,power1, power2, length = expression.length();
	result.termNumber = 2;
	result.coefficient = getGCF(p1.coefficient, p2.coefficient);
	p1.coefficient /= result.coefficient;
	p2.coefficient /= result.coefficient;
	for(int i=0;i<length;i++)
		if(power1=getPower(p1.expression,i))
			if (power2 = getPower(p2.expression, p1.expression[i]))
			{
				m = min(power1, power2);
				changePower(result.expression, p1.expression[i], m);
				changePower(p1.expression, i, power1 - m);
				changePower(p2.expression, p1.expression[i], power2 - m);
			}
	result.terms.push_back(p1);
	result.terms.push_back(p2);
	return result;
}

polynomial monomial::operator-(monomial const & m2) const
{
	return polynomial();
}

monomial monomial::operator*(monomial const & m2) const
{
	monomial result;
	result.coefficient = coefficient * m2.coefficient;
	result.expression = expression;
	int power0, power1;
	int length1 = expression.length();
	int length2 = m2.expression.length();
	for (int i = 0; i < length2; i++)
		if (power1 = getPower(m2.expression, i))
		{
			power0 = getPower(result.expression, m2.expression[i]);
			changePower(result.expression, m2.expression[i], power0 + power1);
		}
	result.arrange();
	return result;
}



ostream & operator<<(ostream & output,monomial const & m)
{
	output << m.coefficient << m.expression;
	return output;
}


