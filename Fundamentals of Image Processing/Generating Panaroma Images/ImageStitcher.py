import cv2
import numpy as np

image1 = cv2.imread("building1.jpg")
image2 = cv2.imread("building2.jpg")
image3 = cv2.imread("building3.jpg")


def imagestitch(img1,img2):

    img1gs = cv2.cvtColor(img1,cv2.COLOR_BGR2GRAY)
    img2gs = cv2.cvtColor(img2,cv2.COLOR_BGR2GRAY)
    sift = cv2.SIFT_create()
    kp1, des1 = sift.detectAndCompute(img2gs,None)
    kp2, des2 = sift.detectAndCompute(img1gs,None)

    match = cv2.BFMatcher()
    matches = match.knnMatch(des1,des2,k=2)

    threshold = []
    for m,n in matches:
        if m.distance < 0.80*n.distance:
            threshold.append(m)

    sourcepoints = np.float32([kp1[m.queryIdx].pt for m in threshold]).reshape(-1,1,2)
    distancepoints = np.float32([kp2[m.trainIdx].pt for m in threshold]).reshape(-1,1,2)

    M, mask = cv2.findHomography(sourcepoints, distancepoints, cv2.RANSAC, 5.0)

    distance = cv2.warpPerspective(img2,M,(img1.shape[1] + img2.shape[1], img1.shape[0]))
    distance[0:img1.shape[0],0:img1.shape[1]] = img1

    return distance


part2 = imagestitch(image2,image3)
stitched = imagestitch(image1,part2)
cv2.imshow("Stitched", stitched)
cv2.waitKey(0)
