#include "tools.h"
#include "symbolize.h"



/*����ʽ����*/

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

//��ȡ����ĳ����ĸ��ϵ��(Ҳ���ò���)
monomial monomial::getCoeff(char var) const
{
	monomial result = *this;
	changePower(result.expression, var, 0);
	return result;
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
polynomial polynomial::substitution(char var, polynomial value) const
{
	polynomial result = *this;
	for (int i = 0; i < termNumber; i++)
	{
		int power = getPower(terms[i].expression, var);
		if (power > 0)
		{
			polynomial temp;
			temp = temp + terms[i].expression;
			changePower(temp.terms[0].expression, var, 0);
			for (int i = 0; i < power; i++)
				temp = temp * value;
			result = result + temp;
			result = result + terms[i].changeSign();
		}
	}
	return result;
}

//�ı����ʽÿ��������ڴ������
polynomial polynomial::changeSign(void) const
{
	polynomial result = *this;
	for (int i = 0; i < result.termNumber; i++)
		result.terms[i].coefficient *= -1;
	return result;
}

//�ݹ�طֽ���ʽ
vector<polynomial> polynomial::factorize(char var) const
{
	vector<polynomial> result;
	polynomial exp(*this); exp.orderBy(var);
	int power = getPower(exp.terms[0].expression, var);
	polynomial Const = exp.getConst(var);
	polynomial Coeff = exp.getCoeff(var, power);
	vector<char> ConstVar = Const.getVar(); int ConstSize = ConstVar.size();
	vector<char> CoeffVar = Coeff.getVar(); int CoeffSize = CoeffVar.size();
	bool flag = true;
	if (Const.termNumber == 1 && Coeff.termNumber == 1)
	{
		flag == false;
		for (int i = 0; i < CoeffSize; i++)
			for (int j = 0; j < ConstSize; i++)
			{
				monomial value = monomial(string(1, ConstVar[i]) + string(1, CoeffVar[j]));
				for (int k = 1; k <= getPower(Const.terms[0].expression, ConstVar[i]); k++)
					for (int l = 1; l <= getPower(Coeff.terms[0].expression, CoeffVar[j]); l++)
					{
						changePower(value.expression, ConstVar[i], k);
						changePower(value.expression, CoeffVar[j], -1 * l);
						if (exp.substitution(var, value).isZero())
						{
							flag = true;
							result.push_back(monomial(string(1, var)) + value.changeSign());
						}
					}
			}
		if (flag == false) result.push_back(*this);
	}
	vector<polynomial> CONST = Const.factorize(ConstVar[0]);
	vector<polynomial> COEFF = Coeff.factorize(CoeffVar[0]);
	return result;
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

//��ȡ��ĳ��ĸ���Եĳ�����
polynomial polynomial::getConst(char var) const
{
	polynomial result;
	for (int i = 0; i < termNumber; i++)
		if (getPower(terms[i].expression, var) == 0)
			result = result + terms[i];
	return result;	
}

//��ȡ��ĳ��ĸ������ߴ��ݵ�ϵ����
polynomial polynomial::getCoeff(char var, int power) const
{
	polynomial result;
	for (int i = 0; i < termNumber; i++)
		if (getPower(terms[i].expression, var) == power)
			result = result + terms[i];
	for (int i = 0; i < result.termNumber; i++)
		changePower(result.terms[i].expression, var, 0);
	return result;
}

//��ȡ����ʽ��������ĸ
vector<char> polynomial::getVar(void) const
{
	char cur;
	vector<char>::iterator iter;
	vector<char> var;
	for (int i = 0; i < expression.length(); i++)
	{
		cur = expression[i];
		if (!isalpha(cur)) continue;
		iter = find(var.begin(), var.end(), cur);
		if (iter == var.end()) var.push_back(cur);
	}
	for (int i = 0; i < termNumber; i++)
		for (int j = 0; j < terms[i].expression.length(); j++)
		{
			cur = terms[i].expression[j];
			if (!isalpha(cur)) continue;
			iter = find(var.begin(), var.end(), cur);
			if (iter == var.end()) var.push_back(cur);
		}
	return var;
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

//���ض���ʽ����,�Դ��ֽ���ʽ�ĳ���(��Ч��)
fraction polynomial::operator/(polynomial const & p2) const
{
	char var;
	fraction result;
	polynomial quotient;
	result.numerator = *this;
	result.denominator = p2;
	var = getComVar(result.numerator.getVar(), result.denominator.getVar());
	polynomial temp = result.numerator;
	if (var != '\0') //�й�������
	{
		result.numerator.orderBy(var);
		result.denominator.orderBy(var);
		while (!temp.terms.empty()&&getPower(temp.terms[0].expression, var) >= getPower(result.denominator.terms[0].expression, var)&& getPower(temp.terms[0].expression, var)>0)
		{
			quotient = temp.terms[0] / result.denominator.terms[0] + quotient;
			temp = temp + temp.terms[0] / result.denominator.terms[0] * result.denominator.changeSign();
		}
		if (temp.isZero())
			return quotient;
		result.numerator = this->extraction();
		result.denominator = p2.extraction();
		monomial &m1 = result.numerator, &m2 = result.denominator;
		result.numerator.coefficient = 1; result.numerator.expression.erase();
		result.denominator.coefficient = 1; result.denominator.expression.erase();
		result.numerator = result.numerator * m1; result.numerator = result.numerator / m2;
	}
	

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

//�Ӷ���ʽ�����ʽ,��ĸΪ1
fraction::fraction(polynomial & p)
{
	numerator = p;
	denominator.termNumber = 1;
	denominator.terms.push_back(monomial("1"));
}

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

//���Ի����ʽ
fraction fraction::trySimplify(void)
{
	fraction result = *this;
	char var = getComVar(result.numerator.getVar(), result.denominator.getVar());
	if (var == '\0') return;
	result.numerator.orderBy(var);
	result.denominator.orderBy(var);
	int power1 = getPower(result.numerator.terms[0].expression, var);
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

//���ط�ʽ����
fraction fraction::operator*(fraction const & f2) const
{
	fraction result;
	if (f2.termNumber != 0)
		cout << "err!fracton multuply!" << endl;
	result.numerator = numerator * f2.numerator;
	result.denominator = denominator * f2.denominator;
	//result.substitution();
	return result;
}

//���ط�ʽ����
fraction fraction::operator/(fraction const & f2) const
{
	fraction result;
	if (f2.termNumber != 0)
		cout << "err!fracton division!" << endl;
	result.numerator = numerator * f2.denominator;
	result.denominator = denominator * f2.numerator;
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