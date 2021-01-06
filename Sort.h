#pragma once
#include<stdio.h>
#include<stdlib.h>
#include"SqList.h" //��˳�������
#include"LNode.h"

void InsertSort(SqList &L)	//ֱ�Ӳ�������
{
	int i, j;
	for (i = 2; i <= L.length; ++i)
	{
		L.elem[0] = L.elem[i];	//�ڱ�λ���Ƶ�ǰֵ
		for (j = i - 1; L.elem[0] < L.elem[j]; --j)
		{
			L.elem[j + 1] = L.elem[j];	//��¼����
		}
		L.elem[j + 1] = L.elem[0];	//���뵽��ȷλ��
	}
}

void InsertSort_Node(LinkList &L)	//�������ֱ�Ӳ������򡣷��������
{
	LNode *p, *q, *insert;
	p = L->next;	//pָ��ʼ���
	q = p->next;	//qָ��ڶ������
	p->next = NULL;	//��L����ʼ����Ժ��ÿ�
	p = q;	//��p��ԭL��ĵڶ�����㿪ʼ���൱��˳����дӵڶ���Ԫ�ؿ�ʼѭ��
	while (p)
	{
		q = p->next;	//q����ָ��ԭ������ֹ����
		insert = L;	//�ӱ�ͷ��ʼ�Ҳ���λ��
		while (insert->next != NULL && insert->next->data < p->data)
		{
			insert = insert->next;	//�ҵ�����λ��
		}
		p->next = insert->next;
		insert->next = p;
		p = q;
	}
}

void BInsertSort(SqList &L)	//��˳�������۰��������
{
	int i, j, low, high, mid;
	for (i = 2; i <= L.length; i++)
	{
		L.elem[0] = L.elem[i];	//�ڱ�λ���Ƶ�ǰֵ
		low = 1;
		high = i - 1;
		while (low <= high)	//�����൱���۰���Ҳ�ѯ�����ڵ�Ԫ�أ�����ʱ��lowֵ(high+1)ǡ����Ӧ�ò����λ��
		{
			mid = (low + high) / 2;
			if (L.elem[0] < L.elem[mid])
				high = mid - 1;	//���L.elem[0]<L.elem[mid]������ڵͰ���
			else
				low = mid + 1;	//��֮����߰���
		}
		for (j = i - 1; j >= high + 1; --j)
			L.elem[j + 1] = L.elem[j];	//��¼����
		L.elem[high + 1] = L.elem[0];
	}
}

SqList TwoPathInsert(SqList &L)	//2·����
{
	int *d;	//��������d���洢����������������Ұ�d�����ѭ���ģ�������first��finalָ��
	int first = 0, final = 0; //first��final�ֱ���d�е���Сֵ�����ֵָ�򣬳�ʼΪ0�����ᣩ
	int i, j;

	d = (int*)malloc(L.length * sizeof(int));	//��ʼ����������
	for (i = 1; i < L.length; i++)
	{
		d[i] = 0;
	}
	d[0] = L.elem[1];
	printf("����forѭ��֮ǰ:\n");
	printf("d[%d]=%d, L.elem[%d]=%d\n\n", 0, d[0], 1, L.elem[1]);

	for (i = 2; i <= L.length; i++)	//��d���������
	{
		printf("��ǰָ��%d \n", L.elem[i]);
		if (L.elem[i] >= d[final])	//�����ǰֵ���ڵ���d�����ֵ
		{
			d[++final] = L.elem[i];	//final���Ʋ���d�в���ֵ
			printf("ִ�е�һ��if���\n");
			printf("first=%d, final=%d\n", first, final);
			printf("d[%d]=%d��L.elem[%d]=%d\n\n",final, d[final],i,L.elem[i]);
		}
		else
			if (L.elem[i] <= d[first])	//�����ǰֵС�ڵ���d����Сֵ
			{
				first = (first - 1 + L.length) % L.length;	//��β����ʼ����ǰ��ֵ(����ѭ������)
				d[first] = L.elem[i];
				printf("ִ�еڶ���if���\n");
				printf("first=%d, final=%d\n", first, final);
				printf("d[%d]=%d��L.elem[%d]=%d\n\n",first, d[first],i,L.elem[i]);
			}
			else
				if (L.elem[i] >= d[0] && L.elem[i] < d[final])	//�����ǰֵ���Ҳ�����
				{
					for (j = final++; L.elem[i] < d[j]; j--)	//ֱ�Ӳ�������ע������finalλ�ú���
					{
						d[j+1] = d[j];
					}
					d[j + 1] = L.elem[i];
					printf("ִ�е�����if���\n");
					printf("first=%d, final=%d\n", first, final);
					printf("d[%d]=%d��L.elem[%d]=%d\n\n", j+1, d[j+1], i, L.elem[i]);
				}
				else
					if (L.elem[i] > d[first] && L.elem[i] < d[0])	//�����ǰֵ���������
					{
						for (j = first--; L.elem[i] > d[j] && j<L.length; j++)	//ֱ�Ӳ������򣨷����෴����ע������firstǰ��
						{
							printf("j=%d\n", j);
							d[j - 1] = d[j];
						}
						d[j-1] = L.elem[i];
						printf("ִ�е��ĸ�if���\n");
						printf("first=%d, final=%d\n", first, final);
						printf("d[%d]=%d��L.elem[%d]=%d\n\n", j - 1, d[j - 1], i, L.elem[i]);
					}
	}

	printf("�����d���飺\n");
	printf("first=%d, final=%d\n", first, final);
	j = first;
	for (i = 1,j; i <= L.length; i++,j=(j+1)%L.length)
	{
		printf("d[%d]=%d\n",j, d[j]);
		L.elem[i] = d[j];
	}
	return L;
}

void ShellSort(SqList &L)	//ϣ������
{
	int i, j, k;
	int gap; //gap�Ƿ��鲽�����������Ƕ��忪ʼ����Ϊlength/2��ÿ������Ϊһ�룬���Ⲣ����Ч����ߵķ���
	for (gap = L.length / 2; gap >=1; gap /= 2)
	{
		for (i = 1; i <= gap; i++)	//��gap����
		{
			for (j = i + gap; j <= L.length; j += gap)	//һ�β��������õ�ֱ�Ӳ�������
			{
				if (L.elem[j] < L.elem[j - gap])
				{
					L.elem[0] = L.elem[j];
					for (k = j - gap; L.elem[0] < L.elem[k] && k>0; k -= gap)	//ע����Ϊÿ����ǰgap��Ҫ�ж���û��Խ��(k>0)
					{
						L.elem[k + gap] = L.elem[k];	//����λ��
					}
					L.elem[k + gap] = L.elem[0];
				}
			}
		}
	}
}

void BubbleSort(SqList &L)	//ð������
{
	int i, j, temp;	//��΢�Ż�һ�¾��ǵ�����һ�˶�û�з�������ʱ��ǰ�˳����������Ż����Լ�¼��һ������λ��
	for (i = 1; i <= L.length; i++)	//ȷ����������
	{
		int flag = 0;
		for (j = 1; j <= L.length - i; j++)	//ȷ���Ƚϴ���
		{
			if (L.elem[j] > L.elem[j + 1])
			{
				temp = L.elem[j];
				L.elem[j] = L.elem[j + 1];
				L.elem[j + 1] = temp;
				flag = 1;	//���������־λ1
			}
		}
		if (flag == 0)	//û�з����������˳�
			break;
	}
}

int Partition(SqList &L, int low, int high) //һ�˿������򣨻��֣�
//����˳���L���ӱ�r[low...high]�ļ�¼�������¼��Ϊ��������������λ�á���ʱ��֮ǰ���󣩵ļ�¼����С������
{
	L.elem[0] = L.elem[low];	//���ӱ�ĵ�һ����¼��Ϊ�����¼
	int pivotkey = L.elem[0];	//������ʵ��Ϊ�˱���keyֵ����ΪElemtype���ܲ�ֹһ��ֵ
	while (low < high)	//�ӱ�����˽�������м�ɨ��
	{	//��low==highʱ����λ�ü������¼Ӧ�ñ����õ�λ��
		while (low < high && L.elem[high] >= pivotkey)
			--high;
		L.elem[low] = L.elem[high];	//���������¼С�ļ�¼�Ƶ��Ͷ�
		while (low < high && L.elem[low] <= pivotkey)
			++low;
		L.elem[high] = L.elem[low];	//���������¼��ļ�¼�Ƶ��߶�
	}
	L.elem[low] = L.elem[0];	//�����¼��λ
	return low;	//��������λ��
}

void QuickSort(SqList &L,int low,int high)  //�������򣬶�˳���L��������r[low..high]����������
{
	int pivotloc;
	if (low < high)	//���������䳤�ȴ���1��������ֱ�ӷ���
	{
		pivotloc = Partition(L, low, high);	//��r[low..high]һ��Ϊ����pivotloc��һ�˿�����������������λ��
		QuickSort(L, low, pivotloc - 1);	 //�Ե��ӱ�ݹ�����
		QuickSort(L, pivotloc + 1, high);	 //�Ը��ӱ�ݹ�����
	}
}

int SelectMinKey(SqList L, int i)	//�ҵ�˳���L[i..L.length]����С��¼���±�
{
	int min = L.elem[i], m, n = i;
	for (m = i+1; m <= L.length; m++)
	{
		if (L.elem[m] <= min)
		{
			min = L.elem[m];
			n = m;
		}
	}
	return n;
}

void SelectSort(SqList &L)	//ѡ������ÿ���ҵ���nС�ļ�¼���Ƶ�λ��n�����һ���ҵ���1С���Ƶ�L.elem[1]
{
	int i, j;
	for (i = 1; i < L.length; i++)
	{
		j = SelectMinKey(L, i);	//�ҵ�key��С�ļ�¼
		if (i != j)
		{
			int temp;
			temp = L.elem[i];
			L.elem[i] = L.elem[j];	//���j����¼����λ��
			L.elem[j] = temp;
		}
	}
}

//�����Ƕ�����Ĳ���
void Swap(SqList L, int i, int k)	//������������Ҫ���ڶѶ��Ͷѵ׵���
{
	int temp = L.elem[i];
	L.elem[i] = L.elem[k];
	L.elem[k] = temp;
}


void Max_Heapify(SqList L, int start, int end)	//��˳������飩���������
{
	//�������ڵ��±���ӽڵ��±�
	int dad = start;	

	int son = dad * 2;	//�������±��0��ʼʱ��ӦΪson=dad*2+1

	while (son <= end)
	{   //���ӽڵ��±��ڷ�Χ�ڲ����Ƚ�
		if (son + 1 <= end && L.elem[son] < L.elem[son + 1]) //�ȱȽ������ӽڵ��С��ѡ������
		{
			son++;
		}

		if (L.elem[dad] > L.elem[son]) //������ڵ�����ӽڵ����������,ֱ������
		{
			return;
		}
		else
		{   //���򽻻����ӽڵ��ֵ�ټ��������ӽڵ�ֵ�ñȽ�
			Swap(L, dad, son);
			printf("dad=%d, son=%d\n", dad, son);
			dad = son;
			son = dad * 2;
		}
	}
}

void Heap_Sort(SqList L)
{
	int i;
	//��ʼ����i�����һ�����ڵ㿪ʼ����
	for (i = L.length / 2; i >= 1; i--)
	{
		Max_Heapify(L, i, L.length);
	}

	for (i = L.length; i >= 1; i--)
	{
		Swap(L, 1, i);
		Max_Heapify(L, 1, i);
	}
}