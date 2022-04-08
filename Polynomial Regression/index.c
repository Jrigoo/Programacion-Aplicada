# include <stdio.h>
# include<stdlib.h>
# include <string.h>
# include<math.h>

#define DATA "gps.csv"

void printMatrix(double matrix[][100],int rows,int columns){
    for (int i = 0; i < rows; i++){
        for (int j = 0; j < columns; j++){
            printf("%lf ",matrix[i][j]);
        }
        printf("\n");         
    }
}

void printArray(double values[],int n){
    for (int i = 0; i < n; i++){
        printf("%f",values[i]);
    }
    printf("\n");  
}

double **multiply(double mat1[][100], double mat2[][100],int row1,int row2,int col2){
    double **matrix;
    matrix = malloc(sizeof(double) * 100);
     
    for(int i = 0; i < 100; i++) {
        matrix[i] = malloc(sizeof(double) * 100);
    }

    /* Matrix resultante (row1 x col1) * (row2 x col2) -> row1 x col2*/
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

double **transpose(double mat1[][100],int rows,int columns){
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

double **inverse(double matrix[][100],int order){
    double adj[100][100],ratio;
    double **XInv;

    XInv = malloc(sizeof(double) * 100);
    for(int i = 0; i < 100; i++) {
        XInv[i] = malloc(sizeof(double) * 100);
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

double **polynomialRegression(double x[100],double Y[][100],int grado,int n){
    double ratio;
	int order = grado + 1;

    double X[100][100];
    double XT[100][100];
    double XRes[100][100];
    double XYRes[100][100];
    double adj[100][100];
    double XInv[100][100];
    double beta[100][100];

    double **XTP;
    double **XPRes;
    double **XYPRes;
    double **XPInv;
    double **bp;

    //printf("-------------------------------------------\n");
    //printf("Matriz X\n"); //n x order (46 x 6)
    for (int i = 0; i < n; i++){
        for (int j = 0; j < order; j++){
            X[i][j] = powf(x[i],j);
        }
    }
    //printMatrix(X,n,order);
    //printf("-------------------------------------------\n");
    //printf("Transponemos la matriz X\n");
    XTP = transpose(X,n,order); /* 6 x 46 */
    for (int i = 0; i < order; i++) {
        for (int j = 0; j < n; j++) {
            XT[i][j] = XTP[i][j];
        }
    } 
    //printMatrix(XT,order,n);
    //printf("-------------------------------------------\n");
    //printf("Multiplicamos XT*X ->>> XRes\n");
    for (int i = 0; i < order; i++) {
		for (int j = 0; j < order; j++) {
			XRes[i][j] = 0;
			for (int k = 0; k < n; k++) {
				XRes[i][j] += XT[i][k] * X[k][j];
			}
		}
	} 
    //printMatrix(XRes,order,order);
    //printf("-------------------------------------------\n");;
    //printf("Multiplicamos XT*Y ->>> XYRes\n");
    for (int i = 0; i < order; i++) {
		for (int j = 0; j < 1; j++) {
			XYRes[i][j] = 0;
			for (int k = 0; k < n; k++) {
				XYRes[i][j] += XT[i][k] * Y[k][j];
			}
		}
	} 
    //printMatrix(XYRes,order,1);
    //printf("-------------------------------------------\n");
    //printf("Invertimos XYRes -> XInv\n");
	for(int i=0;i<order;i++){
		for(int j=0;j<order;j++){
		    adj[i][j] = XRes[i][j];
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
			//printf("Mathematical Error!");
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
    //printMatrix(XInv,order,order);
    //printf("-------------------------------------------\n");
    //printf("Obtenemos coeficientes beta\n");
    bp = multiply(XInv,XYRes,order,order,1);
    /* for (int i = 0; i < order; i++) {
		for (int j = 0; j < 1; j++) {
			beta[i][j] = 0;
			for (int k = 0; k < order; k++) {
				beta[i][j] += XInv[i][k] * XYRes[k][j];
			}
		}
	} 
    printMatrix(beta,order,1); */
    return bp;
}

int countLines(){
    FILE * fp = fopen(DATA,"r");
	if(!fp){ 
		printf("\n ERROR! \n\n No se puede abrir el archivo. \n");
		return 0;
	}
	int ch = 0; int n = 0; //detectar el numero de lineas del archivo
	while(!feof(fp)){ 		//determinar el numero de datos.
		ch = fgetc(fp);
		if (ch == '\n'){
			n++;
		}
	}
    return n;
}

double **readFile(int n){
    FILE * fp = fopen(DATA,"r");
    double **csvData;
	int x = 0; int y = 0;

    csvData = malloc(sizeof(double) * n);
    for(int i = 0; i < n; i++) {
        csvData[i] = malloc(sizeof(double) * n);
    }

	while(x<n){		//ciclo while para guardar los datos del csv a nuestra matriz
		fscanf(fp, "%lf", &csvData[x][y]); 	
        fscanf(fp,",");
        y++;
        fscanf(fp, "%lf", &csvData[x][y]); 	
        x++;
        y = 0;
	}
    return csvData;
}


int main(){
    int n = countLines();
    double **gpsData;
    double x[100];
    double Y[100][100];

    gpsData = readFile(n);
    for (int i = 0; i < n; i++){
        for (int j = 0; j < 2; j++){
            if (j == 0){
                x[i] = gpsData[i][j];
            }else{
                Y[i][0] = gpsData[i][j];
            }
        }
    }
    
    int grado;
    printf("Ingresa el grado de la matriz: ");
    scanf("%d",&grado);

    double **bp;
    bp = polynomialRegression(x,Y,grado,n);
    printf("Coeficientes Beta ------------->");
    for (int i = 0; i < grado+1; i++){
        printf("Para x^%d: %f",i,bp[i][0]);
        printf("\n");
    }

    return 0;
}
