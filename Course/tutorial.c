#include<stdio.h>


void main(){
	int matrix[5][5] = {1,1,1,0,0,0,1,1,1,0,0,0,1,1,1,0,0,1,1,0,0,1,1,0,0};
	int filter[3][3] = {1,0,1,0,1,0,1,0,1};
	int resultado[3][3];

	for (int x = 0; x < 3; x++){ //Mueva entre filas
		for (int y = 0; y < 3;y++){ //Mueva entre columnas
			int r = 0;
			for(int i = 0; i < 3;i++){
				for(int j = 0; j < 3;j++){
					r = r + matrix[i+x][j+y]*filter[i][j];
				}
			}
			resultado[x][y] = r;
		}
	}

    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 3; j++){
            printf("%d",resultado[i][j]);
        }
        printf("\n");    
    }
}




