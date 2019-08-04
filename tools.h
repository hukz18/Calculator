#ifndef tools
#define tools

#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

bool isZero(double x);                        //�ж�һ��double���Ƿ�Ϊ"0"
double myStod(string const &str);              //����ϵ��Ϊ1ʱstod������bug
double getGCF(double *a, int n);              //����Ϊ�����򷵻��������
void changeSign(string & str);                //�ı�һ���ַ�����"����"
int getPower(string const &str, int pos);     //��ȡstr[pos]���ݴ�
int getPower(string const &str, char var);    //��ȡstr��(�׸�)�ַ�var���ݴ�
int getIntPower(int n, int value);            //��ȡ����n��ĳ�����ӵ��ݴΣ�Ҳ���ò���
char getComVar(vector<char> const&v1, vector<char> const&v2);  //��ȡ��������й��б����������򷵻�'\0'                   //��ȡ����ʽ��ĳ��ĸ��"ϵ��"
bool changePower(string &str, int pos, int power);   //�ı�str[pos]���ݴ�
bool changePower(string &str, char var, int power);  //�ı�str��(�׸�)�ַ�var���ݴ�
bool *Subset(int n,int cur);                            //������Ϊn�ļ��ϵ���һ�Ӽ�
vector<int> factorize(int n);                        //��������ȫ�����������ڷֽ�
vector<int> getFactor(int n);                        //��������ȫ��������
vector<double> getValue(vector<int> &con, vector<int> &eff); //��ȫ����ͬ��ϵ�����

string multiply(string const &str1, string const &str2);         //�����ַ������ʽ��"��"


#endif // !tools