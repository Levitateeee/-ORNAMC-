#include "FUNCTIONS.h"
#include "stdafx.h"

//判断矩形是否为同类块
bool JudgeSameBlock(Mat &img,int x1,int y1,int x2,int y2) {
	for (int y = y1; y <= y2; y++) {
		for (int x = x1; x <= x2; x++) {
			if (img.at<uchar>(y, x) == 0)   continue;
			else   return false;
		}
	}
	return true;
}