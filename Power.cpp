#include "FUNCTIONS.h"
#include "stdafx.h"

//����
double Power(double p, int k) {
	if (p == 0)   return 0;
	double val = 1;
	while (k--) {
		val *= p;
	}
	return val;
}