#include<stdio.h>
#include<stdlib.h>

int calculator(char operator,int num1,int num2);

void main(){
    calculator("a",2,2);
}



int calculator(char operator,int num1,int num2){
    switch (operator)
    {
    case 'a':
        return num1 + num2;
        break;
    case 's':
        return num1 - num2;
        break;
    case 'm':
        return num1*num2;
        break;
    case 'd':
        return num1/num2;
        break;
    default:
        return 0;
        break;
    }
}