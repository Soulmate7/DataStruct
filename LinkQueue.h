#pragma once
#include<stdio.h>
#include<stdlib.h>

typedef int QElemtype;

typedef struct QNode {	//���е���ʽ��ʾ
	QElemtype data;
	struct QNode *next;
}QNode,*QueuePtr;

typedef struct {	//������
	QueuePtr front;	//ͷָ��
	QueuePtr rear;	//βָ��
}LinkQueue;

void InitQueue(LinkQueue &Q)	//����ն���Q
{
	Q.front = Q.rear = (QueuePtr)malloc(sizeof(QNode));
	if (!Q.front)
	{
		printf("ERROR\n");
		exit(0);
	}
	Q.front->next = NULL;
}

void DestroyQueue(LinkQueue &Q)	//���ٶ���Q
{
	while (Q.front)
	{
		Q.rear = Q.front->next;
		free(Q.front);
		Q.front = Q.rear;
	}
}

void ClearQueue(LinkQueue &Q)	 //��Q��Ϊ�ն���
{
	Q.rear = Q.front;
	Q.front->next = NULL;
}

bool QueueEmpty(LinkQueue Q)	 //������QΪ���򷵻�true
{
	if (Q.front == Q.rear)
		return true;
	else
		return false;
}

int QueueLength(LinkQueue Q)	 //����Q��Ԫ�ظ��������г��ȣ�
{
	int i = 0;
	QNode *q = Q.front->next;
	while (q)
	{
		i++;
		q = q->next;
	}
}

QElemtype GetHead(LinkQueue Q)  //��Q��Ϊ�գ�����ͷԪ��ֵ
{
	if (Q.front == Q.rear)
	{
		printf("Empty Queue");
		return;
	}
	else
		return Q.front->next->data;
}

void EnQueue(LinkQueue &Q, QElemtype e)	//Ԫ��e�����β
{
	QueuePtr p = (QueuePtr)malloc(sizeof(QNode));
	if (!p)
	{
		printf("ERROR\n");
		exit(0);
	}
	p->data = e;
	p->next = NULL;
	Q.rear->next = p;	//��ԭ��βԪ��ָ��p
	Q.rear = p;		//��p��Ϊ�µĶ�β
}

/*ɾ����ͷԪ�أ�һ�����Ҫ����ͷ����е�ָ�롣����������һ��Ԫ�ر�ɾ������βָ����Ҫָ��ͷָ��*/
QElemtype DeQueue(LinkQueue &Q)	//ɾ����ͷԪ�أ���e����ֵ
{
	if (Q.front == Q.rear)
	{
		printf("Empty Queue\n");
		exit(0);
	}
	QueuePtr p = Q.front->next;	//pָ���ͷԪ��
	QElemtype e = p->data;
	Q.front->next = p->next;
	if (Q.rear == p)	//��ɾ��֮���Ϊ�ն���
	{
		Q.rear = Q.front;
	}
	free(p);
	return e;
}