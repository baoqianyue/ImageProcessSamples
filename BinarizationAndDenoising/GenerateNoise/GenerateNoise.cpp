#include <opencv2\opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

//������������
void add_salt_pepper_noise(Mat &src);
//������˹����
void add_gaussian_noise(Mat &src);

int main(int argc, char** argv)
{
	Mat src = imread("D:/Images/lena.jpg");
	if (src.empty())
	{
		printf("can not find the img");
		return -1;
	}
	namedWindow("src", CV_WINDOW_AUTOSIZE);
	imshow("src", src);
	add_salt_pepper_noise(src);
	add_gaussian_noise(src);
	waitKey(0);
	return 0;
}

void add_salt_pepper_noise(Mat &src)
{
	RNG random(10000);
	int width = src.cols;
	int height = src.rows;
	//��������Ϊ10000
	int noise_nums = 1000;
	for (int i = 0; i < noise_nums; i++)
	{
		//���ȷֲ�������������   
		int x = random.uniform(0, height);
		int y = random.uniform(0, width);
		if (i % 2 == 1)
		{
			src.at<Vec3b>(y, x) = Vec3b(255, 255, 255);
		}
		else
		{
			src.at<Vec3b>(y, x) = Vec3b(0, 0, 0);
		}
	}
	imshow("salt pepper", src);
}

void add_gaussian_noise(Mat & src)
{
	Mat noise = Mat::zeros(src.size(), src.type());
	//���ɸ�˹����ͼ��, �ڶ���������Ӧÿ��ͨ���Ͼ�ֵ��������������Ӧÿ��ͨ���ϵķ���
	randn(noise, (15, 15, 15), (30, 30, 30));
	Mat dst;
	//�����ͼ����ԭͼ����е���
	add(src, noise, dst);
	imshow("gaussian noise", noise);
	imshow("gaussian dst", dst);
}




