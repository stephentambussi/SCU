#Stephen Tambussi - COEN140 - Lab4
#Linear Regression with Gradient Descent - Problem1
import numpy as np 
import pandas as pd 
import matplotlib.pyplot as plt
import tensorflow.compat.v1 as tf 
tf.disable_v2_behavior()

df_train = pd.read_csv("C:/Users/steve/Desktop/COEN140/Lab3/crime-train.csv")
df_train_np = pd.DataFrame(df_train).to_numpy()
df_test = pd.read_csv("C:/Users/steve/Desktop/COEN140/Lab3/crime-test.csv")
df_test_np = pd.DataFrame(df_test).to_numpy()

# =================== Data preparation =====================
#training data preparation
print("Training Matrix w/o Modification: ")
print(df_train_np)
#N = total number of samples(rows); M = number of features/attributes(columns)
N_1, M_1 = df_train_np.shape
print("Number of samples(rows): %d"  %N_1)
print("Number of features/attributes(columns): %d" %M_1)
train_target_val = np.delete(df_train_np, slice(1, 96), 1) #extracts first column of target values
df_train_np = np.delete(df_train_np, 0, 1) #removes first column of target values
print()
print("Train Matrix w/o Bias:")
print(df_train_np)
print()
print("Train target vector: ")
print(train_target_val)
#Each row is one data sample
train_data_plus_bias = np.c_[np.ones((N_1, 1)), df_train_np] #adds bias 
print()
print("Train Matrix w/ Bias: ")
print(train_data_plus_bias)

print()
#testing data preparation
print("Testing Matrix w/o Modification: ")
print(df_test_np)
#N = total number of samples(rows); M = number of features/attributes(columns)
N_2, M_2 = df_test_np.shape
print("Number of samples(rows): %d"  %N_2)
print("Number of features/attributes(columns): %d" %M_2)
test_target_val = np.delete(df_test_np, slice(1, 96), 1) #extracts first column of target values
df_test_np = np.delete(df_test_np, 0, 1) #removes first column of target values
print()
print("Test Matrix w/o Bias:")
print(df_test_np)
print()
print("Test target vector: ")
print(test_target_val)
test_data_plus_bias = np.c_[np.ones((N_2, 1)), df_test_np] #adds bias
print()
print("Test Matrix w/ Bias: ")
print(test_data_plus_bias)

# =================== Gradient Descent =====================
maxIter = 10000 #max iterations
learning_rate = 1e-5 #eta
epsilon = 1e-5 #threshold for stopping criterion
w = np.zeros((M_1, 1), dtype=np.float64) #w^t
w_prev = np.zeros((M_1, 1), dtype=np.float64) #to hold previous weight values for checking stopping criterion
E = np.zeros(maxIter+1) #error function results array initialization
#print(w)
end_iteration = 0 #variable to hold iteration end

print()
#Ntrain = number of training samples(rows)
Ntrain=train_data_plus_bias.shape[0]
#Ntest = number of test samples(rows)
Ntest=test_data_plus_bias.shape[0]
print("Ntrain = %d" %Ntrain)
print("Ntest = %d" %Ntest)


#Matrix computations
#train_data_plus_bias = X_train
#test_data_plus_bias = X_test
XT = np.transpose(train_data_plus_bias) #X^T
XTX = np.matmul(XT, train_data_plus_bias)
XTt = np.matmul(XT, train_target_val)

#Initial prediction
y = np.matmul(train_data_plus_bias, w)
#Initial error function value
E[0] = np.linalg.norm(y - train_target_val)**2/2

#Training model
for k in range(1, maxIter+1):
    grad = np.matmul(XTX, w) - XTt #update gradient
    w_prev = w
    w = w - learning_rate * grad #update weights
    y = np.matmul(train_data_plus_bias, w) #update prediction
    E[k] = np.linalg.norm(y - train_target_val)**2/2 #update error function value
    end_iteration = k
    #check stopping criterion
    #Add other stopping criterion 
    #if np.abs(E[k] - E[k-1]) < epsilon:
    if max(np.abs(w - w_prev)) < epsilon:
        end_iteration = k
        break

print()
print("Results after trained model with gradient descent")
print("=================================================")

print()
print("Iteration that algorithm exits: %d"  %end_iteration)

print()
#MSE calculation for training data
MSE_train = np.divide(np.matmul(np.transpose(y - train_target_val), y - train_target_val), Ntrain)
print("MSE of train: ")
print(MSE_train)

#Runs testing data through trained model then calculates MSE
y_test = np.matmul(test_data_plus_bias, w) #gets prediction for testing data with trained weights
MSE_test = np.divide(np.matmul(np.transpose(y_test - test_target_val), y_test - test_target_val), Ntest)
print("MSE of test: ")
print(MSE_test)

print()
#prints values of trained weights
print("Trained weight vector (optimal weights): ")
print(w)

print()
#prints predicted crime rates of test samples
print("Predicted crime rate of testing samples: ")
print(y_test)

E = np.resize(E, end_iteration+1) #resize Error function array to remove extra zeroes
iterations = np.zeros(end_iteration+1)
for i in range(end_iteration+1):
    iterations[i] = i
#plotting error function as a function of iteration number
fig, ax = plt.subplots()
ax.plot(iterations, E, 'r-', label="Error Function", linewidth=2)
plt.xlabel('Iteration Number')
plt.ylabel('Error function value', color="blue")
plt.grid(True)
plt.show()

