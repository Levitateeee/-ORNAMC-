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

struct doubleCoordinate//��¼���Ͻǣ����½�����
{
	int x1;
	int y1;
	int x2;
	int y2;
};

//�жϾ����Ƿ�Ϊͬ���
bool JudgeSameBlock(Mat& img, int x1, int y1, int x2, int y2);
//�ָ�ԭͼ������R���󣬻�ȡ��ģʽ�ؼ�����Թ��ɵ���������ȡ�ص���ؼ�����Թ��ɵ�����
void BuildMatrixR(Mat& RH, Mat& RV, Mat& RA, Mat& img, vector<doubleCoordinate>& C, vector<doubleCoordinate>& D);
//����
double Power(double p, int k);
//�ؼ���--���ݿ�����
double CalculationM(vector<doubleCoordinate>C, vector<doubleCoordinate>D, int p, int q);
//�ؼ���-��դɨ��
double Calculation(Mat img, int p, int q);
