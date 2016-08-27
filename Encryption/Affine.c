#include<stdio.h>
#include<string.h>
#define size 100
int main()
{
	char a[size];
	int C, P;
	int n = 5, s = 7;
	int add, cipher;
	int num;

	printf("평문값 = ");
	fgets(a,sizeof(a),stdin);
	num = strlen(a);
	printf("ciphertext = ");

	for (int i = 0; i < num; i++)
	{
	if ('A' <= a[i] && a[i]  <= 'Z' || a[i] ==' '){
		if (a[i] == ' ') a[i] = 91;
		P = a[i] - 65;
		C = n * P + s;
		add = C % 27;
		cipher = add + 65;
		if (cipher == 91) cipher = ' ';
		printf("%c ", cipher);
		}
		else if ('a' <= a[i] && a[i] <= 'z'){
			P = a[i] - 97;
			C = n * P + s;
			add = C % 27;
			cipher = add + 97;
			if (cipher == 123) cipher = ' ';
			printf("%c ", cipher);
		}
	}
	printf("\n");
}
