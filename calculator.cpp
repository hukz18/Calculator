#include "tools.h"
#include "symbolize.h"
#include "operation.h"
#include "calculator.h"






//�������������Ԫ��
void exchangeRow(int r1, int r2, int col,fraction ** Augument)
{
	for (int i = 0; i < col; i++)
		swap(Augument[r1][i], Augument[r2][i]);
}


//��ȡ������,����������
int getEqution(vector <string> *equ)     
{
	string temp;
	int position = 0;
	getline(cin, temp);
	simplize(temp);
	while (!temp.empty())
	{
		if (temp[0] != '-')
			temp.insert(0, 1, '+');
		equ->push_back(temp);
		getline(cin, temp);
		simplize(temp);
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

void simplize(string & equ)
{
	string equL, equR, result;
	if (equ.empty()) return;
	int pos = equ.find('=');
	equL = equ.substr(0, pos); equR = equ.substr(pos + 1);
	fraction fL = calculate(equL);
	fraction fR = calculate(equR);
	polynomial pL = fL.numerator*fR.denominator;
	polynomial pR = fR.numerator*fL.denominator;
	stringstream stream;
	stream << pL;
	equ = stream.str();
	equ += "=";
	stream.str("");
	stream << pR;
	equ.append(stream.str());
}

//��ȡϵ�����󣬷����Ƿ�ɹ�,�����������ϵ��Ϊ1��feature
bool getMatrix(vector<string>& equ, vector<string>& var, string ** Matrix)
{
	string temp;
	bool flag1 = false, flag2 = false;
	int head, cur, pos, length, equNum = equ.size(), varNum = var.size();
	//��ʼ������һ�����mystodʱֱ�ӿ��ַ�����ֵΪ0��ɾȥ���
	for (int i = 0; i < equNum; i++)
		for (int j = 0; j < varNum + 1; j++)
			Matrix[i][j] = "0";
	for (int i = 0; i < equNum; i++)
	{
		flag1 = false;
		head = cur = 0;
		length = equ[i].length();
		while (cur < length)    //δ����õ�ʽĩβ
		{
			head = cur++;
			flag2 = false;
			while ((equ[i][cur] != '+') && (equ[i][cur] != '-') && (equ[i][cur] != '=') && cur < length) cur++;
			temp = equ[i].substr(head, cur - head);
			pos = 0;//��ȥ�����еĿո�
			while ((pos = temp.find(' ', pos)) != string::npos)
				temp.erase(pos, 1);
			pos = 0;//��ȥ�����еĳ˺�(ǰ���Ϊ���ֳ���)
			while (((pos = temp.find('*', pos)) != string::npos) && (!((isdigit(temp[pos - 1])) && (isdigit(temp[pos + 1])))))
				temp.erase(pos, 1);
			for (int j = 0; j < varNum; j++)
			{
				int pos = temp.find(var[j]);
				if (pos != string::npos)
				{
					flag2 = true;                  //����б���
					temp.erase(pos, var[j].size());
					if (temp == "+" || temp == "-")
						temp += "1";
					if (flag1 == true)             //�����ڵȺ��Ҳ��Һ��б���
						changeSign(temp);
					if (Matrix[i][j] == "0")
						Matrix[i][j] = temp;
					else Matrix[i][j].append(temp);
				}
			}
			if (flag2 == false)  //����δ�ҵ�����
			{
				if (flag1 == false)
					changeSign(temp);
				if (Matrix[i][varNum] == "0")
					Matrix[i][varNum] = temp;
				else Matrix[i][varNum].append(temp);
			}
			if (equ[i][cur] == '=')
			{
				flag1 = true; cur++;
				if ((equ[i][cur] != '-') && (equ[i][cur] != '0'))
				{
					equ[i].insert(cur, 1, '+'); length++;
				}
			}
		}
	}
	return true;
}

//��˹��Ԫ����������ϵ������
bool Elimination(fraction ** Augument, int equ, int var)
{
	int i, j, k, flag = 1;
	fraction temp;
	if (equ < var)//��鷽���Ƿ�Ƿ��
	{
		cout << "The equtions are underdetermined ,please input more equtions and try again!" << endl;
		return false;
	}
	for (k = 0; k < var; k++)
	{
		flag = 1;
		//����Ƿ������Ԫ
		if (Augument[k][k].isZero())
		{
			flag = 0;
			for (i = k; i < equ; i++)
				if (!Augument[i][k].isZero())
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
			Augument[k][i] = Augument[k][i] / temp;
		//����k������ϵ����Ϊ0
		for (i = 0; i < equ; i++)
		{
			if (i == k) continue;
			temp = Augument[i][k];
			for (j = k; j <= var; j++)
				Augument[i][j] = Augument[i][j] +(temp * Augument[k][j]).changeSign();
		}
	}
	if (equ > var)//��鷽���Ƿ񳬶�,���Ƿ��н�
	{
		for (i = var; i < equ; i++)
		{
			fraction temp;
			for (j = 0; j < var; j++)
				temp = Augument[i][j] * Augument[j][var] + temp;
			if (!(temp + Augument[i][var].changeSign()).isZero())
			{
				cout << "The equtions are overdeterminated, and there's no sotion!" << endl;
				return false;
			}
		}
		cout << "The equtions are overdeterminated, but there's still a sotion!" << endl;
	}
	return true;
}