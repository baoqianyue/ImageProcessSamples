import sys
import cv2 as cv
import numpy as np


def preprocess(src):
    """
    图像预处理
    1.高斯双边边缘保留滤波
    2.中值滤波去除小噪点
    3.边缘提取
    4.二值化
    5.图像数字形态学处理
      5.1 闭运算
    :param src:
    :return: plate contour 车牌轮廓
    """

    # 1.先去噪，这里使用了高斯双边模糊，较好的保留了边缘信息
    # 疯狂乱调参...
    bilateralGauss = cv.bilateralFilter(src, 7, 120, 20, borderType=4)
    gray = cv.cvtColor(bilateralGauss, cv.COLOR_RGB2GRAY)
    # 2.中值滤波
    gray = cv.medianBlur(gray, 7)
    # sobel 算子，对水平方向边缘检测
    sobel = cv.Sobel(gray, cv.CV_8U, 1, 0, ksize=3)
    # 二值化
    thredhold, binary = cv.threshold(sobel, 150, 255, cv.THRESH_BINARY)
    cv.imshow("binary", binary)

    # 形态学处理
    # 疯狂乱调参...
    # 直接一个侧重于水平方向的闭运算，将车牌区域进行填充，便于寻找到该区域
    element = cv.getStructuringElement(cv.MORPH_RECT, (40, 5))
    closed = cv.morphologyEx(binary, cv.MORPH_CLOSE, element)
    cv.imshow("closed", closed)

    return closed


def splitPlateNumberRegion(img):
    # 检测所有轮廓，所有轮廓建立等级树
    # 仅保留图像边缘上的拐点
    copy = np.copy(img)
    cv.imshow("gray", copy)
    _, contours, hieracy = cv.findContours(copy, cv.RETR_TREE, cv.CHAIN_APPROX_SIMPLE)
    print("contours num is: %s" % (len(contours)))
    for i in range(len(contours)):
        cont = contours[i]
        area = cv.contourArea(cont)
        # 面积太小的直接忽略
        if area < 1000:
            continue

        # 将所有疑似轮廓都转换成对应的最小矩形
        rect = cv.minAreaRect(cont)
        # 转换成box类型
        box = np.int32(cv.boxPoints(rect))
        # 计算矩形长宽
        height = abs(box[0][1] - box[2][1])
        width = abs(box[0][0] - box[2][0])
        # 计算长宽比
        radio = width / height



if __name__ == "__main__":
    src = cv.imread("./ChePaiKu/normal2.jpg")
    cv.imshow("src", src)
    closed = preprocess(src)
    # region = splitPlateNumberRegion(closed)

    cv.waitKey(0)
    cv.destroyAllWindows()
