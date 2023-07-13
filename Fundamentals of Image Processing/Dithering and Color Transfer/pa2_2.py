import numpy as np
import cv2.cv2 as cv2
import math


def bgr2lab(image):
    image_array = np.asarray(image)
    h, w, d = image_array.shape
    colors_lab = np.zeros((h*w, d))
    counter = 0
    # Function for changing image RGB to lab
    for y in range(h):
        for x in range(w):
            B = image_array[y][x][0]
            G = image_array[y][x][1]
            R = image_array[y][x][2]
            # Apply the given transformation to convert RGB source and target images to LMS cone space:
            L = 0.3811 * R + 0.5783 * G + 0.0402 * B
            M = 0.1967 * R + 0.7244 * G + 0.0782 * B
            S = 0.0241 * R + 0.1288 * G + 0.8444 * B
            # Apply the given transformation to convert RGB source and target images to LMS cone space:
            if L == 0:
                L = 0
            else:
                L = math.log10(L)  # To prevent the logarithm from taking the log0
            if M == 0:
                M = 0
            else:
                M = math.log10(M)
            if S == 0:
                S = 0
            else:
                S = math.log10(S)
            # Apply the given transformation to convert to l space:
            iota = 1.0 / math.sqrt(3) * L + 1.0 / math.sqrt(3) * M + 1.0 / math.sqrt(3) * S
            alpha = 1.0 / math.sqrt(6) * L + 1.0 / math.sqrt(6) * M - 2 / math.sqrt(6) * S
            beta = 1.0 / math.sqrt(2) * L - 1.0 / math.sqrt(2) * M + 0 * S

            colors_lab[counter] = [iota, alpha, beta]
            counter = counter + 1
    return colors_lab


def colorTransfer(source, target):
    src = bgr2lab(source)
    targ = bgr2lab(target)
    # Compute the mean and variance of the images for iota,alpha,beta channels:

    mean_src = np.mean(src, axis=0)
    mean_srciota = mean_src[0]
    mean_srcalpha = mean_src[1]
    mean_srcbeta = mean_src[2]

    mean_targ = np.mean(targ, axis=0)
    mean_targiota = mean_targ[0]
    mean_targalpha = mean_targ[1]
    mean_targbeta = mean_targ[2]

    var_src = np.var(src, axis=0)
    var_srciota = var_src[0]
    var_srcalpha = var_src[1]
    var_srcbeta = var_src[2]

    var_targ = np.var(targ, axis=0)
    var_targiota = var_targ[0]
    var_targalpha= var_targ[1]
    var_targbeta= var_targ[2]

    for index in src:
        iota = index[0]
        alpha = index[1]
        beta = index[2]

        # Subtract the mean of source image from the source image:
        iota = iota - mean_srciota
        alpha = alpha - mean_srcalpha
        beta = beta - mean_srcbeta

        # Scale the data points by the respective standard deviations:
        iota = (var_targiota/var_srciota) * iota
        alpha = (var_targalpha/var_srcalpha) * alpha
        beta = (var_targbeta/var_srcbeta) * beta

        # Add the target's mean to the scaled data points:
        iota = iota + mean_targiota
        alpha = alpha + mean_targalpha
        beta = beta + mean_targbeta

        index[0] = iota
        index[1] = alpha
        index[2] = beta
    counter = 0
    # Apply transform matrix to convert l to LMS:
    for indice in src:
        iota = indice[0]
        alpha = indice[1]
        beta = indice[2]

        L = math.sqrt(3.0) / 3.0 * iota + math.sqrt(6) / 6.0 * alpha + math.sqrt(2) / 2.0 * beta
        M = math.sqrt(3.0) / 3.0 * iota + math.sqrt(6) / 6.0 * alpha - math.sqrt(2) / 2.0 * beta
        S = math.sqrt(3.0) / 3.0 * iota - math.sqrt(6) / 3.0 * alpha - 0 * beta
        # Go back to linear space:
        L = pow(10.0, L)
        M = pow(10.0, M)
        S = pow(10.0, S)
        # Apply transform matrix to convert LMS to RGB:
        R = 4.4679 * L - 3.5873 * M + 0.1193 * S
        G = -1.2186 * L + 2.3809 * M - 0.1624 * S
        B = 0.0497 * L - 0.2439 * M + 1.2045 * S

        if R > 255:
            R = 255
        if R < 0:
            R = 0
        if G > 255:
            G = 255
        if G < 0:
            G = 0
        if B > 255:
            B =255
        if B < 0:
            B = 0

        indice[0] = B
        indice[1] = G
        indice[2] = R
    # Observe the result.
    for i in source:
        for j in i:
            bgr = src[counter]
            counter = counter + 1
            j[0] = bgr[0]
            j[1] = bgr[1]
            j[2] = bgr[2]
