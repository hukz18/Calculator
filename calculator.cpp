#include "calculator.h"



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
					Matrix[i][j].append(temp);
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

