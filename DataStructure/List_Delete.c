#include<stdio.h>
#define MAX 80
#pragma warning (disable:4996)

void del(int where);

char msg[MAX] = "Data Structure";
int length = 14;

void main()
{
	int where;
	do{
		scanf("%d", &where);
		del(where);
	} while (where > 0);
}

void del(int where)
{
	int i;
	printf("before[%s]\t", msg);
	if (where > 0 && where <= length){
		for (i = where; i <= length; i++) 
			msg[i - 1] = msg[i];
		length++;
	}
	printf("after[%s]\n", msg);
	printf("length=%d\n", length);
}