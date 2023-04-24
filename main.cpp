#include "FUNCTIONS.h"
#include "stdafx.h"

int main() {

	//��ȡ��ֵͼƬ
	//Mat img = imread("E:\\����\\Pepper256.bmp", 0);   
	//Mat img = imread("E:\\����\\Building256.bmp", 0);
	//Mat img = imread("E:\\����\\Flight256.bmp", 0);
	//Mat img = imread("E:\\����\\Lena256.bmp", 0);

	//��ȡ�Ҷ�ͼƬ
	Mat img = imread("E:\\����\\baboon256gray.bmp", 0);

	//�ԻҶ�ͼ����в���
	vector<Mat> Pic;
	vector<doubleCoordinate> Subschema;           //��ģʽ
	vector<doubleCoordinate> OverlappingBlock;     //�ص���
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

		//����R���������ģʽ���ص���
		BuildMatrixR(RH, RV, RA, pic, Subschema, OverlappingBlock);

		//��ö�ֵλƽ��ľ�
		double MomentsCal = Calculation(pic, 1, 1);
		//��ö�ֵλƽ������
		int area = AreaCalculation(pic);

		Moments += MomentsCal;
		count = Subschema.size() - count;

		cout << "��λƽ�����ģʽ������" << count << endl;
		cout << "��λƽ��ľأ�" << MomentsCal << endl;
		cout << "��λƽ��������" << area << endl << endl;
	}

	double Moment = CalculationM(Subschema, OverlappingBlock, 1, 1);

	cout << "��ģʽ������" << Subschema.size() << endl;
	cout << "ͼ��ľأ�" << Moments << endl;
	cout << "��͵ľأ�" << Moments << endl;
	

	//�Զ�ֵͼ�����
//	int M = img.rows;    //��
//	int N = img.cols;    //��
//
//	Mat RH = Mat::zeros(M, N, CV_8UC1);
//	Mat RV = Mat::zeros(M, N, CV_8UC1);
//	Mat RA = Mat::zeros(M, N, CV_8UC1);
//
//	vector<doubleCoordinate> Subschema;           //��ģʽ
//	vector<doubleCoordinate> OverlappingBlock;     //�ص���
//
//	BuildMatrixR(RH, RV, RA, img, Subschema, OverlappingBlock);
//
//	double MomentsCalM = CalculationM(Subschema, OverlappingBlock, 1, 1);
//	double MomentsCal = Calculation(img, 1, 1);
//
//	int areaM = AreaCalculationM(Subschema, OverlappingBlock);
//	int area = AreaCalculation(img);
//
//	cout << "��ģʽ����:" << Subschema.size() << endl;
//	cout << "��-��ģʽ:" << MomentsCalM << endl;
//	cout << "��-��դɨ��:" << MomentsCal << endl;
//	cout << "���-��ģʽ:" << areaM << endl;
//	cout << "���-��դɨ��:" << area << endl;
}