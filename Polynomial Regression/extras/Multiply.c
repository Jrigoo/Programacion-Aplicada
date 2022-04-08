/*
* This C program can multiply any two square or rectangular matrices.
* The below program multiplies two square matrices of size 4 * 4.
* There is also an example of a rectangular matrix for the same code (commented below).
* We can change the Matrix value with the number of rows and columns (from MACROs) for Matrix-1
* and Matrix-2 for different dimensions.
*/

/*
* Note: i- The number of columns in Matrix-1 must be equal to the number of rows in Matrix-2.
*	 ii- Output of multiplicationof Matrix-1 and Matrix-2, results with equalto the number
*		 of rows of Matrix-1 and thenumber of columns of Matrix-2 i.e. rslt[R1][C2].
*/

#include <stdio.h>
#include <stdlib.h>

// Edit MACROs here, according to your Matrix Dimensions for mat1[R1][C1] and mat2[R2][C2]
#define R1 4		 // number of rows in Matrix-1
#define C1 4		 // number of columns in Matrix-1
#define R2 4		 // number of rows in Matrix-2
#define C2 4		 // number of columns in Matrix-2


int **matrix_multi(int mat1[][C1], int mat2[][C2]){
    int **matrix;
    matrix = malloc(sizeof(int) * R1);
     
    for(int i = 0; i < R1; i++) {
        matrix[i] = malloc(sizeof(int) * C2);
    }
	for (int i = 0; i < R1; i++) {
		for (int j = 0; j < C2; j++) {
			matrix[i][j] = 0;
			for (int k = 0; k < R2; k++) {
				matrix[i][j] += mat1[i][k] * mat2[k][j];
			}
		}
	} 
    return matrix;
}

float **transpose(float mat1[][4],int rows,int columns){
    float **matrix;
    matrix = malloc(sizeof(float) * columns);
     
    for(int i = 0; i < rows; i++) {
        matrix[i] = malloc(sizeof(float) * rows);
    }
    for (int i = 0; i < rows; ++i){ //8
        for (int j = 0; j < columns; ++j) { //4
            matrix[j][i] = mat1[i][j];
        }
    }
    return matrix;
}


int main(void) {
	float mat1[8][4] = {
			{1.0, 1.0, 1.0, 1.0},
			{2.0, 2.0, 2.0, 2.0},
			{3.0, 3.0, 3.0, 3.0},
			{4.0, 4.0, 4.0, 4.0},
            {5.0, 5.0, 5.0, 5.0},
            {6.0, 6.0, 6.0, 6.0},
            {7.0, 7.0, 7.0, 7.0},
            {8.0, 8.0, 8.0, 8.0}
	};

    float **res;
	res = transpose(mat1,8,4);
    for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 8; j++) {
            printf("%f",res[i][j]);
            printf("\t");
		}
		printf("\n");
	} 
	return 0;
}


