#include <stdio.h>
#include <stdlib.h>

int main(){
    int data;
    FILE *file = fopen("COM13","w"); //Opening device file
    int a;

    printf("Insertar valor:\n");
    scanf("%d",&data);

    if (data >=0  && data < 256){
        fprintf(file,"%d",data); //Writing to the file
    }
    fclose(file);
    return 0;
}