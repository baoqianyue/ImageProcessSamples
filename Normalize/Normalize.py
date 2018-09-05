import cv2 as cv
import numpy as np

src = cv.imread("D:/Images/lena.jpg")
cv.namedWindow("input", cv.WINDOW_AUTOSIZE)
cv.imshow("input", src)
gray = cv.cvtColor(src, cv.COLOR_BGR2GRAY)

# 转换为浮点数类型数据进行计算
gray = np.float32(gray)
print(gray)

# scale by NORM_MINMAX
dst = np.zeros(shape=gray.shape, dtype=np.float32)
cv.normalize(gray, dst, alpha=0, beta=1, norm_type=cv.NORM_MINMAX)
print(dst)
cv.imshow("NORM_MINMAX", dst)
dst = np.uint8(dst * 255)
cv.imshow("NORM_MINMAX1", dst)

cv.waitKey(0)
cv.destroyAllWindows()
