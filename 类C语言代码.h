#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include"BiTree.h"

typedef int Status;
typedef int QElemtype;
#define OK 1;
#define Error 0;

typedef struct QNode { //���е���ʽ��ʾ
	QElemtype data;
	struct QNode *next;
}QNode, *QueuePtr;

typedef struct { //������
	QueuePtr rear; //βָ��
}LinkQueue;

Status InitQueue(LinkQueue &T) //��ʼ��һ��ֻ����βָ��ĵ�ѭ�������ʾ����
{
	T.rear = (QueuePtr)malloc(sizeof(QNode));
	T.rear->next = T.rear;
	return OK;
}

bool EmptyQueue(LinkQueue T)    //�ж��Ƿ�Ϊ�ն���
{
	if (T.rear->next == T.rear) //���βָ��ָ���Լ���˵������Ϊ��
	{
		return OK;
	}
	else
		return 0;
}

Status EnQueue(LinkQueue &T, QElemtype e) //�ڶ�β����Ԫ��
{
	QueuePtr p = (QueuePtr)malloc(sizeof(QNode));
	if (!p)
	{
		return Error;
	}
	p->data = e;
	p->next = T.rear->next; //��pָ���ͷԪ��
	T.rear->next = p; //��ԭ��βԪ��ָ��p��
	T.rear = p; //��p��Ϊ�µĶ�β
	return OK;
}

QElemtype DeQueue(LinkQueue &T, QElemtype &e) //ɾ����ͷԪ��
{
	QueuePtr p = (QueuePtr)malloc(sizeof(QNode));
	if (EmptyQueue(T))
		return Error;
	p = T.rear->next;   //pָ���ͷԪ��
	e = p->data;
	T.rear->next = p->next; //��βָ��nextָ���ͷԪ�ص���һ��Ԫ�أ���ɾ����ͷԪ��
	free(p); //�ͷŶ�ͷԪ��
	return OK;
}

BiTree firstLeaf;	//Ҷ�ӽ��õ�������Ŀ�ʼ���
BiTree pcur;	//��ǰָ���Ҷ�ӽ��

Status leafLink(BiTree T)	//��Ҷ�ӽ����������ӳɵ�����
{
	if (!T)	//���Ϊ�������˳�
	{
		return Error;
	}
	if (T->lchild == NULL && T->rchild == NULL)	//�����ǰ��ֻ�и���㣨��ǰ���ΪҶ�ӽ�㣩
	{
		if (firstLeaf == NULL)	//��һ���ҵ�Ҷ�ӽڵ�ʱ
		{
			firstLeaf = T; // �����ҵ��ĵ�һ��Ҷ�ӽ��
			pcur = firstLeaf;
		}
		else
		{
			// ����ʱ��Ҷ�ӽ���rchild����ָ��
			pcur->rchild = T;
			pcur = pcur->rchild;
		}
	}
	if (T->lchild)	//������������Ҷ�ӽ��
	{
		leafLink(T->lchild);
	}
	if (T->rchild)	//������������Ҷ�ӽ��
	{
		leafLink(T->rchild);
	}
	return OK;
}

Status Bigger(int a, int b)
{
	return a > b ? a : b;
}

Status getMax(BiTree T)
{
	if (T == NULL)	//����ǿ��������߱�����Ҷ�ӽ������Һ���
	{
		return 0;
	}
	else
	{
		int maxValue = Bigger(getMax(T->lchild), getMax(T->rchild));
		return T->data > maxValue ? T->data : maxValue;
	}
}

