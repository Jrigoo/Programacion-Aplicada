# include <stdio.h>
# include<stdlib.h>
# include <string.h>
# include<math.h>

void printMatrix(double matrix[][20],int rows,int columns){
    for (int i = 0; i < rows; i++){
        for (int j = 0; j < columns; j++){
            printf("%f ",matrix[i][j]);
        }
        printf("\n");         
    }
}

double **multiply(double mat1[][20], double mat2[][20],int row1,int row2,int col2){
    double **matrix;
    matrix = malloc(sizeof(double) * row1);
     
    for(int i = 0; i < row1; i++) {
        matrix[i] = malloc(sizeof(double) * col2);
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

double **transpose(double mat1[][20],int rows,int columns){
    double **matrix;
    matrix = malloc(sizeof(double) * columns);
     
    for(int i = 0; i < rows; i++) {
        matrix[i] = malloc(sizeof(double) * rows);
    }
    for (int i = 0; i < rows; ++i){ 
        for (int j = 0; j < columns; ++j) { 
            matrix[j][i] = mat1[i][j];
        }
    }
    return matrix;
}

double **inverse(double matrix[][20],int order){
    double adj[20][20],ratio;
    double **XInv;

    XInv = malloc(sizeof(double) * order);
    for(int i = 0; i < order; i++) {
        XInv[i] = malloc(sizeof(double) * order);
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
    double ratio;
    int grado = 4;
	int order = grado + 1;
    double x[8] = {1,2,3,4,5,6,7,8};
    double Y[8][1] = {5.74, 66.06, 301.46000000000004, 903.9399999999999, 2137.5, 4338.139999999999, 7913.86, 13344.66};
    size_t n = sizeof(x) / sizeof(double);

    double X[20][20];
    double XT[20][20];
    double XRes[20][20];
    double XYRes[20][20];
    double adj[20][20];
    double XInv[20][20];
    double beta[20][20];

    double **XTP;
    double **XPRes;
    double **XYPRes;
    double **XPInv;
    double **bp;

    printf("-------------------------------------------\n");
    printf("Matriz X\n");
    for (int i = 0; i < n; i++){
        for (int j = 0; j < order; j++){
            X[i][j] = powf(x[i],j);
        }
    }
    printMatrix(X,n,order);
    printf("-------------------------------------------\n");

    printf("Transponemos la matriz X\n");
    XTP = transpose(X,n,order);
    for (int i = 0; i < order; i++) {
        for (int j = 0; j < n; j++) {
            XT[i][j] = XTP[i][j];
        }
    } 
    printMatrix(XT,order,n);
    printf("-------------------------------------------\n");

    printf("Multiplicamos XT*X ->>> XRes\n");
    XPRes = multiply(XT,X,order,n,order); //m1,m2,fila1,fila2,columna2
    for (int i = 0; i < order; i++) {
        for (int j = 0; j < order; j++) {
            XRes[i][j] = XPRes[i][j];
        }
    } 
    printMatrix(XRes,order,order);
    printf("-------------------------------------------\n");;

    printf("Multiplicamos XT*Y ->>> XYRes\n");
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
    printMatrix(XInv,order,order);
    printf("-------------------------------------------\n");

    printf("Obtenemos coeficientes beta\n");
    bp = multiply(XInv,XYRes,5,5,1);
    for (int i = 0; i < order; i++) {
        for (int j = 0; j < 1; j++) {
            beta[i][j] = bp[i][j];
        }
    } 
    printMatrix(beta,order,1);
    printf("------------------------------\n");

    printf("Nuestra funcion termina siendo: f(x) = %.2f + (%.2fx) + (%.2fx^2) + (%.2fx^3) + (%.2fx^4)",bp[0][0],bp[1][0],bp[2][0],bp[3][0],bp[4][0]);
    
    return 0;
}
