#ifndef calculator
#define calculator

#define maxLength 80

#include <map>
#include <vector>
#include <string>
#include <iostream>
#include <algorithm>

using namespace std;


int getEqution(vector <string> *equ);     //��ȡ������,����������
int getVariable(vector <string> *var);    //��ȡδ֪��������������
string simplize(vector <string> *var);    //���򷽳�ʽ���������е����źͷ����ȣ���Ϊ�Ⱥ����Ϊ�������Ҳ�Ϊ��������ʽ
bool getMatrix(vector <string> &equ, vector <string> &var, string **Matrix);   //��ȡϵ�����󣬷����Ƿ�ɹ�

#endif // !calculator.h