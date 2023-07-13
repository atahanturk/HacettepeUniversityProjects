import cv2.cv2 as cv2
import numpy as np
import math


def meanFilter(img, kernel_value):
    radius = math.floor(kernel_value / 2)
    h,w,d = img.shape
    for i in range(radius, h - radius):
        for j in range(radius, w - radius):
            for k in range(d):
                kernel = np.zeros((kernel_value, kernel_value))
                for y in range(kernel_value):
                    for x in range(kernel_value):
                        kernel[y][x] = img[i - radius + y][j - radius + x][k]
                img[i][j][k]=np.mean(kernel)


image = cv2.imread("france.jpg")
meanFilter(image, 3)
cv2.imshow("Mean Filtered Image", image)
cv2.waitKey(0)
