#include <iostream>
#include <opencv2\opencv.hpp>

using namespace std;
using namespace cv;

int main(int argc, char **argv)
{
	Mat src = imread("D:/Images/lena.jpg");
	if (src.empty())
	{
		cout << "can not find the img" << endl;
		return -1;
	}
	//�ȶ�ͼ�����ȥ��Ͷ�ֵ��
	Mat blur, binary;
	GaussianBlur(src, blur, Size(3, 3), 10);
	cvtColor(blur, binary, CV_BGR2GRAY);
	threshold(binary, binary, 0, 255, THRESH_BINARY | THRESH_OTSU);
	imshow("binary", binary);
	
	//ͼ��������Ϣ��ÿ������������һЩ�㹹�ɵ�
	vector<vector<Point>> contours;
	//ÿ�������Ĳ����Ϣ��ÿ���������ĸ���ص���Ϣ
	//�ֱ���ͬ����һ����ǰһ������һ���ڵ㡢���ڵ���hierachy�е�����
	vector<Vec4i> hierarchy;
	//���ĸ����������������˽ṹ��RETR_RTEE�ǽ���һ������������һ�������ڲ�������������Ϣ
	//RETR_EXTERNAL��ʾֻ���������������Ϣ
	//�����������ʾ�����㼯�ϵĻ�ȡ����������CHAIN_APPROX_SIMPLE��ʾֻ���������Ĺյ�
	findContours(binary, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE, Point());

	//������ȡ��������
	for (int i = 0; i < contours.size(); i++)
	{
		//ʹ��ѭ����ÿ���������Ƴ���
		//���������thickness������ʱ��ʾ���Ƹ�����
		//����������thickness=-1ʱ��ʾ��������
		drawContours(src, contours, i, Scalar(0, 0, 255), 2, 8);
	}
	imshow("dst", src);
	waitKey(0);
	return 0;
}
