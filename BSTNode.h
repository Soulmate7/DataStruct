#pragma once
#include<stdio.h>
#include<stdlib.h>
typedef int KeyType;

typedef struct node {	//�����������Ķ���
	KeyType key;	//�ؼ��ֵ�ֵ
	struct node *lchild, *rchild;	//����ָ��
}BSTNode,*BSTree;

void InsertBST(BSTree &T, KeyType key)	 //���ڶ����������в����ڹؼ���Ϊkey��Ԫ�أ�������Ԫ��
{
	if (T==NULL)	//�������㲻���ڣ������Ϊ����㣨����֮��ÿ�β�����½�㶼��ΪҶ�ӽ�㣩
	{
		T = (BSTree)malloc(sizeof(BSTNode));	   //�����µĽ��
		T->key = key;
		T->lchild = NULL;
		T->rchild = NULL;
	}
	else
	{
		if (key < T->key)
			InsertBST(T->lchild, key);	 //��s����������
		else
			if (key > T->key)
				InsertBST(T->rchild, key);	 //��s����������
	}
}
//�������һ���������������Եõ�һ���������У���Ϊ���Ķ�������������ȸ����С���������ȸ�����

void CreateBST_pre(BSTree &T)	//������չ�����������������������
{
	int key;
	scanf_s("%d", &key);
	if (key == 0)
	{
		T = NULL;
	}
	else
	{
		if (!(T = (BSTree)malloc(sizeof(BSTNode))))
		{
			printf("OVERFLOW\n");
			exit(1);
		}
		T->key = key;	//Ϊ���ڵ㸳ֵ
		CreateBST_pre(T->lchild);	//����������
		CreateBST_pre(T->rchild);	//����������
	}
}

void CreateBST(BSTree &T)	//�����������ݴ�С��ϵ��������������
{	//��������������ʼ������ô������Ҫע��T=NULL
	int key;
	scanf_s("%d", &key);
	while (key != 0)
	{
		InsertBST(T, key);
		scanf_s("%d", &key);
	};
}

BSTree SearchBST(BSTree bst, KeyType key)   //���ҹؼ���key������ҵ�������ָ���Ԫ�ؽ���ָ�룬��֮���ؿ�ָ��
{
	BSTree q;
	q = bst;
	while (q) {
		if (q->key == key)
		{
			printf("%d ", q->key);
			return q;	//���ҳɹ�
		}
		if (key < q->key)
		{
			printf("%d ", q->key);
			q = q->lchild;	//���������в���
		}
		else
		{
			printf("%d ", q->key);
			q = q->rchild;	//���������в���
		}
	}
	return NULL;	//����ʧ��
}

bool SearchBST_bool(BSTree T, KeyType key)   //ȷ�Ϲؼ���key�Ƿ�����T��
{
	if (!T)	//������û���ҵ�
	{
		printf("Not Found!\n");
		return false;
	}
	else
		if (T->key == key)
		{
			printf("Find key:%d, Continue\n", T->key);
			return true;
		}
		else
			if (T->key > key)
				SearchBST_bool(T->lchild, key);
			else
				if (T->key < key)
					SearchBST_bool(T->rchild, key);
}

bool Delete(BSTree &T)	//ɾ�������������еĽ��T
{
	BSTree L;
	if (!T->lchild && !T->rchild)	//��T��û��������Ҳû��������������ΪҶ�ӽ��
	{
		T = NULL;
		free(T);
	}
	else
		if (!T->lchild)	//���ֻ��������
			T = T->rchild;	//�������������浱ǰ���
		else
			if (!T->rchild)	//���ֻ��������
				T = T->lchild;	//�������������浱ǰ���
			else	//�������������������������
			{
				L = T->lchild;	//Lָ��ɾ������������
				while (L->rchild)	//Ѱ��L�����Һ���
					L = L->rchild;
				L->rchild = T->rchild;  //��T���������ӵ����������Һ��ӵ���������
				T = T->lchild;	//T��������ֱ����ΪT������������
			}
	return true;
}

bool DeleteBST(BSTree &T, int key)
{
	if (!T)
	{
		printf("Empty Tree!\n");
		return false;
	}
	else
		if (key == T->key)
		{
			Delete(T);
			return true;
		}
		else
			if (key < T->key)
				return DeleteBST(T->lchild, key);
			else
				return DeleteBST(T->rchild, key);
}

void PrintBST(BSTree T)	//�������������������������õ�����˳��
{
	if (!T)
	{
		return;
	}
	PrintBST(T->lchild);
	printf("%d ", T->key);
	PrintBST(T->rchild);
}