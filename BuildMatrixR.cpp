#include "FUNCTIONS.h"
#include "stdafx.h"

//分割原图，建立R矩阵，获取子模式关键坐标对构成的向量，获取重叠块关键坐标对构成的向量
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


	for (y1 = 0; y1 < M; y1++) {
		for (x1 = 0; x1 < N; x1++) {
			if (img.at<uchar>(y1, x1) == 255)   continue;
			if ((AllocatedH.at<uchar>(y1, x1) != 0) || (AllocatedV.at<uchar>(y1, x1) != 0))   continue;
			mode = 1;
			x2 = x1;
			y2 = y1;
			//临时向量，存储横向拓展中发生重叠的所有不同块的坐标
			vector<doubleCoordinate> E;


			//寻找最大子模式
			while ((a = JudgeSameBlock(img, x1, y1, x2, y2)) && x2 != N - 1) {
				x2++;
				
				//遇到已重叠的水平块
				if (AllocatedH.at<uchar>(y2, x2) == 2)   break;

				//遇到未重叠的水平块
				else if (AllocatedH.at<uchar>(y2, x2) == 1 && JudgeSameBlock(img, x1, y1, x2, y2)) {
					mode = 2;
					int c = C.size() - 1;
					//找到该未重叠水平块的坐标
					for (; c >= 0; c--) {
						if (x2 >= C[c].x1 && x2 <= C[c].x2 && y2 >= C[c].y1 && y2 <= C[c].y2)   break;
					}
					doubleCoordinate vec;
					vec.x1 = C[c].x1;
					vec.y1 = C[c].y1;
					vec.x2 = C[c].x2;
					vec.y2 = C[c].y2;

					bool flag = false;

					//判断E向量中是否存在当前块
					for (int b = 0; b < E.size(); b++) {
						if (vec.x1 == E[b].x1 && vec.y1 == E[b].y1 && vec.x2 == E[b].x2 && vec.y2 == E[b].y2) {
							flag = true;
							break;
						}
					}

					if (!flag) {
						E.push_back(vec);
						//对已分配好的H区域进行取消标识
						for (int y = C[c].y1; y <= C[c].y2; y++) {
							for (int x = C[c].x1; x <= C[c].x1; x++)   AllocatedH.at<uchar>(y, x) = 0;
						}
						//对该水平块进行转移--在垂直块V区域进行标识
						for (int y = C[c].y1; y <= C[c].y2; y++) {
							for (int x = C[c].x1; x <= C[c].x2; x++)   AllocatedV.at<uchar>(y, x) = 1;
						}

						//转移RH块--取消RH块区域的标识，增加RV区域的标识
						RH.at<uchar>(C[c].y1, C[c].x1) = 0;
						RH.at<uchar>(C[c].y2, C[c].x2) = 0;
						RV.at<uchar>(C[c].y1, C[c].x1) = 1;
						RV.at<uchar>(C[c].y2, C[c].x2) = 2;
					}
				}
				//遇到已转移的垂直块
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

					//判断E向量中是否存在当前块
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
			//处理边界
			if (a && (x2 + 1) == N - 1 && AllocatedH.at<uchar>(y2, x2 + 1) == 0)   x2++;
			while ((a = JudgeSameBlock(img, x1, y1, x2, y2)) && y2 != M - 1)   y2++;
			y2--;
			//处理边界
			if (a && (y2 + 1) == M - 1)   y2++;
			//对该找到的水平块区域进行标识
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
			//对RH进行标识
			if (x1 == x2 && y1 == y2)   RA.at<uchar>(y1, x1) = 1;   //孤立点
			else {
				RH.at<uchar>(y1, x1) = 1;
				RH.at<uchar>(y2, x2) = 2;
			}

			temp.x1 = x1;
			temp.y1 = y1;
			temp.x2 = x2;
			temp.y2 = y2;
			C.push_back(temp);

			//求重叠块的坐标
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