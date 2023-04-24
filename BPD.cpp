#include "FUNCTIONS.h"
#include "stdafx.h"

void BPD(Mat& img, vector<Mat> &A) {
	
	int M = img.rows;
	int N = img.cols;

	vector<Mat> temp;
	for (int i = 0; i <= 7; i++) {
		
		Mat fig = Mat::zeros(M, N, CV_8UC1);
		temp.push_back(fig);
	}
	for (int i = 0; i < M; i++) {
		for (int j = 0; j < N; j++) {
			
			int num = img.at<uchar>(i, j);
			vector<int> a;
			DecToBin(num, a);
			int count = 7;

			for (int n = a.size() - 1; count >= 0;n--) {
				temp[count].at<uchar>(i, j) = a[n] == 0 ? uchar(0) : uchar(255);
				count--;
			}
		}
	}

	for (int i = 7; i >= 0; i--) {
		A.push_back(temp[i]);
	}
}
