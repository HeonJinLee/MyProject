#include<stdio.h>
#define MAX 80
#pragma warning (disable:4996)

void add(int where, char what);

char msg[MAX] = "Data Structure";
int length = 14;

void main()
{
	int where;
	char what;
	do{
		scanf("%d %c", &where, &what);
		add(where, what);
	} while (where > 0);
}

void add(int where, char what)
{
	int i;
	printf("before[%s]\t",msg);
	if (where > 0 && where < length - 1){
		for (i = length; i >= where; i--) msg[i + 1] = msg[i];
		msg[where - 1] = what;
		length++;
	}
	printf("after[%s]\n", msg);
	printf("length=%d\n", length);
}