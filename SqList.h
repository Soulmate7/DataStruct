#pragma once
#include<iostream>
#include<stdlib.h>
using namespace std;

const int LIST_INIT_SIZE = 100;
const int LISINCREMENT = 10;
typedef int Elemtype;

typedef struct{		//˳�����
	Elemtype *elem;	//����ַ
	int length;	//����
	int listsize;	//����
}SqList;

void InitList(SqList &L)	//��ʼ��˳������ٿռ�
{
	L.elem = (Elemtype*)malloc(LIST_INIT_SIZE * sizeof(Elemtype));
	if (!L.elem)
	{
		cerr << "OVERFLOW";
		exit(1);
	}
	L.length= 0;
	L.listsize = LIST_INIT_SIZE;
}
void DestroyList(SqList &L)	//�ݻ�˳���
{
	if (L.elem)
	{
		cerr << "ERROR";
		exit(1);
	}
	free(L.elem);
	L.length = 0;
	L.listsize = 0;
}
void ListInsert(SqList &L, int i, Elemtype e)	//��˳����i��λ�ò���e
{
	if (i<1 || i>L.length + 1)	//�жϲ���λ���Ƿ���Ч, ע����±�1��ʼ����
	{
		cerr << "ERROR";
		exit(1);
	}
	if (L.length >= L.listsize)	//�ж�˳����Ƿ�����
	{
		Elemtype *newbase = (Elemtype*)realloc(L.elem, (L.listsize + LISINCREMENT) * sizeof(Elemtype));
		if (!newbase)
		{
			cerr << "ERROR";
			exit(1);
		}
		L.elem = newbase;
		L.listsize += LISINCREMENT;
	}
	Elemtype *q = &(L.elem[i]);	//qָ�����λ��
	for (Elemtype *p = &(L.elem[L.length - 1]); p >= q; --p)	//��λ����
	{
		*(p + 1) = *p;
	}
	*q = e;
	++L.length;
}
Elemtype ListDelete(SqList &L, int i)	//ɾ����i��Ԫ�أ�������ֵ
{
	if ((i < 1) || (i > L.length))
	{
		cerr << "ERROR";
		exit(1);
	}
	Elemtype *p = &(L.elem[i]);	//ɾ��Ԫ��λ��
	Elemtype e = *p;
	Elemtype *q = L.elem + L.length - 1; //��βλ��
	for (++p; p <= q; ++p)
	{
		*(p - 1) = *p;
	}
	--L.length;
	return e;
}
Elemtype GetElem(SqList &L, int i)	//����˳����i��Ԫ��
{
	return L.elem[i];
}
bool compare(Elemtype a, Elemtype b)   //�ж�Ԫ���Ƿ���ȣ���������ҵ���ͬԪ�أ�����false
{
	if (a == b)
		return false;
	else
		return true;
}
Elemtype LocateElem(SqList &L, Elemtype e)	//�����Ա��в��ҵ�һ����e��ȵ�Ԫ�ص�λ��
{
	int i = 1;
	Elemtype *p = L.elem;
	while (i <= L.length && compare(*p++, e))
		++i;
	if (i <= L.length)
		return i;
	else
		return 0;
}
SqList MergeList(SqList La, SqList Lb)	//������˳���Ԫ�ش�С����ϲ�
{
	SqList Lc;
	Elemtype* pa,*pb;
	pa = La.elem;
	pb = Lb.elem;
	Lc.listsize = Lc.length = La.length + Lb.length;
	Elemtype *pc;
	pc = Lc.elem = (Elemtype*)malloc(Lc.listsize * sizeof(Elemtype));
	if (!Lc.elem)
	{
		cerr << "ERROR";
		exit(1);
	}
	Elemtype *pa_last = La.elem + La.length - 1;
	Elemtype *pb_last = Lb.elem + Lb.length - 1;
	while (pa <= pa_last && pb <= pb_last)
	{
		if (*pa <= *pb)
		{
			*pc++ = *pa++;
		}
		else
		{
			*pc++ = *pb++;
		}
	}
	while (pa <= pa_last)
	{
		*pc++ = *pa++;
	}
	while (pb <= pb_last)
	{
		*pc++ = *pb++;
	}
	return Lc;
}

SqList CombineList(SqList La, SqList Lb) //��Lb��Ԫ�ز��뵽Laβ������֤���ظ�
{
	SqList Lc;
	Lc.listsize = La.length + Lb.length;
	Elemtype* pc = Lc.elem = (Elemtype*)malloc(Lc.listsize * sizeof(Elemtype));
	Lc.length = 0;
	Elemtype *pa = La.elem;
	Elemtype *pb = Lb.elem;
	Elemtype *pa_last = La.elem + La.length - 1;
	Elemtype *pb_last = Lb.elem + Lb.length - 1;
	int i = 0;
	for (i=1; pa < pa_last; pa++,i++)
	{
		ListInsert(Lc, i, *pa);		//��La��Ԫ�ز��뵽Lc
	}
	for (pb; pb < pb_last; pb++)
	{
		if (!LocateElem(La, *pb))
		{
			ListInsert(Lc,i++,*pb);
		}
	}
	return Lc;
}

void PrintList(SqList L)
{
	int i;
	for (i = 1; i <= L.length; i++)
	{
		printf("%d ", GetElem(L, i));
	}
	printf("\n");
}