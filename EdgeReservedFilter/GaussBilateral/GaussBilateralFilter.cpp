#include <opencv2\opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

int main(int argc, char ** argv)
{
	Mat src = imread("D:/Images/lena.jpg");
	if (src.empty())
	{
		printf("can not find the img\n");
		return -1;
	}
	namedWindow("src", CV_WINDOW_AUTOSIZE);
	imshow("src", src);

	Mat dst;
	Mat dst1;
	//第三个参数代表滤波过程中各像素领域的直径，相当于卷积核的尺寸
	//如果是实际应用，建议使用5，对于需要过滤严重噪声的离线应用，使用9
	//如果d>5执行的效率较低
	//如果d<0，d的值将由第5个参数sigmaSpace的值计算得到
	//第四个参数代表该色差范围(RGB色彩空间)内的像素点参与运算
	//第五个参数代表高斯模糊中的sigma的值，就是x和y方向上的方差的值
	//第六个参数代表卷积的边界填充规则
	bilateralFilter(src, dst, 5, 100, 10, 4);
	imshow("dst", dst);

	waitKey(0);
	return 0;
}