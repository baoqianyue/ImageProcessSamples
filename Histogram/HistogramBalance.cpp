#include <opencv2/opencv.hpp>

using namespace cv;

/*
直方图均衡
*/
Mat HistogramBalance(Mat& src)
{
	Mat des(src);//为节省空间，只复制矩阵头
	int gray_freq[256] = { 0 };//统计每个灰度级出现的次数
	float gray_prob[256] = { 0 };//每个灰度级在图像中的概率
	float gray_cdf_prob[256] = { 0 };//每个灰度级经过直方图均衡变换T后的积累分布概率之和	
	int gray_des_lut[256] = { 0 };//直方图均衡后的灰度查找表
	int total_pixels = src.rows * src.cols;
	//首先统计每个灰度级在图像中出现的次数
	for (int i = 0; i < src.rows; i++)
	{
		uchar* p = src.ptr<uchar>(i); //获取到行像素指针
		for (int j = 0; j < src.cols; j++)
		{
			int pixel = p[j];
			gray_freq[pixel]++;
		}
	}

	//计算灰度级在图像中出现的概率
	for (int i = 0; i < 256; i++)
		gray_prob[i] = ((float)gray_freq[i] / total_pixels); //每个灰度级占像素总数的比例


	//计算每个灰度级经直方图均衡变换后的累计分布概率之和
	gray_cdf_prob[0] = gray_prob[0];//灰度值为0为第一个值，概率和等于它本身
	for (int i = 1; i < 256; i++)
		gray_cdf_prob[i] = gray_cdf_prob[i - 1] + gray_prob[i];

	//构建直方图均衡后的灰度级查找表,公式s = T(r) = (L-1)ΣP(rj)   
	//最终灰度值四舍五入
	for (int i = 0; i < 256; i++)
		gray_des_lut[i] = (256 - 1) * gray_cdf_prob[i] + 0.5;

	//构建变换后的图像Mat
	for (int i = 0; i < des.rows; i++)
	{
		uchar *p = des.ptr<uchar>(i);
		for (int j = 0; j < des.cols; j++)
		{
			p[j] = gray_des_lut[p[j]]; //从查找表中读取变换后的灰度值
		}
	}

	return des;
}



int main(int argc, char* argv[])
{
	Mat src = imread("C://Users//鲍骞月//Desktop//testImag//Histogramtestsrc2.jpg", CV_LOAD_IMAGE_GRAYSCALE);
	namedWindow("灰度图原图像", WINDOW_AUTOSIZE);
	imshow("灰度图原图像", src);
	Mat des = HistogramBalance(src);
	imshow("灰度图直方图均衡", des);
	Mat src_color = imread("C://Users//鲍骞月//Desktop//testImag//Histogramtestsrc2.jpg", CV_LOAD_IMAGE_COLOR);
	imshow("彩图原图像", src_color);
	Mat imgBlueChannel, imgGreenChannel, imgRedChannel, des_color; //三通道Mat
	std::vector<Mat> channels;//三通道灰度值
	split(src_color, channels);
	imgBlueChannel = channels.at(0);
	imgGreenChannel = channels.at(1);
	imgRedChannel = channels.at(2);
	//分通道进行直方图均衡处理
	imgBlueChannel = HistogramBalance(imgBlueChannel);
	imgGreenChannel = HistogramBalance(imgGreenChannel);
	imgRedChannel = HistogramBalance(imgRedChannel);
	channels.clear();
	channels.push_back(imgBlueChannel);
	channels.push_back(imgGreenChannel);
	channels.push_back(imgRedChannel);
	//合并处理后的三个通道
	merge(channels, des_color);
	imshow("彩图直方图均衡", des_color);
	waitKey(0);
	return 0;
}