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
int getEqution(vector <string> *equ);     //获取方程组,返回其总数
int getVariable(vector <string> *var);    //获取未知数，返回其总数
string simplize(vector <string> *var);    //化简方程式：处理其中的括号和分数等，化为等号左侧为变量，右侧为常量的形式
bool getMatrix(vector <string> &equ, vector <string> &var, string **Matrix);   //获取系数矩阵，返回是否成功
bool Elimination(double **Augument,int equ,int var);        //高斯消元法处理增广系数矩阵

#endif // !calculator.h