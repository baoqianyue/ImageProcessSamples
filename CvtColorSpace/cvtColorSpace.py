import cv2 as cv

src = cv.imread("D:/Images/lena.jpg")
cv.namedWindow("rgb", cv.WINDOW_NORMAL)
cv.imshow("rgb", src)

# RGB to HSV
hsv = cv.cvtColor(src, cv.COLOR_BGR2HSV)
cv.namedWindow("hsv", cv.WINDOW_NORMAL)
cv.imshow("hsv", hsv)

# RGB to YUV
yuv = cv.cvtColor(src, cv.COLOR_BGR2YUV)
cv.namedWindow("yuv", cv.WINDOW_NORMAL)
cv.imshow("yuv", yuv)

# RGB to YCrCb
ycrcb = cv.cvtColor(src, cv.COLOR_BGR2YCrCb)
cv.namedWindow("ycrcb", cv.WINDOW_NORMAL)
cv.imshow("ycrcb", ycrcb)

# mask操作
src1 = cv.imread("D:/Images/tinygreen.png")
cv.namedWindow("src1", cv.WINDOW_NORMAL)
cv.imshow("src1", src1)
# 转换色彩空间
hsv = cv.cvtColor(src1, cv.COLOR_BGR2HSV)
cv.namedWindow("dst1", cv.WINDOW_NORMAL)
cv.imshow("dst1", hsv)
# 设置mask 这里mask取值为HSV空间中绿色的取值
mask = cv.inRange(hsv, (35, 43, 46), (77, 255, 255))
# 得到反mask
negMask = cv.bitwise_not(mask)
cv.namedWindow("mask", cv.WINDOW_NORMAL)
cv.namedWindow("negMask", cv.WINDOW_NORMAL)
cv.imshow("mask", mask)
cv.imshow("negMask", negMask)

# 使用mask配合逻辑与操作抠出背景绿幕
dst = cv.bitwise_and(src1, src1, mask=mask)
cv.namedWindow("dst", cv.WINDOW_NORMAL)
cv.imshow("dst", dst)

# 使用negMask配合逻辑与操作抠出图像中人物
dst2 = cv.bitwise_and(src1, src1, mask=negMask)
cv.namedWindow("dst2", cv.WINDOW_NORMAL)
cv.imshow("dst2", dst2)

cv.waitKey(0)
cv.destroyAllWindows()
