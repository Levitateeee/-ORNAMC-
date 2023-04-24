#include "FUNCTIONS.h"
#include "stdafx.h"

double Calculation(Mat img, int p, int q) {
	int M = img.rows;
	int N = img.cols;
	double cal = 0;
	for (int i = 0; i < M; i++) {
		for (int j = 0; j < N; j++) {
			if (img.at<uchar>(i, j) == 0) {
				
				double a = j + 0.5;
				double b = j - 0.5;
				double c = i + 0.5;
				double d = i - 0.5;

				double temp = (Power(a, p + 1) - Power(b, p + 1))* (Power(c, q + 1) - Power(d, q + 1)) / (q + 1) / (p + 1);
				cal += temp;
			}
		}
	}
	return cal;
}