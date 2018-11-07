import cv2 as cv

def threshold_demo(src):
    # 去噪+二值化
    dst = cv.GaussianBlur(src, (3, 3), 10)
    dst = cv.cvtColor(dst, cv.COLOR_BGR2GRAY)
    threValue, binary = cv.threshold(dst, 150, 255, cv.THRESH_BINARY)
    cv.imshow("binary", binary)
    return binary


def canny_demo(src):
    t = 100
    # 提取边缘
    dst = cv.Canny(src, t, t * 2)
    cv.imshow("canny_out", dst)
    return dst


src = cv.imread("./ChePaiKu/normal1.jpg")
binary = threshold_demo(src)
# 第二个参数是检测所有轮廓，并为他们建立等级树
# 第三个参数是定义轮廓的近似方法，这里是只保留轮廓的拐点信息
# 第一个返回值是binary
# 第二个返回值是轮廓信息，包括每个轮廓的元素信息
# 第三个返回值是每个轮廓的层次信息
out, contours, hierarchy = cv.findContours(binary, cv.RETR_TREE, cv.CHAIN_APPROX_SIMPLE)
for i in range(len(contours)):
    # 第一个参数表示绘制轮廓在哪个图像上
    # 第二个参数传入轮廓信息
    # 第三个参数表示第一个轮廓
    # 第四个参数表示绘制颜色
    # 第五个参数是绘制线宽，如果是-1就表示填充区域
    # 第六个参数图形渲染模式，这里是八领域绘制
    cv.drawContours(src, contours, i, (0, 0, 255), 2, 8)

cv.imshow("contours", src)
cv.waitKey(0)
cv.destroyAllWindows()
