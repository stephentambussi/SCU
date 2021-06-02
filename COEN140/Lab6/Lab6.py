#Stephen Tambussi - COEN140 - Lab6
#Logistic Regression
import tensorflow as tf
mnist = tf.keras.datasets.mnist
import numpy as np
import matplotlib.pyplot as plt 
from sklearn.metrics import confusion_matrix
from sklearn.metrics import plot_confusion_matrix
from sklearn.linear_model import LogisticRegression 
from sklearn.model_selection import train_test_split

#data preparation
(x_traino, y_train), (x_testo, y_test) = mnist.load_data()
#converting the 28x28 images to vectors
x_train = np.reshape(x_traino, (60000, 28*28)) #60,000 rows (samples); 28*28 columns (data points)
x_test = np.reshape(x_testo, (10000, 28*28)) #10,000 rows (samples); 28*28 columns (data points)
#normalize the pixel values to be real numbers in [0, 1] --optional
x_train, x_test = x_train / 255.0, x_test / 255.0

print(y_test)
test_add = []
#plot 10 grayscale images from test set (each with different class label) 
i = 0
num_count = 0
while num_count < 10:
    flag = 0
    for num in test_add:
        if y_test[i] == num:
            flag = 1
            break
    if flag == 0:
        plt.imshow(x_testo[i, :, :], cmap='gray', vmin=0, vmax=255) #only displays 1 image (first one of set)
        s = "Class Label: " + str(y_test[i])
        plt.text(10, -2, s, bbox=dict(fill=False, edgecolor='black', linewidth=2)) #add text to display class label of image
        plt.show()
        test_add.append(y_test[i])
        num_count += 1
    i = i + 1
print(test_add)

#Train logistic regression model
log_reg = LogisticRegression(multi_class='multinomial', max_iter=100, verbose=2)
#log_reg = LogisticRegression(multi_class='multinomial', max_iter=100, penalty='l2', fit_intercept=True)
log_reg.fit(x_train, y_train)

#Test trained model
#get predicted probabilities
y_predicted = log_reg.predict_proba(x_test)

#get predicted class labels
k_predicted = log_reg.predict(x_test)

#Calculate classification accuracy rate of test set
accuracy = log_reg.score(x_test, y_test)
S = "Classification accuracy of model on testing set: " + str(accuracy)
print(S)

#Confusion matrix
CM = confusion_matrix(y_test, k_predicted)
fig, ax = plt.subplots(figsize=(10, 10))
plt.rcParams.update({'font.size': 12})
plot_confusion_matrix(log_reg, x_test, y_test, values_format='.5g')
plt.show()
