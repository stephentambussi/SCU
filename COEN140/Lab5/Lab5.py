#Stephen Tambussi - COEN140 - Lab5
#K-Means Clustering

import numpy as np
import matplotlib.pyplot as plt
from sklearn import datasets
iris = datasets.load_iris()
print(list(iris.keys()))
print(iris.feature_names)
print(iris.target_names)
print()

X = iris.data #each row is a sample
Y = iris.target #target labels

print("Iris data matrix: ")
print(X)
print("Iris target values: ")
print(Y)

print()
#Initialize cluster centers to the first 3 data samples
m = np.zeros((3, 4))
m[0] = iris.data[0] #center for cluster 1
#m[0] = np.random.rand(4) * 5
m[1] = iris.data[1] #center for cluster 2
#m[1] = np.random.rand(4)
m[2] = iris.data[2] #center for cluster 3
#m[2] = np.random.rand(4) * 10
print("Initialized values for center 1, 2, 3:")
print(m)

K = 3 #3 clusters
epsilon = 1e-5 #threshold for stopping criterion
N = X.shape[0] #number of data samples (rows)
maxIter = 1000 #maximum iterations
r = np.zeros(N, dtype=int) #array to hold rkn values (1 if xn is assigned to cluster k) -- assignment
temp = np.zeros(3) #holds the calculated distance between centers 1, 2, 3 and data samples
J = np.zeros(maxIter) #objective function
end_iteration = 0
J[0] = 0 #temp

print()
#Model running
for i in range(0, maxIter):
    #print()
    #print("Iteration: ")
    #print(i)
    #assignment - calculate the distance for each data point X
    #predicted labels - find the nearest center (class label)
    for n in range(N): 
        for k in range(K):
            temp[k] = np.linalg.norm(m[k] - X[n])**2 #gets distance between centers and xn sample to store in temp
        #print(temp)
        r[n] = int(np.argmin(temp))  #assigns the cluster(column) that xn is closests to -- assignment
    #print(r)

    #update objective function J - for each cluster calculate the distance
    for n in range(N):
        J[i] += np.linalg.norm(m[r[n]] - X[n])**2

    #check stopping criterion - check if J from current iteration and previous iteration is below a certain value
    if np.abs(J[i - 1] - J[i]) < epsilon:
        end_iteration = i
        break
    
    #update centers, calculate the mean and update the center
    sums = np.zeros((3, 4)) #2d array to hold summed values at each index for each center
    #rows = sums of points at cluster k; columns = each data point of sum
    cnt = np.zeros(3) #holds count of samples assigned to each cluster
    for n in range(N):
        for j in range(4):
            sums[r[n]][j] += X[n][j]
        cnt[r[n]] += 1
    #print(sums)
    #print(cnt)
    #print()
    m[0] = sums[0] / cnt[0] #update center for cluster 1
    m[1] = sums[1] / cnt[1] #update center for cluster 2
    m[2] = sums[2] / cnt[2] #update center for cluster 3
    #print(m)
    #print()

print()
print(end_iteration)
print(r)

#Plot of objective function J vs iteration number
J = np.resize(J, end_iteration+1)
iterations = np.zeros(end_iteration + 1)
for i in range(end_iteration+1):
    iterations[i] = i
fig, ax = plt.subplots()
ax.plot(iterations, J, 'r-', label="Objective Function", linewidth=2)
plt.xlabel('Iteration Number')
plt.ylabel('Objective function value', color="blue")
plt.grid(True)
plt.show()
