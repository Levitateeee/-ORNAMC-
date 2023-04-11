#include "FUNCTIONS.h"
#include "stdafx.h"

int main() {

	Mat img = imread("E:\\����\\Pepper256.bmp", 0);   //��ȡͼƬ

	int M = img.rows;    //��
	int N = img.cols;    //��

	Mat RH = Mat::zeros(M, N, CV_8UC1);
	Mat RV = Mat::zeros(M, N, CV_8UC1);
	Mat RA = Mat::zeros(M, N, CV_8UC1);

	vector<doubleCoordinate> Subschema;           //��ģʽ
	vector<doubleCoordinate> OverlappingBlock;     //�ص���

	BuildMatrixR(RH, RV, RA, img, Subschema, OverlappingBlock);

	double MomentsCalM = CalculationM(Subschema, OverlappingBlock, 1, 1);
	double MomentsCal = Calculation(img, 1, 1);

	cout << "��ģʽ����:" << Subschema.size() << endl;
	cout << "������ģʽ����ľ�:" << MomentsCalM << endl;
	cout << "��դɨ������ľ�:" << MomentsCal << endl;
}