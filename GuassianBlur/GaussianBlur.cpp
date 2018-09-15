#include <iostream>
#include <opencv2/opencv.hpp>
#define PI 3.1415926


using namespace std;
using namespace cv;

Mat customGaussianBlur(Mat src, double sigma)
{
	//生成高斯核   
	Mat gauss(5, 5, CV_64FC1);
	//构建5x5的高斯卷积核
	for (int i = -2; i <= 2; i++)
	{
		for (int j = -2; j <= 2; j++)
		{
			//计算二维高斯分布
			gauss.at<double>(i + 2, j + 2) = exp(-(i * i + j * j) / (2 * sigma * sigma))
				/ (2 * PI * sigma * sigma);
		}
	}

	//满足加权平均条件
	double gaussSum = sum(gauss).val[0];
	//权值归一化
	for (int i = -2; i <= 2; i++)
	{
		for (int j = -2; j <= 2; j++)
		{
			gauss.at<double>(i + 2, j + 2) /= gaussSum;
		}
	}

	//卷积操作    
	//首先对边缘进行补零操作，这里核大小为5x5，所以width+4, height+4
	copyMakeBorder(src, src, 2, 2, 2, 2, BORDER_CONSTANT, Scalar(0));
	//创建输出图像，同样是填充过后的
	Mat dst = src.clone();
	for (int i = 0; i < src.rows - 4; i++)
	{
		for (int j = 0; j < src.cols - 4; j++)
		{
			double sum = 0; //初始化卷积中心值

			for (int k = 0; k < gauss.rows; k++)
			{
				for (int s = 0; s < gauss.cols; s++)
				{
					//求卷积
					sum += (double)(src.at<uchar>(i + k, j + s)) * gauss.at<double>(k, s);
				}
			}
			//因为输出图像也进行了边缘填充，所以真正第一个卷积中心是(i+2,j+2)
			//可以看到，输出图像有一圈黑边,这就是没有处理到的图像边缘
			dst.at<uchar>(i + 2, j + 2) = (uchar)sum;
		}
	}
	return dst;
}

int main(int argc, const char * argv[])
{
	Mat src = imread("D:/Images/lena.jpg");
	if (src.empty()) {
		cout << "could not load the image" << endl;
		return -1;
	}
	cvtColor(src, src, CV_BGR2GRAY);
	namedWindow("src", WINDOW_AUTOSIZE);
	imshow("src", src);

	Mat dst1, dst2, dst3, dst4;
	//自定义高斯模糊
	dst1 = customGaussianBlur(src, 50);
	imshow("dst1", dst1);
	//线性平滑滤波
	blur(src, dst2, Size(5, 5), Point(-1, -1), 4);
	imshow("dst2", dst2);
	//高斯模糊
	GaussianBlur(src, dst3, Size(5, 5), 15, 0, 4);
	imshow("dst3", dst3);
	GaussianBlur(src, dst4, Size(0, 0), 15, 0, 4);
	imshow("dst4", dst4);


	waitKey(0);
	return 0;
}