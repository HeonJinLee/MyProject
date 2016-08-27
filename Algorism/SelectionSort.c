#include<stdio.h>
int main()
{
	int a[5] = { 7, 2, 9, 5, 3 };
	int m = 0;
	for (int i = 0; i < 5; i++)
	{
		for (int j = i+1; j < 5; j++)
		{
			if (a[j] < a[i]) {
				m = a[j];
				a[j] = a[i];
				a[i] = m;
			}
		}
		printf("ÃÖ¼Ò°ª%d\n", a[i]);
	}
}