import numpy as np
from scipy import linalg as la

print("Matrix Operations Demo\n")

print("Matrix A")
A = np.array([[1, 2], [3, 4], [5, 6]])
print(A)
input("hit enter\n")

print("Row vector v")
v = np.array([1, 2, 3])
print(v)
input("hit enter\n")

print("Row vector v times matrix A")
v = v @ A
print(v)
input("hit enter\n")

print("Element A_ij with i=3, j=1 of A")
x = A[3-1, 1-1]  # Indices starting at Zero!!!
print(x)
input("hit enter\n")

print("B as the Transpose of A")
B = A.T
print(B)
input("hit enter\n")

print("C from Matrix Multiplication of A and B")
C = A.dot(B)  # A*B does not work as matrix multiplication!!!
print(C)
input("hit enter\n")

print("C from Matrix Multiplication of A and B (with @ as mul-symbol)")
C = A @ B  # preferred option for denoting matrix multiplication
print(C)
input("hit enter\n")

print("C from Matrix Multiplication of A and B (with dot as fct)")
C = np.dot(A, B)  # A*B does not work as matrix multiplication!!!
print(C)
input("hit enter\n")

print("C from Matrix Multiplication of A and B using matmul")
C = np.matmul(A, B)  # works for 2D matrizes
print(C)
input("hit enter\n")


print("Adding C to itself")
D = C + C
print(D)
input("hit enter\n")

print("D as Matrix Inverse of C")
D = la.inv(C)
print(D)
input("hit enter\n")

print("Row vector v1")
v1 = np.array([[1, 2, 3]])
print(v1)
input("hit enter\n")

print("Column vector v2")
v2 = np.array([[1], [2], [3]])
print(v2)
input("hit enter\n")

print("Column vector v2 as Transpose of v1")
v2 = v1.T
print(v2)
input("hit enter\n")

print("E as Matrix Vector Product of C and v2")
E = C.dot(v2)
print(E)
input("hit enter\n")

print("The determinant of C")
d = la.det(C)  # note: C must be square
print(d)
input("hit enter\n")

#print("The determinant of A")
# d = la.det(A) # note: A is not square, hence we get an error if we try this
