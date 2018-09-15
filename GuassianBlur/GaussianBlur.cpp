#include <iostream>
#include <opencv2/opencv.hpp>
#define PI 3.1415926


using namespace std;
using namespace cv;

Mat customGaussianBlur(Mat src, double sigma)
{
	//���ɸ�˹��   
	Mat gauss(5, 5, CV_64FC1);
	//����5x5�ĸ�˹�����
	for (int i = -2; i <= 2; i++)
	{
		for (int j = -2; j <= 2; j++)
		{
			//�����ά��˹�ֲ�
			gauss.at<double>(i + 2, j + 2) = exp(-(i * i + j * j) / (2 * sigma * sigma))
				/ (2 * PI * sigma * sigma);
		}
	}

	//�����Ȩƽ������
	double gaussSum = sum(gauss).val[0];
	//Ȩֵ��һ��
	for (int i = -2; i <= 2; i++)
	{
		for (int j = -2; j <= 2; j++)
		{
			gauss.at<double>(i + 2, j + 2) /= gaussSum;
		}
	}

	//�������    
	//���ȶԱ�Ե���в������������˴�СΪ5x5������width+4, height+4
	copyMakeBorder(src, src, 2, 2, 2, 2, BORDER_CONSTANT, Scalar(0));
	//�������ͼ��ͬ�����������
	Mat dst = src.clone();
	for (int i = 0; i < src.rows - 4; i++)
	{
		for (int j = 0; j < src.cols - 4; j++)
		{
			double sum = 0; //��ʼ���������ֵ

			for (int k = 0; k < gauss.rows; k++)
			{
				for (int s = 0; s < gauss.cols; s++)
				{
					//����
					sum += (double)(src.at<uchar>(i + k, j + s)) * gauss.at<double>(k, s);
				}
			}
			//��Ϊ���ͼ��Ҳ�����˱�Ե��䣬����������һ�����������(i+2,j+2)
			//���Կ��������ͼ����һȦ�ڱ�,�����û�д�����ͼ���Ե
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
	//�Զ����˹ģ��
	dst1 = customGaussianBlur(src, 50);
	imshow("dst1", dst1);
	//����ƽ���˲�
	blur(src, dst2, Size(5, 5), Point(-1, -1), 4);
	imshow("dst2", dst2);
	//��˹ģ��
	GaussianBlur(src, dst3, Size(5, 5), 15, 0, 4);
	imshow("dst3", dst3);
	GaussianBlur(src, dst4, Size(0, 0), 15, 0, 4);
	imshow("dst4", dst4);


	waitKey(0);
	return 0;
}