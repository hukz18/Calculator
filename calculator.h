#ifndef calculator
#define calculator

#define maxLength 80

#include <map>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

//Kits
bool isNum(char c);         //�ж�һ���ַ��Ƿ�Ϊ����
void changeSign(string & str);            //�ı�һ���ַ�����"����"
void exchangeRow(int r1, int r2, int col, double **Augument);      //�������������Ԫ��


//Functions
int getEqution(vector <string> *equ);     //��ȡ������,����������
int getVariable(vector <string> *var);    //��ȡδ֪��������������
string simplize(vector <string> *var);    //���򷽳�ʽ���������е����źͷ����ȣ���Ϊ�Ⱥ����Ϊ�������Ҳ�Ϊ��������ʽ
bool getMatrix(vector <string> &equ, vector <string> &var, string **Matrix);   //��ȡϵ�����󣬷����Ƿ�ɹ�
bool Elimination(double **Augument,int equ,int var);        //��˹��Ԫ����������ϵ������

#endif // !calculator.h