#Stephen Tambussi - COEN140 - Lab7
#Neural Network
import tensorflow as tf
from tensorflow import keras
from tensorflow.keras.models import Sequential
from tensorflow.keras.layers import Dense, Flatten
import matplotlib.pyplot as plt
from sklearn.metrics import confusion_matrix
from sklearn.metrics import ConfusionMatrixDisplay
import numpy as np

fashion_mnist = keras.datasets.fashion_mnist

#Load data and normalize
#train = (60000, 28, 28), test = (10000, 28, 28)
(x_train, y_train), (x_test, y_test) = fashion_mnist.load_data()
#normalize the data samples to numbers in [0, 1]
x_train, x_test = x_train / 255.0, x_test / 255.0

#Display one image from each class in grayscale
test_add = []
i = 0
num_count = 0
while num_count < 10:
    flag = 0
    for num in test_add:
        if y_test[i] == num:
            flag = 1
            break
    if flag == 0:
        plt.imshow(x_test[i, :, :], cmap='gray', vmin=0, vmax=1) #only displays 1 image (first one of set)
        s = "Class Label: " + str(y_test[i])
        plt.text(10, -2, s, bbox=dict(fill=False, edgecolor='black', linewidth=2)) #add text to display class label of image
        plt.show()
        test_add.append(y_test[i])
        num_count += 1
    i = i + 1
print(test_add)

#Create Model
model = Sequential()
model.add(Flatten()) #Flatten inputs before running NN
model.add(Dense(512, activation='relu')) #Hidden layer
model.add(Dense(10, activation='softmax')) #Output layer

#Compile model
model.compile(loss='sparse_categorical_crossentropy', optimizer='adam', metrics=['accuracy'])

#Fit model to the data
model.fit(x_train, y_train, epochs=5, verbose=2) #default batch size = 32

#Predictions - evaluating model
loss_test, acc_test = model.evaluate(x_test, y_test)
print("Accuracy Rate = ", acc_test)
print("Loss = ", loss_test)

#Confusion matrix
predict_y = model.predict_classes(x_test)
CM = confusion_matrix(y_test, predict_y)
fig, ax = plt.subplots(figsize=(10, 10))
plt.rcParams.update({'font.size': 12})
disp = ConfusionMatrixDisplay(confusion_matrix=CM)
disp = disp.plot()
plt.show()

#Calculates the number of parameters in neural network model - num of weight elements including bias terms
flattened_input = 28 * 28 #since each image is 28x28 = 784
hidden_layer = (flattened_input + 1) * 512 #1 is added for the bias
output_layer = (512 + 1) * 10 #1 is added for the bias
total_weights = hidden_layer + output_layer 
print()
print("Total number of parameters (weights with bias) in model = ", total_weights)
print()
model.summary() #To check answers

#Calculates the number of multiplications required to generate hidden and output layer
#Hidden layer number of multiplications = (sample dimensions + bias) * (output dimension of hidden layer)
#(28*28 + 1) * 512
hidden_layer_mult = (28 * 28 + 1) * 512
print("Number of multiplications for hidden layer = ", hidden_layer_mult)
#Output layer number of multiplications = (output dimension of hidden layer (input to this layer) + bias) * (output dimension of output layer)
#(512*1 + 1) * 10
output_layer_mult = (512 * 1 + 1) * 10
print("Number of multiplications for output layer = ", output_layer_mult)
print()
total_mult = hidden_layer_mult + output_layer_mult
print("Total number of multiplications to train model = ", total_mult)