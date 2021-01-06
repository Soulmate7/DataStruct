#pragma once		//ͼ�������ʾ��
#include<stdio.h>
#include<limits.h>
#define INFINITY INT_MAX	//���ֵ��
#define MAX_VNUM 20	//��󶥵����
typedef enum {DG,DN,UDG,UDN} GraphKind;	//{����ͼ��������������ͼ��������}
typedef int VRType; //VRType�Ƕ����ϵ���ͣ�����Ȩͼ��1��0��ʾ�Ƿ����ڣ��Դ�Ȩͼ����ΪȨֵ����
typedef char InfoType;	//�û������Ϣ��ָ��(�������Ϣһ��ָȨֵ)
typedef char VertexType;	//�������
bool visited[MAX_VNUM]; //��Ƕ����Ƿ񱻷��ʹ�

typedef struct ArcCell {	//�ڽӾ����е�ÿ����㶨��
	VRType adj;
	InfoType *info;
}ArcCell,AdjMatrix[MAX_VNUM][MAX_VNUM];

typedef struct {
	VertexType vexs[MAX_VNUM]; //һά�����ʾ��������
	AdjMatrix arcs;	//��ά�����ʾ�ڽӾ���
	int vexnum, arcnum;	//ͼ�ĵ�ǰ�������ͻ���
	GraphKind kind;	//ͼ�������־
}MGraph;

#include"SqStack.h"
#include"SqQueue.h"

int LocateVex(MGraph G, VertexType v)	//�󶥵�v��ͼG�е�λ�ã����±꣩
{
	int j = -1, k;
	for (k = 0; k < G.vexnum; k++)
	{
		if (G.vexs[k] == v)
		{
			j = k;
			break;
		}
	}
	return j;
}

void CreateUDN(MGraph &G)	//���������ʾ������������G
{
	int IncInfo, i, j, k;
	G.kind = UDG;
	printf("�������������������Ķ������������Լ��Ƿ��л���������Ϣ:��IncInfoΪ0���������������Ϣ��\n");
	scanf_s("%d %d %d",&G.vexnum, &G.arcnum, &IncInfo); //IncInfoΪ0���������������Ϣ
	printf("����������Ϣ�����֣�:\n");
	getchar();

	for (i = 0; i < G.vexnum; i++)	//���춥������
	{
		printf("vexnum[%d]:",i);
		scanf_s("%c",&G.vexs[i]);	//���붥�����֣���v1��v2
		printf("\n");
		getchar();
	}

	for (i = 0; i < G.vexnum; i++)	//��ʼ���ڽӾ���
	{
		for (j = 0; j < G.vexnum; j++)
		{
			G.arcs[i][j] = { INFINITY,NULL };	 //{adj,info}
		}
	}

	for (k = 0; k < G.arcnum; k++)	//�����ڽӾ���
	{
		VertexType v1, v2;
		VRType w;
		printf("�������һ�������Ķ���:\n");
		scanf_s("%c", &v1);  //����һ���������Ķ����Ȩֵ
		getchar();
		printf("������ڶ��������Ķ���:\n");
		scanf_s("%c", &v2);
		getchar();
		printf("������Ȩֵ:\n");
		scanf_s("%d", &w);
		getchar();
		i = LocateVex(G, v1);	//ȷ��v1��v2��G�е�λ��
		j = LocateVex(G, v2);
		G.arcs[i][j].adj = w;	//��<v1,v2>��Ȩֵ
		if (IncInfo)	//�������������Ϣ��������
			gets_s(G.arcs[i][j].info,sizeof(G.arcs[i][j].info));
		G.arcs[j][i] = G.arcs[i][j];	//��<v1,v2>�ĶԳƻ�<v2,v1>
		printf("\n");
	}
}

int FirstAdjVex(MGraph G, int v)	//�����������±�Ϊv�Ķ���֮���бߵĶ��㣬���������±�
{
	for (int i = 0; i < G.vexnum; i++)
	{
		if (G.arcs[v][i].adj)
			return i;
	}
	return -1;
}

int NextAdjVex(MGraph G, int v, int w)	//�����±�Ϊv�Ķ��� ��� �±�Ϊw�Ķ��� ����һ������
{
	for (int i = w + 1; i < G.vexnum; i++)
	{
		if (G.arcs[v][i].adj)
			return i;
	}
	return -1;
}

bool visit(MGraph G, int v)	//����Gͼ���±�Ϊv�Ķ���
{
	if (G.vexs[v])
	{
		printf("%c", G.vexs[v]);
		return true;
	}
	return false;
}

void DFS_recur(MGraph G, int v)	//�ӵ�v����������ݹ��������ȱ���ͼG
{
	int w;
	visited[v] = true;
	visit(G, v);	//���ʵ�v������
	for (w = FirstAdjVex(G, v); w >= 0; w = NextAdjVex(G, v, w))
	{
		if (!visited[w])	//��v����δ���ʵ��ڽӶ���w�ݹ����DFS
			DFS_recur(G, w);
	}
}

void DFSTraverse_recur(MGraph G)	//��ͼG��������ȱ����ĵݹ��㷨
{
	int v;
	for (v = 0; v < G.vexnum; v++)	//���ʱ�־�����ʼ��
	{
		visited[v] = false;
	}
	for (v = 0; v < G.vexnum; v++)	//����δ���ʵĶ������DFS
	{
		if (!visited[v])
			DFS_recur(G, v);
	} 
}

void DFSTraverse(MGraph G,int v0)	//��ͼG��������ȱ����ķǵݹ��㷨�����ͼ�д��ڻ�����Ԫ���ظ���ջ
{
	int v, w;
	SqStack S;
	InitStack(S);
	Push(S, v0);	//��v�����������������ͼG
	while (!StackEmpty(S))
	{
		v = Pop(S);
		if (!visited[v])
		{
			visit(G, v);
			visited[v] = true;
		}
		w = FirstAdjVex(G, v);
		while (w != -1)
		{
			if (!visited[w])
				Push(S, w);
			w = NextAdjVex(G, v, w);
		}
	}
}

void BFSTraverse(MGraph G)
{
	int v, u, w;
	for (v = 0; v < G.vexnum; v++)
	{
		visited[v] = false;
	}
	SqQueue Q;
	InitQueue(Q);	//�ÿյĸ�������Q
	for (v = 0; v < G.vexnum; v++)
	{
		if (!visited[v])	//v��δ����
		{
			visited[v] = true;
			visit(G,v);
			EnQueue(Q, v);	//v�����
			while (!QueueEmpty(Q))
			{
				u = DeQueue(Q);	//��ͷԪ�س���
				for (w = FirstAdjVex(G, u); w >= 0; w = NextAdjVex(G, u, w))
				{
					if (!visited[w])	//wΪu����δ���ʵ��ڽӶ���
					{
						visited[w] = true;
						visit(G,w);
						EnQueue(Q, w);
					}
				}
			}
		}
	}
}

struct AssistArray{	//��¼�Ӷ��㼯U��V-U�Ĵ�����С�ıߵĸ������鶨�壬��������С������
	VertexType adjvex;
	VRType lowcost;
}closedge[MAX_VNUM];

int minimum(AssistArray *closedge)	//����Ȩֵ��С�ı߶�Ӧ�Ľ���±�
{
	int i, min;
	VertexType minvex;
	for (i = 0; i < MAX_VNUM; i++)
	{
		if (closedge[i].lowcost != 0)
		{
			min = closedge[i].lowcost;
			minvex = closedge[i].adjvex;
		}
	}
	for (i = 0; i < MAX_VNUM; i++)
	{
		if ((closedge[i].lowcost < min) && (closedge[i].lowcost != 0))
		{
			min = closedge[i].lowcost;
			minvex = closedge[i].adjvex;
		}
	}
	for (i = 0; i < MAX_VNUM; i++)
	{
		if (closedge[i].lowcost==min)
			break;
	}
	return i;
}

void MiniSpanTree_PRIM(MGraph G, VertexType u)	//����ķ�㷨�ӵ�u���������������G����С������T�����T�ĸ�����
{
	int i, j, k = LocateVex(G, u);	//�󶥵�u��λ��
	for (j = 0; j < G.vexnum; j++)	//���������ʼ��
	{
		if (j != k)
			closedge[j] = { u,G.arcs[k][j].adj };	//{adjvex,lowcost}
	}	
	closedge[k].lowcost = 0;	//��ʼ��U={u}
	for (i = 1; i < G.vexnum; i++)	//ѡ������G.vexnum-1������
	{
		k = minimum(closedge);	//���T����һ�����㣬��k����
		printf("%c %c\n", closedge[k].adjvex, G.vexs[k]);
		closedge[k].lowcost = 0;	//��k���㲢��U��
		for (j = 0; j < G.vexnum; j++)  //�¶��㲢��U������ѡ����С��
		{
			if (G.arcs[k][j].adj < closedge[j].lowcost)
				closedge[j] = { G.vexs[k],G.arcs[k][j].adj };
		}
	}
}