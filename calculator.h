#ifndef calculator
#define calculator

#define maxLength 80

#include <map>
#include <vector>
#include <string>
#include <iostream>
#include <algorithm>

using namespace std;

void exchangeRow(int r1, int r2, int col, double **Augument);
bool isZero(double x);
int getEqution(vector <string> *equ);     //��ȡ������,����������
int getVariable(vector <string> *var);    //��ȡδ֪��������������
string simplize(vector <string> *var);    //���򷽳�ʽ���������е����źͷ����ȣ���Ϊ�Ⱥ����Ϊ�������Ҳ�Ϊ��������ʽ
bool getMatrix(vector <string> &equ, vector <string> &var, string **Matrix);   //��ȡϵ�����󣬷����Ƿ�ɹ�
bool Elimination(double **Augument,int equ,int var);        //��˹��Ԫ����������ϵ������

#endif // !calculator.h