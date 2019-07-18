#include "tools.h"
#include "symbolize.h"



/*����ʽ����*/

//������ʽ��ĸ����������
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

//���ַ������쵥��ʽ���ϲ�ָ��
monomial::monomial(string const &exp)
{
	string expression;
	int power0, power1, length = exp.length();
	coefficient = myStod(exp);
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

//���ص���ʽ����
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

//���ص���ʽ����
monomial monomial::operator*(monomial const & m2) const
{
	monomial result;
	result.coefficient = coefficient * m2.coefficient;
	result.expression = multiply(expression, m2.expression);
	result.arrange();
	return result;
}

//���ص���ʽ����
monomial monomial::operator/(monomial const & m2) const
{
	monomial result(*this);
	result.coefficient /= m2.coefficient;
	for (int i = 0; i < m2.expression.length(); i++)
		if (getPower(m2.expression, i))
			changePower(result.expression, m2.expression[i], getPower(result.expression, m2.expression[i]) - getPower(m2.expression, i));
	return result;
}

//���ص���ʽ���
ostream & operator<<(ostream & output,monomial const & m)
{
	if (m.coefficient == 0) return output;
	if (m.expression.empty()) output << m.coefficient;
	else if (m.coefficient == 1) output << m.expression;
	else output << m.coefficient << m.expression;
	return output;
}








/*����ʽ����*/

//�ж�����ʽ�Ƿ�Ϊ��
bool polynomial::isZero(void)
{
	if (termNumber == 0 || coefficient == 0) return true;
	else return false;
}

//��ȡ����ʽ
polynomial polynomial::extraction(void) const
{
	bool flag = true;
	polynomial result(*this);
	int *power = new int[termNumber], copower;
	double *coeff = new double[termNumber];
	for (int i = 0; i < termNumber; i++)
		coeff[i] = terms[i].coefficient;
	result.coefficient = getGCF(coeff, termNumber);
	for (int i = 0; i < result.termNumber; i++)
		result.terms[i].coefficient /= coefficient;
	for (int i = 0; i < terms[0].expression.length(); i++)
		if (power[0] = getPower(terms[0].expression, i))
		{
			flag = true;
			for (int j = 1; j < result.termNumber; j++)
				if (!(power[j] = getPower(terms[j].expression, terms[0].expression[i]))) flag = false;
			if (flag == true)
			{
				copower = *min_element(power, power+termNumber);
				changePower(result.expression, terms[0].expression[i], copower);
				for (int j = 1; j < result.termNumber; j++)
					changePower(result.terms[j].expression, terms[0].expression[i], power[j] - copower);
				changePower(result.terms[0].expression, i--, power[0] - copower);
			}
		}
	return result;
}

//����ʽչ��
polynomial polynomial::expansion(void) const
{
	polynomial result(*this);
	if (expression != "" || coefficient != 1)
	{
		for (int i = 0; i < termNumber; i++)
		{
			result.terms[i].coefficient *= coefficient;
			result.terms[i].expression = multiply(terms[i].expression, expression);
		}
		result.expression.erase(); result.coefficient = 1;
	}
	return result;
}

//���ַ�a��������(�õ�lanbde���ʽ)
void polynomial::orderBy(char a)
{
	sort(terms.begin(), terms.end(), [&](monomial m1, monomial m2)->bool {return(getPower(m1.expression, a) > getPower(m2.expression, a)); });
}

//���벢����ͬ����
polynomial polynomial::substitution(char a, char b) const
{
	monomial temp;
	polynomial result;
	for (int i = 0; i < termNumber; i++)
	{
		temp = terms[i];
		int pos = temp.expression.find(a);
		while (pos != string::npos)
		{
			changePower(temp.expression, b, getPower(temp.expression, b) + getPower(temp.expression, pos));
			changePower(temp.expression, pos, 0);
			pos = temp.expression.find(a);
		}
		temp.arrange();
		result = result + temp;
	}
	return result;
}

//�ı����ʽÿ��������ڴ������
polynomial polynomial::changeSign(void)
{
	for (int i = 0; i < termNumber; i++)
		terms[i].coefficient *= -1;
	return *this;
}

//��ȡ������ַ����ĳ���
int polynomial::getLength(void) const
{
	string temp;
	int length = 0;
	stringstream stream;
	if (termNumber == 0) return 0;
	if (coefficient != 1)
	{
		stream << coefficient;
		stream >> temp;
	}
	temp += expression;
	length += temp.length();
	for (int i = 0; i < termNumber; i++)
	{
		stream.clear(); temp.erase();
		if (terms[i].coefficient != 1)
		{
			stream << terms[i].coefficient;
			stream >> temp;
		}
		temp += terms[i].expression;
		length += temp.length();
	}
	return (length + 2 * termNumber - 2);
}



//���ض���ʽ����
polynomial polynomial::operator+(polynomial const & p2) const
{
	polynomial result(*this);
	for (int i = 0; i < p2.termNumber; i++)
		result = result + p2.terms[i];
	return result;
}

//���ض���ʽ����
polynomial polynomial::operator*(polynomial const & p2) const
{
	polynomial result;
	for (int i = 0; i < termNumber; i++)
		for (int j = 0; j < p2.termNumber; j++)
			result = result + terms[i] * p2.terms[j];
	return result;
}

//���ض���ʽ����
fraction polynomial::operator/(polynomial const & p2) const
{
	fraction result;
	result.numerator = this->extraction();
	result.denominator = p2.extraction();
	monomial &m1 = result.numerator, &m2 = result.denominator;
	result.numerator.coefficient = 1; result.numerator.expression.erase();
	result.denominator.coefficient = 1; result.denominator.expression.erase();
	result.numerator = result.numerator * m1; result.numerator = result.numerator / m2;
	return result;
}

//���ض���ʽ���
ostream & operator<<(ostream & output, polynomial const & p)
{
	monomial const &m = p;
	if (m.expression != ""||m.coefficient!=1)
		output << m << " (";
	if (p.termNumber == 0) return output;
	output << p.terms[0] << " ";
	for (int i = 1; i < p.termNumber; i++)
	{
		if (p.terms[i].coefficient > 0) cout << "+" << p.terms[i] << " ";
		else cout << p.terms[i] << " ";
	}
	if (m.expression != "")
	cout << ")";
	return output;
}


/*��ʽ����*/

//���ط�ʽ���
ostream & operator<<(ostream & output, fraction const & f)
{
	polynomial const &p = f;
	int l1 = p.getLength();
	int l2 = f.numerator.getLength(), l3 = f.denominator.getLength();
	int d1 = (l2 < l3) ? (l1 + (l3 - l2) / 2) : l1;
	int d2 = (l3 < l2) ? (l1 + (l2 - l3) / 2) : l1;
	for (int i = 0; i < d1; i++) output << " ";
	output << f.numerator << endl;
	output << p;
	for (int i = 0; i < max(l2, l3); i++) output << "-";
	output << endl;
	for (int i = 0; i < d2; i++) output << " ";
	output << f.denominator;
	return output;
}

//���ط�ʽ����
fraction fraction::operator+(fraction const & f2) const
{
	fraction result;
	if (f2.termNumber != 0)
		cout << "err!fracton addition!" << endl;
	result.denominator = denominator * f2.denominator;
	polynomial p1 = numerator * f2.denominator;
	polynomial p2 = f2.numerator * denominator;
	result.numerator = p1 + p2;
	//result.substitution();
	return result;
}





/*������㲿��*/

//���ص���ʽ�Ӷ���ʽ
polynomial operator+(monomial const & m, polynomial const & p)
{
	polynomial result(p);
	for (vector<monomial>::iterator iter = result.terms.begin(); iter < result.terms.end(); iter++)
		if (m.expression == iter->expression)
		{
			iter->coefficient += m.coefficient;
			if (iter->coefficient == 0)
			{
				result.termNumber--;
				result.terms.erase(iter);
			}
			return result;
		}
	result.termNumber++;
	result.terms.push_back(m);
	return result;
}
polynomial operator +(polynomial const &p, monomial const &m) { return m + p; }

//���ص���ʽ�˶���ʽ
polynomial operator*(monomial const & m, polynomial const & p)
{
	polynomial result;
	result.termNumber = p.termNumber;
	if(p.coefficient!=1||p.expression!="")
		 cout << "monomial&polynomial multiply error : having common factor";
	for (int i = 0; i < p.termNumber; i++)
		result.terms.push_back(m*p.terms[i]);
	return result;
}
polynomial operator *(polynomial const &p, monomial const &m) { return m * p; }

//���ص���ʽ���Զ���ʽ
fraction operator/(monomial const & m, polynomial const & p)
{
	fraction result;
	polynomial divider(p.extraction());
	monomial &subdivider = divider;
	result.numerator.terms.push_back(m / subdivider);result.numerator.termNumber++;
	divider.coefficient = 1; divider.expression.erase();
	result.denominator = divider;
	return result;
}

//���ض���ʽ���Ե���ʽ
polynomial operator/(polynomial const & p, monomial const & m)
{
	polynomial result;
	result.termNumber = p.termNumber;
	if (p.coefficient != 1 || p.expression != "")
		cout << "monomial&polynomial divide error : having common factor";
	for (int i = 0; i < result.termNumber; i++)
		result.terms.push_back(p.terms[i] / m);
	return result;
}


