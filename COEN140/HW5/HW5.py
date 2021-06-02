#Stephen Tambussi - COEN140 - HW5
#Problem 3 - 2D Convolution from scratch
import numpy as np
import matplotlib.pyplot as plt 
import math
import cv2 

img = cv2.imread('C:/Users/steve/Desktop/COEN140/HW5/lena256.jpg', 0) #0 - loads img in grayscale mode
filter = np.array([[-1, 1], [-1, 1]]) #2x2 filter matrix
strides = 1
padding = 0 #no zero-padding
print(img)
filter = np.flipud(np.fliplr(filter))
print(filter)

xFilterShape = filter.shape[0]
yFilterShape = filter.shape[1]
xImgShape = img.shape[0]
yImgShape = img.shape[1]

#Gets shape of output image size after convolution
xOutput = int(((xImgShape - xFilterShape + 2 * padding) / strides) + 1)
yOutput = int(((yImgShape - yFilterShape + 2 * padding) / strides) + 1)
print(xOutput)
print(yOutput)
output = np.zeros((xOutput, yOutput))

#Iterate through the image
for y in range(img.shape[1]):
    #Exit when filter reaches edge of image
    if y > img.shape[1] - yFilterShape:
        break
    if y % strides == 0:
        for x in range(img.shape[0]):
            #Goes to next row in image once filter reaches edge of image
            if x > img.shape[0] - xFilterShape:
                break
            try:
                if x % strides == 0:
                    #Convolution calculation
                    output[x, y] = (filter * img[x: x + xFilterShape, y: y + yFilterShape]).sum()
            except:
                break

#Take absolute values of output and normalize values into range [0,255]
output = np.abs(output)
o_max = max(output.flatten())
o_min = min(output.flatten())
output_normalized = (output - o_min)/ o_max * 255

#Compare convoluted image with original
cv2.imwrite('C:/Users/steve/Desktop/COEN140/HW5/lena_convoluted.jpg', output_normalized)
conv = cv2.imread('C:/Users/steve/Desktop/COEN140/HW5/lena_convoluted.jpg', 0)
fig = plt.figure(figsize=(16, 25))
ax1 = fig.add_subplot(2, 2, 1)
ax1.axis("off")
ax1.title.set_text('Original')
ax1.imshow(img, cmap='gray')
ax2 = fig.add_subplot(2, 2, 2)
ax2.axis("off")
ax2.title.set_text("Convoluted")
ax2.imshow(conv, cmap='gray')
plt.show()