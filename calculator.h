#ifndef calculator
#define calculator

#define maxLength 80

#include <vector>
#include <string>
#include <sstream>
#include <algorithm>

using namespace std;

//Kits


void exchangeRow(int r1, int r2, int col, fraction **Augument);      //�������������Ԫ��


//Functions
int getEqution(vector <string> *equ);     //��ȡ������,����������
int getVariable(vector <string> *var);    //��ȡδ֪��������������
void simplize(string &equ);    //���򷽳�ʽ�����㲢�������е����źͷ�����
bool getMatrix(vector <string> &equ, vector <string> &var, string **Matrix);   //��ȡϵ�����󣬷����Ƿ�ɹ�
bool Elimination(fraction **Augument,int equ,int var);        //��˹��Ԫ����������ϵ������

#endif // !calculator.h