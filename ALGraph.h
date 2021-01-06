#pragma once	//ͼ����ʽ��ʾ��
#include<stdio.h>
#include<stdlib.h>
#define MAX_VNUM 20	//��ඥ�����
bool visited[MAX_VNUM]; //��Ƕ����Ƿ񱻷��ʹ�
int indegree[MAX_VNUM]; //��������ʱ���ڴ�Ÿ���������
typedef int InfoType;	//�û������Ϣ��ָ��
typedef char VertexType;
typedef enum { DG, DN, UDG, UDN } GraphKind;

typedef struct ArcNode {	//�����еĽ��
	int adjvex;	//�û�ָ��Ķ����λ��
	struct ArcNode *nextarc;	//ָ����һ������ָ��
	InfoType info;	//��û���ص���Ϣ��������������ԣ��˴����Դ洢���ϵ�Ȩֵ
};
typedef struct VNode {	//��ͷ���
	VertexType data;	//������Ϣ�򶥵����
	ArcNode *firstarc;	//ָ���һ�������ö���Ļ���ָ��
}VNode,AdjList[MAX_VNUM];
typedef struct {	//ͼ���ڽӱ��ʾ
	AdjList vertices;	//һά�����ű�ͷ���
	int vexnum, arcnum;	//ͼ�ĵ�ǰ�������ͻ���
	GraphKind kind;	//ͼ�������־
}ALGraph;

#include"SqQueue.h"
#include"SqStack.h"

int LocateVex(ALGraph G, VertexType v) 
{
	int i;
	for (i = 0; i < G.vexnum; i++)
		if (G.vertices[i].data == v)
			return i;
	return -1;
}

void CreateUDN(ALGraph &G) 
{
	//�����ڽӱ��ʾ��������������G
	int i, k;
	G.kind = UDN;
	printf("�������ܶ��������ܱ������м��ÿո������\n");	
	scanf_s("%d %d", &G.vexnum, &G.arcnum);
	getchar();
	printf("\n");
	printf("�������ʾ���������ƣ���A\n");
	for (i = 0; i < G.vexnum; i++) 
	{	//������㣬������ͷ���
		printf("�������%d�����������:", (i + 1));
		scanf_s("%c",&G.vertices[i].data);
		G.vertices[i].firstarc = NULL;    //��ʼ����ͷ����ָ����ΪNULL
		getchar();
	}

	printf("\n");
	printf("������һ���������Ķ��㣬��:A B\n");
	for (k = 0; k < G.arcnum; k++)
	{
		VertexType v1, v2;
		int i, j, w;
		printf("�������%d���������Ķ���:", (k + 1));
		scanf_s("%c", &v1);		//����һ������������������
		getchar();
		scanf_s("%c", &v2);
		getchar();
		printf("\n");
		i = LocateVex(G, v1);	//ȷ��v1��v2��G�е�λ��
		j = LocateVex(G, v2);	//��������G.vertices(�ڽӱ�)�е����
		printf("������ñߵ�Ȩֵ:");
		scanf_s("%d", &w);
		getchar();
		printf("\n");
		ArcNode *p1 =(ArcNode*)malloc(sizeof(ArcNode));	 //����һ���µı߽��*p1
		p1->adjvex = j;		//�ڽӵ����Ϊj
		p1->nextarc = G.vertices[i].firstarc;	
		p1->info = w;
		G.vertices[i].firstarc = p1;	//���½ڵ�*p1����vi�ı߱�ͷ��

		ArcNode *p2 = (ArcNode*)malloc(sizeof(ArcNode)); //������һ���ԳƵ��µı߽��*p2
		p2->adjvex = i;					//�ڽӵ����Ϊi
		p2->nextarc = G.vertices[j].firstarc;
		p2->info = w;
		G.vertices[j].firstarc = p2;	//���½��*p2���붥��vj�ı߱�ͷ��
	}
}

void CreateUDG(ALGraph &G)
{
	//�����ڽӱ��ʾ������������ͼG
	int i, k;
	G.kind = UDG;
	printf("�������ܶ��������ܱ������м��ÿո������\n");
	scanf_s("%d %d", &G.vexnum, &G.arcnum);
	getchar();
	printf("\n");
	printf("�������ʾ���������ƣ���A\n");
	for (i = 0; i < G.vexnum; i++)
	{	//������㣬������ͷ���
		printf("�������%d�����������:", (i + 1));
		scanf_s("%c", &G.vertices[i].data);
		G.vertices[i].firstarc = NULL;    //��ʼ����ͷ����ָ����ΪNULL
		getchar();
	}

	printf("\n");
	printf("������һ���������Ķ��㣬��:A B\n");
	for (k = 0; k < G.arcnum; k++)
	{
		VertexType v1, v2;
		int i, j, w;
		printf("�������%d���������Ķ���:", (k + 1));
		scanf_s("%c", &v1);		//����һ������������������
		getchar();
		scanf_s("%c", &v2);
		getchar();
		printf("\n");
		i = LocateVex(G, v1);	//ȷ��v1��v2��G�е�λ��
		j = LocateVex(G, v2);	//��������G.vertices(�ڽӱ�)�е����
		printf("\n");
		ArcNode *p1 = (ArcNode*)malloc(sizeof(ArcNode));	 //����һ���µı߽��*p1
		p1->adjvex = j;		//�ڽӵ����Ϊj
		p1->nextarc = G.vertices[i].firstarc;
		(p1->info) = NULL;
		G.vertices[i].firstarc = p1;	//���½ڵ�*p1����vi�ı߱�ͷ��

		ArcNode *p2 = (ArcNode*)malloc(sizeof(ArcNode)); //������һ���ԳƵ��µı߽��*p2
		p2->adjvex = i;					//�ڽӵ����Ϊi
		p2->nextarc = G.vertices[j].firstarc;
		(p2->info) = NULL;
		G.vertices[j].firstarc = p2;	//���½��*p2���붥��vj�ı߱�ͷ��
	}
}

void CreateDG(ALGraph &G) {	//�����ڽӱ�����������ͼ
	G.kind = DG;
	int i, j, k;
	char v1, v2;
	ArcNode *p;
	printf("�������ܶ��������ܱ������м��ÿո������\n");
	scanf_s("%d %d", &G.vexnum, &G.arcnum);
	getchar();
	printf("�������ʾ���������ƣ���A\n");
	for (i = 0; i < G.vexnum; i++)
	{	//������㣬������ͷ���
		printf("�������%d�����������:", (i + 1));
		scanf_s("%c", &G.vertices[i].data);
		G.vertices[i].firstarc = NULL;    //��ʼ����ͷ����ָ����ΪNULL
		getchar();
	}
	printf("\n");
	printf("������ͼ�ıߵ���Ϣ��\n");
	for (k = 0; k < G.arcnum; k++)
	{
		printf("�������%d���ߵĻ�β:", (k + 1));
		scanf_s("%c", &v1);		//����һ������������������
		getchar();
		printf("�������%d���ߵĻ�ͷ:", (k + 1));
		scanf_s("%c", &v2);
		getchar();
		printf("\n");
		i = LocateVex(G, v1);
		j = LocateVex(G, v2);
		if (i >= 0 && j >= 0) {
			p = (ArcNode *)malloc(sizeof(ArcNode));
			p->adjvex = j;
			p->nextarc = G.vertices[i].firstarc;
			G.vertices[i].firstarc = p;
		}
	}
}

bool visit(ALGraph G, int v)	//����Gͼ���±�Ϊv�Ķ���
{
	if (G.vertices[v].data)
	{
		printf("%c", G.vertices[v].data);
		return true;
	}
	return false;
}

void DFS_recur(ALGraph G, int v)	//������ȱ���ͼ�ĵݹ��㷨
{
	visit(G, v);	//���ʶ���v0
	visited[v] = true;
	ArcNode *p = G.vertices[v].firstarc;
	while (p != NULL)	//��������ڽӵ�
	{
		if (!visited[p->adjvex])	//�ݹ�����ڽӵ�
			DFS_recur(G, p->adjvex);
		p = p->nextarc;
	}
}

void DFSTraverse_recur(ALGraph G,int i)
{
	int v;
	for (v = 0; v < G.vexnum; v++)
	{
		visited[v] = false;
	}
	if (!visited[i])
		DFS_recur(G, i);
	for (v = 0; v < G.vexnum; v++)
	{
		if (!visited[v])
			DFS_recur(G, v);
	}
}

void BFSTraverse(ALGraph G,int k)	//������ȱ����㷨
{
	int v, u;
	ArcNode *w;
	for (v = 0; v < G.vexnum; v++)
	{
		visited[v] = false;	//��־�����ʼ��
	}
	SqQueue Q;
	InitQueue(Q);	//��ʼ����������Q
	for (v = k; v < G.vexnum; v++)
	{
		if (!visited[v])	//v��δ����
		{
			visit(G,v);
			visited[v] = true;
			EnQueue(Q, v);	//v���
			while (!QueueEmpty(Q))
			{
				u = DeQueue(Q);	//��ͷԪ�س��Ӳ���Ϊu
				for (w = G.vertices[u].firstarc; w != NULL; w = w->nextarc) //wΪu����δ���ʹ����ڽӽ��
				{
					if (!visited[w->adjvex])
					{
						visit(G,w->adjvex);
						visited[w->adjvex] = true;
						EnQueue(Q, w->adjvex);
					}
				}
			}
		}
	}
	for (v = 0; v < k; v++)
	{
		if (!visited[v])	//v��δ����
		{
			visit(G, v);
			visited[v] = true;
			EnQueue(Q, v);	//v���
			while (!QueueEmpty(Q))
			{
				u = DeQueue(Q);	//��ͷԪ�س��Ӳ���Ϊu
				for (w = G.vertices[u].firstarc; w != NULL; w = w->nextarc) //wΪu����δ���ʹ����ڽӽ��
				{
					if (!visited[w->adjvex])
					{
						visit(G, w->adjvex);
						visited[w->adjvex] = true;
						EnQueue(Q, w->adjvex);
					}
				}
			}
		}
	}
}

void FindInDegree(ALGraph G, int indegree[MAX_VNUM])	//��ͼG�и��������Ȳ���������indegree��
{
	int i;
	ArcNode *p;
	for (i = 0; i < G.vexnum; i++)	//��ʼ��indegree����
		indegree[i] = 0;
	for (i = 0; i < G.vexnum; i++)	//�����ڽӱ�
	{
		p = G.vertices[i].firstarc;
		while (p != NULL)
		{
			indegree[p->adjvex]++;	//��ͼ��λ��Ϊp->adjvex�Ķ������ȼ�1
			p = p->nextarc;
		}
	}
}

void TopologicalSort(ALGraph G)	//����ͼ�����ڽӱ�洢�ṹ����G�޻�·�����G�Ķ����һ����������
{
	FindInDegree(G, indegree);
	SqStack S;
	InitStack(S);	//��ʼ������ջ
	ArcNode *p;
	int i, k, count = 0;	//countΪ���������ļ���
	for (i = 0; i < G.vexnum; i++)
	{
		if (indegree[i] == 0)
			Push(S, i);	//�����Ϊ0�Ķ�����ջ
	}
	while (!StackEmpty(S))
	{
		i = Pop(S);
		printf("%c", G.vertices[i].data);	//���i�Ŷ��㲢����
		count++;
		p = G.vertices[i].firstarc;
		while (p != NULL)
		{
			k = p->adjvex;
			indegree[k]--;
			if (indegree[k] == 0)
				Push(S, k);
			p = p->nextarc;
		}
	}
	if (count < G.vexnum)
	{
		printf("ͼ�д��ڻ�·���޷������������\n");
	}
}