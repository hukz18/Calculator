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

//��ȡ������,����������
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
//��ȡδ֪��������������������ظ�bug
int getVariable(vector<string> *var)  
{
	string name;
	cin  >> name;
	while (cin.peek()!='\n')                                        //����cin.peek()�����ж��Ƿ��ȡ���
	{
		var->push_back(name);
		cin >> name;
	}
	var->push_back(name);
	sort(var->begin(), var->end());                                 //���var�п��ܵ��ظ�Ԫ�أ�����bug
	var->erase(unique(var->begin(), var->end()), var->end());
	return var->size();
}

//��ȡϵ�����󣬷����Ƿ�ɹ�
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
		while (!flag1)    //δ�ҵ�"="��
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
			int pos = 0;           //��ȥ�����еĿո���һ����simplify��
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
			if (flag2 == false)  //�����ڵȺ������δ�ҵ�����
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
		//����Ƿ������Ԫ
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
		//����k�����Ϊ1
		temp = Augument[k][k];
		for (i = k; i <= var; i++)
			Augument[k][i] /= temp;
		//����k������ϵ����Ϊ0
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


