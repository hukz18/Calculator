#ifndef tools
#define tools

#include <string>
#include <iostream>
#include <algorithm>
using namespace std;

bool isZero(double x);               //判定一个double数是否为"0"
double getGCF(double *a, int n);   //若均为整数则返回最大公因数
void changeSign(string & str);               //改变一个字符串的"符号"
int getPower(string const &str, int pos);     //获取str[pos]的幂次
int getPower(string const &str, char var);    //获取str中(首个)字符var的幂次
bool changePower(string &str, int pos, int power);   //改变str[pos]的幂次
bool changePower(string &str, char var, int power);  //改变str中(首个)字符var的幂次


#endif // !tools