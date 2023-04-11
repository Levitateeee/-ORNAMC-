#include "FUNCTIONS.h"
#include "stdafx.h"

//�ָ�ԭͼ������R���󣬻�ȡ��ģʽ�ؼ�����Թ��ɵ���������ȡ�ص���ؼ�����Թ��ɵ�����
void BuildMatrixR(Mat& RH, Mat& RV, Mat& RA, Mat& img, vector<doubleCoordinate>& C, vector<doubleCoordinate>& D) {
	
	int M = img.rows;
	int N = img.cols;

	Mat AllocatedH = Mat::zeros(M, N, CV_8UC1);
	Mat AllocatedV = Mat::zeros(M, N, CV_8UC1);

	
	doubleCoordinate temp;
	int x1 = 0, y1 = 0;
	int x2 = 0, y2 = 0;
	bool a = true;
	int mode = 1;

	if (AllocatedH.at<uchar>(y1, x1) == 1)   cout << 1 << endl;
	else   cout << 0 << endl;

	for (; y1 < M; y1++) {
		for (; x1 < N; x1++) {
			cout << "�������ڲ�ѭ��" << endl;
			cout << y1 << x1 << endl;
			if (AllocatedH.at<uchar>(y1, x1) != 0 || AllocatedV.at<uchar>(y1, x1) != 0)   continue;

			mode = 1;
			x2 = x1;
			y2 = y1;
			//��ʱ�������洢������չ�з����ص������в�ͬ�������
			vector<doubleCoordinate> E;

			//Ѱ�������ģʽ
			while ((a = JudgeSameBlock(img, x1, y1, x2, y2)) && x2 != N - 1) {

				x2++;
				
				//�������ص���ˮƽ��
				if (AllocatedH.at<uchar>(y2, x2) == 2)   break;

				//����δ�ص���ˮƽ��
				else if (AllocatedH.at<uchar>(y2, x2) == 1 && JudgeSameBlock(img, x1, y1, x2, y2)) {
					mode = 2;
					int c = C.size() - 1;
					//�ҵ���δ�ص�ˮƽ�������
					for (; c >= 0; c--) {
						if (x2 >= C[c].x1 && x2 <= C[c].x2 && y2 >= C[c].y1 && y2 <= C[c].y2)   break;
					}
					doubleCoordinate vec;
					vec.x1 = C[c].x1;
					vec.y1 = C[c].y1;
					vec.x2 = C[c].x2;
					vec.y2 = C[c].y2;

					bool flag = false;

					//�ж�E�������Ƿ���ڵ�ǰ��
					for (int b = 0; b < E.size(); b++) {
						if (vec.x1 == E[b].x1 && vec.y1 == E[b].y1 && vec.x2 == E[b].x2 && vec.y2 == E[b].y2) {
							flag = true;
							break;
						}
					}

					if (!flag) {
						E.push_back(vec);
						//���ѷ���õ�H�������ȡ����ʶ
						for (int y = C[c].y1; y <= C[c].y2; y++) {
							for (int x = C[c].x1; x <= C[c].x1; x++)   AllocatedH.at<uchar>(y, x) = 0;
						}
						//�Ը�ˮƽ�����ת��--�ڴ�ֱ��V������б�ʶ
						for (int y = C[c].y1; y <= C[c].y2; y++) {
							for (int x = C[c].x1; x <= C[c].x2; x++)   AllocatedV.at<uchar>(y, x) = 1;
						}

						//ת��RH��--ȡ��RH������ı�ʶ������RV����ı�ʶ
						RH.at<uchar>(C[c].y1, C[c].x1) = 0;
						RH.at<uchar>(C[c].y2, C[c].x2) = 0;
						RV.at<uchar>(C[c].y1, C[c].x1) = 1;
						RV.at<uchar>(C[c].y2, C[c].x2) = 2;
					}
				}
				else if (AllocatedV.at<uchar>(y2, x2) == 1 && JudgeSameBlock(img, x1, y1, x2, y2)) {
					mode = 2;
					int c = C.size() - 1;
					for (; c >= 0; c--) {
						if (x2 >= C[c].x1 && x2 <= C[c].x2 && y2 >= C[c].y1 && y2 <= C[c].y2)   break;
					}
					doubleCoordinate vec;
					vec.x1 = C[c].x1;
					vec.y1 = C[c].y1;
					vec.x2 = C[c].x2;
					vec.y2 = C[c].y2;

					bool flag = false;

					//�ж�E�������Ƿ���ڵ�ǰ��
					for (int b = 0; b < E.size(); b++) {
						if (vec.x1 == E[b].x1 && vec.y1 == E[b].y1 && vec.x2 == E[b].x2 && vec.y2 == E[b].y2) {
							flag = true;
							break;
						}
					}

					if (!flag)   E.push_back(vec);
				}
			}
			x2--;
			//����߽�
			if (a && (x2 + 1) == N - 1 && AllocatedH.at<uchar>(y2, x2 + 1) == 0)   x2++;
			while ((a = JudgeSameBlock(img, x1, y1, x2, y2)) && y2 != M - 1)   y2++;
			y2--;
			//����߽�
			if (a && (y2 + 1) == M - 1 && AllocatedH.at<uchar>(y2 + 1, x2) == 0)   y2++;
			//�Ը��ҵ���ˮƽ��������б�ʶ
			if (mode == 2) {
				for (int a = y1; a <= y2; a++) {
					for (int b = x1; b <= x2; b++)   AllocatedH.at<uchar>(a, b) = 2;
				}
			}
			else {
				for (int a = y1; a <= y2; a++) {
					for (int b = x1; b <= x2; b++)   AllocatedH.at<uchar>(a, b) = 1;
				}
			}
			//��RH���б�ʶ
			if (x1 == x2 && y1 == y2)   RA.at<uchar>(y1, x1) = 1;   //������
			else {
				RH.at<uchar>(y1, x1) = 1;
				RH.at<uchar>(y2, x2) = 2;
			}

			temp.x1 = x1;
			temp.y1 = y1;
			temp.x2 = x2;
			temp.y2 = y2;
			C.push_back(temp);

			for (int i = 0; i < E.size(); i++) {
				doubleCoordinate vec;
				vec.x1 = E[i].x1;
				vec.y1 = temp.y1;
				vec.x2 = E[i].x2;
				vec.y2 = temp.y2;
				D.push_back(vec);
			}
		}
	}
}