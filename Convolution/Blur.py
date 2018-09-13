import cv2 as cv
import numpy as np

src = cv.imread("D:/Images/lena.jpg")
cv.namedWindow("src", cv.WINDOW_AUTOSIZE)
cv.imshow("src", src)


def custom_blur_avg(src):
    width, height, channel = src.shape
    dst = np.copy(src)
    for i in range(1, height - 1, 1):
        for j in range(1, width - 1, 1):
            t1 = np.int32(src[i - 1, j - 1])
            t2 = np.int32(src[i - 1, j])
            t3 = np.int32(src[i - 1, j + 1])
            t4 = np.int32(src[i, j - 1])
            t5 = np.int32(src[i, j])
            t6 = np.int32(src[i, j + 1])
            t7 = np.int32(src[i + 1, j - 1])
            t8 = np.int32(src[i + 1, j])
            t9 = np.int32(src[i + 1, j + 1])

            b = t1[0] + t2[0] + t3[0] + t4[0] + t5[0] + t6[0] + t7[0] + t8[0] + t9[0]
            g = t1[1] + t2[1] + t3[1] + t4[1] + t5[1] + t6[1] + t7[1] + t8[1] + t9[1]
            r = t1[2] + t2[2] + t3[2] + t4[2] + t5[2] + t6[2] + t7[2] + t8[2] + t9[2]
            dst[i, j] = [b // 9, g // 9, r // 9]
    return dst


dst = custom_blur_avg(src)
cv.imshow("dst", dst)
dst1 = np.copy(src)
dst1 = cv.blur(src, ksize=(15, 15), anchor=(-1, -1), borderType=4)
cv.imshow("dst1", dst1)

cv.waitKey(0)
cv.destroyAllWindows()
