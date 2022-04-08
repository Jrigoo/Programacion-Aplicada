#include<math.h>
#include<stdio.h>
#include<conio.h>
int main(){
   int i,j,k;
   int m = 3;
   int n = 8;
   float u,a[10],c[20][20],power,r;

    float x[8] = {1,2,3,4,5,6,7,8};
    float y[8] = {2.74, 18.06, 58.46, 135.94, 262.5, 450.14, 710.86, 1056.66};

   for(j=1;j<=m+1;j++)
   for(k=1;k<=m+1;k++){
      c[j][k]=0;
      for(i=1;i<=n;i++){
         power=pow(x[i],j+k-2);
         c[j][k]=c[j][k]+power;
      }
   }
   for(j=1;j<=m+1;j++){
      c[j][m+2]=0;
      for(i=1;i<=n;i++){
         r=pow(x[i],j-1);
         c[j][m+2]=c[j][m+2]+y[i]*r;
      }
   }
   for(i=1;i<=m+1;i++){
      for(j=1;j<=m+2;j++){
         printf("%.2f\t",c[i][j]);
      }
      printf("\n");
   }
   for(k=1;k<=m+1;k++)
      for(i=1;i<=m+1;i++){
         if(i!=k){
            u=c[i][k]/c[k][k];
            for(j=k;j<=m+2;j++){
               c[i][j]=c[i][j]-u*c[k][j];
         }
      }
   }
   for(i=1;i<=m+1;i++){
      a[i]=c[i][m+2]/c[i][i];
      printf("a[%d]=%f\n",i,a[i]);
   }
   getch();
}