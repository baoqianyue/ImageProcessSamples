import cv2 as cv
import numpy as np


def connected_component_demo(src):
    src = cv.GaussianBlur(src, (3, 3), 10)
    # 中值滤波去除小噪点
    src = cv.medianBlur(src, 5)
    gray = cv.cvtColor(src, cv.COLOR_BGR2GRAY)
    # 图像二值化
    thr, binary = cv.threshold(gray, 150, 255, cv.THRESH_BINARY)

    # 进行联通组件查找
    # 给每一个像素都标上相应的label
    # 第一个参数必须为二值图像，黑色背景, 因为这里黑色背景的label值为0
    # 第三个参数表示在八连通域查找
    # 第四个参数表示输出labels图像的数据类型，默认为带符号整形CV_32S
    output = cv.connectedComponents(binary, connectivity=8, ltype=cv.CV_32S)
    num_labels = output[0]
    labels = output[1]

    colors = []

    for i in range(0, num_labels):
        b = np.random.randint(0, 256)
        g = np.random.randint(0, 256)
        r = np.random.randint(0, 256)
        colors.append((b, g, r))

    # index为0的是背景色彩，黑色
    colors[0] = (0, 0, 0)

    # 给加上标记图像进行重新上色
    dst = np.zeros(src.shape, dtype=src.dtype)
    height, width = src.shape[:2]
    for i in range(height):
        for j in range(width):
            dst[i, j] = colors[labels[i, j]]

    cv.imshow("dst", dst)
    # 联通组件数量要减去黑色背景
    print("total connected component: " + str(num_labels - 1))


if __name__ == "__main__":
    src = cv.imread("D:/Images/normal1.jpg")
    cv.namedWindow("src", cv.WINDOW_AUTOSIZE)
    cv.imshow("src", src)
    connected_component_demo(src)
    cv.waitKey(0)
    cv.destroyAllWindows()
