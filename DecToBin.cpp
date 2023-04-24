#include "FUNCTIONS.h"
#include "stdafx.h"

void DecToBin(int num, vector<int> &vec) {
	if (num == 0)   vec.push_back(0);
	else {
		int n = num;
		int res = 0;
		while (n > 0) {
			res = n % 2;
			vec.push_back(res);
			n = n / 2;
		}
	}
	//����8λ����0
	while (vec.size() < 8)   vec.push_back(0);
}