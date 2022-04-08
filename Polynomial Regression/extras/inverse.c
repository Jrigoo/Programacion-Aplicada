#include<stdio.h>
#include<conio.h>
#include<math.h>

#define SIZE 10

int main()
{
	float a[SIZE][SIZE], x[SIZE], ratio;
	int i,j,k,order;
	order = 4;
	float b[4][4] = {8.0,36.0,204.0,1296.0,36.0,204.0,1296.0,8772.0,204.0,1296.0,8772.0,61776.0,1296.0,8772.0,61776.0,446964.0};
	/* 2. Reading Matrix */
	for(i=0;i<order;i++)
	{
		for(j=0;j<order;j++)
		{
			a[i][j] = b[i][j];
		}
	}
	/* Augmenting Identity Matrix of Order order */
	for(i=0;i<order;i++)
	{
		for(j=0;j<order;j++)
		{
			if(i==j)
			{
				a[i][j+order] = 1;
			}
			else
			{
				a[i][j+order] = 0;
			}
		}
	}
	/* Applying Gauss Jordan Elimination */
	for(i=0;i<order;i++)
	{
		if(a[i][i] == 0.0)
		{
			printf("Mathematical Error!");
			return 0;
		}
		for(j=0;j<order;j++)
		{
			if(i!=j)
			{
				ratio = a[j][i]/a[i][i];
				for(k=1;k<2*order;k++)
				{
					a[j][k] = a[j][k] - ratio*a[i][k];
				}
			}
		}
	}
	/* Row Operation to Make Principal Diagonal to 1 */
	for(i=0;i<order;i++)
	{
		for(j=order;j<2*order;j++)
		{
		a[i][j] = a[i][j]/a[i][i];
		}
	}
	/* Displaying Inverse Matrix */
	printf("\nInverse Matrix is:\n");
	for(i=0;i<order;i++)
	{
		for(j=order;j<2*order;j++)
		{
		printf("%0.3f\t",a[i][j]);
		}
		printf("\n");
	}

	return 0;
}