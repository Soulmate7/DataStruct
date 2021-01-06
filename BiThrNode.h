#pragma once
#include<stdio.h>
#include<stdlib.h>

typedef char TElemtype;
typedef enum PointerTag{Link,Thread}; //��LTagΪ0����lchildָ������/RTagΪ0��rchildָ���Һ��ӡ����LTagΪ1����lchildָ��ǰ�����/��RtagΪ1��rchildָ���̽��
typedef struct BiThrNode {
	TElemtype data;
	struct BiThrNode *lchild, *rchild;
	PointerTag LTag, RTag;	//���ұ�־
}BiThrNode, *BiThrTree;

BiThrTree pre = (BiThrTree)malloc(sizeof(BiThrNode));	//pre����ָ��p��ǰ��

void CreateBiThrTree(BiThrTree &T) //�������������������н���ֵ�����������
{
	char ch;
	scanf_s("%c", &ch,sizeof(ch));
	if (ch == '.')T = NULL;
	else
	{
		if (!(T = (BiThrNode*)malloc(sizeof(BiThrNode))))
		{
			printf("OVERFLOW\n");
			exit(1);
		}
		T->data = ch;	//Ϊ���ڵ㸳ֵ
		CreateBiThrTree(T->lchild);	//����������
		CreateBiThrTree(T->rchild);	//����������
		T->LTag = Link;	//�ȸ���Ĭ��ֵ����ĳ��˳�������������������ֵ
		T->RTag = Link;
	}
}

void InThreading(BiThrTree &p)
{
	if (p)
	{
		InThreading(p->lchild);	//������������
		if (!p->lchild)
		{
			p->LTag = Thread;
			p->lchild = pre;
		}
		if (!pre->rchild)
		{
			pre->RTag = Thread;
			pre->rchild = p;
		}
		pre = p;	//����preָ��p��ǰ��
		InThreading(p->rchild);	//������������
	}
}

void InOrderThreading(BiThrTree &Thrt, BiThrTree &T)
{
	if (!(Thrt = (BiThrTree)malloc(sizeof(BiThrNode))))	//Thrt��ͷ���
	{
		printf("OVERFLOW\n");
		exit(0);
	}
	Thrt->LTag = Link;	//����ͷ���
	Thrt->RTag = Thread;
	Thrt->rchild = Thrt;	//��ָ���ָ
	if (!T)	//����ǿ���������ָ���ָ
		Thrt->lchild = Thrt;
	else
	{
		Thrt->lchild = T;
		pre = Thrt;	//preָ��ǰ�����
		InThreading(T);	//�������������
		pre->rchild = Thrt;	//���һ�����������
		pre->RTag = Thread;
		Thrt->rchild = pre;
	}
}

/*	���BiTree��BiThrNodeͬʱinclude����Ҫע�͵��������ظ�����
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
*/

void InOrderTraverse(BiThrTree T,BiThrTree Thrt)	//�����������������,ThrtΪͷ��㣬ָ��T
{
	BiThrTree p = (BiThrTree)malloc(sizeof(BiThrNode));
	p = Thrt->lchild;	//pָ������
	while (p != Thrt)	//�������߱������ʱp==T
	{
		while (p->LTag == Link)	//�Ƚ������ߵ�ͷ
			p = p->lchild;
		if (!visit(p->data))	//����������Ϊ�յĽ��
		{
			printf("ERROR\n");
			exit(0);
		}
		while ((p->RTag == Thread) && (p->rchild != Thrt))	//���rchildָ��ֱ�Ӻ�̽�㣬���Ҳ����������������һ����㣬���������ֱ�Ӻ�̽��
		{
			p = p->rchild;	//���ʺ�̽ڵ�
			visit(p->data);
		}
		p = p->rchild;	//������Һ��ӣ������Һ���
	}
}
