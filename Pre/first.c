#include<stdio.h> /* Acceso a archivo de biblioteca */

#define PI 3.1416 /* Macro/Constante */

float procesar(float radio); /* Prototipo de función */

/* Función Principal, encargada de la ejecución 
y terminación del programa */
void main(){
    float radio,area; /* Declaración de variables */
    printf("Radio = ? "); /* Imprimir en consola */
    scanf("%f",&radio); /* Obtener el radio por parte del usuario */
    
    area = procesar(radio); /* Asignar valor a la variable area */
    printf("El area del circulo es: %f",area); /* Imprimir en consola */
} 

/* Definición de función */
float procesar(float radio){
    return PI*radio*radio;
}

