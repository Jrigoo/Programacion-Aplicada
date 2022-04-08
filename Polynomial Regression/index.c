# include <stdio.h>
# include<stdlib.h>
# include <string.h>
# include<math.h>

void printMatrix(float matrix[][20],int rows,int columns){
    for (int i = 0; i < rows; i++){
        for (int j = 0; j < columns; j++){
            printf("%.2f ",matrix[i][j]);
        }
        printf("\n");         
    }
}

float **multiply(float mat1[][20], float mat2[][20],int row1,int row2,int col2){
    float **matrix;
    matrix = malloc(sizeof(float) * row1);
     
    for(int i = 0; i < row1; i++) {
        matrix[i] = malloc(sizeof(float) * col2);
    }

	for (int i = 0; i < row1; i++) {
		for (int j = 0; j < col2; j++) {
			matrix[i][j] = 0;
			for (int k = 0; k < row2; k++) {
				matrix[i][j] += mat1[i][k] * mat2[k][j];
			}
		}
	} 
    return matrix;
}

float **transpose(float mat1[][20],int rows,int columns){
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

float **inverse(float matrix[][20],int order){
    float adj[20][20],ratio;
    float **XInv;

    XInv = malloc(sizeof(float) * order);
    for(int i = 0; i < order; i++) {
        XInv[i] = malloc(sizeof(float) * order);
    }
    
	for(int i=0;i<order;i++){
		for(int j=0;j<order;j++){
		    adj[i][j] = matrix[i][j];
		}
	}
	for(int i=0;i<order;i++){
		for(int j=0;j<order;j++){
			if(i==j){
				adj[i][j+order] = 1;
			}
			else{
				adj[i][j+order] = 0;
			}
		}
	}
	for(int i=0;i<order;i++){
		if(adj[i][i] == 0.0){
			printf("Mathematical Error!");
			return 0;
		}
		for(int j=0;j<order;j++){
			if(i!=j){
				ratio = adj[j][i]/adj[i][i];
				for(int k=1;k<2*order;k++)
				{
					adj[j][k] = adj[j][k] - ratio*adj[i][k];
				}
			}
		}
	}
	for(int i=0;i<order;i++){
		for(int j=order;j<2*order;j++){
		adj[i][j] = adj[i][j]/adj[i][i];
		}
	}
	for(int i=0;i<order;i++){
        int c = 0;
		for(int j=order;j<2*order;j++){
            XInv[i][c] = adj[i][j];
            c++;
		}
	}
    return XInv;
}

int main(){
    /* Declaramos nuestra variable independiente y puntos que se nos brindó */
    float ratio;
    int grado = 3;
	int order = grado + 1;
    float x[8] = {1,2,3,4,5,6,7,8};
    float Y[8][1] = {2.74, 18.06, 58.46, 135.94, 262.5, 450.14, 710.86, 1056.66};
    size_t n = sizeof(x) / sizeof(float);

    float X[20][20];
    float XT[20][20];
    float XRes[20][20];
    float XYRes[20][20];
    float adj[20][20];
    float XInv[20][20];
    float beta[20][20];

    float **XTP;
    float **XPRes;
    float **XYPRes;
    float **XPInv;
    float **bp;

    printf("-------------------------------------------\n");
    printf("Matriz X\n");
    for (int i = 0; i < n; i++){
        for (int j = 0; j < order; j++){
            X[i][j] = powf(x[i],j);
        }
    }
    printMatrix(X,n,order);
    printf("-------------------------------------------\n");

    printf("Transponemos la matriz X --- 4 X 8\n");
    XTP = transpose(X,n,order);
    for (int i = 0; i < order; i++) {
        for (int j = 0; j < n; j++) {
            XT[i][j] = XTP[i][j];
        }
    } 
    printMatrix(XT,order,n);
    printf("-------------------------------------------\n");

    printf("Multiplicamos XT*X ->>> XRes (4x8)*(8x4) -> 4x4\n");
    XPRes = multiply(XT,X,order,n,order); //m1,m2,fila1,fila2,columna2
    for (int i = 0; i < order; i++) {
        for (int j = 0; j < order; j++) {
            XRes[i][j] = XPRes[i][j];
        }
    } 
    printMatrix(XRes,order,order);
    printf("-------------------------------------------\n");;

    printf("Multiplicamos XT*Y (4x8)*(8x1) -> 4x1 ->>> XYRes\n");
    for (int i = 0; i < order; i++) {
		for (int j = 0; j < 1; j++) {
			XYRes[i][j] = 0;
			for (int k = 0; k < n; k++) {
				XYRes[i][j] += XT[i][k] * Y[k][j];
			}
		}
	} 
    printMatrix(XYRes,order,1);
    printf("-------------------------------------------\n");

    printf("Invertimos XYRes -> XInv\n");
    XPInv = inverse(XRes,order);
    for (int i = 0; i < order; i++) {
        for (int j = 0; j < order; j++) {
            XInv[i][j] = XPInv[i][j];
        }
    } 
    printMatrix(XInv,4,4);
    printf("-------------------------------------------\n");

    printf("Obtenemos coeficientes beta\n");
    bp = multiply(XInv,XYRes,4,4,1);
    for (int i = 0; i < order; i++) {
        for (int j = 0; j < 1; j++) {
            beta[i][j] = bp[i][j];
        }
    } 
    printMatrix(beta,order,1);
    printf("------------------------------\n");

    printf("Nuestra funcion termina siendo: f(x) = %.2f + (%.2fx) + (%.2fx^2) + (%.2fx^3)",beta[0][0],beta[1][0],beta[2][0],beta[3][0]);
    
    return 0;
}
