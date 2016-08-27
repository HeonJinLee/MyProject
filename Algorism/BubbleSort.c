#include<stdio.h>
#define size 5

int main()
{
	int m=0;
	int a[size] = { 7,2,1,5,3 };

	printf("버블정렬전 배열값 = ");
	for (int i = 0; i < size; i++) printf("%d ", a[i]);
	printf("\n");

	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j<(size-1)-i; j++)
		{
			if (a[j]>a[j+1]) 
			{ 
				m = a[j]; 
				a[j] = a[j+1];	
				a[j+1] = m; 
			}
		}
	}
	printf("버블정렬후 배열값 = ");
	for (int i = 0; i < size; i++) printf("%d ", a[i]);
	printf("\n");
}