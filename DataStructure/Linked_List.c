#pragma warning(disable:4996)
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct ListNode{
	char data[10];
	struct ListNode* link;
} listNode;

typedef struct{
	listNode* head;
} linkedList_h;

linkedList_h* createLinkedList_h(void);
void freeLinkedList_h(linkedList_h*);
void addLastNode(linkedList_h*, char*);
void reverse(linkedList_h*);
void deleteLastNode(linkedList_h*);
void printList(linkedList_h*);

linkedList_h* createLinkedList_h(void){
	linkedList_h* L;
	L = (linkedList_h*)malloc(sizeof(linkedList_h));
	L->head = NULL;
	return L;
}

void addLastNode(linkedList_h* L, char* x){
	listNode* newNode;
	listNode* p;
	newNode = (listNode*)malloc(sizeof(listNode));
	strcpy(newNode->data, x);
	newNode->link = NULL;
	if (L->head == NULL){
		L->head = newNode;
		return;
	}
	p = L->head;
	while (p->link != NULL) p = p->link;
	p->link = newNode;
}
void reverse(linkedList_h * L){
	listNode* p;
	listNode* q;
	listNode* r;

	p = L->head;
	q = NULL;
	r = NULL;

	while (p != NULL){
		r = q;
		q = p;
		p = p->link;
		q->link = r;
	}
	L->head = q;
}
void deleteLastNode(linkedList_h * L){
	listNode* previous;
	listNode* current;
	if (L->head == NULL) return;
	if (L->head->link == NULL){
		free(L->head);
		L->head = NULL;
		return;
	}
	else {
		previous = L->head;
		current = L->head->link;
		while (current->link != NULL){
			previous = current;
			current = current->link;
		}
		free(current);
		previous->link = NULL;
	}
}
void freeLinkedList_h(linkedList_h* L){
	listNode* p;
	while (L->head != NULL){
		p = L->head;
		L->head = L->head->link;
		free(p);
		p = NULL;
	}
}
void printList(linkedList_h* L){
	listNode* p;
	printf("L = C");
	p = L->head;
	while (p != NULL){
		printf("%s", p->data);
		p = p->link;
		if (p != NULL) printf(", ");
	}
	printf("> \n");
}

int main(){
	linkedList_h* L;
	L = createLinkedList_h();
	printf("(1) 공백 리스트 생성하기! \n");
	printList(L); getchar();

	printf("(2) 리스트에 3개의 노드 추가하기! \n");
	addLastNode(L, "월");
	addLastNode(L, "수");
	addLastNode(L, "금");
	printList(L); getchar();

	printf("(3) 리스트 마지막에 노드 한개 추가하기! \n");
	addLastNode(L, "일");
	printList(L); getchar();

	printf("(4) 마지막 노드 삭제하기! \n");
	deleteLastNode(L);
	printList(L); getchar();

	printf("(5) 리스트 원소를 역순으로 변환하기! \n");
	reverse(L);
	printList(L); getchar();

	printf("(6) 리스트 공간을 해제하여, 공백 리스트 상태로 만들기! \n");
	freeLinkedList_h(L);
	printList(L);

	getchar();
	return 0;
}