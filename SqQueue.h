#pragma once
#include<stdio.h>
#include<stdlib.h>
//#include"BiTree.h"		//Ӧ�ö�����ʱ��Ҫ����

const int MAXQSIZE = 100; //һ�㶨��100��ʵ��ʱ����Ϊ10
const int QUINCREMENT = 20;

typedef int QElemtype;
//typedef BiTree QElemtype;	//���Բ������������ʱ��Ҫ���ö���
//typedef ArcCell QElemtype;

typedef struct {		//ѭ�����С���˳��ṹ
	QElemtype *base;	//��ʼ����ռ�
	int front;			//ͷָ��
	int rear;			//βָ��
	int maxqsize;		//ѭ������󳤶�
}SqQueue;

void InitQueue(SqQueue &Q)  //����һ����ѭ������
{
	Q.base = (QElemtype*)malloc(MAXQSIZE * sizeof(QElemtype));
	if (!Q.base)
	{
		printf("ERROR\n");
		exit(0);
	}
	Q.front = Q.rear = 0; //�˴���һ��Ϊ0
	Q.maxqsize = MAXQSIZE;
}

void DestoryQueue(SqQueue &Q) //����һ��ѭ������
{
	if (Q.base == NULL)
	{
		printf("ERROR\n");
		exit(0);
	}
	free(Q.base);
}

void ClearQueue(SqQueue &Q) //���һ��ѭ������
{
	if (Q.base == NULL)
	{
		printf("ERROR\n");
		exit(0);
	}
	else
		Q.front = Q.rear;
}

bool QueueEmpty(SqQueue Q)	 //�ж�һ��ѭ�������Ƿ�Ϊ��
{
	if (Q.front == Q.rear)
		return true;
	else
		return false;
}

int QueueLength(SqQueue Q)	 //�õ�ѭ������Ԫ�ظ���
{
	return (Q.rear - Q.front + Q.maxqsize) % Q.maxqsize;
}

QElemtype GetHead(SqQueue Q)	   //�õ�����Q�Ķ�ͷԪ��
{
	if (Q.front == Q.rear)
	{
		printf("Empty Queue\n");
		return 0;
	}
	else
		return Q.base[Q.front];
}

void SpecialEnqueue(SqQueue &Q, QElemtype e)	//10.14ʵ��2��Ҫ��
{
	if ((Q.rear + 1) % Q.maxqsize == Q.front) //����������������
	{
		printf("Queue FULL! exit\n");
		system("pause");
		exit(1);
	}
	else
	{
		Q.base[Q.rear] = e;
		Q.rear = (Q.rear + 1) % Q.maxqsize;	//��βָ��ָ���βԪ�ص���һλ��
	}

}

void EnQueue(SqQueue &Q, QElemtype e)  //����Ԫ��eΪQ���¶�βԪ��
{
	if ((Q.rear + 1) % Q.maxqsize == Q.front) //����������
	{
		QElemtype* newBase = (QElemtype*)malloc((Q.maxqsize + QUINCREMENT) * sizeof(QElemtype));
		int j = 0;	//��¼������Ԫ�ظ���
		int i = Q.front;
		while (i != Q.rear)	//��ԭ�������Q.base�еĶ���Ԫ�ؿ������µ�ַ��
		{
			newBase[j++] = Q.base[i];
			i = (i + 1) % Q.maxqsize;
		}
		Q.front = 0;	//��������ͷָ����0
		Q.rear = j;		//�¶�βָ��ָ���βԪ����һλ
		Q.maxqsize += QUINCREMENT;
		Q.base = newBase;
	}
	Q.base[Q.rear] = e;
	Q.rear = (Q.rear + 1) % Q.maxqsize;
}

QElemtype DeQueue(SqQueue &Q)   //ɾ��Q�Ķ�ͷԪ�ز�����ֵ
{
	if (Q.front == Q.rear)
	{
		printf("Empty Queue\n");
		return 0;
	}
	QElemtype e = Q.base[Q.front];	//�Ѷ�ͷԪ��ֵ����e������
	Q.front = (Q.front + 1) % Q.maxqsize;	//����ͷָ�뵽��һλ��
	return e;
}