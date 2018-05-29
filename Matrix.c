#include "Matrix.h"
#include <string.h>
#include <stdio.h>
#include <math.h>

// static int Factorial(int);

//------------------------------ CreateMatrix ------------------------------
/* Create a matrix.  */

int CreateMatrix(Matrix *M, int rows, int columns, float *values)
{
	//Let's make sure that the dimensions make sense!
	if (rows <=0 || columns <= 0)
		return 1;

	M->rows    				= rows;
	M->columns 				= columns;
	M->numel   				= rows * columns;	
	M->values  				= values;

	return 0;
}

//------------------------------ MultiplyMatrix ------------------------------
/* Multiply two matrices! Get angry if the dimensions don't match! 
	0: Multiplication successful
	1: Dimension mismatch

*/

int MultiplyMatrix(Matrix *C, Matrix *A, Matrix *B)
{
	// Ensure that the dimensions match!
	if ((A->columns != B->rows) || 
		(C->rows    != A->rows) || 
		(C->columns != B->columns))
		return -1;

	memset(C->values, 0, sizeof(float) * C->numel);

	for (int i = 0; i < A->rows; i++)
        for (int j = 0; j < B->columns; j++)
            for (int k = 0; k < B->rows; k++)
				C->values[i + (A->rows)*j] += A->values[i + (A->rows)*k] * B->values[k + (B->rows)*j];

	return 0;
}



//------------------------------ Sub2Ind ------------------------------
/* This is a helper function to convert from 1D indexing to 2D indexing 
Example: I want to access the value of A[25,10], so I use Sub2Ind(A,25,10)
and this will return the linear index value */

int Sub2Ind(Matrix *A, int row, int col)
{
	return row + (A->rows)*col;
}




//------------------------------ Splice ------------------------------
/* Subsample from Matrix A at particular indexes and store them into  C */

int Subsample(Matrix *C, Matrix *A, int *ind, int n)
{
	if (C->numel != n)
		return -1;

	for (int i = 0; i < n; i++)
		C->values[i] = A->values[ind[i]];

	return 0;

}

//------------------------------ PrintMatrix ------------------------------
/* Simple function to print a matrix to the screen */

void PrintMatrix(Matrix *A)
{
	for (int i = 0; i < A->rows; i++)
	{
		for (int j = 0; j < A->columns; j++)
			printf("%10.4f   ", A->values[Sub2Ind(A,i,j)]);
		printf("\n");
	}
}


//------------------------------ PrintMatrixDimensions ------------------------------
/* Simple function to print a matrix dimensions to the screen */

void PrintMatrixDimensions(Matrix *A)
{
	printf("%d x %d\n", A->rows, A->columns);
}






int ApplyFunctionSingle(Matrix *A, float (*f)(float))
//------------------------------ PairwiseOperation ------------------------------
/* Perform operations on each element of a matrix! 
   This function always succeeds... Right? */
{
	for (int i = 0; i < A->numel; i++)
		A->values[i] = f(A->values[i]);

	return 0;

}

int ApplyFunctionFloat(Matrix *A, Matrix *B, float(*f)(float, float))
/* Apply pairwise operations to each element of both arrays! */
{
	if ((A->columns != B->columns) ||
		(A->rows    != A->rows))
		return -1;

	for (int i = 0; i < A->numel; i++)
		A->values[i] = f(A->values[i], B->values[i]);

	return 0;

}



//------------------------------ ResizeMatrix ------------------------------
/* Resizes the matrix to different dimensions. 
	0: Everything OK
	1: columns and rows don't match the new dimensions
*/


int ResizeMatrix(Matrix *A, int rows, int columns)
{
	if (A->numel != rows * columns)
		return -1;	

	A->rows    = rows;
	A->columns = columns;
	return 0;
}

//------------------------------ Math functions ------------------------------

float GetAngle(float x1, float y1, float x2, float y2)
{
	float dotProduct = x1*x2 + y1*y2;
	float magX = sqrt(x1*x1 + y1*y1);
	float magY = sqrt(x2*x2 + y2*y2);
	return acos(dotProduct/(magX*magY));
	//return atan2(fabs(x1*y2 - y1*x2), x1*x2 + y1*y2); 
}

float GetDistanceSquared(float x1, float y1, float x2, float y2)
{
	return (x1-x2)*(x1-x2) + (y1-y2)*(y1-y2);
}

//------------------------------ Helper function ------------------------------
/* compute the Factorial of a number */



// static int Factorial (int n)
// {
// 	int fact = 1;
//   	for (int c = 1; c <= n; c++)
//     	fact = fact * c;
//     return fact;
// }

int Numel(Matrix *A, Matrix *B)
{
	return A->rows * B->columns;
}
float add(float a, float b)
{
	return a + b;
}
float subtract(float a, float b)
{
	return a - b;
}
float divide(float a, float b)
{
	return a / b;
}
float multiply(float a, float b)
{
	return a * b;
}

/*
void ClearMatrix(Matrix *M)
{
	if (M->hasAllocatedMemory > 0)
		free(M->values);
	M->rows    = 0;
	M->columns = 0;
	M->numel   = 0;
	M->hasAllocatedMemory = 0;
}

void floatElementOperation(Matrix *C, float (*f)(float, float), float val, Matrix *A)
//------------------------------ PairwiseOperation ------------------------------
Perform operations on each element of a matrix! 
{

	C->rows    = A->rows;
	C->columns = A->columns;
	C->numel   = A->numel;
	C->values  = malloc(sizeof(float) * (C->numel));

	for (int i = 0; i < A->numel; i++)
		C->values[i] = f(A->values[i], val);
}


//------------------------------ PairwiseOperation ------------------------------
 Perform pairwise operations on matrices! 

int MatrixArithmetic(Matrix *C, MatrixOperation op, Matrix *A, Matrix *B)
{
	// Ensure that the dimensions match!
	if ((A->columns != B->columns) || 
		(A->rows    != B->rows)    ||
		(C->rows    != A->rows)    ||
		(C->columns != B->columns))
		return 1;

	switch(op)
	{
		case ADD : 	
			for (int i = 0; i < A->numel; i++)
				C->values[i] = A->values[i] + B->values[i];
			break;

		case SUBTRACT : 	
			for (int i = 0; i < A->numel; i++)
				C->values[i] = A->values[i] - B->values[i];
			break;

		case MULTIPLY : 	
			for (int i = 0; i < A->numel; i++)
				C->values[i] = A->values[i] * B->values[i];
			break;

		case DIVIDE : 	
			for (int i = 0; i < A->numel; i++)
				C->values[i] = A->values[i] / B->values[i];
			break;

		default:
			return 2;
			break;
	}

	return 0;

}


//------------------------------ PairwiseDistance ------------------------------
 Get the pairwise distance between elements in a matrix! 

void PairwiseDistance(Matrix *C, Matrix *A)
{

	 int n = A->rows;
	 int k = 2;
	 int nCombinations = Factorial(n) / (Factorial(n-k) * Factorial(k));

	 int numel = n * n;

	 float values[nCombinations];
	 
	 int indCounter = 0;
	 float val = 0;

	 // This code produces n Choose 2 combinations of pairwise distances
	 // into a pre-allocated array of size nCombinations

	 for(int i = 0; i < n; i++)
	 {
	 	for(int j = i+1; j < n; j++)
	 	{
	 		for(int k = 0; k < A->columns; k++)
	 		{
	 			val = A->values[Sub2Ind(A,i,k)] - A->values[Sub2Ind(A,j,k)];
	 			val *= val;
	 			values[indCounter] += val;
	 		}
	 		values[indCounter] = sqrt(values[indCounter]);
	 		indCounter++;
	 	}
	 }

	 // This code converts n choose 2 combinations to 
	 // a square matrix of entries
	 // We're not going to traverse every value, so we're going to use 
	 // calloc() instead of malloc()
	 float *squareMatrixValues = calloc(sizeof(float) * numel, sizeof(float));

	 indCounter = 0;
	 for (int i = 0; i < n; i++)
	 	for (int j = i+1; j < n; j++)
	 	{
	 		squareMatrixValues[Sub2Ind(A,i,j)] = values[indCounter];
	 		squareMatrixValues[Sub2Ind(A,j,i)] = values[indCounter];
	 		indCounter++;
	 	}
	
	// Was this created inside PairwiseDistance or MatrixMultiply?
	// If so, memory was dynamically created and needs to be freed
	if(C->hasAllocatedMemory == 1)
		free(C->values);

	//Finally, create our matrix!
	C->rows    			  = n;
	C->columns 			  = n;
	C->numel   			  = numel;	
	C->values  			  = squareMatrixValues;
	C->hasAllocatedMemory = 1;


	// Create our matrix!
	// CreateMatrix(C, squareMatrixValues, numel, n, n);
	


	 // C->numel   = n * n;
	 // C->rows    = n;
	 // C->columns = n;
	 // C->values  = malloc(sizeof(float) * C->numel);

	 // for (int i = 0; i < nCombinations; i++)
	 // 	C->values[i] = values[i];


}

*/


