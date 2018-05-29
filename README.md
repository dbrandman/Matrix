# Matrix
A straightforward Matrix library written in C


This is `Matrix`, a rather lightweight matrix library. This is a series of functions that makes it pretty easy to perform simple matrix operations.

How it works
==============

The data used in Matrix works exclusively with floats. Suppose you have a 2x2 matrix, with values: 1.0, 2.0, 3.0, and 4.0, at the (1,1), (2,1), (2,1), and (2,2) positions, respectively (row, column). One would begin as follows:

```C
float myData[4] = {1.0, 2.0, 3.0, 4.0};
Matrix A = {0};
CreateMatrix(&A, 2, 2, myData);
```

The Matrix A now contains the row and column information needed to be able to perform matrix operations. Note, the system is designed such that the data lives in the space where the matrix will be used. There is *no* dynamic matrix allocation as part of this code. This is a deliberate design choice, since the library is designed to be implemented in a real-time embedded system. One could have certainly made this much more cleverer by taking care of the memory allocation, but that's for another time. Also, cache-misses are not optimized using clever looping techniques; best to use this library with small matrices. Perhaps the nicest thing about this library is that there's a tool for slicing. 

Some notes about Matrix
=======================

1. The code works with floats
2. The code works with 2D matrices
3. The code uses (row, column) notation
4. The user is reponsible for ensuring the memory allocation is appropriate
   When creating new matrices.
5. Most Matrix library functions return 0 when everything is OK, and then
   return a negative number if there was some kind of problem. Usually
   this is related to dimension mismatch. 

Applying Matlab notation to this library.
=========================

Suppose we had the following notation:

```Matlab
	A = [1, 2; 3, 4]; 	% Declare A
	A = A + 1; 			% Add one to every element to make A
	B = A * A; 			% Multiply A and A

```

This would be rewritten in the Matrix library as follows:

```C
float addOne(float val) {
	return val + 1;
}

void main()
{

	float myData[4] = {1.0, 3.0, 2.0, 4.0}; // Note number order
	float myNewData[4];
	Matrix A = {0}, B = {0};
	CreateMatrix(&A, 2, 2, myData); // Declare A
	CreateMatrix(&B, 2, 2, myNewData); // Declare B
 	ApplyFunctionSingle(&A, addOne); // Add one to every element to make A
	MultiplyMatrix(&C, &A, &A); // Multiply A and B
}
```
