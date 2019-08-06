#include "tools.h"

//判定一个double数是否为"0"
bool isZero(double x)
{
	if (abs(x) < 1e-5) return true;
	return false;
}

bool isInteger(double x)
{
	return isZero(x - (int)x);
}

//修正系数为1时stod函数的bug
double myStod(string const & str)
{
	if (isalpha(str[0])) return 1;
	else if (isdigit(str[0])) return stod(str);
	else if ((str[0] == '+'&&isdigit(str[1])) || (str[0] == '-'&&isdigit(str[1]))) return stod(str);
	else if (str[0] == '+'&&isalpha(str[1])) return 1;
	else if (str[0] == '-'&&isalpha(str[1])) return -1;
	else return 0;
}

//若均为整数则返回最大公因数
double getGCF(double *a,int n)
{
	bool flag = true;
	int *b = new int[n];
	for (int i = 0; i < n; i++)
	{
		b[i] = abs((int)a[i]);
		if (!isZero(abs(a[i]) - b[i])) return 1;
	}
	int gcf = 1, m = *min_element(b, b + n);
	for (int i = 1; i <= m; i++)
	{
		flag = true;
		for (int j = 0; j < n; j++)
			if (b[j] % i != 0) flag = false;
		if (flag == true) gcf = i;
	}
	return gcf;
}

//改变一个字符串的"符号"
void changeSign(string & str)
{
	if (str[0] == '+') str[0] = '-';
	else if (str[0] == '-') str[0] = '+';
	else str.insert(0,1, '-');
}

//获取str[pos]的幂次
int getPower(string const & str, int pos)
{
	if (!isalpha(str[pos])) return 0;
	else if (str[pos + 1] == '^')
		return stoi(str.substr(pos + 2));
	else return 1;
}

//获取str中(首个)字符var的幂次
int getPower(string const & str, char var)
{
	int pos = str.find(var);
	if (pos == string::npos) return 0;
	else if (str[pos + 1] != '^') return 1;
	else return stoi(str.substr(pos + 2));
}

//获取整数n的某质因子的幂次
int getIntPower(int n, int value)
{
	int power = 0;
	while(n>1)
		if (isZero(((double)n / value) - n / value))
			{ power++; n /= value; }
		else break;
	return power;
}

//获取两组变量中共有变量，若无则返回'\0'
char getComVar(vector<char> const& v1, vector<char> const& v2)
{
	for (auto iter1 = v1.begin(); iter1 < v1.end(); iter1++)
	{
		for (auto iter2 = v2.begin(); iter2 < v2.end(); iter2++)
			if ((*iter1) == (*iter2)) return (*iter1);
	}
	return '\0';
}

//改变str[pos]的幂次
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
			str.insert(pos + 1, 1, '^');
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

//改变str中(首个)字符var的幂次
bool changePower(string & str, char var, int target)
{
	int pos = str.find(var);
	if (pos != string::npos)
		return(changePower(str, pos, target));
	else if (target == 0) return true;
	else if (target == 1) str.insert(0, 1, var);
	else
	{
		str.insert(0, 1, var);
		str.insert(1, 1, '^');
		str.insert(2, to_string(target));
	}
	return true;
}

bool * Subset(int n, int cur)
{
	bool *result = new bool[n];
	int temp = cur, pos = 0;
	for (int i = 0; i < n; i++) result[i] = false;
	while (temp > 0)
	{
		result[pos++] = temp % 2;
		temp /= 2;
	}
	return result;
}




//求整数的全部质因子用于分解
//仿照这个写分解因式，elae value++->value=valuenext,term=termnext
vector<int> factorize(int n)
{
	int value = 2, temp = n;
	vector<int> factors;
	if (n == 1 || n == -1)
	{
		factors.push_back(1);
		return factors;
	}
	factors.push_back(1);
	while (n >= value )
		if ((n % value) == 0)
		{
			n /= value;
			if(find(factors.begin(),factors.end(),value)==factors.end())
				factors.push_back(value);
			value = 2;
		}
		else value++;
	return factors;
}

//求整数的全部因子
vector<int> getFactor(int n)
{
	vector<int> factors;
	n = abs(n);
	for (int i = 1; i <= n / 2; i++)
		if (n % i == 0) factors.push_back(i);
	factors.push_back(n);
	return factors;
}


vector<double> getValue(vector<int> &con, vector<int> &eff)
{
	int lcon = con.size(), leff = eff.size();
	vector<double> result;
	for(int i=0;i<lcon;i++)
		for(int j=0;j<leff;j++)
			if(find(result.begin(),result.end(),(double)con[i]/eff[j])==result.end())
				result.push_back((double)con[i] / eff[j]);
	return result;
}

//两个字符串表达式相"乘"
string multiply(string const& str1, string const& str2)
{
	string result = str1;
	int power1, power2;
	int length1 = str1.length();
	int length2 = str2.length();
	if (str1[0] == '\0') return str2;
	if (str2[0] == '\0') return str1;
	for (int i = 0; i < length2; i++)
		if (power2 = getPower(str2, i))
		{
			power1 = getPower(result, str2[i]);
			changePower(result, str2[i], power1 + power2);
		}
	return result;
}