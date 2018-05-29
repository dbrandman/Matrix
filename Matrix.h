/**
@file
@brief A rather lightweight and simple matrix library
@authors David Brandman

This is `Matrix`, a rather lightweight matrix library. This is a series of 
functions that makes it pretty easy to perform simple matrix operations.

How it works
==============

The data used in Matrix works exclusively with floats. Suppose you have
a 2x2 matrix, with values: 1.0, 2.0, 3.0, and 4.0, at the (1,1), (2,1),
(2,1), and (2,2) positions, respectively (row, column). One would begin
as follows:

```
float myData[4] = {1.0, 2.0, 3.0, 4.0};
Matrix A = {0};
CreateMatrix(&A, 2, 2, myData);
```
The Matrix A now contains the row and column information needed to be
able to perform matrix operations. Note, the system is designed such
that the data lives in the space where the matrix will be used. There
is *no* dynamic matrix allocation as part of this code. This is a deliberate
design choice, since the library is designed to be implemented in a RTOS
situation. One could have certainly made this much more cleverer by
taking care of the memory allocation, but that's for another time.

Some notes about Matrix
=======================

1. The code works *only* with floats
2. The code works *only* with 2D matrices
3. The code uses (row, column) notation
4. The user is reponsible for ensuring the memory allocation is appropriate
   When creating new matrices.
5. Most Matrix library functions return 0 when everything is OK, and then
   return a negative number if there was some kind of problem. Usually
   this is related to dimension mismatch. 



Applying Matlab notation to this library.
=========================

Suppose we had the following notation:

```
	A = [1, 2; 3, 4]; 	% Declare A
	A = A + 1; 			% Add one to every element to make A
	B = A * A; 			% Multiply A and A

```

This would be rewritten in the Matrix library as follows:

```
float addOne(float val)
{
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
Yes! I know! This looks cumbersome. But C wasn't designed
for making things look pretty. If you'd like that, use Matlab or Julia.

Again, the point of this library is to facilitate 
book-keeping for RTOS system where you know the dimensions
of things ahead of time. 
*/

//---------------------------------------------------------------
// 	The Matrix Structure
//---------------------------------------------------------------


/**
@brief The Matrix structure

A Matrix structure is a simple bookeeping device that allows the
user to perform operations. 

	1. rows --> Number of rows
	2. columns --> Number of columns
	3. numel --> Number of elements (rows * columns), computed
	   when the Matrix is declared
	4. *values --> pointer to the data 
*/
#pragma once

typedef struct
{
    int rows, columns;      
    int numel; 			   
    float *values;        

} Matrix;

//---------------------------------------------------------------
// 	Creating and accessing a Matrix
//---------------------------------------------------------------


/**
* @brief Create a Matrix by specifying a new Matrix structure, dimensions and data
*/
int      CreateMatrix(Matrix *, int, int, float *);

/**
@brief Convert the (row, column) notation to the position in the *float array
*/
int      Sub2Ind(Matrix *, int , int );

/**
@brief Copy a subsample of elements into a new matrix

This function takes the integer coordinates of the original matrix 
and then copies these entries into a new matrix. You need to specify
an array of indexes, and also how many there are.
*/
int      Subsample(Matrix *, Matrix *, int *, int);

/** @brief Change the number of rows and columns in the matrix */
int      ResizeMatrix(Matrix *, int , int );



//---------------------------------------------------------------
// 	Functions to print Matrix contents. 
//---------------------------------------------------------------

/**
@brief Print the matrix to the screen

This is a rather useful function that automagically formats the matrix
using tabs, and ensures that everything looks elegant. 
*/
void     PrintMatrix(Matrix *);

/**
@brief Print the dimensions of the matrix 
*/

void 	 PrintMatrixDimensions(Matrix *A);


//---------------------------------------------------------------
// 	Matrix Arithmetic functions
//---------------------------------------------------------------

/**
@brief Perform matrix multiplication
*/

int      MultiplyMatrix(Matrix *, Matrix *, Matrix *);

/**
@brief Perform element-wise function

This function applies a function to each element in the Matrix.
For instance, Suppose you would like to take the sqrt of each
element in a matrix. You would do:

```
Matrix A = {0};
float myData[4] = {1.0, 2.0, 3.0, 4.0};
CreateMatrix(&A, 2, 2, myData);
ApplyFunctionSingle(&A, sqrt);
```
*/
int 	 ApplyFunctionSingle(Matrix *, float (*f)(float));

/**
@brief Apply pairwise element operations to two matrices

Suppose you have Matrices A and B, and you would ike to perform an
operation to A, and B to each element, like A + B, A .* B, etc.
You use ApplyFunctionFloat, specifying A and B and the function that
takes as inputs two floats, and then it'll make it happen!
*/
int 	 ApplyFunctionFloat(Matrix *, Matrix *, float (*f)(float, float));


/** @brief Compute the number of elements predicted in a Matrix Multiplcation */
int      Numel(Matrix *, Matrix *);

//---------------------------------------------------------------
// 	Helper functions for basic arithmetic between two matrices
//---------------------------------------------------------------

/** @brief Add two floats */
float add(float a, float b);

/** @brief Subtract two floats */
float subtract(float a, float b);

/** @brief Divide two floats */
float divide(float a, float b);

/** @brief multiply two floats */
float multiply(float a, float b);

//float GetAngle(float x1, float y1, float x2, float y2);
//float GetDistanceSquared(float x1, float y1, float x2, float y2);
