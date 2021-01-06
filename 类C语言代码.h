#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include"BiTree.h"

typedef int Status;
typedef int QElemtype;
#define OK 1;
#define Error 0;

typedef struct QNode { //队列的链式表示
	QElemtype data;
	struct QNode *next;
}QNode, *QueuePtr;

typedef struct { //链队列
	QueuePtr rear; //尾指针
}LinkQueue;

Status InitQueue(LinkQueue &T) //初始化一个只含有尾指针的单循环链表表示队列
{
	T.rear = (QueuePtr)malloc(sizeof(QNode));
	T.rear->next = T.rear;
	return OK;
}

bool EmptyQueue(LinkQueue T)    //判断是否为空队列
{
	if (T.rear->next == T.rear) //如果尾指针指向自己，说明队列为空
	{
		return OK;
	}
	else
		return 0;
}

Status EnQueue(LinkQueue &T, QElemtype e) //在队尾插入元素
{
	QueuePtr p = (QueuePtr)malloc(sizeof(QNode));
	if (!p)
	{
		return Error;
	}
	p->data = e;
	p->next = T.rear->next; //令p指向队头元素
	T.rear->next = p; //令原队尾元素指向p；
	T.rear = p; //令p成为新的队尾
	return OK;
}

QElemtype DeQueue(LinkQueue &T, QElemtype &e) //删除队头元素
{
	QueuePtr p = (QueuePtr)malloc(sizeof(QNode));
	if (EmptyQueue(T))
		return Error;
	p = T.rear->next;   //p指向队头元素
	e = p->data;
	T.rear->next = p->next; //令尾指针next指向队头元素的下一个元素，即删除队头元素
	free(p); //释放队头元素
	return OK;
}

BiTree firstLeaf;	//叶子结点得到的链表的开始结点
BiTree pcur;	//当前指向的叶子结点

Status leafLink(BiTree T)	//将叶子结点从左到右连接成单链表
{
	if (!T)	//如果为空树，退出
	{
		return Error;
	}
	if (T->lchild == NULL && T->rchild == NULL)	//如果当前树只有根结点（当前结点为叶子结点）
	{
		if (firstLeaf == NULL)	//第一次找到叶子节点时
		{
			firstLeaf = T; // 保存找到的第一个叶子结点
			pcur = firstLeaf;
		}
		else
		{
			// 链接时用叶子结点的rchild域存放指针
			pcur->rchild = T;
			pcur = pcur->rchild;
		}
	}
	if (T->lchild)	//对左子树查找叶子结点
	{
		leafLink(T->lchild);
	}
	if (T->rchild)	//对右子树查找叶子结点
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
	if (T == NULL)	//如果是空树，或者遍历到叶子结点的左右孩子
	{
		return 0;
	}
	else
	{
		int maxValue = Bigger(getMax(T->lchild), getMax(T->rchild));
		return T->data > maxValue ? T->data : maxValue;
	}
}

