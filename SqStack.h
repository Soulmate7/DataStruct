#pragma once
#include<stdio.h>
#include<stdlib.h>
//#include"BiTree.h"	//�ڶ������ǵݹ�����㷨����Ҫ�õ�ջ

const int STACK_INIT_SIZE = 100;
const int STACKINCREMENT = 100;

typedef int SElemtype;	//��ͼ��������ȷǵݹ��㷨����Ҫʹ��

//typedef BiTree SElemtype; //�ڶ������㷨����Ҫ�ѽ��ѹ��ջ��

typedef struct {	//˳��ջ����
	SElemtype *base;	//ջ��ָ��
	SElemtype *top;		//ջ��ָ��
	int stacksize;		//��ǰջ�������
}SqStack;

void InitStack(SqStack &S)	//��ʼ����ջ
{
	S.base = (SElemtype*)malloc(STACK_INIT_SIZE * sizeof(SElemtype));
	if (!S.base)
	{
		printf("ERROR\n");
		exit(0);
	}
	S.top = S.base;
	S.stacksize = STACK_INIT_SIZE;
}

void DestroyStack(SqStack &S)
{
	if (S.base == S.top)	//���Ϊ��ջ
	{
		free(S.base);
		S.stacksize = 0;
	}
	else
		if(S.base != NULL)	//������ǿ�ջ
		{
			free(S.base);
			free(S.top);
			S.stacksize = 0;
		}
}

void ClearStack(SqStack &S)
{
	if (S.base == NULL)
	{
		printf("ERROR\n");
		exit(0);
	}
	else
		S.top = S.base;
}

SElemtype GetTop(SqStack S)	//����ջ��Ԫ�ص�ֵ
{
	if (S.top == S.base)
	{
		printf("ERROR\n");
		exit(0);
	}
	SElemtype e = *(S.top - 1);
	return e;
}

int StackLength(SqStack S)	//����ջ�ĳ���
{
	return S.top - S.base;	//ͬ����ָ������Ӽ�����
}

void Push(SqStack &S, SElemtype e)	//��Ԫ��e����ջ
{
	if (S.top - S.base >=S.stacksize)	//���ջ������������
	{
		S.base = (SElemtype*)realloc(S.base, (S.stacksize + STACKINCREMENT) * sizeof(SElemtype));
		if (!S.base)
		{
			printf("ERROR\n");
			exit(0);
		}
		S.top = S.base + S.stacksize;
		S.stacksize += STACKINCREMENT;
	}
	*S.top++ = e;
}

SElemtype Pop(SqStack &S)	//��ջ��Ϊ�գ�ɾ��ջ��Ԫ�أ�������ֵ
{
	if (S.top == S.base)	//ջΪ��
	{
		printf("EMPTY STACK\n");
		exit(0);
	}
	SElemtype e = *--S.top;
	return e;
}

bool StackEmpty(SqStack &S)	//�ж��Ƿ�Ϊ��ջ
{
	if (S.base == NULL)	//�ж�ջ�Ƿ����
	{
		printf("ERROR\n");
		exit(0);
	}
	else
	{
		if (S.top == S.base)
			return true;	//��ջ��ָ���ջ��ָ��ָ��ͬһλ�ã���Ϊ��ջ
		else
			return false;
	}
}