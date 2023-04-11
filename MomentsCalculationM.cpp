#include "FUNCTIONS.h"
#include "stdafx.h"

double CalculationM(vector<doubleCoordinate>C, vector<doubleCoordinate>D, int p, int q) {
	double cal = 0;
	for (int i = 0; i < C.size(); i++) {
		
		double a = C[i].x2 + 0.5;
		double b = C[i].x1 - 0.5;
		double c = C[i].y2 + 0.5;
		double d = C[i].y1 - 0.5;

		double temp = (Power(a, p + 1) - Power(b, p + 1)) * (Power(c, q + 1) - Power(d, q + 1)) / (q + 1) / (p + 1);
		cal += temp;
	}
	for (int j = 0; j < D.size(); j++) {
		
		double a = D[j].x2 + 0.5;
		double b = D[j].x1 - 0.5;
		double c = D[j].y2 + 0.5;
		double d = D[j].y1 - 0.5;

		double temp = (Power(a, p + 1) - Power(b, p + 1)) * (Power(c, q + 1) - Power(d, q + 1)) / (q + 1) / (p + 1);
		cal -= temp;
	}

	return cal;
}