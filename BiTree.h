#pragma once
#include<stdlib.h>
#include<stdio.h>

typedef char TElemtype;

typedef struct BiTNode {	//����������ʽ��ʾ
	TElemtype data;
	struct BiTNode *lchild, *rchild; //���Һ���ָ��
}BiTNode,*BiTree;

#include"SqStack.h"				//����ͷ�ļ���˳�����н����ģ�����ڶ��������֮ǰ���룬�൱��
#include"SqQueue.h"				//�ڻ�û�ж���BiTree��ʱ��ͽ�SElemtype����ΪBiTree���ᱨ��

void CreateBiTree(BiTree &T) //�������������������н���ֵ�����������
{
	char ch;
	scanf_s("%c", &ch,sizeof(ch));
	if (ch == '.')T = NULL;
	else
	{
		if (!(T = (BiTNode*)malloc(sizeof(BiTNode))))
		{
			printf("OVERFLOW\n");
			exit(1);
		}
		T->data = ch;	//Ϊ���ڵ㸳ֵ
		CreateBiTree(T->lchild);	//����������
		CreateBiTree(T->rchild);	//����������
	}
}

bool visit(TElemtype e)
{
	if (e)
	{
		printf("%c ", e);
		return true;
	}
	else
		return false;
}

void PreOrderTraverse_recur(BiTree T)	//��������������ĵݹ��㷨
{
	if (T != NULL)	//������ڵ㲻Ϊ��
	{
		visit(T->data);	//���ʸ��ڵ�
		PreOrderTraverse_recur(T->lchild);	 //�������������
		PreOrderTraverse_recur(T->rchild);	 //�������������
	}
}

void InOrderTraverse(BiTree T)	//��������������ķǵݹ��㷨
{
	SqStack S;	
	InitStack(S);
	Push(S, T);	//����ָ���ջ
	BiTree p;
	while (!StackEmpty(S))
	{
		while ((p = GetTop(S)) && p)
		{
			Push(S, p->lchild);	//�����ߵ���ͷ�����һ�������Ҷ�ӽ�㣬����Ϊ�գ�����������ջ
		}
		p=Pop(S);	//��ָ����ջ
		if (!StackEmpty(S))	//���ʽ�㣬����һ��
		{
			p = Pop(S);
			if (!visit(p->data))
			{
				printf("Empty Node!\n");
				exit(1);
			}
			Push(S, p->rchild);
		}
	}
	DestroyStack(S);
}

void PostOrderTraverse(BiTree T) {	//��������������ķǵݹ��㷨
	SqStack S;
	InitStack(S);
	BiTNode *pre = (BiTNode*)malloc(sizeof(BiTNode));	//��������ָ��ָ��������ʹ���㣬�Ӷ��ж������ӻ����Һ���
	pre = NULL;		//��ʼ��ǰһ�����Ϊ��
	BiTree p = T;
	while (p||!StackEmpty(S))
	{
		while (p)
		{
			Push(S, p);
			p = p->lchild;
		}
		p = GetTop(S);
		if (p->rchild == NULL || pre == p->rchild)	//��������û���Һ��ӻ��߷��ʵ�ǰһ�����Ϊ������Һ��ӣ�����ʸ���㣨�����ÿһ����㶼��������㣩
		{
			if (!visit(p->data))
			{
				printf("Empty Node!\n");
				exit(1);
			}
			pre = Pop(S);
			p = NULL;
		}
		else
			p = p->rchild;	//��֮��Ӧ���ȷ��������Һ���
	}

}//PostOrderTraverse

void PostOrderTraverse_recur(BiTree T)	//��������������ĵݹ��㷨
{
	if (T != NULL)
	{
		PostOrderTraverse_recur(T->lchild);	//�������������
		PostOrderTraverse_recur(T->rchild);	//�������������
		visit(T->data);	//���ʸ����
	}
}



int leaf(BiTree T)	//ͳ��Ҷ�ӽ����Ŀ
{
	int LeafCount=0;	//Ҷ�ӽ����
	if (T != NULL)
	{
		leaf(T->lchild);	//��������ķ���
		leaf(T->rchild);
		if (T->lchild == NULL && T->rchild == NULL) //���û�к��ӽ�㣬���ҵ���Ҷ�ӽ��
			LeafCount++;
	}
	return LeafCount;
}

int PostTreeDepth(BiTree bt)	//���������������ĸ߶ȣ���ȣ��ݹ��㷨
{
	int hl, hr, max;
	if (bt != NULL)
	{
		hl = PostTreeDepth(bt->lchild); //���������߶�
		hr = PostTreeDepth(bt->rchild); //���������߶�
		max = hl > hr ? hl : hr;	   //�õ����������߶Ƚϴ���
		return (max + 1);	//�������ĸ߶�
	}
	else
		return 0;	//����Ϊ0
}

int Max(int a, int b)
{
	return a > b ? a : b;
}

int TreeDepth(BiTree T)	//���������
{
	if (!T)		//Ҷ�ӽ������Һ����ǲ����ڵģ�����Ӧ������-1
	{
		return 0;
	}
	return 1 + Max(TreeDepth(T->lchild), TreeDepth(T->rchild));
}


void LayerOrder(BiTree T)	//�������������
{
	SqQueue Q;
	InitQueue(Q);
	EnQueue(Q, T);	//��Ҫ�õ�ʱ�򣬰�Queue�е��������͸���
	while (!QueueEmpty(Q))
	{
		BiTree p;
		p=DeQueue(Q);
		if (visit(p->data))
		{
			if (p->lchild)
				EnQueue(Q, p->lchild);
			if (p->rchild)
				EnQueue(Q, p->rchild);
		}

	}
	DestoryQueue(Q);
}

int LevelWidth(BiTree T, int level)		//��ָ��level�Ŀ��
{
	if (!T)return 0;
	else
	{
		if (level == 1)return 1;
		level = LevelWidth(T->lchild, level - 1) + LevelWidth(T->rchild, level - 1);
	}
	return level;
}

int Width(BiTree T)	//�����������
{
	int width, i;
	int w[20];
	for (i = 0; i < 20; i++)
		w[i] = 0;
	if (!T)width = 0;
	else
	{
		for (i = 0; i <= PostTreeDepth(T); i++)w[i] = LevelWidth(T, i + 1);
	}
	i = 0;
	while (w[i])
	{
		if (w[i] > width)width = w[i];
		i++;
	}
	return width;
}
