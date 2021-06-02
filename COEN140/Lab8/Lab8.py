#Stephen Tambussi - COEN140 - Lab8
#Convolutional Neural Network
import tensorflow as tf
from tensorflow import keras
from tensorflow.keras import layers, models
import matplotlib.pyplot as plt
from sklearn.metrics import confusion_matrix
from sklearn.metrics import ConfusionMatrixDisplay
import numpy as np
import math

fashion_mnist = keras.datasets.fashion_mnist 

#Load data and normalize
#train = (60000, 28, 28), test = (10000, 28, 28)
(train_images, train_labels), (test_images, test_labels) = fashion_mnist.load_data()
train_images = train_images.reshape((60000, 28, 28, 1))
test_images = test_images.reshape((10000, 28, 28, 1))
#normalize the data samples to numbers in [0, 1]
train_images, test_images = train_images / 255.0, test_images / 255.0

#Create Model
model = models.Sequential()
#2D convolution layer: filter size=3x3, depth=32
model.add(layers.Conv2D(32, (3, 3), activation='relu', padding='same', strides=(1, 1), input_shape=(28, 28, 1)))
#2x2 max pooling layer
model.add(layers.MaxPooling2D((2, 2), padding='same', strides=(2, 2)))
#2D convolution layer: filter size=3x3, depth=64
model.add(layers.Conv2D(64, (3, 3), activation='relu', padding='same', strides=(1, 1)))
#2x2 max pooling layer
model.add(layers.MaxPooling2D((2, 2), padding='same', strides=(2, 2)))
#2D convolution layer: filter size=3x3, depth=64
model.add(layers.Conv2D(64, (3, 3), activation='relu', padding='same', strides=(1, 1)))
#Flattening layer
model.add(layers.Flatten())
#Fully-connected layer: 64 nodes, relu activation
model.add(layers.Dense(64, activation='relu'))
#Output fully-connected layer: 10 nodes, softmax activation
model.add(layers.Dense(10, activation='softmax'))

#Compile model
model.compile(loss='sparse_categorical_crossentropy', optimizer='adam', metrics=['accuracy'])

#Fit model to the data
model.fit(train_images, train_labels, epochs=5, verbose=2) #default batch size = 32

#Evaluting model
loss_test, acc_test = model.evaluate(test_images, test_labels)
print("Accuracy rate = ", acc_test)
print("Loss = ", loss_test)

#Confusion matrix
predict_y = model.predict_classes(test_images)
CM = confusion_matrix(test_labels, predict_y)
fig, ax = plt.subplots(figsize=(10, 10))
plt.rcParams.update({'font.size': 12})
disp = ConfusionMatrixDisplay(confusion_matrix=CM)
disp = disp.plot()
plt.show()

#For each layer, calculate the number of parameters, output dimensions, and number of multiplications to generate that layer
parameters = 0
output = np.zeros(3, dtype=int) #output[0] = height | output[1] = width | output[2] = depth
num_multiplications = 0
total_multiplications = 0
print()
print("----------------Layer info calculations----------------")
#1 - input layer 
print()
print("Input Layer")
print("-------------------------------------------------------")
parameters = 0
print("Parameters = ", parameters)
output[0] = 28
output[1] = 28
output[2] = 1
print("Output dimensions = ", output)
num_multiplications = 0
print("Number of multiplications = ", num_multiplications) 

#2 - 2D convolution layer
print()
print("2D Convolutional Layer: filter size 3x3, depth=32, padding=same, strides=(1,1), input size=28x28x1")
print("-------------------------------------------------------")
parameters = (3*3*1 + 1)*32 #320
print("Parameters = ", parameters)
output[0] = math.floor((28 + 2*1 - 3) / 1) + 1
output[1] = output[0]
output[2] = 32
print("Output dimensions = ", output)
num_multiplications = (3*3*1 + 1) * output[0] * output[1] * output[2] #250,880
total_multiplications += num_multiplications
print("Number of multiplications = ", num_multiplications) 

#3 - Max pooling layer
print()
print("2x2 Max Pooling Layer: strides=(2,2), padding=same")
print("-------------------------------------------------------")
parameters = 0
print("Parameters = ", parameters)
output[0] = math.floor((28 + 2*0 - 2) / 2) + 1 
output[1] = output[0]
output[2] = 32 #keep same depth dimension as previous layer
print("Output dimensions = ", output)
num_multiplications = 0 
print("Number of multiplications = ", num_multiplications) 

#4 - 2D convolutional layer
print()
print("2D Convolutional Layer: filter size 3x3, depth=64, padding=same, strides=(1,1)")
print("-------------------------------------------------------")
parameters = (3*3*32 + 1)*64 #18496
print("Parameters = ", parameters)
output[0] = math.floor((14 + 2*1 - 3) / 1) + 1 
output[1] = output[0]
output[2] = 64
print("Output dimensions = ", output)
num_multiplications = (3*3*32 + 1) * output[0] * output[1] * output[2] 
total_multiplications += num_multiplications
print("Number of multiplications = ", num_multiplications) 

#5 - Max pooling layer
print()
print("2x2 Max Pooling Layer: strides=(2,2), padding=same")
print("-------------------------------------------------------")
parameters = 0
print("Parameters = ", parameters)
output[0] = math.floor((14 + 2*0 - 2) / 2) + 1 
output[1] = output[0]
output[2] = 64 #keep same depth dimension as previous layer
print("Output dimensions = ", output)
num_multiplications = 0
print("Number of multiplications = ", num_multiplications) 

#6 - 2D convolutional layer
print()
print("2D Convolutional Layer: filter size 3x3, depth=64, padding=same, strides=(1,1)")
print("-------------------------------------------------------")
parameters = (3*3*64 + 1)*64 #36928
print("Parameters = ", parameters)
output[0] = math.floor((7 + 2*1 - 3) / 1) + 1 
output[1] = output[0]
output[2] = 64
print("Output dimensions = ", output)
num_multiplications = (3*3*64 + 1) * output[0] * output[1] * output[2] 
total_multiplications += num_multiplications
print("Number of multiplications = ", num_multiplications)

#7 - Flattening layer
print()
print("Flattening Layer")
print("-------------------------------------------------------")
parameters = 0
print("Parameters = ", parameters)
output[0] = output[0] * output[0] * 64  
output[1] = 1
output[2] = 1
print("Output dimensions = ", output[0])
num_multiplications = 0
print("Number of multiplications = ", num_multiplications)

#8 - Fully-connected layer
print()
print("Fully-connected Layer: 64 nodes, activation=relu")
print("-------------------------------------------------------")
parameters = (output[0] + 1) * 64 #(3136 + 1) * 64
print("Parameters = ", parameters)
output[0] = 64
output[1] = 1
output[2] = 1
print("Output dimensions = ", output[0])
num_multiplications = (3136 + 1) * 64 
total_multiplications += num_multiplications
print("Number of multiplications = ", num_multiplications)

#9 - Fully-connected output layer
print()
print("Fully-connected Layer: 10 nodes, activation=softmax")
print("-------------------------------------------------------")
parameters = (output[0] + 1) * 10 #(64 + 1) * 10
print("Parameters = ", parameters)
output[0] = 10  
output[1] = 1
output[2] = 1
print("Output dimensions = ", output[0])
num_multiplications = (64 + 1) * 10 
total_multiplications += num_multiplications
print("Number of multiplications = ", num_multiplications)

print()
print("Total number of multiplications = ", total_multiplications)
print()
model.summary() #to check answers