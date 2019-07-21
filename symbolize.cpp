#include "tools.h"
#include "symbolize.h"



/*单项式部分*/

//从字符串构造单项式并合并指数
monomial::monomial(string const &exp)
{
	string expression="";
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

//将单项式字母按升序排列
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

//获取其中某个字母的系数(也许用不到)
monomial monomial::getCoeff(char var) const
{
	monomial result = *this;
	changePower(result.expression, var, 0);
	return result;
}
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
	result.expression = multiply(expression, m2.expression);
	result.arrange();
	return result;
}

//重载单项式互除
monomial monomial::operator/(monomial const & m2) const
{
	monomial result(*this);
	result.coefficient /= m2.coefficient;
	for (int i = 0; i < m2.expression.length(); i++)
		if (getPower(m2.expression, i))
			changePower(result.expression, m2.expression[i], getPower(result.expression, m2.expression[i]) - getPower(m2.expression, i));
	return result;
}

//重载单项式输出
ostream & operator<<(ostream & output,monomial const & m)
{
	if (m.coefficient == 0) return output;
	if (m.expression.empty()) output << m.coefficient;
	else if (m.coefficient == 1) output << m.expression;
	else output << m.coefficient << m.expression;
	return output;
}








/*多项式部分*/

//判定多项式是否为零
bool polynomial::isZero(void) const
{
	if (termNumber == 0 || coefficient == 0 || terms.empty()) return true;
	else return false;
}

//提取公因式
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
		result.terms[i].coefficient /= result.coefficient;
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
				changePower(result.terms[0].expression, terms[0].expression[i], power[0] - copower);
			}
		}
	return result;
}

//多项式展开
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

//创建提取公因式中的一项
polynomial createTerm(char var, polynomial const Coeff, int coeffPower, polynomial const Const, int constpower) 
{
	polynomial result;
	monomial Var(string(1, var));
	result = result + Var;
	for (int i = 0; i < coeffPower; i++)
		result = result * Coeff;
	polynomial temp = Const;
	for (int i = 1; i < constpower; i++)
		temp = temp * Const;
	result = result + temp.changeSign();
	return result;
}

//按字符a降幂排序(用到lambda表达式)
void polynomial::orderBy(char a)
{
	sort(terms.begin(), terms.end(), [&](monomial m1, monomial m2)->bool {return(getPower(m1.expression, a) > getPower(m2.expression, a)); });
}

//带入并消除同类项
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

//带余除法，返回余式
polynomial polynomial::DivideWithRemainder(polynomial & divider)
{
	polynomial result, remainder;
	remainder = *this;
	char var = getComVar(remainder.getVar(), divider.getVar());
	if (var != '\0')
	{
		remainder.orderBy(var);
		divider.orderBy(var);
		while ((!remainder.terms.empty()) && getPower(remainder.terms[0].expression, var) >= getPower(divider.terms[0].expression, var))
		{
			result = remainder.terms[0] / divider.terms[0] + result;
			remainder = remainder + remainder.terms[0] / divider.terms[0] * divider.changeSign();
		}
	}
	return remainder;
}

//改变多项式每项符号用于处理减法
polynomial polynomial::changeSign(void) const
{
	polynomial result = *this;
	if (result.terms.empty()) return result;
	for (int i = 0; i < result.termNumber; i++)
		result.terms[i].coefficient *= -1;
	return result;
}

//递归地分解因式,想得太复杂,回头再做
vector<polynomial> polynomial::factorize(char var) const
{
	vector<polynomial> result;
	polynomial exp(*this); exp.orderBy(var);
	int power = getPower(exp.terms[0].expression, var);
	polynomial Const = exp.getConst(var);
	polynomial Coeff = exp.getCoeff(var, power);
	vector<char> ConstVar = Const.getVar(); int ConstSize = ConstVar.size();
	vector<char> CoeffVar = Coeff.getVar(); int CoeffSize = CoeffVar.size();
	bool flag = false;
	if (Const.termNumber == 1 && Coeff.termNumber == 1)
	{
		flag == false;
		for (int i = 0; i < CoeffSize; i++)
			for (int j = 0; j < ConstSize; i++)
			{
				monomial value = monomial(string(1, CoeffVar[i]) + string(1, ConstVar[j]));
				for (int k = 1; k <= getPower(Const.terms[0].expression, ConstVar[i]); k++)
					for (int l = 1; l <= getPower(Coeff.terms[0].expression, CoeffVar[j]); l++)
					{
						changePower(value.expression, ConstVar[i], k);
						changePower(value.expression, CoeffVar[j], -1 * l);
						if (exp.substitution(var, value).isZero())
						{
							flag = true;
							polynomial term = createTerm(var, monomial(string(1, CoeffVar[j])), l, monomial(string(1, ConstVar[i])), k);
							if (exp.DivideWithRemainder(term).isZero())
								result.push_back(term);
							if(getPower(exp.terms[0].expression,var==0))
								return result;
						}
						if (exp.substitution(var, value.changeSign()).isZero())
						{
							flag = true;
							result.push_back(monomial(string(1, var)) + value);
						}
					}
			}
		if (flag == false) result.push_back(*this);
	}
	vector<polynomial> CONST = Const.factorize(ConstVar[0]);
	vector<polynomial> COEFF = Coeff.factorize(CoeffVar[0]);
	return result;
}

//获取输出后字符串的长度
int polynomial::getLength(void) const
{
	string temp;
	int length = 0;
	stringstream stream;
	if (terms.empty()) return 0;
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
	return (length + 2*termNumber - 2);
}

//获取对某字母而言的常数项
polynomial polynomial::getConst(char var) const
{
	polynomial result;
	if (terms.empty()) return result;
	for (int i = 0; i < termNumber; i++)
		if (getPower(terms[i].expression, var) == 0)
			result = result + terms[i];
	return result;	
}

//获取对某字母而言最高次幂的系数项
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

//获取多项式中所含字母
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



//重载多项式互加
polynomial polynomial::operator+(polynomial const & p2) const
{
	polynomial result(*this);
	for (int i = 0; i < p2.termNumber; i++)
		result = result + p2.terms[i];
	return result;
}

//重载多项式互乘
polynomial polynomial::operator*(polynomial const & p2) const
{
	polynomial result;
	for (int i = 0; i < termNumber; i++)
		for (int j = 0; j < p2.termNumber; j++)
			result = result + terms[i] * p2.terms[j];
	return result;
}


//重载多项式互除
fraction polynomial::operator/(polynomial const & p2) const
{
	fraction result;
	result.numerator = *this;
	result.denominator = p2;
	result.numerator = this->extraction();
	result.denominator = p2.extraction();
	monomial &m1 = result.numerator, &m2 = result.denominator;
	result.numerator = result.numerator * m1; result.numerator = result.numerator / m2;
	result.numerator.coefficient = 1; result.numerator.expression.erase();
	result.denominator.coefficient = 1; result.denominator.expression.erase();
	return result;
}

//重载多项式输出
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


/*分式部分*/

//从单项式构造分式,分母为1
fraction::fraction(monomial const & m)
{
	numerator = polynomial(m);
	denominator.termNumber = 1;
	denominator.terms.push_back(monomial("1"));
	for (int i = 0; i < m.expression.length(); i++)
	{
		int power = getPower(m.expression, i);
		if (power < 0)
		{
			changePower(numerator.terms[0].expression, m.expression[i], 0);
			changePower(denominator.terms[0].expression, m.expression[i], -1*power);
		}
	}
}

//从多项式构造分式,分母为1
fraction::fraction(polynomial const & p)
{
	numerator = p;
	monomial m = p.extraction();
	denominator.termNumber = 1;
	denominator.terms.push_back(monomial("1"));
	for (int i = 0; i < m.expression.length(); i++)
	{
		int power = getPower(m.expression, i);
		if (power > 0)
			changePower(m.expression, i--, 0);
	}
	for(int i=0;i<p.termNumber;i++)
		numerator.terms[i] = numerator.terms[i] / m;
	denominator.terms[0] = denominator.terms[0] / m;
}

//重载分式输出
ostream & operator<<(ostream & output, fraction const & f)
{
	polynomial const &p = f;
	int l1 = p.getLength();
	int l2 = f.numerator.getLength(), l3 = f.denominator.getLength();
	int d1 = (l2 < l3) ? (l1 + (l3 - l2) / 2)+1 : l1;
	int d2 = (l3 < l2) ? (l1 + (l2 - l3) / 2)+1 : l1;
	for (int i = 0; i < d1; i++) output << " ";
	output << f.numerator << endl;
	if(!p.terms.empty())
		output << p;
	for (int i = 0; i < max(l2, l3); i++) output << "-";
	output << endl;
	for (int i = 0; i < d2; i++) output << " ";
	output << f.denominator;
	return output;
}


fraction fraction::changeSign(void) const
{
	fraction result = *this;
	if (result.numerator.terms.empty()) return result;
	for (int i = 0; i < result.termNumber; i++)
		result.numerator.terms[i].coefficient *= -1;
	return result;
}

//尝试化简分式
fraction fraction::trySimplify(void)
{
	fraction result = *this;
	char var = getComVar(result.numerator.getVar(), result.denominator.getVar());
	if (var == '\0') return *this;
	result.numerator.orderBy(var);
	result.denominator.orderBy(var);
	int power1 = getPower(result.numerator.terms[0].expression, var);
	return result;
}

//重载分式互加
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

//重载分式互乘
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

//重载分式互除
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




/*混合运算部分*/

//重载单项式加多项式
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

//重载单项式乘多项式
polynomial operator*(monomial const & m, polynomial const & p)
{
	polynomial result;
	result.termNumber = p.termNumber;
	for (int i = 0; i < p.termNumber; i++)
		result.terms.push_back(m*p.terms[i]);
	return result;
}
polynomial operator *(polynomial const &p, monomial const &m) { return m * p; }

//重载单项式除以多项式
fraction operator/(monomial const & m, polynomial const & p)
{
	fraction result;
	result.denominator = p.extraction();
	monomial &coeff = result.denominator;
	result.numerator = polynomial(m / coeff);
	result.denominator.coefficient = 1; result.denominator.expression = "";
	return result;
}

//重载多项式除以单项式
polynomial operator/(polynomial const & p, monomial const & m)
{
	polynomial result = p.extraction();
	monomial &coeff = result;
	result = coeff / m * result;
	result.coefficient = 1; result.expression = "";
	return result;
}

fraction operator+(monomial const & m, fraction const & f)
{
	return fraction(m) + f;
}

fraction operator+(fraction const & f, monomial const & m)
{
	return fraction(m) + f;
}

fraction operator*(monomial const & m, fraction const & f)
{
	return fraction(m) * f;
}

fraction operator*(fraction const & f, monomial const & m)
{
	return fraction(m) * f;
}

fraction operator/(monomial const & m, fraction const & f)
{
	return fraction(m) / f;
}

fraction operator/(fraction const & f, monomial const & m)
{
	return f / fraction(m);
}

fraction operator+(polynomial const & p, fraction const & f)
{
	return fraction(p) + f;
}

fraction operator+(fraction const & f, polynomial const & p)
{
	return fraction(p) + f;
}

fraction operator*(polynomial const & p, fraction const & f)
{
	return fraction(p) * f;
}

fraction operator*(fraction const & f, polynomial const & p)
{
	return fraction(p) * f;
}

fraction operator/(polynomial const & p, fraction const & f)
{
	return fraction(p) / f;
}

fraction operator/(fraction const & f, polynomial const & p)
{
	return f / fraction(p);
}
