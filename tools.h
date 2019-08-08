#ifndef tools
#define tools

#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;
#define rows 2
#define cols 3
bool isOpe(char c);                           //判断一个字符是否为运算符
bool isZero(double x);                        //判定一个double数是否为"0"
bool isLegal(char c);                         //判定输入合法性
bool isInteger(double x);
double myStod(string const &str);             //修正系数为1时stod函数的bug
double getGCF(double *a, int n);              //若均为整数则返回最大公因数
void changeSign(string & str);                //改变一个字符串的"符号"
int nextVar(string const &str, int pos);      //获取从当前位置起下一个变量或结尾的位置
int getPower(string const &str, int pos);     //获取str[pos]的幂次
int getPower(string const &str, char var);    //获取str中(首个)字符var的幂次
int getIntPower(int n, int value);            //获取整数n的某质因子的幂次，也许用不到
char getComVar(vector<char> const&v1, vector<char> const&v2);  //获取两组变量中共有变量，若无则返回'\0'                   //获取单项式中某字母的"系数"
bool changePower(string &str, int pos, int power);   //改变str[pos]的幂次
bool changePower(string &str, char var, int power);  //改变str中(首个)字符var的幂次
bool *Subset(int n,int cur);                            //创建长为n的集合的下一子集
vector<int> factorize(int n);                        //求整数的全部质因子用于分解
vector<int> getFactor(int n);                        //求整数的全部因子
vector<double> getValue(vector<int> &con, vector<int> &eff); //求全部不同的系数组合

string multiply(string const &str1, string const &str2);         //两个字符串表达式相"乘"


#endif // !tools