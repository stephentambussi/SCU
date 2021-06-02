#Stephen Tambussi - COEN140 - Lab9
#Face Recognition
import numpy as np
import matplotlib.pyplot as plt
import math
import cv2
import os
import re 

#these functions are to properly sort the files
def atoi(text):
    return int(text) if text.isdigit() else text
def natural_keys(text):
    return [atoi(c) for c in re.split('(\d+)', text)] #sorts files/folders like a person would: s1 --> s10

#load images as train and test dataset
#each image is 112x92 pixels = 10,304
#load face images 1,3,4,5,7,9 as training images and images 2,6,8,10 as test images for each subject
inputDirectoryPath = r'C:\Users\steve\Desktop\COEN140\Lab9\att_faces_10'
trainingFilesPath = set() #create sets to load paths of each img file for testing and training
testingFilesPath = set()
for inputDirectory in inputDirectoryPath:
    for currentpath, folders, files in os.walk(inputDirectoryPath):
        for file in files:
            if(file.endswith(".pgm") and ((file.startswith("1") and not(file.startswith("10"))) or file.startswith("3")
            or file.startswith("4") or file.startswith("5") or file.startswith("7") 
            or file.startswith("9"))):
                trainingFilesPath.add(os.path.join(currentpath, file))
            elif(file.endswith(".pgm") and (file.startswith("10") or file.startswith("8")
            or file.startswith("6") or file.startswith("2"))):
                testingFilesPath.add(os.path.join(currentpath, file))
    
trainingFilesPath = sorted(trainingFilesPath, key=natural_keys) #converts set into list and sorts it
testingFilesPath = sorted(testingFilesPath, key=natural_keys)
print(trainingFilesPath)
print(testingFilesPath)
print()
train_stacked = np.zeros((10304, 60)) #matrix of size 10304x60 (rows x columns)
test_stacked = np.zeros((10304, 40)) #matrix of size 10304x40
col = 0 #to keep track of column index in matrix
for trainingFile in trainingFilesPath:
    img = cv2.imread(trainingFile, 0) #convert to matrix
    #print(img)
    img = img.flatten() #flatten img to 1D array
    #print(img)
    train_stacked[:, col] = img #add flattened 1D array to stacked matrix
    col += 1
col = 0
for testingFile in testingFilesPath:
    img = cv2.imread(testingFile, 0) #convert to matrix
    #print(img)
    img = img.flatten() #flatten img to 1D array
    #print(img)
    test_stacked[:, col] = img #add flattened 1D array to stacked matrix
    col += 1
print("Training matrix of 10304x60: ")
print(train_stacked)
print(train_stacked.shape)
print()
print("Testing matrix of 10304x40: ")
print(test_stacked)
print(test_stacked.shape)

#Apply SVD to training data set (stacked) for dimensionality reduction
U, sigma, V = np.linalg.svd(train_stacked, full_matrices=False) 
print()
print("Left singular vectors: ")
print(U)
print(U.shape)
print()
print("Singular values matrix: ")
print(sigma)
print(sigma.shape)
print()
print("Right singular vectors: ")
print(V)
print(V.shape)


#Find the top-K left singular vectors (K=1,2,3,6,10,20,30,50) corresponding to the K largest singular values of the data matrix
k_values = [1, 2, 3, 6, 10, 20, 30, 50] #8 elements
recognition_accuracy = np.zeros(8) #1D array to hold the recognition accuracies for each k value
k_count = 0 #to properly iterate through recognition_accuracy array
for k in k_values:
    top_vectors = np.zeros((10304, k)) #10304 x k array(matrix)
    top_values = np.zeros(k) #k-length 1D array
    
    for i in range(k): 
        top_vectors[:, i] = U[:, i] #adds vector from column of U to top_vectors matrix
        top_values[i] = sigma[i]

    #Project the face images to the top-K left singular vectors
    yc = np.zeros((10, k, 6)) #results of projecting training image onto vectors - 3D matrix = (subjects)x(top-K left singular vectors)x(training images per subject) 
    count = 0 #to iterate through images in train_stacked matrix
    for c in range(10): #for each subject
        for n in range(6): #for each training image of the subject - each subject has 6
            for i in range(k): 
                yc[c][i][n] = np.matmul(np.transpose(top_vectors[:, i]), train_stacked[:, count])
            count += 1 #0 to 59

    print()
    print("K-value = ", k)
    print()
    print("yc matrix for training images: ")
    print(yc)
    print(yc.shape)
    print("top_vectors: ")
    print(top_vectors)
    print("top_values: ")
    print(top_values)

    #Apply nearest-neighbor classifier in the reduced dimensional space
    y = np.zeros(k)
    p_class = np.zeros(40) #holds what class each test image is predicted to belong to
    for t in range(40): #for all testing images - each subject(10) has 4 test images
        for i in range(k): #for all the top-K left singular vectors
            y[i] = np.matmul(np.transpose(top_vectors[:, i]), test_stacked[:, t])

        compare = float('inf')
        for c in range(10): #for each subject of training images
            for n in range(6): #for each training image of the subject - each subject has 6
                prediction = np.linalg.norm(y - yc[c, :, n])
                if(prediction < compare): #goal is to minimize 
                    compare = prediction
                    p_class[t] = c #set predicted class
    print()
    print("predicted classes: ")
    print(p_class)

    #Calculate number of correct classifications
    num_correct = 0
    count = 0
    for i in range(10): #for each subject
        for j in range(4): #for each test image
            if(p_class[count] == i): #checks if predicted class is correct
                num_correct += 1
            count += 1
    print()
    print("Number of correct classifications = ", num_correct)

    #Calculate recognition accuracy rate for each k-value
    #(number of correct classification / total number of test images)
    recognition_accuracy[k_count] = (num_correct / 40) * 100 
    print()
    print("Recognition accuracy = ", recognition_accuracy[k_count])
    k_count += 1

#Plot the recognition accuracy rate versus different K values
fig, ax = plt.subplots()
ax.plot(k_values, recognition_accuracy, 'r-', label="Recognition accuracy vs. K values", linewidth=2)
plt.xticks(k_values) #Comment out for more normal display 
plt.xlabel('K values')
plt.ylabel('Recognition accuracy rate %', color="blue")
plt.grid(True)
plt.text(13, 105, "Recognition accuracy vs. K values")
plt.show()
