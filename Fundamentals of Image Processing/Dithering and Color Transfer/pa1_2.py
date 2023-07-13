import numpy as np
import cv2.cv2 as cv2
# In this part, we just use the given F-S algorithm and dithering the image
def FloydSteinberg(image, q):
    image_array = np.asarray(image)
    h, w = image_array.shape

    for y in range(0, h-1):
        for x in range(1, w-1):
            old_pixel = image_array[y][x]
            new_pixel = np.round(old_pixel/(255/q)) * (255/q)
            quant_error = old_pixel - new_pixel
            image_array[y][x] = new_pixel
            image_array[y][x+1] = image_array[y][x+1] + quant_error * 7/16.0
            image_array[y+1][x-1] = image_array[y+1][x-1] + quant_error * 3/16.0
            image_array[y+1][x] = image_array[y+1][x] + quant_error * 5/16.0
            image_array[y+1][x+1] = image_array[y+1][x+1] + quant_error * 1/16.0
            

    return image_array





