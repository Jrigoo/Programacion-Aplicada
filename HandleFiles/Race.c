
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define Nfltr 3

int main(){
	
	int Nmatrix1 = 10; //	tamano de matriz cuadrada
	float matrix1[Nmatrix1][Nmatrix1]; //declaracion de la matriz principal
	
	FILE * fp = fopen("doc1.csv", "r"); 		//abrir el archivo
	
	int x = 0, y = 0; 		//desingando contadores
	
	float fltr[Nfltr][Nfltr];	 // creando la matriz filtro kernel
		x = y = 0;
		while(x<Nfltr && y <Nfltr+1){		//asignando valores 1 a toda la matriz
			fltr[x][y] = 1;
			y++;
			if(y == Nfltr){
				x++;
				y = 0;
			} 
		}
	
// LECTURA DE DATOS A LA MATRIZ
	x = y = 0; 	// reset contadores
	while (x<Nmatrix1){ 	//ciclo while para guardar los datos del csv a nuestra matriz
		while(y<Nmatrix1){
			fscanf(fp, "%f", &matrix1[x][y]); 	//almacena el valor token leido como un valor float
				//dentro del array en la posicion [x][y]
			if(!feof(fp)){ 		// es para que lea los valores de manera correcta
				fscanf(fp,","); 	//mejor explicado, determina si se encuentra al final del archivo
			} 		//de estarlo, lee las "," pero no las almacena, de manera que las "salta" para nosotros
			y++;
		}
		x++;
		y = 0;
	}
	
	printf("\n DATOS DEL DOCUMENTO (MATRIZ ENTRADA) \n");
	x = y = 0 ; 	//ciclo while para imprimir la matriz
	while (x<Nmatrix1 && y<Nmatrix1+1){
		
		printf("%.2f ", matrix1[x][y]);		//determino impresion con 2 valores decimales
		y++;
		if(y == Nmatrix1){
			x++;
			y = 0;
			printf("\n");
		}	
}
	printf("\n");
	
	printf(" FILTRO (MATRIZ KERNEL) \n");
	x = y = 0 ; 	//ciclo while para imprimir la matriz
	while (x<Nfltr && y<Nfltr+1){
		
		printf("%.2f ", fltr[x][y]);		//determino impresion con 2 valores decimales
		y++;
		if(y == Nfltr){
			x++;
			y = 0;
			printf("\n");
		}	
}

printf("\n");

//	CONVOLUCION

	int Nres = Nmatrix1 - Nfltr +1;		//tamano de la matriz resultado
	float rmatrix[Nres][Nres];		//matriz resultado
	float pmatrix[Nres][Nres];		//matriz pasajera
		x = y = 0;
		while(x<Nres && y <Nres+1){		//asignando valores 0 a toda la matriz
			rmatrix[x][y] = 0;
			pmatrix[x][y] = 0;
			y++;
			if(y == Nres){
				x++;
				y = 0;
			} 
		}
		
	int xc = 0, yc = 0; 	//nuevos contadores para convolucion
	float C = 0; // constante de convolucion donde se almacenaran los valores momentaneos
	xc = yc = x = y = 0; // reset contadores
	
	while(xc<Nres && yc<=Nres){ //cliclo while contadores de convolucion
		x = y = C = 0;
		while(x<Nfltr && y<Nfltr){
			C = C + fltr[x][y]*matrix1[x+xc][y+yc]; // almacenamiento de operaciones de convolucion
			y++;
			if(y == Nfltr){
				x++;
				y = 0;
			}
		}
		rmatrix[xc][yc] = C; 	//datos de convolucion a la matriz
		yc++;
		if(yc == Nres){
			xc++;
			yc = 0;
		}
			
	}
					
	printf("\n MATRIZ RESULTADO DE CONVOLUCION\n\n");
	x = y = 0 ; 	//ciclo while para imprimir la matriz
	while (x<Nres){
		while (y<Nres){
			
			printf(" %.2f", rmatrix[x][y]);		//determino impresion con 2 valores decimales
			y++;
		}
	printf("\n");	
	x++;
	y = 0;
}
	fclose(fp);
	
	printf("\n 	POR FIN FUNCIONA!!! \n");
	
return 1;
	
}