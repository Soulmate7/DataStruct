#pragma once
#include<stdio.h>
#include<stdarg.h> //���ڴ�ȡ�䳤������
#include<stdlib.h>

const int MAX_ARRAY_DIM = 8;	//�ٶ����ά��Ϊ8

typedef int Elemtype;

typedef struct {
	Elemtype *base;	//����Ԫ�ػ�ַ
	int dim;	//����ά��
	int *bounds;	//����ά���ַ
	int *constants;	//����ӳ����������ַ	LOC(j1,...jn)=LOC(0,...0)+��(i=1,n)ci*ji������cn=L,c(i-1)=bi*ci
}Array;

void InitArray(Array &A, int dim, ...)	//...ʡ�Ե��Ǹ�ά�ȳ���
{
	if (dim<1 || dim>MAX_ARRAY_DIM)	//ά�����Ϸ�
	{
		printf("ERROR: Dimension invalid\n");
		exit(1);
	}
	else
	{
		A.dim = dim;
		A.bounds = (int*)malloc(dim * sizeof(int));
		if (!A.bounds)
		{
			printf("OVERFLOW\n");
			exit(1);
		}
		//��ά���Ϸ�����������ά���ȴ���A.bounds
		int elemtotal = 1; //��elemtotal��¼A��Ԫ������
		va_list ap;	//ap�Ǵ�ű䳤��������Ϣ������
		va_start(ap, dim);
		for (int i = 0; i < dim; ++i)
		{
			A.bounds[i] = va_arg(ap, int);
			if (A.bounds[i] < 0)
			{
				printf("UnderFlow\n");
				exit(1);
			}
			elemtotal *= A.bounds[i];
		}
		va_end(ap);
		A.base = (Elemtype*)malloc(elemtotal * sizeof(Elemtype));	//����Ԫ�ظ�����������ռ�
		if (!A.base)
		{
			printf("OVERFLOW\n");
			exit(1);
		}
		//��������ӳ�����ĳ���ci��������A.constants[i-1]��i=1,...,dim
		A.constants = (int*)malloc(dim * sizeof(int));
		if (!A.constants)
		{
			printf("OVERFLOW\n");
			exit(1);
		}
		A.constants[dim - 1] = 1; //L=1��ָ���������Ԫ�صĴ�С��Ϊ��λ
		for (int i = dim - 2; i >= 0; --i)
		{
			A.constants[i] = A.bounds[i + 1] * A.constants[i + 1];
		}
	}
}

void DestroyArray(Array &A)	//�ݻ�����A
{
	if (!A.base)
	{
		printf("ERROR\n");
		exit(1);
	}
	free(A.base);
	A.base = NULL;
	if (!A.bounds)
	{
		printf("ERROR\n");
		exit(1);
	}
	free(A.bounds);
	A.bounds = NULL;
	if (!A.constants)
	{
		printf("ERROR\n");
		exit(1);
	}
	free(A.constants);
	A.constants = NULL;
}

int Locate(Array A, va_list ap, int &off)	//��ap��ָ���±�ֵ���Ϸ��������Ԫ����A�����λ�ò�����
{
	int off = 0, ind, i;
	for (i = 0; i < A.dim; i++)
	{
		ind = va_arg(ap, int);
		if (ind < 0 || ind >= A.bounds[i])
		{
			printf("OVERFLOW\n");
			exit(1);
		}
		off += A.constants[i] * ind;
	}
	return off;
}

int Value(Array A, ...)	//...ʡ��n���±�ֵ����������±겻Խ�磬�򷵻���ָԪ��ֵ
{
	int e, result, off;
	va_list ap;
	va_start(ap, e);
	if ((result = Locate(A, ap, off)) <= 0)
	{
		return A.base[result];
	}
}