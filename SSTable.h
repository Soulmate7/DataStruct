#pragma once
#include<stdio.h>
#include<stdlib.h>
typedef int KeyType;
typedef struct {
	KeyType key;
}Elemtype;

typedef struct {	//˳���ʾ�ľ�̬���ұ����ϣ�
	Elemtype *elem;	//����Ԫ�ش洢�ռ����ַ������ʱ��ʵ�ʳ��ȷ��䣬0�ŵ�Ԫ����
	int length;	//����
}SSTable;

void init_SSTable(SSTable &ST)	//��ʼ��˳���
{
	int length, i;
	printf("������Ҫ�����ı���\n");
	scanf_s("%d", &length);
	ST.elem = (Elemtype*)malloc(length+1 * sizeof(Elemtype));
	printf("������������ݣ�\n");
	for (i = 1; i <= length ; i++)
	{
		scanf_s("%d", &ST.elem[i].key);
	}
	ST.length = length;
}

int Search_Seq(SSTable ST, KeyType key)
{
	int i;
	ST.elem[0].key = key;	//�ڱ���ʡ�Զ�Խ���±�ļ��
	for (i = ST.length; ST.elem[i].key != key; --i);	 //�Ӻ���ǰ��
	return i;	//�Ҳ�������0
}

void sortTable(SSTable &ST)	//��˳�������
{
	int i, j;
	for (i = 1; i <= ST.length; i++)	  //ð�ݷ�����
	{
		for (j = 1; j <= ST.length - i; j++)
		{
			if (ST.elem[j].key > ST.elem[j + 1].key)
			{
				Elemtype temp = ST.elem[j];
				ST.elem[j] = ST.elem[j + 1];
				ST.elem[j + 1] = temp;
			}
		}
	}
}

int Search_Bin(SSTable ST, KeyType key) //�����������۰���ҵķǵݹ��㷨
{
	sortTable(ST); //��˳���ST����
	int low = 1, high = ST.length, mid;	//��������ұ�־λ
	while (low <= high)	//���ӱ����
	{
		mid = (low + high) >> 1;	//�����м�λ��
		if (key == ST.elem[mid].key)
			return mid;	//�ҵ�������Ԫ��
		else
			if (key < ST.elem[mid].key)
				high = mid - 1;	//û���ҵ��ҵ�ǰmidָ��С�������������ǰ���������
			else
				low = mid + 1;	//��֮�ں���������
	}
	return 0;	//û�в鵽
}

int Search_Bin_recur(SSTable ST, KeyType key,int low,int high) //�����������۰���ҵĵݹ��㷨
{
	sortTable(ST); //��˳���ST����
	int i = low;
	int j = high;
	int mid = (low + high) >> 1;
	if (i > j)
		return 0;	//��������������䣬˵��û���ҵ�
	if (key == ST.elem[mid].key)
		return mid;	//�ҵ�������
	else
		if (key > ST.elem[mid].key)
			return (Search_Bin_recur(ST, key, mid + 1, j)); //���������۰����
		else
			return (Search_Bin_recur(ST, key, i, mid - 1)); //���������۰����
	return 0;	//û���ҵ�
}

void printTable(SSTable ST)
{
	int i;
	for (i = 1; i <= ST.length; i++)
	{
		printf("%d ", ST.elem[i].key);
	}
	printf("\n");
}