#include "FUNCTIONS.h"
#include "stdafx.h"

int main() {

	//读取二值图片
	//Mat img = imread("E:\\毕设\\Pepper256.bmp", 0);   
	//Mat img = imread("E:\\毕设\\Building256.bmp", 0);
	//Mat img = imread("E:\\毕设\\Flight256.bmp", 0);
	//Mat img = imread("E:\\毕设\\Lena256.bmp", 0);

	//读取灰度图片
	Mat img = imread("E:\\毕设\\baboon256gray.bmp", 0);

	//对灰度图像进行操作
	vector<Mat> Pic;
	vector<doubleCoordinate> Subschema;           //子模式
	vector<doubleCoordinate> OverlappingBlock;     //重叠块
	double Moments = 0;

	BPD(img, Pic);

	for (int i = 0; i <= 7; i++) {
		
		Mat pic = Pic[i];
		int M = pic.rows;
		int N = pic.cols;
		int count = Subschema.size();

		Mat RH = Mat::zeros(M, N, CV_8UC1);
		Mat RV = Mat::zeros(M, N, CV_8UC1);
		Mat RA = Mat::zeros(M, N, CV_8UC1);

		//构造R矩阵，输出子模式与重叠块
		BuildMatrixR(RH, RV, RA, pic, Subschema, OverlappingBlock);

		//求该二值位平面的矩
		double MomentsCal = Calculation(pic, 1, 1);
		//求该二值位平面的面积
		int area = AreaCalculation(pic);

		Moments += MomentsCal;
		count = Subschema.size() - count;

		cout << "该位平面的子模式个数：" << count << endl;
		cout << "该位平面的矩：" << MomentsCal << endl;
		cout << "该位平面的面积：" << area << endl << endl;
	}

	double Moment = CalculationM(Subschema, OverlappingBlock, 1, 1);

	cout << "子模式个数：" << Subschema.size() << endl;
	cout << "图像的矩：" << Moments << endl;
	cout << "求和的矩：" << Moments << endl;
	

	//对二值图像操作
//	int M = img.rows;    //行
//	int N = img.cols;    //列
//
//	Mat RH = Mat::zeros(M, N, CV_8UC1);
//	Mat RV = Mat::zeros(M, N, CV_8UC1);
//	Mat RA = Mat::zeros(M, N, CV_8UC1);
//
//	vector<doubleCoordinate> Subschema;           //子模式
//	vector<doubleCoordinate> OverlappingBlock;     //重叠块
//
//	BuildMatrixR(RH, RV, RA, img, Subschema, OverlappingBlock);
//
//	double MomentsCalM = CalculationM(Subschema, OverlappingBlock, 1, 1);
//	double MomentsCal = Calculation(img, 1, 1);
//
//	int areaM = AreaCalculationM(Subschema, OverlappingBlock);
//	int area = AreaCalculation(img);
//
//	cout << "子模式个数:" << Subschema.size() << endl;
//	cout << "矩-子模式:" << MomentsCalM << endl;
//	cout << "矩-光栅扫描:" << MomentsCal << endl;
//	cout << "面积-子模式:" << areaM << endl;
//	cout << "面积-光栅扫描:" << area << endl;
}