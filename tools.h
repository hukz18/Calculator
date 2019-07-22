#ifndef tools
#define tools

#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

bool isZero(double x);                        //判定一个double数是否为"0"
double myStod(string const&str);              //修正系数为1时stod函数的bug
double getGCF(double *a, int n);              //若均为整数则返回最大公因数
void changeSign(string & str);                //改变一个字符串的"符号"
int getPower(string const &str, int pos);     //获取str[pos]的幂次
int getPower(string const &str, char var);    //获取str中(首个)字符var的幂次
char getComVar(vector<char> const&v1, vector<char> const&v2);  //获取两组变量中共有变量，若无则返回'\0'                   //获取单项式中某字母的"系数"
bool changePower(string &str, int pos, int power);   //改变str[pos]的幂次
bool changePower(string &str, char var, int power);  //改变str中(首个)字符var的幂次
monomial createValue(vector<char> const &Coeff, double coeffvalue, vector<char> const &Const, double constvalue);   //创造一项可能的因式
polynomial createTerm(char var, polynomial const Coeff, int coeffPower, polynomial const Const, int constpower);    //创造提取公因式中的一项
vector<int> factorize(int n);                        //求整数的全部质因子用于分解

string multiply(string const &str1, string const &str2);         //两个字符串表达式相"乘"
void output();//思考如何输出带分式的式子


#endif // !tools