#include<stdio.h>

int rango(int val1,int val2,int x);
void main(){
    int f = rango(2,4,3);
    printf("El valor de f es %d",f);
}

int rango(int val1,int val2,int x){
    int f = 0;
    if (x >= val1 && x <= val2)
    {
        return f;
    }
    f = -1;
    return f;
}