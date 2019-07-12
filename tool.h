#include <iostream>
//判定一个double数是否为"0"
bool isZero(double x)
{
	if (abs(x) < 1e-5) return true;
	return false;
}
