#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#include<math.h>
int prime(int);
int main()
{
	srand(time(NULL));
	int r = 0, m = 0, p = 0, q = 0;
	int i=0, j,z=0;
	int s=0, t=0;

//	----------------------------s-----------------------------
	while (m == 0)
	{
		s = rand();
		m = prime(s);
	}
	m = 0;

//	----------------------------t-----------------------------
	while (m == 0)
	{
		t = rand();
		m = prime(t);
	}
	m = 0;

//	------------------- r = 2 * i * t + 1 --------------------

	while (m==0)
	{
		i++;
		r = 2 * i * t + 1;
		m = prime(r);
	}

//	------------------- z = s^(r-2)의 mod(r)--------------------
	z = s;
	for (j = 0; j < r - 2; j++)
	{
		z *= s;
		if (z > r)
		{
			z%=r;
		}
	}

//	-------------------- p' = 2 * z * s - 1 ---------------------
	p = 2 * z*s - 1;

//	-------------------- p = p' + 2 k r s ---------------------
	m = 0, i = 0;
	while (m == 0)
	{
		i++;
		q = p + 2 * i * r * s;
		m = prime(q);
	}
	printf("%d 강한소수 이다.\n",q);
}

int prime(int n)
{
	int j, count = 0;
	if (n < 2)return 0;

	for (j = 2; j < (int)sqrt((double)n); j++) {
		if (n % j == 0) { count++; }
	}
	if (count == 0) return 1;
	else return 0;
}