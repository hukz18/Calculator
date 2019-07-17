#include "tools.h"

//判定一个double数是否为"0"
bool isZero(double x)
{
	if (abs(x) < 1e-5) return true;
	return false;
}

//修正系数为1时stod函数的bug
double myStod(string const & str)
{
	if (!isdigit(str[0])) return 1;
	else return stod(str);
}

//若均为整数则返回最大公因数
double getGCF(double *a,int n)
{
	bool flag = true;
	int *b = new int[n];
	int gcf = 1, m = *min_element(a, a+n);
	for (int i = 0; i < n; i++)
	{
		b[i] = (int)a[i];
		if (!isZero(a[i] - b[i])) return 1;
	}
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
	if (str[pos + 1] == '^')
		return stoi(str.substr(pos + 2));
	else return 1;
}

//获取str中(首个)字符var的幂次
int getPower(string const & str, char var)
{
	int pos = str.find(string(1, var));
	if (pos == string::npos) return 0;
	else if (str[pos + 1] != '^') return 1;
	else return stoi(str.substr(pos + 2));
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

//两个字符串表达式相"乘"
string multiply(string const& str1, string const& str2)
{
	string result = str1;
	int power1, power2;
	int length1 = str1.length();
	int length2 = str2.length();
	for (int i = 0; i < length2; i++)
		if (power2 = getPower(str2, i))
		{
			power1 = getPower(result, str2[i]);
			changePower(result, str2[i], power1 + power2);
		}
	return result;
}