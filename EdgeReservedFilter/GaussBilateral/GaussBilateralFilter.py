import numpy as np
import cv2 as cv

src = cv.imread("D:/Images/lena.jpg")
height, width = src.shape[:2]

# 第二个参数代表滤波过程中各像素领域的直径，相当于卷积核的尺寸
# 如果是实际应用，建议使用5，对于需要过滤严重噪声的离线应用，使用9
# 如果d>5执行的效率较低
# 如果d<0，d的值将由第5个参数sigmaSpace的值计算得到
# 第三个参数代表该色差范围(RGB色彩空间)内的像素点参与运算
# 第四个参数代表高斯模糊中的sigma的值，就是x和y方向上的方差的值
# 第五个参数代表卷积的边界填充规则
bilaFilter = cv.bilateralFilter(src, 5, 100, 10, borderType=4)
gaussFilter = cv.GaussianBlur(src, (5, 5), 10, borderType=4)
result = np.zeros((height, width * 3, 3), dtype=src.dtype)

result[:height, : width, :] = src
result[:, width: width * 2, :] = gaussFilter
result[:, width * 2: width * 3, :] = bilaFilter
cv.putText(result, "src", (10, 50), cv.FONT_HERSHEY_PLAIN, 2.0, (255, 255, 0), 1)
cv.putText(result, "gaussFilter", (10 + width, 50), cv.FONT_HERSHEY_PLAIN, 2.0, (255, 255, 0), 1)
cv.putText(result, "bilateralFilter", (10 + width * 2, 50), cv.FONT_HERSHEY_PLAIN, 2.0, (255, 255, 0), 1)
cv.namedWindow("result", cv.WINDOW_NORMAL)
cv.imshow("result", result)

cv.waitKey(0)
cv.destroyAllWindows()
