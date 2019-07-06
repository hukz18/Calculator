#include "calculator.h"



void exchangeRow(int r1, int r2, int col,double ** Augument)
{
	for (int i = 0; i < col; i++)
		swap(Augument[r1][i], Augument[r2][i]);
}

bool isZero(double x)
{
	if (abs(x) < 1e-5) return true;
	return false;
}

//获取方程组,返回其总数
int getEqution(vector <string> *equ)     
{
	string temp;
	int position = 0;
	getline(cin, temp);
	while (!temp.empty())
	{
		if (temp[0] != '-')
			temp.insert(0, 1, '+');
		equ->push_back(temp);
		getline(cin, temp);
	}
	return equ->size();
}
//获取未知数，返回其总数，解决重复bug
int getVariable(vector<string> *var)  
{
	string name;
	cin  >> name;
	while (cin.peek()!='\n')                                        //利用cin.peek()函数判断是否读取完毕
	{
		var->push_back(name);
		cin >> name;
	}
	var->push_back(name);
	sort(var->begin(), var->end());                                 //清除var中可能的重复元素，避免bug
	var->erase(unique(var->begin(), var->end()), var->end());
	return var->size();
}

//获取系数矩阵，返回是否成功
bool getMatrix(vector<string>& equ, vector<string>& var, string ** Matrix)
{
	string temp;
	bool flag1 = false, flag2 = false;
	int head, cur, equNum = equ.size(), varNum = var.size();
	for (int i = 0; i < equNum; i++)
		for (int j = 0; j < varNum + 1; j++)
			Matrix[i][j] = "0";
	for (int i = 0; i < equNum; i++)
	{
		head = cur = flag1 = 0;
		while (!flag1)    //未找到"="号
		{
			head = cur++;
			flag2 = false;
			while ((equ[i][cur] != '+') && (equ[i][cur] != '-'))
			{
				if (equ[i][cur] == '=')
				{ flag1 = true; break; }
				cur++;
			}
			temp = equ[i].substr(head, cur - head);
			int pos = 0;           //除去代码中的空格，下一步添到simplify里
			while ((pos = temp.find(' ', pos)) != string::npos)
				temp.erase(pos, 1);
			for (int j = 0; j < varNum; j++)
			{
				int pos = temp.find(var[j]);
				if (pos != string::npos)
				{
					temp.erase(pos, var[j].size());
					if (temp == "+" || temp == "-")
						temp += "1";
					Matrix[i][j]=temp;
					flag2 = true;
				}
			}
			if (flag2 == false)  //该项在等号左侧且未找到变量
			{
				if (temp[0] == '+')
					temp[0] = '-';
				else temp[0] = '+';
				equ[i].append(temp);
			}
		}
		Matrix[i][varNum] = equ[i].substr(++cur);
	}
	return true;
}

bool Elimination(double ** Augument, int equ, int var)
{
	int i, j, k, flag = 1;
	double temp = 0;
	if (equ < var)
	{
		cout << "The equtions are not enough ,please input more equtions and try again!" << endl;
		return false;
	}
	for (k = 0; k < var; k++)
	{
		flag = 1;
		//检查是否可以消元
		if (isZero(Augument[k][k]))
		{
			flag = 0;
			for (i = k; i < equ; i++)
				if (!isZero(Augument[i][k]))
				{
					exchangeRow(i, k, var + 1, Augument);
					flag = 1;
				}
		}
		if (!flag) {
			cout << "The matrix is single,thre's no solution!" << endl;
			return false;
		}
		//将第k行首项划为1
		temp = Augument[k][k];
		for (i = k; i <= var; i++)
			Augument[k][i] /= temp;
		//将第k列其余系数划为0
		for (i = 0; i < equ; i++)
		{
			if (i == k) continue;
			temp = Augument[i][k];
			for (j = k; j <= var; j++)
				Augument[i][j] -= temp * Augument[k][j];
		}
	}
	return true;
}


