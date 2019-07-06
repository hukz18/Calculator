#include "calculator.h"



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
	bool flag = false;
	int head, cur, equNum = equ.size(), varNum = var.size();
	for (int i = 0; i < equNum; i++)
		for (int j = 0; j < varNum + 1; j++)
			Matrix[i][j] = "0";
	for (int i = 0; i < equNum; i++)
	{
		head = cur = flag = 0;
		while (!flag)    //未找到"="号
		{
			head = cur++;
			while ((equ[i][cur] != '+') && (equ[i][cur] != '-'))
			{
				if (equ[i][cur] == '=')
				{ flag = true; break; }
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
					Matrix[i][j] = temp;
				}
			}
		}
		Matrix[i][varNum] = equ[i].substr(++cur);
	}
	return true;
}

