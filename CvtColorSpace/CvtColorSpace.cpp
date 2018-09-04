#include <iostream>
#include <opencv2/opencv.hpp>   

using namespace std;
using namespace cv;

int main(int argc, const char *argv[])
{
	//read the src img
	Mat src = imread("D:/Images/lena.jpg");
	if (src.empty()) 
	{
		cout << "can not find the image" << endl;
		return -1;
	}
	namedWindow("input", CV_WINDOW_NORMAL);
	imshow("input", src);

	// RGB to HSV 
	Mat hsv;
	cvtColor(src, hsv, CV_BGR2HSV);
	imshow("hsv", hsv);

	//RGB to YUV
	Mat yuv;
	cvtColor(src, yuv, CV_BGR2YUV);
	imshow("yuv", yuv);

	//RGB to YCrCb
	Mat ycrcb;
	cvtColor(src, ycrcb, CV_BGR2YCrCb);
	imshow("ycrcb", ycrcb);

	//inrange 
	Mat src1 = imread("D:/Images/tinygreen.png");
	imshow("src1", src1);
	
	//RGB to HSV 
	cvtColor(src1, hsv, CV_BGR2HSV);
	//将图像中绿色背景保留下来，构成一个mask
	//并对mask取反，将图像中人物保留下来
	Mat mask, negMask;
	inRange(hsv, Scalar(35, 43, 36), Scalar(99, 255, 255), mask);
	bitwise_not(mask, negMask);
	//show mask and negMask
	imshow("mask", mask);
	imshow("negMask", negMask);
	
	Mat dst, dst1;
	//将背景保留   
	bitwise_and(src1, src1, dst, mask);
	//将人物保留
	bitwise_and(src1, src1, dst1, negMask);
	imshow("dst", dst);
	imshow("dst1", dst1);


	waitKey(0);
	return 0;
}