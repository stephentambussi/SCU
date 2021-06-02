#Stephen Tambussi - COEN140 - Lab3
#Ridge Regression - Problem2b
import numpy as np 
import pandas as pd 
import tensorflow.compat.v1 as tf 
tf.disable_v2_behavior()

df_train = pd.read_csv("C:/Users/steve/Desktop/COEN140/Lab3/crime-train.csv")
df_train_np = pd.DataFrame(df_train).to_numpy()
df_test = pd.read_csv("C:/Users/steve/Desktop/COEN140/Lab3/crime-test.csv")
df_test_np = pd.DataFrame(df_test).to_numpy()

#training data preparation
print("Training Matrix w/o Modification: ")
print(df_train_np)
df_train_np = np.delete(df_train_np, slice(100, 1595), 0) #only uses the first 100 training samples
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
test_data_plus_bias = np.c_[np.ones((N_2, 1)), df_test_np]
print()
print("Test Matrix w/ Bias: ")
print(test_data_plus_bias)

print()
#Ntrain = number of training samples(rows)
Ntrain=train_data_plus_bias.shape[0]
#Ntest = number of test samples(rows)
Ntest=test_data_plus_bias.shape[0]
print("Ntrain = %d" %Ntrain)
print("Ntest = %d" %Ntest)

lbda = 100 #lambda
#create tensors
X = tf.placeholder(tf.float64, shape = (None, M_1), name = 'X') #rows as samples
t = tf.placeholder(tf.float64, shape = (None, 1), name = 't') #target values: t vector
n = tf.placeholder(tf.float64, name='n') #number of samples
XT = tf.transpose(X)

I = tf.eye(M_1, dtype=tf.float64) #identity matrix of MxM
w = tf.matmul(tf.matmul(tf.matrix_inverse(tf.math.add(tf.scalar_mul(lbda, I), tf.matmul(XT, X))), XT), t) #w = inv(lambda*I + XT*X)*XT*t


#predicted values: a column vector y=[y1, y2, ..., yn]', where yn=xn'*w
y = tf.matmul(X, w)

#mean-squared error (MSE) of the prediction
MSE = tf.div(tf.matmul(tf.transpose(y-t), y-t), n)

#train_data_plus_bias = X_train
#test_data_plus_bias = X_test
#does training and testing
with tf.Session() as sess:
    MSE_train, w_star, y_train = \
        sess.run([MSE, w, y], feed_dict={X: train_data_plus_bias, t: train_target_val, n: Ntrain})
    
    MSE_test, y_test = \
        sess.run([MSE, y], feed_dict={X: test_data_plus_bias, t: test_target_val, n: Ntest, w: w_star})

print()
print("Results")
print("===================================")
print("MSE of train: ")
print(MSE_train)
print("MSE of test: ")
print(MSE_test)
print("Optimal weight (w*): ")
print(w_star)
print("Predicted crime rate of testing samples: ")
print(y_test)
