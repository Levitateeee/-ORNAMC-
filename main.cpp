#include "FUNCTIONS.h"
#include "stdafx.h"

int main() {

	Mat img = imread("E:\\毕设\\Pepper256.bmp", 0);   //读取图片

	int M = img.rows;    //行
	int N = img.cols;    //列

	Mat RH = Mat::zeros(M, N, CV_8UC1);
	Mat RV = Mat::zeros(M, N, CV_8UC1);
	Mat RA = Mat::zeros(M, N, CV_8UC1);

	vector<doubleCoordinate> Subschema;           //子模式
	vector<doubleCoordinate> OverlappingBlock;     //重叠块

	BuildMatrixR(RH, RV, RA, img, Subschema, OverlappingBlock);

	double MomentsCalM = CalculationM(Subschema, OverlappingBlock, 1, 1);
	double MomentsCal = Calculation(img, 1, 1);

	cout << "子模式个数:" << Subschema.size() << endl;
	cout << "基于子模式求出的矩:" << MomentsCalM << endl;
	cout << "光栅扫描求出的矩:" << MomentsCal << endl;
}