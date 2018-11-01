import cv2 as cv
import numpy as np

src = cv.imread("D:/Images/saltimg.jpg")

dst = cv.medianBlur(src, 5)

height, width = src.shape[:2]
result = np.zeros([height, width * 2, 3], dtype=src.dtype)
result[0: height, 0: width, :] = src
result[:, width: width * 2, :] = dst
cv.putText(result, "salt_src", (10, 50), cv.FONT_HERSHEY_SIMPLEX, 2.0, (0, 255, 255), 1)
cv.putText(result, "median_img", (10 + width, 50), cv.FONT_HERSHEY_SIMPLEX, 2.0, (0, 255, 255), 1)
cv.imshow("result", result)

cv.waitKey(0)
cv.destroyAllWindows()
