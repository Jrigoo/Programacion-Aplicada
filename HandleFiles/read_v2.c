# include <stdio.h>
# include<stdlib.h>
# include <string.h>

void printArray(int values[],int n); //Declaro una función para imprimir un arreglo. n es el tamño de values
void printMatrix(int values[100][100],int n); //Declaro una función para imprimir una matriz. n es el tamaño de values

int main(){
	FILE * fp = fopen("Datax.txt", "r"); //Apuntador de archivo para leer el .txt
	char buff[999]; //String en donde se leera cada linea de el archivo
    int raw[999]; //Array en donde se guardará la data extraida
    int c=0; //Numero entero c

    int sizeMatrix = 5; //Largo de la matriz principal
    int sizeFilter = 3; //Largo del filtro
    int sizeResult = sizeMatrix - sizeFilter + 1; //Largo de la matriz resultante
    
    int matrix[100][100]; //Matriz
	int filter[3][3] = {1,0,1,0,1,0,1,0,1}; //Kernel
	int resultado[100][100]; //Matriz resultante

    /* Variables Convolución */
    int x = 0;int y = 0;int i = 0;int j = 0;int r = 0;
    
	if (fp == NULL){
		printf( "Data.txt file failed to open." ) ;
        return 0;
	}
    /* Leer la data del archivo .txt
        - Lo que hace fgets() es leer linea a linea
        - Luego teniendo ese string, usamos strtok() para dividirlo en
        substrings con el delimitador ","
        - Por ultimo con atoi() hacemos que el substring se vuelva un int y lo agregamos
        a nuestro array raw
    */
    while (fgets(buff,300,fp)){
        char *field = strtok(buff,",");
        while (field){
            raw[c] = atoi(field);
            field = strtok(NULL,",");
            c++;
        }
    }

    /* Imprimir data cruda */
    printf("RAW DATA ----------------------------------\n");
    printArray(raw,sizeMatrix*sizeMatrix);


    /* Asignar data cruda a matriz 
        - Pasamos del array raw (1 dimension) 
        a nuestra matriz matrix (2 dimensiones)
    */
    c = 0;
    for (int i = 0; i < sizeMatrix; i++){
        for (int j = 0; j < sizeMatrix; j++){
            matrix[i][j] = raw[c];
            c++;
        }
    }

    /* Imprimir matriz */
    printf("MATRIX DATA -------------------------------\n");
    printMatrix(matrix,sizeMatrix);

    printf("FILTER DATA -------------------------------\n");
    for (int i = 0; i < sizeFilter; i++){
        for (int j = 0; j < sizeFilter; j++){
            printf("%d",filter[i][j]);
        }
        printf("\n");
    }
    printf("\n");
    
    
    /* Convolucion 
        - 1 while loop:
            - x se encarga de mover el filtro por fila
            - y se encarga de mover el filtro por columnas
            - i se encarga de multiplicar las filas del filtro por las
            columnas de la principal
            - j se encarga de multiplicar las columnas del filtro por 
            las de la principal
    */
    while (x < sizeResult){
        if (y == sizeResult){
            x++;
            i=0;j=0;r=0;y=0;
        }else if (i == sizeFilter){
            resultado[x][y] = r;
            y++;
            i=0;j=0;r=0;
        }else if (j == sizeFilter){
            i++;
            j=0;
        }else{
            r = r + matrix[i+x][j+y]*filter[i][j];
            j++;
        }
    }
    
    /* Resultado de convolucion */
    printf("CONVOLUTION RESULT ------------------------\n");
    printMatrix(resultado,sizeResult);
    
	return 0;	
}

/* Función para imprimir un arreglo, recibe el arreglo y su largo */
void printArray(int values[],int n){
    printf("-------------------------------------------\n");
    for (int i = 0; i < n; i++){
        printf("%d",values[i]);
    }
    printf("\n");  
    printf("-------------------------------------------\n");
}
/* Función para imprimir una matriz cuadrada, recibe la matriz y su largo */
void printMatrix(int values[100][100],int n){
    printf("-------------------------------------------\n");
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            printf("%d",values[i][j]);
        }
        printf("\n");         
    }
    printf("-------------------------------------------\n");
}

