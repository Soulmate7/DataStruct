#pragma once
#include<iostream>
#include<stdlib.h>
#include<stdio.h>
using namespace std;

typedef int Elemtype;

typedef struct LNode {	//��������
	Elemtype data;
	struct LNode *next;
}LNode,*LinkList;

void CreateList_HeadInsert(LinkList &L, int n)	//ͷ�巨����������
{
	L = (LinkList)malloc(sizeof(LNode));
	L->next = NULL;	//������һ��ͷ��������
	for (int i = n; i > 0; i--)
	{
		LinkList p = (LinkList)malloc(sizeof(LNode));	//�����½��
		cin >> (p->data);
		p->next = L->next;
		L->next = p;
	}
}

void CreatList_TailInsert(LinkList &L,int n)	//β�巨����������
{
	L = (LinkList)malloc(sizeof(LNode));          //  Ϊͷָ�뿪���ڴ�ռ�
	LinkList Node = NULL;           //  ������
	LinkList end = NULL;            //  ����β���
	L->next = NULL;              //  ��ʼ��ͷ���ָ�����һ����ַΪ NULL
	end = L;                     //  δ����������֮ǰ��ֻ��һ��ͷ���
	int count = n;                 //  ������
	for (int i = 0; i < count; i++) {
		Node = (LinkList)malloc(sizeof(LNode));          //  Ϊ�½�㿪�����ڴ�
		Elemtype temp;
		scanf_s("%d",&temp);
		Node->data = temp;                                  //  �½���������ֵ
		end->next = Node;
		end = Node;
	}
	end->next = NULL;
}


void ListInsert(LinkList &L, int i, Elemtype e) //�������i��λ�ò���e
{
	LinkList p = L;	//pָ��ͷ���
	int j = 0;
	while (p && j < i - 1)	//�ҵ���i-1�����
	{
		p = p->next;
		++j;		
	}
	if (!p || j > i - 1)
	{
		cerr << "ERROR";
		exit(1);
	}
	LinkList s = (LinkList)malloc(sizeof(LNode));
	s->data = e;
	s->next = p->next;
	p->next = s;
}

Elemtype ListDelete(LinkList &L, int i) //ɾ����i��Ԫ�أ�����ֵe
{
	LinkList p = L;
	int j = 0;
	while (p->next && j < i - 1) //�ҵ���i�����
	{
		p = p->next;
		++j;
	}
	if (!(p->next) || j > i - 1)
	{
		cerr << "ERROR";
		exit(1);
	}
	LinkList q = p->next;	//ɾ�����ͷ�
	p->next = q->next;
	Elemtype e = q->data;
	free(q);
	return e;
}

Elemtype GetElem(LinkList L, int i)	//�õ��������е�i��Ԫ��
{
	LinkList p = L->next;	//pָ��ʼ���
	int j = 1;
	while (p && j < i)
	{
		p = p->next;
		++j;
	}
	if (!p || j > i)
	{
		//cerr << "ERROR";
		return -1;
	}
	return p->data;
}

void ReverseList(LinkList &L)	//��ռ�ö���ռ佫������
{
	LinkList p = L->next->next,q;	//pָ��ʼԪ��֮���Ԫ��
	L->next->next = NULL;	//��ԭ����һ��Ϊ����֮����ͷ�巨
	while (p)
	{
		q = p;			//ÿ�δ�p��ȡ��㣬��q����¼���ַ
		p = p->next;
		q->next = L->next;	//��q���뵽Lͷ���֮��
		L->next = q;
	}
}

void CopyList(LinkList &La, LinkList &Lb)	//��La���Ƶ�Lb
{
	Lb = (LinkList)malloc(sizeof(LNode)); //ΪLb���ٿռ�
	Lb->next = NULL;	//��LbΪ������
	LinkList p = La->next; //pΪָ��La��k��ʼ���
	int i = 1;
	while (p)
	{
		ListInsert(Lb, i, p->data);
		i++;
		p = p->next;
	}
}

void PrintLNode(LinkList L)
{
	LNode *p;
	p = L->next;
	while (p)
	{
		printf("%d ", p->data);
		p = p->next;
	}
	printf("\n");
}
