#include<stdio.h>
#include"Sort.h"

void exp1()
{
	SqList L;
	InitList(L);
	int i = 1, key;
	printf("������һ�����֣��Կո�ָ���0����\n");
	scanf_s("%d", &key);
	while (key != 0)
	{
		ListInsert(L, i, key);
		i++;
		scanf_s("%d", &key);
	}
	L = TwoPathInsert(L);
	SelectSort(L);
	PrintList(L);
	system("pause");
}

void exp2()
{
	LinkList L;
	printf("������ʮ�����֣��Կո�ָ�\n");
	CreateList_HeadInsert(L, 10);	//3 7 1 4 5 8 9 6 2 0
	InsertSort_Node(L);
	PrintLNode(L);
	system("pause");
}

int main()
{/*
	while (true)
	{
		printf("��ѡ����ţ�1/2����0�˳�\n");
		int choose;
		scanf_s("%d", &choose);
		getchar();
		system("cls");
		switch (choose)	
		{
		case 1:exp1(); break;
		case 2:exp2(); break;
		case 0:exit(0);
		}
		system("cls");
	}
	*/
	SqList L;
	InitList(L);
	int i = 1, key;
	printf("������һ�����֣��Կո�ָ���0����\n");
	scanf_s("%d", &key);
	while (key != 0)
	{
		ListInsert(L, i, key);
		i++;
		scanf_s("%d", &key);
	}
	Heap_Sort(L);
	PrintList(L);
	system("pause");
	return 0;
}