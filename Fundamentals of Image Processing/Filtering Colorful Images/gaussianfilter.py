import numpy as np
import cv2.cv2 as cv2
import math


def gaussianKernel(kernel_value):
    radius = math.floor(kernel_value / 2)
    sigma = max((radius/2), 1)
    kernel = np.zeros((kernel_value, kernel_value))
    sum = 0.0
    for y in range(-radius,radius+1):
        for x in range(-radius,radius+1):
            enumerator = -(x * x + y * y)
            edenominator = 2 * sigma * sigma
            eExpression = pow(math.e, enumerator / edenominator)
            gformula = (eExpression / 2 * math.pi * sigma * sigma)
            kernel[y+radius][x+radius] = gformula
            sum += gformula
    for y in range(kernel_value):
        for x in range(kernel_value):
            kernel[y][x] = kernel[y][x] / sum
    return kernel


def gaussianFilter(img, kernel_value):
    radius = kernel_value // 2
    kernel = gaussianKernel(kernel_value)
    h,w,d = img.shape
    for i in range(radius, h - radius):
        for j in range(radius, w - radius):
            blue = 0.0
            green = 0.0
            red = 0.0
            for y in range(-radius, radius+1):
                for x in range(-radius, radius+1):
                    kernelPixel = kernel[y + radius][x + radius]
                    blue += (img[i - y][j - x][0]) * kernelPixel
                    green += (img[i - y][j - x][1]) * kernelPixel
                    red += (img[i - y][j - x][2]) * kernelPixel

            img[i][j][0] = blue
            img[i][j][1] = green
            img[i][j][2] = red


image = cv2.imread("france.jpg")
gaussianFilter(image,3)
cv2.imshow("Gaussian Filtered Image", image)
cv2.waitKey(0)
