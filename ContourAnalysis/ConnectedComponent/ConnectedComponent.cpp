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
	//进行联通组件寻找
	connect_component_demo(src);
	waitKey(0);
	return 0;
}

void connect_component_demo(Mat &img)
{
	Mat gray, binary;
	//世界聚焦于你
	RNG rng(77777);
	//高斯模糊去噪
	GaussianBlur(img, img, Size(3, 3), 10);
	medianBlur(img, img, 5);
	cvtColor(img, gray, COLOR_BGR2GRAY);
	threshold(gray, binary, 150, 255, THRESH_BINARY);
	//输出的带标记图像
	Mat labels = Mat::zeros(img.size(), CV_32S);
	//第一个参数必须为二值图像，黑色背景,因为这里黑色背景的label值为0
	//第三个参数表示在八连通域查找
	//第四个参数表示输出labels图像的数据类型，默认为带符号整形CV_32S
	int num_labels = connectedComponents(binary, labels, 8, CV_32S);
	//labels为0的是背景,所以实际的联通组件的数量为num_labels - 1
	cout << "the total labels/component is: " << num_labels - 1 << endl;
	//为每个component定义一个色彩，Vec3b是一个结构体，元素类型为uchar类型
	vector<Vec3b> colors(num_labels);
	//第一个component应该是背景，为黑色
	colors[0] = Vec3b(0, 0, 0);
	for (int i = 1; i < num_labels; i++)
	{
		colors[i] = Vec3b(rng.uniform(0, 256), rng.uniform(0, 256), rng.uniform(0, 256));
	}
	//给联通组件填充颜色
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