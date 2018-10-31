import cv2 as cv
import numpy as np


def add_salt_pepper_noise(src):
    """
    生成椒盐噪点图像
    :param src:
    :return:
    """
    height, width = src.shape[:2]
    noise_num = 1000
    # 随机生成噪点坐标
    xs = np.random.randint(0, width, noise_num, dtype=np.int)
    ys = np.random.randint(0, height, noise_num, dtype=np.int)

    for i in range(noise_num):
        # 保证黑色和白色噪点间隔出现
        if i % 2 == 1:
            src[ys[i], xs[i]] = (255, 255, 255)
        else:
            src[ys[i], xs[i]] = (0, 0, 0)
    return src


def add_gaussian_noise(src):
    """
    生成高斯噪声图像
    :param src:
    :return:
    """
    noise = np.zeros(src.shape, src.dtype)
    # 各通道均值
    mean = (15, 15, 15)
    # 各通道方差
    stddev = (30, 30, 30)
    cv.randn(noise, mean, stddev)
    cv.imshow("gaussian noise", noise)
    dst = cv.add(src, noise)
    cv.imshow("gussian dst", dst)
    return dst


src = cv.imread("D:/Images/lena.jpg")
add_gaussian_noise(src)

height, width = src.shape[:2]
copy = np.copy(src)
copy = add_salt_pepper_noise(copy)
# 将原图和处理后的图像并排显示在一张图像上
result = np.zeros([height, 2 * width, 3], dtype=src.dtype)

result[0: height, 0: width, :] = src
result[0: height, width: width * 2, :] = copy
cv.putText(result, "src", (10, 30), cv.FONT_HERSHEY_COMPLEX, 2.0, (0, 255, 255), 1)
cv.putText(result, "salt pepper", (10 + width, 30), cv.FONT_HERSHEY_SIMPLEX, 2.0, (0, 255, 255), 1)
cv.imshow("salt pepper img", result)

cv.waitKey(0)
cv.destroyAllWindows()
