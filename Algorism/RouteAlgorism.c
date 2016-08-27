#include<stdio.h>
#include<time.h>
#include<stdlib.h>
int mx(int a, int b);

int mx(int a, int b){
	if (a > b) return a;
	else return b;
}
void main()
{
	srand(time(0));
	int m[4][4], c[4][4];
	int i, j;
	for (i = 0; i < 4; i++){
		for (j = 0; j < 4; j++){
			m[i][j] = rand() % 50; //난수가 0~32767까지여서 50까지 수만 출력
			printf("%d  ", m[i][j]);
		}
		printf("\n");
	}
	printf("\n\n\n");
	c[0][0] = m[0][0];


	for (i = 1; i < 4; i++)
		c[i][0] = m[i][0] + c[i - 1][0]; // c00 ~c30가로줄 
	for (j = 1; j < 4; j++)
		c[0][j] = m[0][j] + c[0][j - 1]; //c00~c03 세로줄

	for (i = 1; i < 4; i++){  //c11부터 c33까지
		for (j = 1; j < 4; j++){
			c[i][j] = m[i][j] + mx(c[i][j - 1], c[i - 1][j]);

		}

	}
	for (i = 0; i < 4; i++){
		for (j = 0; j < 4; j++){
			printf("%d  ", c[i][j]);
		}
		printf("\n");
	}
	printf("\n\n\n");


}