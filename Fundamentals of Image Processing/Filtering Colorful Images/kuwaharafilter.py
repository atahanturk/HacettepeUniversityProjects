import numpy as np
import cv2.cv2 as cv2
import math


def kuwaharafilter(img, windowsize):
    radius = math.floor(windowsize/2)
    hsvimage = cv2.cvtColor(img, cv2.COLOR_BGR2HSV)
    h,w,d = img.shape
    for i in range(radius, h-radius):
        for j in range(radius, w-radius):
            quadrant_1 = hsvimage[i - radius : i + 1, j - radius : j + 1, 2]
            quadrant_2 = hsvimage[i - radius : i + 1, j : j + radius + 1, 2]
            quadrant_3 = hsvimage[i : i + radius +1, j - radius : j + 1, 2]
            quadrant_4 = hsvimage[i : i + radius + 1, j : j + radius +1, 2]

            qua1_std = np.std(quadrant_1)
            qua2_std = np.std(quadrant_2)
            qua3_std = np.std(quadrant_3)
            qua4_std = np.std(quadrant_4)

            selectedqua = min(qua1_std, qua2_std, qua3_std, qua4_std)

            if selectedqua == qua1_std:
                img[i][j][0] = np.mean(img[i - radius : i + 1, j - radius : j + 1, 0])
                img[i][j][1] = np.mean(img[i - radius : i + 1, j - radius : j + 1, 1])
                img[i][j][2] = np.mean(img[i - radius : i + 1, j - radius : j + 1, 2])

            elif selectedqua == qua2_std:
                img[i][j][0] = np.mean(img[i - radius : i + 1, j : j + radius + 1, 0])
                img[i][j][1] = np.mean(img[i - radius : i + 1, j : j + radius + 1, 1])
                img[i][j][2] = np.mean(img[i - radius : i + 1, j : j + radius + 1, 2])

            elif selectedqua == qua3_std:
                img[i][j][0] = np.mean(img[i : i + radius +1, j - radius : j + 1, 0])
                img[i][j][1] = np.mean(img[i : i + radius +1, j - radius : j + 1, 1])
                img[i][j][2] = np.mean(img[i : i + radius +1, j - radius : j + 1, 2])

            elif selectedqua == qua4_std:
                img[i][j][0] = np.mean(img[i : i + radius + 1, j : j + radius +1, 0])
                img[i][j][1] = np.mean(img[i : i + radius + 1, j : j + radius +1, 1])
                img[i][j][2] = np.mean(img[i : i + radius + 1, j : j + radius +1, 2])
    return img


image = cv2.imread("france.jpg")
kuwaharafilter(image,3)
cv2.imshow("Kuwahara Filtered Image", image)
cv2.waitKey(0)
