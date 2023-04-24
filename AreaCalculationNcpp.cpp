#include "FUNCTIONS.h"
#include "stdafx.h"

int AreaCalculation(Mat &img){
	int M = img.rows;
	int N = img.cols;
	int area = 0;
	for (int i = 0; i < M; i++) {
		for (int j = 0; j < N; j++) {
			if (img.at<uchar>(i, j) == 0)   area++;
		}
	}
	return area;
}