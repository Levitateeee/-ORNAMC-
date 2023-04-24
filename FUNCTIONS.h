//#include "highgui.h"
#include <opencv2/highgui/highgui.hpp>
//#include "cxcore.h"
#include <opencv/cxcore.h>
#include "vector"
//#include "cv.h"
#include <opencv/cv.h>
#include "ctime"
#include "iostream"
#include "math.h"
using namespace cv;
using namespace std;

struct doubleCoordinate//记录左上角，右下角坐标
{
	int x1;
	int y1;
	int x2;
	int y2;
};

//判断矩形是否为同类块
bool JudgeSameBlock(Mat& img, int x1, int y1, int x2, int y2);
//分割原图，建立R矩阵，获取子模式关键坐标对构成的向量，获取重叠块关键坐标对构成的向量
void BuildMatrixR(Mat& RH, Mat& RV, Mat& RA, Mat& img, vector<doubleCoordinate>& C, vector<doubleCoordinate>& D);
//求幂
double Power(double p, int k);
//矩计算--依据块坐标
double CalculationM(vector<doubleCoordinate>C, vector<doubleCoordinate>D, int p, int q);
//矩计算-光栅扫描
double Calculation(Mat img, int p, int q);
//面积计算-块坐标
int AreaCalculationM(vector<doubleCoordinate>C, vector<doubleCoordinate>D);
//面积计算-光栅扫描
int AreaCalculation(Mat& img);
//十进制转二进制
void DecToBin(int num, vector<int> &vec);
//BPD位平面分解
void BPD(Mat& img, vector<Mat> &A);
