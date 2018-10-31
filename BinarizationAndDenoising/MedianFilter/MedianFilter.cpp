#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main(int argc, char **argv)
{
	Mat src = imread("D:/Images/saltimg.jpg");
	if (src.empty())
	{
		cout << "can not find the img" << endl;
		return -1;
	}
	namedWindow("src", CV_WINDOW_AUTOSIZE);
	imshow("src", src);

	Mat dst;
	//第三个参数表示统计中位数的窗口大小为5x5
	medianBlur(src, dst, 5);
	imshow("median blur", dst);
	
	waitKey(0);
	return 0;
}