# include <stdio.h>
# include<stdlib.h>
# include <string.h>
# include<math.h>

#define DATA1 "gpsPt1.csv"
#define DATA2 "gpsPt2.csv"

void printMatrix(double matrix[][100],int rows,int columns);
void printArray(double values[],int n);
int countLines(char file[]);
double RMSE(int n, double ys[],double yr[]);
double * getResult(int n, double x[], double beta[], int order);
double **polynomialRegression(double x[100],double Y[][100],int grado,int n);
double **inverse(double matrix[][100],int order);
double **multiply(double mat1[][100], double mat2[][100],int row1,int row2,int col2);
double **transpose(double mat1[][100],int rows,int columns);
double **readFile(char file[],int n);

void main(){
    double **gpsData,**gpsData1;
    double x[100];
    double y[100];
    double Y[100][100];
    double beta[100];
    int grado = 4; //Para DATA 2 Grado 4, Para DATA 1 Grado 1

    double **bp;
    double *yrp;
    int n = countLines(DATA2);
    gpsData = readFile(DATA2,n);
    
    /* Leemos data y la guardamos en una matrix */
    for (int i = 0; i < n; i++){
        for (int j = 0; j < 2; j++){
            if (j == 0){
                x[i] = gpsData[i][j];
            }else{
                Y[i][0] = gpsData[i][j];
                y[i] = gpsData[i][j];
            }
        }
    }
    
    bp = polynomialRegression(x,Y,grado,n);
    printf("Ecuacion resultante y junto a coeficientes beta ------------->\n");
    for (int i = 0; i < grado+1; i++){
        beta[i] = bp[i][0];
        if (beta[i] > 0){
            printf("+%f*x^%d\t",beta[i],i);
        }else{
            printf("%f*x^%d\t",beta[i],i);
        }
    }   

    yrp = getResult(n,x,beta,grado+1);
    free(yrp);

    printf("\n Variable independiente x \n");
    printArray(x,n);

    printf("\n Puntos resultantes yr \n");
    printArray(yrp,n);
    RMSE(n,y,yrp);
}

void printArray(double values[],int n){
    for (int i = 0; i < n; i++){
        printf("%f \n",values[i]);
    }
}

void printMatrix(double matrix[][100],int rows,int columns){
    for (int i = 0; i < rows; i++){
        for (int j = 0; j < columns; j++){
            printf("%lf ",matrix[i][j]);
        }
        printf("\n");         
    }
}

int countLines(char file[]){
    FILE * fp = fopen(file,"r");
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

double **readFile(char file[],int n){
    FILE * fp = fopen(file,"r");
    double **csvData;
	int x = 0; int y = 0;

    csvData = malloc(sizeof(double) * n);
    for(int i = 0; i < n; i++) {
        csvData[i] = malloc(sizeof(double) * n);
    }

    //ciclo while para guardar los datos del csv a nuestra matriz
    //Matriz n x 2
	while(x<n){		
		fscanf(fp, "%lf", &csvData[x][y]); 	
        fscanf(fp,",");
        y++;
        fscanf(fp, "%lf", &csvData[x][y]); 	
        x++;
        y = 0;
	}
    
    /* 
    Quiero que todas las X sean (X - 9.02)*1000
    Quiero que todas las Y sean (Y - 79.53)*1000
    */
    //printf("Normalize Data -----------------------------> \n");
    for (int i = 0; i < n; i++){
        for (int j = 0; j < 2; j++){
            if(j == 0){
                csvData[i][j] = (csvData[i][j] - 9.02)*1000;
            }
            if(j == 1){
                csvData[i][j] = (csvData[i][j] - 79.53)*1000;
            }
            //printf("%f \t",csvData[i][j]);
        }
        //printf("\n");
    }
    return csvData;
}

double **polynomialRegression(double x[100],double Y[][100],int grado,int n){
	int order = grado + 1;
    double X[100][100];
    double XT[100][100];
    double XRes[100][100];
    double XYRes[100][100];
    double XInv[100][100];
    double beta[100][100];

    double **XTP;
    double **XPRes;
    double **XYPRes;
    double **XPInv;
    double **bp;

    bp = malloc(sizeof(double) * 100);
    for(int i = 0; i < 100; i++) {
        bp[i] = malloc(sizeof(double) * 100);
    }

    //printf("Matriz X\n"); 
    for (int i = 0; i < n; i++){
        for (int j = 0; j < order; j++){
            X[i][j] = powf(x[i],j);
            //printf("%f \t",X[i][j]);
        }
        //printf("\n");
    }
    //printf("\n");

    //printf("Transponemos la matriz X\n");
    XTP = transpose(X,n,order);
    for (int i = 0; i < order; i++) {
        for (int j = 0; j < n; j++) {
            XT[i][j] = XTP[i][j];
            //printf("%f \t",XTP[i][j]);
        }
        //printf("\n");
    } 
    //printf("\n");


    //printf("Multiplicamos XT*X ->>> XRes\n");
    XPRes = multiply(XT,X,order,n,order);
    for (int i = 0; i < order; i++) {
        for (int j = 0; j < n; j++) {
            XRes[i][j] = XPRes[i][j];
            //printf("%f \t",XPRes[i][j]);
        }
        //printf("\n");
    } 
    //printf("\n");

    //printf("Multiplicamos XT*Y ->>> XYRes\n");
    XYPRes = multiply(XT,Y,order,n,1);
    for (int i = 0; i < order; i++) {
        for (int j = 0; j < n; j++) {
            XYRes[i][j] = XYPRes[i][j];
            //printf("%f \t",XYPRes[i][j]);
        }
        //printf("\n");
    } 
    //printf("\n");

    //printf("Invertimos XRes -> XInv\n");
    XPInv = inverse(XRes,order);
    for (int i = 0; i < order; i++) {
        for (int j = 0; j < n; j++) {
            XInv[i][j] = XPInv[i][j];
            //printf("%f \t",XPInv[i][j]);
        }
        //printf("\n");
    } 
    //printf("\n");


    bp = multiply(XInv,XYRes,order,order,1);
    return bp;
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

double RMSE(int n, double ys[100],double yr[]){
    double r = 0;
    for (int i = 0; i < n; i++){
        r = r + pow(ys[i]-yr[i],2); 
    }
    printf("\n Root Mean Square Error: %f",sqrt(r/n));
    return sqrt(r/n);
}

double * getResult(int n, double x[], double beta[], int order){
    static double array[100],result;
    for (int i = 0; i < n; i++){
        result = 0;
        for (int j = 0; j < order; j++){
            result = result + beta[j]*pow(x[i],j);
        }
        array[i] = result;
    }
    return array;
}