import cv2 as cv
import numpy as np

src = cv.imread("D:/Images/lena.jpg")
cv.namedWindow("src", cv.WINDOW_NORMAL)
cv.imshow("src", src)

# X flip 镜像
dst = cv.flip(src, 0)
cv.namedWindow("X_flip", cv.WINDOW_NORMAL)
cv.imshow("X_flip", dst)

# Y flip 倒影
dst = cv.flip(src, 1)
cv.namedWindow("Y_flip", cv.WINDOW_NORMAL)
cv.imshow("Y_flip", dst)

# XY flip 对角
dst = cv.flip(src, -1)
cv.namedWindow("XY_flip", cv.WINDOW_NORMAL)
cv.imshow("XY_flip", dst)

# custom X flip
dst1 = np.zeros(shape=src.shape, dtype=src.dtype)
row, col, ch = dst1.shape
for i in range(row):
    for j in range(col):
        r, g, b = src[i, j]
        dst1[row - i - 1, j] = [r, g, b]
cv.imshow("custom_X_flip", dst1)
cv.waitKey(0)
cv.destroyAllWindows()
