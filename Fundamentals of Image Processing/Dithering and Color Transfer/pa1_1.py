import numpy as np
import cv2.cv2 as cv2
from pa1_2 import FloydSteinberg
# In this part, we read the source image and I wrote a function for quantization. Also we call the dithering function.
def quantizer(image, q):
    image_array = np.asarray(image)
    h, w = image_array.shape

    for y in range(h):
        for x in range(w):
            old_pixel = image_array[y][x]
            new_pixel = np.round(old_pixel/(255/q)) * (255/q)
            image_array[y][x] = new_pixel
    return image

image = cv2.imread("1.png")
image = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)
FloydSteinberg(image, 16)
cv2.imshow("Dıthered Image", image)
cv2.waitKey(0)
