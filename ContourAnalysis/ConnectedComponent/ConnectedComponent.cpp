#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

void connect_component_demo(Mat &img);

int main(int argc, char ** argv)
{
	Mat src = imread("D:/Images/normal1.jpg");
	if (src.empty())
	{
		cout << "can not find the img" << endl;
		return -1;
	}
	namedWindow("src", WINDOW_AUTOSIZE);
	imshow("src", src);
	//������ͨ���Ѱ��
	connect_component_demo(src);
	waitKey(0);
	return 0;
}

void connect_component_demo(Mat &img)
{
	Mat gray, binary;
	//����۽�����
	RNG rng(77777);
	//��˹ģ��ȥ��
	GaussianBlur(img, img, Size(3, 3), 10);
	medianBlur(img, img, 5);
	cvtColor(img, gray, COLOR_BGR2GRAY);
	threshold(gray, binary, 150, 255, THRESH_BINARY);
	//����Ĵ����ͼ��
	Mat labels = Mat::zeros(img.size(), CV_32S);
	//��һ����������Ϊ��ֵͼ�񣬺�ɫ����,��Ϊ�����ɫ������labelֵΪ0
	//������������ʾ�ڰ���ͨ�����
	//���ĸ�������ʾ���labelsͼ����������ͣ�Ĭ��Ϊ����������CV_32S
	int num_labels = connectedComponents(binary, labels, 8, CV_32S);
	//labelsΪ0���Ǳ���,����ʵ�ʵ���ͨ���������Ϊnum_labels - 1
	cout << "the total labels/component is: " << num_labels - 1 << endl;
	//Ϊÿ��component����һ��ɫ�ʣ�Vec3b��һ���ṹ�壬Ԫ������Ϊuchar����
	vector<Vec3b> colors(num_labels);
	//��һ��componentӦ���Ǳ�����Ϊ��ɫ
	colors[0] = Vec3b(0, 0, 0);
	for (int i = 1; i < num_labels; i++)
	{
		colors[i] = Vec3b(rng.uniform(0, 256), rng.uniform(0, 256), rng.uniform(0, 256));
	}
	//����ͨ��������ɫ
	Mat dst = Mat::zeros(img.size(), img.type());
	int height = img.rows;
	int width = img.cols;
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			int label = labels.at<int>(i, j);
			if (label == 0)
				continue;
			dst.at<Vec3b>(i, j) = colors[label];
		}
	}
	imshow("dst", dst);
}