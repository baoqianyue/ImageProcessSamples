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
# 当归一化类型为MINMAX时，alpha和beta参数限制取值范围
cv.normalize(gray, dst=dst, alpha=0, beta=1.0, norm_type=cv.NORM_MINMAX)
print(dst)
# 在显示图像之前需要转换成int类型数据，imshow函数自动会计算转换成整形数据
dst = np.uint8(dst * 255)
cv.imshow("NORM_MINMAX", dst)

# scale by NORM_INF
dst = np.zeros(shape=gray.shape, dtype=np.float32)
cv.normalize(gray, dst, alpha=1.0, beta=0, norm_type=cv.NORM_INF)
# 转换数据类型
cv.imshow("NORM_INF", np.uint8(dst * 255))

# scale by NORM_L1
dst = np.zeros(shape=gray.shape, dtype=np.float32)
cv.normalize(gray, dst=dst, alpha=1.0, beta=0, norm_type=cv.NORM_L1)
print(dst)
# 归一化后的数据在e-6次方
cv.imshow("NORM_L1", np.uint8(dst * 10000000))

# scale by NORM_L2
dst = np.zeros(shape=gray.shape, dtype=np.float32)
cv.normalize(gray, dst=dst, alpha=1.0, beta=0, norm_type=cv.NORM_L2)
print(dst)
cv.imshow("NORM_L2", np.uint8(dst * 10000))

cv.waitKey(0)
cv.destroyAllWindows()
