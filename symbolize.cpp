#include "tools.h"
#include "symbolize.h"




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
monomial::monomial(string const &exp)
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

/*单项式部分*/
//重载单项式互加
polynomial monomial::operator+(monomial const & m2) const
{
	polynomial result;
	if (expression == m2.expression)
	{
		result.termNumber = 1;
		result.terms.push_back(monomial(coefficient + m2.coefficient, expression));
	}
	else
	{
		result.termNumber = 2;
		result.terms.push_back(*this);
		result.terms.push_back(m2);
	}
	return result;
}

//重载单项式互乘
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

//重载单项式输出
ostream & operator<<(ostream & output,monomial const & m)
{
	output << m.coefficient << m.expression;
	return output;
}








/*多项式部分*/
//提取公因式
void polynomial::extractCom(void)
{
	bool flag = true;
	int *power = new int[termNumber], copower;
	double *coeff = new double[termNumber];
	for (int i = 0; i < termNumber; i++)
		coeff[i] = terms[i].coefficient;
	coefficient = getGCF(coeff, termNumber);
	for (int i = 0; i < termNumber; i++)
		terms[i].coefficient /= coefficient;
	for (int i = 0; i < terms[0].expression.length(); i++)
		if (power[0] = getPower(terms[0].expression, i))
		{
			flag = true;
			for (int j = 1; j < termNumber; j++)
				if (!(power[j] = getPower(terms[j].expression, terms[0].expression[i]))) flag = false;
			if (flag == true)
			{
				copower = *min_element(power, power+termNumber);
				changePower(expression, terms[0].expression[i], copower);
				for (int j = 1; j < termNumber; j++)
					changePower(terms[j].expression, terms[0].expression[i], power[j] - copower);
				changePower(terms[0].expression, i--, power[0] - copower);
			}
		}
}

//改变多项式每项符号用于处理减法
void polynomial::changeSign(void)
{
	for (int i = 0; i < termNumber; i++)
		terms[i].coefficient *= -1;
}


//重载多项式互加
polynomial polynomial::operator+(polynomial const & p2) const
{
	if (p2.coefficient != 1||p2.expression!="")
		 cout << "polynomial plus error:having common factor";
	polynomial result = *this;
	result.termNumber += p2.termNumber;
	for (int i = 0; i < p2.termNumber; i++)
		result.terms.push_back(p2.terms[i]);
	return result;
}

//重载多项式互乘
polynomial polynomial::operator*(polynomial const & p2) const
{
	polynomial result;
	if (p2.coefficient != 1 || p2.expression != "")
		 cout << "polynomial multiply error:having common factor";
	for (int i = 0; i < termNumber; i++)
		for (int j = 0; j < p2.termNumber; j++)
			result = result + terms[i] * p2.terms[j];
}

/*混合运算部分*/
//重载单项式加多项式
polynomial operator+(monomial const & m, polynomial const & p)
{
	polynomial result(p);
	for (int i = 0; i < result.termNumber; i++)
		if (m.expression == result.terms[i].expression)
		{
			result.terms[i].coefficient;
			return result;
		}
	result.termNumber++;
	result.terms.push_back(m);
	return result;
}

//重载单项式乘多项式
polynomial operator*(monomial const & m, polynomial const & p)
{
	polynomial result;
	result.termNumber = p.termNumber;
	if(p.coefficient!=1||p.expression!="")
		 cout << "monomial&polynomial multiply error : having common factor";
	for (int i = 0; i < p.termNumber; i++)
		result.terms.push_back(m*p.terms[i]);
}
