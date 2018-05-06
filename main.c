#include <stdio.h>
#include <stdlib.h>
#include <string.h>
const int MAX = 10;

typedef struct QNode {
	char data[20];
	struct QNode* link;
}QNode;

typedef struct {
	QNode* front,* rear;
}Qtype;

QNode* free_s;
QNode* createfree();
void returnNode(QNode* old);
QNode* getNode();
Qtype* createLinkedQueue();
int isempty(Qtype* LQ);
void enQueue(Qtype* LQ, char* item);
char* deQueue(Qtype* LQ);
void del(Qtype* LQ);
char* peek(Qtype* LQ);
void printQueue(Qtype* LQ);
void printfree();
QNode* createfree();
QNode* getNode();
void returnNode(QNode* old);

int main()
{
	char item[20];
	int func;
	Qtype* LQ = createLinkedQueue();
	free_s = createfree();
	while (1) {
		printf("\n-----�޴�-----\n");
		printf("1. ť�� ���һ���\n");
		printf("2. ť���� ���Ұ�������\n");
		printf("3. ť���� ���һ����ϱ�\n");
		printf("4. ť���� front ����Ȯ��\n");
		printf("5. �����ϱ�\n");
		printf("����� �Է��ϼ��� : ");
		scanf("%d", &func);
		switch (func) {
		case 1:
			printf("������ �����Է� : ");
			scanf("%s", item);
			enQueue(LQ, item);
			printQueue(LQ);
			printfree();
			break;
		case 2:
			strcpy(item, deQueue(LQ));
			printf("���� : %s\n",item);
			printQueue(LQ);
			printfree();
			break;
		case 3:
			del(LQ);
			printQueue(LQ);
			printfree();
			break;
		case 4:
			strcpy(item, peek(LQ));
			printf("���� : %s\n", item);
			printQueue(LQ);
			printfree();
			break;
		case 5:
			exit(1);
		default:
			break;
		}
	}
	return 0;
}

//���鿬��ť ����
Qtype* createLinkedQueue()
{
	Qtype* LQ;
	LQ = (Qtype*)malloc(sizeof(Qtype));
	LQ->front = NULL;
	LQ->rear = NULL;
	return LQ;
}

int isempty(Qtype* LQ)
{
	if (LQ->front == NULL) {
		return 1;
	}
	else return 0;
}

//����ť�� rear�� ���һ����ϴ� ����
void enQueue(Qtype* LQ, char* item)
{
	QNode* newNode = getNode();
	strcpy(newNode->data, item);
	newNode->link = NULL;
	if (LQ->front == NULL) {
		LQ->front = newNode;
		LQ->rear = newNode;
	}
	else {
		LQ->rear->link = newNode;
		LQ->rear = newNode;
	}
}

//����ť�� front�� ���Ҹ� ��ȯ�ϴ� ����
char* deQueue(Qtype* LQ)
{
	QNode* old = LQ->front;
	char item[20];
	if (isempty(LQ) == 1) {
		return "Queue is empty!";
	}
	else {
		strcpy(item, old->data);
		LQ->front = old->link;
		if (LQ->front == NULL)
			LQ->rear = NULL;
		returnNode(old);
		return item;
	}
}

//����ť���� front���Ҹ� �����ϴ� ����
void del(Qtype* LQ)
{
	QNode* old = LQ->front;
	if (isempty(LQ) == 1) {
		printf("Queue is empty!\n");
		return;
	}
	else {
		LQ->front = old->link;
		if (LQ->front == NULL)LQ->rear = NULL;
		returnNode(old);
	}
}


//����ť���� front���Ҹ� Ȯ���ϴ� ����
char* peek(Qtype* LQ)
{
	char item[20];
	if (isempty(LQ) == 1)return "Queue is empty!";
	else {
		strcpy(item, LQ->front->data);
		return item;
	}
}

void printQueue(Qtype* LQ)
{
	QNode* temp = LQ->front;
	printf("Queue [");
	while (temp != NULL) {
		printf(" %s ", temp->data);
		temp = temp->link;
	}
	printf("]\n");
}

void printfree()
{
	QNode* temp;
	temp = free_s;
	printf("Free [");
	while (temp != NULL) {
		printf(" %s ", temp->data);
		temp = temp->link;
	}
	printf("]\n");
}

QNode* createfree()
{
	QNode* free;
	free = (QNode*)malloc(MAX*sizeof(QNode));
	int i;
	for (i = 0; i < MAX - 1; i++) {
		free[i].link = &free[i + 1];
		strcpy(free[i].data, "empty");
	}
	strcpy(free[MAX - 1].data, "empty");
	free[MAX - 1].link = NULL;
	return free;
}

QNode* getNode()
{
	QNode* newNode;
	newNode = free_s;
	free_s = free_s->link;
	return newNode;
}

void returnNode(QNode* old)
{
	old->link = free_s;
	free_s = old;
}


