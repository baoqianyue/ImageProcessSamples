import cv2 as cv

src = cv.imread("D:/Images/lena.jpg")
cv.namedWindow("src", cv.WINDOW_AUTOSIZE)
src = cv.cvtColor(src, cv.COLOR_BGR2GRAY)
cv.imshow("src", src)

# 只赋值sigmaX，默认sigmaY = sigmaX
dst1 = cv.blur(src, (5, 5), anchor=(-1, -1), borderType=4)
dst2 = cv.GaussianBlur(src, (5, 5), 15, borderType=4)
dst3 = cv.GaussianBlur(src, (0, 0), 15)

cv.imshow("blur ksize=5", dst1)
cv.imshow("gaussian ksize=5", dst2)
cv.imshow("gaussian sigma=15", dst3)

cv.waitKey(0)
cv.destroyAllWindows()
