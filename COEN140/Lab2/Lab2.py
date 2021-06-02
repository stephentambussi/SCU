#Stephen Tambussi - COEN140
import numpy as np


#Number 1
print("Problem 1")
a = np.random.rand(2, 5) #creates a 2x5 matrix of random floats between 0 and 1
print("matrix A: ")
print(a) #prints matrix
print("rank of A: ")
print(np.linalg.matrix_rank(a)) #prints the rank of a

a_t = np.transpose(a) #transposes matrix a
b = np.dot(a, a_t) #creates matrix b
print("matrix B: ")
print(b)
print("rank of B: ")
print(np.linalg.matrix_rank(b))

c = np.dot(a_t, a) #creates matrix c
print("matrix C: ")
print(c)
print("rank of C: ")
print(np.linalg.matrix_rank(c))

print()
#Number 2
print("Problem 2")
x = np.random.randint(0, 10, (3,5)) #creates a 3x5 matrix of random ints between 0 and 10
print("matrix X: ")
print(x) #prints matrix
x_t = np.transpose(x) 
a1 = np.dot(x, x_t)
print("matrix A: ")
print(a1)

w = np.random.randint(0, 10, (3, 1)) #creates a 3x1 column vector of random ints between 0 and 10
print("column vector w: ")
print(w)
aw = np.dot(a1, w)
print("dimension of Aw: ")
print(aw)

w_t = np.transpose(w) 
w_ta = np.dot(w_t, a1)
print("dimension of (w^T)A: ")
print(w_ta)

w_taw = np.dot(w_t, aw)
print("dimension of (w^T)Aw: ")
print(w_taw)

#check if xx^t is symmetric (xx^t == (xx^t)^t) -- 3x3
print("X(X^T): ")
print(a1)
xxt_t = np.transpose(a1)
print("(X(X^T))^T: ")
print(xxt_t)
#coding check
flag = 0
for i in range(3):
    for j in range(3):
        if(a1[i][j] != xxt_t[j][i]):
            print("Not symmetric")
            flag += 1
if flag == 0:
    print("X(X^T) is symmetric")

a_inv = np.linalg.inv(a1)
print("inverse of matrix A: ")
print(a_inv)
a_inv_a = np.dot(a_inv, a1)
print("(A^-1)A: ")
print(a_inv_a)
a_a_inv = np.dot(a1, a_inv)
print("A(A^-1): ")
print(a_a_inv)

print()
#Number 3
print("Problem 3")
x1 = np.random.rand(5, 1) #creates a 5x1 column vector of random floats between 0 and 1
print("column vector x: ")
print(x1)
x1_t = np.transpose(x1)
x_xt = np.dot(x1, x1_t)
print("x(x^T): ")
print(x_xt)
print("rank of x(x^T): ")
print(np.linalg.matrix_rank(x_xt))

print()
#Number 4
print("Problem 4")
i = np.identity(5) #creates a 5x5 identity matrix
print("identity matrix I: ")
print(i)