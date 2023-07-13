import cv2.cv2 as cv2
from pa2_2 import colorTransfer

#In this file we just read the source and target images, then call the function for color transferring.

source_img = cv2.imread("monalisa.jpg")
target_img = cv2.imread("starry.jpg")
colorTransfer(source_img, target_img)
cv2.imshow("Color Transfered Image", source_img)
cv2.waitKey(0)
