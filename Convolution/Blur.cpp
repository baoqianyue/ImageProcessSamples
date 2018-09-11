#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

int main(int argc, const char *argv[])
{
	Mat src = imread("D:/Images/lena.jpg");
	if (src.empty())
	{
		printf("could not load image...\n");
		return -1;
	}
	namedWindow("src", WINDOW_AUTOSIZE);
	imshow("src", src);

	//blur 
	Mat dst = src.clone();
	//为了使卷积核能够重合,i和j都从1开始遍历，到rows-1和cols-1
	for (int i = 1; i < src.rows - 1; i++)
	{
		for (int j = 1; j < src.cols - 1; j++)
		{
			Vec3b p1 = src.at<Vec3b>(i - 1, j - 1);
			Vec3b p2 = src.at<Vec3b>(i - 1, j);
			Vec3b p3 = src.at<Vec3b>(i - 1, j + 1);
			Vec3b p4 = src.at<Vec3b>(i, j - 1);
			Vec3b p5 = src.at<Vec3b>(i, j);
			Vec3b p6 = src.at<Vec3b>(i, j + 1);
			Vec3b p7 = src.at<Vec3b>(i + 1, j - 1);
			Vec3b p8 = src.at<Vec3b>(i + 1, j);
			Vec3b p9 = src.at<Vec3b>(i + 1, j + 1);

			int b = p1[0] + p2[0] + p3[0] + p4[0] + p5[0] + p6[0] + p7[0] + p8[0] + p9[0];
			int g = p1[1] + p2[1] + p3[1] + p4[1] + p5[1] + p6[1] + p7[1] + p8[1] + p9[1];
			int r = p1[2] + p2[2] + p3[2] + p4[2] + p5[2] + p6[2] + p7[2] + p8[2] + p9[2];
			dst.at<Vec3b>(i, j)[0] = saturate_cast<uchar>(b / 9);
			dst.at<Vec3b>(i, j)[1] = saturate_cast<uchar>(g / 9);
			dst.at<Vec3b>(i, j)[2] = saturate_cast<uchar>(r / 9);
		}
	}
	imshow("blur", dst);
	imwrite("D:/Images/bulrRes.png", dst);

	//Opencv实现
	Mat result;
	//Size
	//使用积分图技术加速
	blur(src, result, Size(15, 15), Point(-1, -1), 4);
	imshow("result", result);

	waitKey(0);
	return 0;

}