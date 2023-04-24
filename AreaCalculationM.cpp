#include "FUNCTIONS.h"
#include "stdafx.h"

int AreaCalculationM(vector<doubleCoordinate>C, vector<doubleCoordinate>D) {
	int area = 0;
	for (int i = 0; i < C.size(); i++) {
		area += (C[i].x2 - C[i].x1 + 1) * (C[i].y2 - C[i].y1 + 1);
	}
	for (int j = 0; j < D.size(); j++) {
		area -= (D[j].x2 - D[j].x1 + 1) * (D[j].y2 - D[j].y1 + 1);
	}
	return area;
}