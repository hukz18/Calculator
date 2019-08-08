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

//获取单项式中所含字母
vector<char> monomial::getVar(void) const
{
	vector<char> result;
	for (int i = 0; i < expression.length(); i++)
		if (isalpha(expression[i])) result.push_back(expression[i]);
	return result;
}

//将单项式中指数小于零的项拆分
monomial * monomial::split(void) const
{
	int length = expression.length();
	monomial *split = new monomial[2];
	split[0].coefficient = coefficient;
	string num, denom;
	for (int i = 0; i < length; i++)
		if (getPower(expression, i) > 0)
		{
			num.append(1, expression[i]);
			changePower(num, expression[i], getPower(expression, i));
		}
		else if (getPower(expression, i) < 0)
		{
			denom.append(1, expression[i]);
			changePower(num, 0, -1 * getPower(expression, i));
		}
	split[0].expression = num;
	split[1].expression = denom;
	return split;
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

//重载单项式比较
bool monomial::operator==(monomial const & m2) const
{
	if (coefficient == m2.coefficient&&expression == m2.expression) return true;
	else return false;
}

//重载单项式输出
ostream & operator<<(ostream & output,monomial const & m)
{
	if (m.coefficient == 0) output << "0";
	else if (m.expression[0]=='\0') output << m.coefficient;
	else if (m.coefficient == 1) output << m.expression;
	else if (m.coefficient == -1) output << "-" << m.expression;
	else output << m.coefficient << m.expression;
	return output;
}

//创造下一项可能的根
monomial nextValue(int &step, vector<char> const & Coeff, vector<char> const & Const, vector<double> const &value)  //创造一项可能的因式
{
	string exp1, exp2;
	int lvalue, leffv, lconv;
	lvalue = value.size();
	leffv = Coeff.size(); lconv = Const.size();
	if (step >= (2 * lvalue * pow(2, (leffv + lconv))))
		return monomial(0);	
	bool *vars = Subset(leffv + lconv, (step / (2 * lvalue)) % (int)pow(2, (leffv + lconv)));
	for (int i = 0; i < leffv; i++)
		if (vars[i]) { exp1.append(1, Coeff[i]); exp1.append("^-1"); }
	for (int i = 0; i < lconv; i++)
		if (vars[i + leffv]) exp2.append(1, Const[i]);
	monomial result = monomial(value[(step / 2) % lvalue], exp1 + exp2);
	if ((step++) % 2 == 1)
		result.coefficient *= -1;
	return result;
}


/*多项式部分*/

polynomial::polynomial(string const & expression)
{
	string temp;
	int head, cur = 0;
	int length = expression.length();
	while (cur < length)
	{
		head = cur++;
		while ((expression[cur] != '+') && (expression[cur] != '-') && cur < length) cur++;
		temp = expression.substr(head, cur - head);
		termNumber++;
		terms.push_back(monomial(temp));
	}
}

//判定多项式是否为零
bool polynomial::isZero(void) const
{
	if (termNumber == 0 || coefficient == 0 || terms.empty()) return true;
	bool flag = true;
	for (int i = 0; i < termNumber; i++)
		if (!tools::isZero(terms[i].coefficient)) flag = false;
	return flag;
}

//确认多项式是否"小于零"
bool polynomial::isNegative(void) const
{
	bool flag = true;
	for (int i = 0; i < termNumber; i++)
		if (terms[i].coefficient >= 0) flag = false;
	return flag;
}

//提取公因式
polynomial polynomial::extraction(void) const
{
	bool flag = true;
	polynomial result(*this);
	if (termNumber == 0) return result;
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

//多项式展开(没用?)
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
			temp = temp + terms[i];
			changePower(temp.terms[0].expression, var, 0);
			for (int i = 0; i < power; i++)
				temp = temp * value;
			result = result + temp;
			result = result + terms[i].changeSign();
		}
	}
	return result;
}

//若整除则除并返回true，否则不改变且返回false
bool polynomial::tryDivide(polynomial const & p)
{
	polynomial temp(*this);
	if ((temp.DivideWithRemainder(p).isZero()))
	{
		*this = temp; return true;
	}
	else return false;
}
//带余除法，返回余式
polynomial polynomial::DivideWithRemainder(polynomial const &divider)
{
	polynomial result, remainder, mydivider = divider;
	remainder = *this;
	char var = getComVar(remainder.getVar(), divider.getVar());
	if (var != '\0')
	{
		remainder.orderBy(var);
		mydivider.orderBy(var);
		while ((!remainder.terms.empty()) && getPower(remainder.terms[0].expression, var) >= getPower(mydivider.terms[0].expression, var))
		{
			result = remainder.terms[0] / mydivider.terms[0] + result;
			remainder = remainder + remainder.terms[0] / mydivider.terms[0] * mydivider.changeSign();
			remainder.orderBy(var);
		}
	}
	*this = result;
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
//改进：处理整数，(不能用char了,修正getpower和changepower（if isdigit))处理（x-ab)^2,写多项式系数情况，考虑是否有递归溢出
vector<polynomial> polynomial::factorize(char var) const
{
	#pragma region PreGlobal
	vector<polynomial> result;
	polynomial exp(*this); exp.orderBy(var);
	int step = 0;
	int power = getPower(exp.terms[0].expression, var);
	vector<int> varPower = getFactor(power); int varPowerSize = varPower.size() - 1;
	if (varPowerSize == 0) varPowerSize += 1;
	if (exp.termNumber <= 2) { result.push_back(*this); return result; }
	polynomial Const = exp.getConst(var), Coeff = exp.getCoeff(var, power);
	vector<char> ConstVar = Const.getVar(), CoeffVar = Coeff.getVar();
	int ConstSize = ConstVar.size(), CoeffSize = CoeffVar.size();
	
	#pragma endregion
	//Const,Coeff,ConstVar,CoeffVar,ConstSize,CoeffSize
	if (Const.termNumber == 1 && Coeff.termNumber == 1)
	{
		#pragma region PreValue
		vector<int> effFactor, conFactor;
		double constvalue = Const.terms[0].coefficient; double coeffvalue = Coeff.terms[0].coefficient;
		if (isInteger(coeffvalue) && isInteger(constvalue))
		{
			effFactor = getFactor((int)coeffvalue);
			conFactor = getFactor((int)constvalue);
		}
		else { effFactor.push_back(1); conFactor.push_back(1); }
		vector<double> Coeffvalue = getValue(conFactor, effFactor);
		monomial value = nextValue(step, CoeffVar, ConstVar, Coeffvalue);
		#pragma endregion
		//CoeffValue +CoeffVar,ConstVar->value
		#pragma region PrePower
		vector<char> vars = value.getVar();
		int size = vars.size(), total = 1;
		int *powers = new int[size];
		vector<int> power, *factors = new vector<int>[size];

		for (int i = 0; i < size; i++)
		{
			powers[i] = max(getPower(Const.terms[0].expression, vars[i]), getPower(Coeff.terms[0].expression, vars[i]));
			factors[i] = getFactor(powers[i]);
			total *= factors[i].size();
		}
		power = nextPower(vars, powers, factors, 0);
		polynomial nextTerm = createTerm(var, value, power);
		#pragma endregion
		//vars=value.getVar(),*powers,*factors,power=NextPower
		while ((getPower(exp.terms[0].expression, var) > getPower(nextTerm.terms[0].expression, var)) && (!value.isZero()))
		{
			for (int i = 0; i < varPowerSize; i++)
				for (int j = 0; j < total; j++)
				{
					power = nextPower(vars, powers, factors, j);
					nextTerm = createTerm(var, value, power);
					changePower(nextTerm.terms[0].expression, var, varPower[i]);
					if (exp.tryDivide(nextTerm))
					{
						result.push_back(nextTerm); step = 0;
						if (getPower(exp.terms[0].expression, var) == 1 || getPower(exp.terms[0].expression, var) == 0) { result.push_back(exp); return result; }
					}
				}
			value = nextValue(step, CoeffVar, ConstVar, Coeffvalue);
			#pragma region PrePower
			vars = value.getVar(); size = vars.size();
			delete[]powers; delete[]factors; total = 1;
			powers = new int[size]; factors = new vector<int>[size];
			for (int i = 0; i < size; i++)
			{
				powers[i] = max(getPower(Const.terms[0].expression, vars[i]), getPower(Coeff.terms[0].expression, vars[i]));
				factors[i] = getFactor(powers[i]);
				total *= factors[i].size();
			}
			#pragma endregion
		}
		result.push_back(exp);
		return result;
	}
	else
	//{
		//vector<polynomial>effFactor, conFactor;

	
	result.push_back(*this);
	return result;
}

//获取输出后字符串的长度
int polynomial::getLength(void) const
{
	string temp;
	int length = 0;
	stringstream stream;
	if (terms.empty()) return 0;
	stream << *this;
	temp = stream.str();
	return temp.length();
}

//获取幂次最高的字母
char polynomial::getMainTerm(void) const
{
	char result='0';
	int maxPower = 0;
	for (int i = 0; i < termNumber; i++)
		for (int j = 0; j < terms[i].expression.length(); j++)
			if (getPower(terms[i].expression, j) > maxPower)
			{ maxPower = getPower(terms[i].expression, j); result = terms[i].expression[j]; }
	return result;
}

//获取多项式的公系数
int polynomial::getCoeff(void) const
{
	double *coeff = new double[termNumber];
	for (int i = 0; i < termNumber; i++)
		coeff[i] = terms[i].coefficient;
	double result = getGCF(coeff, termNumber);
	delete[]coeff;
	if (isInteger(result)) return result;
	else return 1;
}

//获取某多项式因子在另一多项式中的次数
int polynomial::factorPower(polynomial const & factor) const
{
	int power = 0;
	polynomial temp(*this);
	while (temp.tryDivide(factor)) power++;
	return power;
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
	if ((*this).isZero() || p2.isZero())
		return result;
	for (int i = 0; i < termNumber; i++)
		for (int j = 0; j < p2.termNumber; j++)
			result = result + terms[i] * p2.terms[j];
	return result;
}


//重载多项式互除
fraction polynomial::operator/(polynomial const & p2) const
{
	fraction result;
	result.numerator = this->extraction();
	result.denominator = p2.extraction();
	monomial m1 = result.numerator, m2 = result.denominator;
	monomial *split = (m1 / m2).split();
	result.numerator = result.numerator * split[0]; result.denominator = result.denominator *split[1];
	delete[]split;
	result.numerator.coefficient = 1; result.numerator.expression.erase();
	result.denominator.coefficient = 1; result.denominator.expression.erase();
	return result;
}

//重载多项式比较
bool polynomial::operator==(polynomial const & p2) const
{
	monomial const &m1 = *this, &m2 = p2;
	for (int i = 0; i < termNumber; i++)
		if (!(terms[i] == p2.terms[i])) return false;
	if (!(m1 == m2)) return false;
	return true;
}

//重载多项式输出
ostream & operator<<(ostream & output, polynomial const & p)
{
	monomial const &m = p;
	if (m.expression != ""||m.coefficient!=1)
		output << m << " (";
	if (p.isZero()) { output << "0"; return output; }
	output << p.terms[0] << " ";
	for (int i = 1; i < p.termNumber; i++)
	{
		if (p.terms[i].coefficient > 0) output << "+" << p.terms[i] << " ";
		else output << p.terms[i] << " ";
	}
	if (m.expression != "")
	output << ")";
	return output;
}

//创造提取公因式中的一项(x的值为单项式)
polynomial createTerm(char var, monomial & value, vector<int> & power)//这里的power都应该是正数
{
	monomial temp;
	polynomial result(string(1, var));
	if (value.isZero())
	{
		changePower(result.terms[0].expression, var, 0);
		return result;
	}
	result = result + monomial(-1 * value.coefficient);
	vector<char> variable = value.getVar();               
	if (variable.size() != power.size()) throw "err!";//处理错误信息
	for (int i = 0; i < variable.size(); i++)
	{
		temp = monomial(string(1, variable[i]));
		changePower(temp.expression, variable[i], power[i]);
		if (getPower(value.expression, variable[i]) < 0)
			result.terms[0] = result.terms[0] * temp;
		else result.terms[1] = result.terms[1] * temp;
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
	for (int i = 1; i < abs(constpower); i++)
		temp = temp * Const;
	if (constpower < 0) result = result + temp;
	else result = result + temp.changeSign();
	return result;
}

//获取下一个因式中可能的幂次组合(单项式因子)
vector<int> nextPower(vector<char>& vars, int *powers,vector<int> *factors,int step)
{
	int size = vars.size(), total = 1, cur;
	int *num = new int[size];
	vector<int> result;
	for (int i = 0; i < size; i++)
	{
		num[i] = factors[i].size();
		total *= num[i];
	}
	for (int i = 0; i < size; i++)
	{
		cur = step;
		for (int j = 0; j < i; j++)
			cur /= num[j];
		cur = cur % num[i];
		result.push_back(factors[i][cur]);
	}
	return result;
}

/*分式部分*/

//从单项式构造分式,分母为1
fraction::fraction(monomial const & m)
{
	termNumber = 1;
	terms.push_back(monomial("1"));
	numerator = polynomial(m);
	denominator.termNumber = 1;
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
	termNumber = 1;
	terms.push_back(monomial("1"));
	monomial m = p.extraction();
	denominator.termNumber = 1;
	denominator.terms.push_back(monomial("1"));
	for (int i = 0; i < m.expression.length(); i++)
	{
		int power = getPower(m.expression, i);
		if (power > 0)
			changePower(m.expression, i--, 0);
	}
	m.coefficient = 1;
	for(int i=0;i<p.termNumber;i++)
		numerator.terms[i] = numerator.terms[i] / m;
	denominator.terms[0] = denominator.terms[0] / m;
}

//重载分式输出
ostream & operator<<(ostream & output, fraction const & f)
{
	if (f.isDigit())
	{
		output << f.toDigit() << endl;
		return output;
	}
	else if (f.denominator == polynomial(1))
	{
		output << f.numerator << endl;
		return output;
	}
	int l2 = f.numerator.getLength(), l3 = f.denominator.getLength();
	int d1 = (l2 < l3) ?  ((l3 - l2) / 2)+1 : 0;
	int d2 = (l3 < l2) ? ((l2 - l3) / 2)+1 : 0;
	for (int i = 0; i < d1; i++) output << " ";
	output << f.numerator << endl;
	for (int i = 0; i < max(l2, l3); i++) output << "-";
	output << endl;
	for (int i = 0; i < d2; i++) output << " ";
	output << f.denominator;
	return output;
}

//改变分式的符号
fraction fraction::changeSign(void) const
{
	fraction result(*this);
	if (result.isZero()) return result;
	for (int i = 0; i < result.numerator.termNumber; i++)
		result.numerator.terms[i].coefficient *= -1;
	return result;
}

//判断分式是否为数字
bool fraction::isDigit(void) const
{
	if (denominator.termNumber == 1 &&numerator.termNumber == 1 )
		if(denominator.terms[0].expression[0] == '\0'&& numerator.terms[0].expression[0] == '\0')
			return true;
	return false;
}

//将是纯数的分式转化为double
double fraction::toDigit(void) const
{
	if(terms.empty()) return numerator.terms[0].coefficient / denominator.terms[0].coefficient;
	else return terms[0].coefficient*numerator.terms[0].coefficient / denominator.terms[0].coefficient;
}

//尝试化简分式
fraction fraction::trySimplify(void)
{
	fraction result(*this);//待处理前缀
	char varnum = result.numerator.getMainTerm();
	char vardenom = result.denominator.getMainTerm();
	if (result.numerator.isNegative() && result.denominator.isNegative()) 
	{ result.numerator = result.numerator.changeSign(); result.denominator = result.denominator.changeSign(); }
	if (result.numerator.isZero()) result.denominator = monomial(1);
	if (varnum == '0' || vardenom == '0') return result;
	vector<polynomial> num = numerator.factorize(varnum);
	vector<polynomial> denom = denominator.factorize(vardenom);
	for (int i = 0; i < num.size(); i++)
	{
		vector<polynomial>::iterator iter = find(denom.begin(), denom.end(), num[i]);
		if (iter != denom.end())
		{
			result.numerator.DivideWithRemainder(num[i]);
			result.denominator.DivideWithRemainder(num[i]);
			denom.erase(iter);
		}
	}
	return result;
}

//用于debug的输出
void output(fraction ** const Matrix, int row, int column)
{
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < column; j++)
			cout << Matrix[i][j].numerator << "/" << Matrix[i][j].denominator << "  ";
		cout << endl;
	}
	cout << endl;
}

//求幂运算，用于计算"^"操作符
fraction myPow(fraction const & f, int power)
{
	fraction result = monomial(1);
	if (power > 0)
		for (int i = 0; i < power; i++)
			result = result * f;
	else if (power < 0)
		for (int i = 0; i < abs(power); i++)
			result = result / f;
	return result;
}

//重载分式互加
fraction fraction::operator+(fraction const & f2) const
{
	fraction result;
	if (f2.terms[0].expression[0] != '\0')
		cout << "err!fracton addition!" << endl;
	result.denominator = denominator * f2.denominator;
	polynomial p1 = numerator * f2.denominator;
	polynomial p2 = f2.numerator * denominator;
	result.numerator = p1 + p2;
	result = result.numerator / result.denominator;
	return result.trySimplify();
}

//重载分式互乘
fraction fraction::operator*(fraction const & f2) const
{
	fraction result;
	if ((*this).isZero() || f2.isZero()) return result;
	if (f2.terms[0].expression[0] != '\0')
		cout << "err!fracton multuply!" << endl;
	result.numerator = numerator * f2.numerator;
	result.denominator = denominator * f2.denominator;
	result = result.numerator / result.denominator;
	return result.trySimplify();
}

//重载分式互除
fraction fraction::operator/(fraction const & f2) const
{
	fraction result;
	if (f2.terms[0].expression[0] != '\0')
		cout << "err!fracton division!" << endl;
	result.numerator = numerator * f2.denominator;
	result.denominator = denominator * f2.numerator;
	result = result.numerator / result.denominator;
	return result.trySimplify();
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
	if (m.isZero() || p.isZero()) return result;
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
	monomial *split = (m / coeff).split();
	result.numerator = split[0]; result.denominator = result.denominator*split[1];
	delete[]split;
	result.denominator.coefficient = 1; result.denominator.expression = "";
	return result;
}

//重载多项式除以单项式
fraction operator/(polynomial const & p, monomial const & m)
{
	fraction result;
	result.numerator= p.extraction();
	monomial &coeff = result.numerator;
	monomial *split = (coeff / m).split();
	result.numerator = result.numerator*split[0]; result.denominator = split[1];
	delete[]split;
	result.numerator.coefficient = 1; result.numerator.expression = "";
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
