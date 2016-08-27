#pragma warning(disable:4996)
#include <stdio.h>

#define size 3
int main()
{
	int a[size], b[size];
	int x = 0, M = 1;
	int m[size], rm[size];
	int i, j;
	for (i = 0; i<size; i++) { //변수값 및 모듈값//

		printf("변수값 : \n");
		scanf("%d", &a[i]);
		printf("모듈값 : \n");
		scanf("%d", &b[i]);
		M *= b[i];
	}
	for (i = 0; i<size; i++){			//전체 모듈러
		m[i] = M / b[i];
	}

	for (i = 0; i<size; i++) {          //입력값에 대한 다음식으로
		for (j = 0; j<b[i]; j++) {		//행마다 노가다
			if (m[i] * j%b[i] == 1) {	//역원
				rm[i] = j;
				break;
			}
		}
		x += a[i] * m[i] * rm[i];
	}
	if (x<0) {
		while (x<0) {
			x += M;
		}
	}
	else if (x>M) {
		while (x>M) {
			x -= M;
		}
	}
	printf("%d (%d)", x, M);
	return 0;
}