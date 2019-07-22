#ifndef calculator
#define calculator

#define maxLength 80

#include <vector>
#include <string>
#include <sstream>
#include <algorithm>

using namespace std;

//Kits


void exchangeRow(int r1, int r2, int col, fraction **Augument);      //交换矩阵的两行元素


//Functions
int getEqution(vector <string> *equ);     //获取方程组,返回其总数
int getVariable(vector <string> *var);    //获取未知数，返回其总数
void simplize(string &equ);    //化简方程式：计算并处理其中的括号和分数等
bool getMatrix(vector <string> &equ, vector <string> &var, string **Matrix);   //获取系数矩阵，返回是否成功
bool Elimination(fraction **Augument,int equ,int var);        //高斯消元法处理增广系数矩阵

#endif // !calculator.h