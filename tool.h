#include <iostream>
//�ж�һ��double���Ƿ�Ϊ"0"
bool isZero(double x)
{
	if (abs(x) < 1e-5) return true;
	return false;
}
