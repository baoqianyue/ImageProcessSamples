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
	//���������������˲������и����������ֱ�����൱�ھ���˵ĳߴ�
	//�����ʵ��Ӧ�ã�����ʹ��5��������Ҫ������������������Ӧ�ã�ʹ��9
	//���d>5ִ�е�Ч�ʽϵ�
	//���d<0��d��ֵ���ɵ�5������sigmaSpace��ֵ����õ�
	//���ĸ����������ɫ�Χ(RGBɫ�ʿռ�)�ڵ����ص��������
	//��������������˹ģ���е�sigma��ֵ������x��y�����ϵķ����ֵ
	//�����������������ı߽�������
	bilateralFilter(src, dst, 5, 100, 10, 4);
	imshow("dst", dst);

	waitKey(0);
	return 0;
}