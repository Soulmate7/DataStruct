#pragma once
#include<stdio.h>
#include<stdlib.h>

typedef int DLinkType;

typedef struct DLinkNode {	//˫��������
	DLinkType data;
	struct DLinkNode* _next;
	struct DLinkNode* _prior;

}DLinkNode;



typedef struct DLinkList {
	DLinkNode* head;	//ͷָ��
	DLinkNode* tail;	//βָ��
	int size;
}DLinkList;

//����һ�����
DLinkNode* CreatNewNode(DLinkType value) {
	DLinkNode* Node = (DLinkNode*)malloc(sizeof(DLinkNode));
	if (!Node)
	{
		printf("ERROR\n");
		exit(0);
	}
	if (Node != NULL) {
		Node->data = value;
		Node->_next = NULL;
		Node->_prior = NULL;
	}
	return Node;
}

//�ͷ�һ�����
void DestoryNode(DLinkNode** node) {
	if (node == NULL) {

		printf("ERROR\n");
		exit(0);
	}

	if (*node == NULL) {

		printf("ERROR\n");
		exit(0);
	}
	free(*node);
	*node = NULL;
}



//��ʼ��˫������

DLinkList* InitDLinkList() {
	DLinkList* plist = (DLinkList*)malloc(sizeof(DLinkList));
	plist->head = CreatNewNode('0');
	if (plist != NULL) {
		if (plist->head != NULL) {
			plist->head = plist->head;
			plist->tail = plist->head;
			plist->size = 0;
		}
		else {
			return NULL;
		}
	}
	return plist;
}



//�ж������Ƿ�Ϊ��

bool DLinkListEmpty(DLinkList* plist) {
	if (plist == NULL) {
		printf("ERROR\n");
		exit(0);
	}

	if (plist->tail == plist->head && plist->size == 0) {
		return true;
	}
	return false;
}

//β��һ��Ԫ��
DLinkNode* DLinkListPushBack(DLinkList* plist, DLinkType value) {
	if (plist->head == NULL) {
		printf("ERROR\n");
		exit(0);
	}
	DLinkNode* InsertNode = CreatNewNode(value);
	DLinkNode* cur = plist->head;
	//��������cur�����βָ��λ��
	while (cur != plist->tail) {
		cur = cur->_next;
	}
	cur->_next = InsertNode;
	InsertNode->_prior = cur;
	plist->tail = InsertNode;
	plist->size++;
	return InsertNode;
}



//��ӡ��������

void PrintChar(DLinkList* plist, char* msg) {
	if (plist == NULL) {
		return;
	}
	printf("%s\n", msg);
	DLinkNode* cur1 = plist->head->_next;
	DLinkNode* cur2 = plist->tail;
	if (cur1 == NULL || cur2->_prior == plist->head) {
		//������
		printf("\n\n[head]<-[tail]\n\n");
		return;
	}
	
	//���Ŵ�ӡ
	printf("\n\n\n[head]->");
	for (; cur1 != plist->tail; cur1 = cur1->_next) {
		printf("[%c]->", cur1->data);
	}

	printf("[%c]<-[tail]", cur1->data);
	
	//���Ŵ�ӡ
	printf("\n\n\n[tail]->");

	for (; cur2 != plist->head; cur2 = cur2->_prior) {
		printf("[%c]->", cur2->data);
	}

	printf("[head]\n\n\n");
}



//βɾһ��Ԫ��

void DLinkListPopBack(DLinkList* plist) {

	if (plist == NULL) {
		printf("ERROR\n");
		exit(0);
	}

	DLinkNode* cur = plist->head;

	while (cur->_next != plist->tail) {
		cur = cur->_next;
	}

	DLinkNode* Delete = cur->_next;

	plist->tail = cur;

	Delete->_prior = NULL;

	cur->_next = NULL;

	plist->size--;

	DestoryNode(&Delete);
}



//ͷ��һ��Ԫ��

void DLinkListPushFront(DLinkList* plist, DLinkType value) {

	if (plist == NULL) {
		printf("ERROR\n");
		exit(0);
	}
	DLinkNode* node = CreatNewNode(value);

	DLinkNode* cur = plist->head->_next;

	plist->head->_next = node;

	node->_prior = plist->head;

	node->_next = cur;

	cur->_prior = node;

	plist->size++;
}



//ͷɾһ��Ԫ��

void DLinkListPopFront(DLinkList* plist) {
	if (plist == NULL) {
		printf("ERROR\n");
		exit(0);
	}

	//����Ҫɾ����Ԫ��

	DLinkNode* Delete = plist->head->_next;

	DLinkNode* cur = plist->head->_next->_next;

	plist->head->_next = cur;

	cur->_prior = plist->head;

	plist->size--;

	DestoryNode(&Delete);
}



//����ĳ��Ԫ��

DLinkNode* DLinkListFind(DLinkList* plist, DLinkType to_find) {
	if (plist == NULL) {
		printf("ERROR\n");
		exit(0);
	}

	DLinkNode* cur = plist->head;

	while (cur != plist->tail) {

		cur = cur->_next;

		if (cur->data == to_find) {
			//����ҵ���һ��ֵ��ȵ�Ԫ�أ��ͷ���cur
			return cur;
		}

	}

	//�������ʧ���ˣ��ǵ��ͷŽ��

	DLinkNode* error = CreatNewNode('-1');

	printf("������δ�����Ԫ��");

	return error;
}



//��ָ��λ��֮ǰ����һ��Ԫ��

void DLinkListInsert(DLinkList* plist, DLinkNode* pos, DLinkType value) {
	if (pos == NULL) {
		printf("ERROR\n");
		exit(0);
	}

	DLinkNode* cur = CreatNewNode(pos->data);

	DLinkNode* pos_next = pos->_next;

	//�ж�pos�Ƿ������һ��Ԫ��

	if (pos_next == NULL) {
		pos->_next = cur;

		cur->_prior = pos;

		pos->data = value;

		plist->tail = cur;

		plist->size++;
	}

	else {

		pos->_next = cur;

		cur->_prior = pos;

		cur->_next = pos_next;

		pos_next->_prior = cur;

		pos->data = value;

		plist->size++;
	}
}



//��ָ��λ��֮�����һ��Ԫ��

void DLinkListInsertAfter(DLinkList* plist, DLinkNode* pos, DLinkType value) {
	if (plist == NULL) {
		printf("ERROR\n");
		exit(0);
	}

	//�����½��

	DLinkNode* insert = CreatNewNode(value);

	DLinkNode* pos_next = pos->_next;

	if (pos_next == NULL) {

		//��ǰ��������һ�����

		pos->_next = insert;

		insert->_prior = pos;

		//����βָ���������size

		plist->size++;

		plist->tail = insert;

	}

	else {

		//����

		pos->_next = insert;

		insert->_prior = pos;

		insert->_next = pos_next;

		pos_next->_prior = insert;

		//����������size

		plist->size++;
	}

}



//ɾ��ָ��λ�õ�Ԫ��

void DLinkListErase(DLinkList* plist, DLinkNode* pos) {
	if (plist == NULL) {
		printf("ERROR\n");
		exit(0);
	}

	DLinkNode* cur = plist->head;

	while (cur->_next != pos) {

		cur = cur->_next;

		if (cur->_next == NULL) {

			printf("posλ�ô������");

			return;

		}
	}

	DLinkNode* Delete = pos;

	DLinkNode* pos_next = pos->_next;

	if (pos_next == NULL) {

		//posΪ���һ��Ԫ��

		cur->_next = NULL;

		//��������size���ͷ�ɾ���Ľ��Ŀռ�

		plist->tail = cur;

		plist->size--;

		DestoryNode(&pos);
	}

	else {
		//��ʼ������

		cur->_next = pos_next;

		pos_next->_prior = cur;

		plist->size--;

		DestoryNode(&pos);

	}
}



//ɾ��ָ��ֵ��Ԫ��

void DLinkListRemove(DLinkList* plist, DLinkType to_delete) {
	if (plist == NULL) {
		printf("ERROR\n");
		exit(0);
	}

	DLinkNode* cur = plist->head;

	while (cur->_next->data != to_delete) {
		cur = cur->_next;

		if (cur->_next == NULL) {

			printf("�����в鲻����Ԫ��\n");

			return;

		}
	}

	DLinkNode* del_next = cur->_next->_next;

	DLinkNode* Delete = cur->_next;

	if (del_next == NULL) {

		//����Ҫɾ����Ԫ��λ����������һλ����ôde_nextһ��Ϊ��ָ��

		cur->_next = NULL;

		//����βָ�룬size�������ͷ�ɾ���Ľ��

		plist->tail = cur;

		plist->size--;

		DestoryNode(&Delete);
	}

	else {
		//������

		cur->_next = del_next;

		del_next->_prior = cur;

		plist->size--;

		DestoryNode(&Delete);

	}
}



//ɾ������ָ��ֵ��Ԫ��

void DLinkListRemoveAll(DLinkList* plist, DLinkType to_delete) {
	if (plist == NULL) {
		printf("ERROR\n");
		exit(0);
	}

	int sz = plist->size;

	while (sz--) {
		//ɾ������ָ��ֵ��Ԫ��
		DLinkListRemove(plist, to_delete);
	}
}



//ɾ��һ�����������Ԫ��

void DLinkListClear(DLinkList* plist) {
	if (plist == NULL) {

		return;

	}

	DLinkNode* cur = plist->head->_next;

	DLinkNode* to_free = plist->head->_next;

	plist->tail = plist->head;

	while (cur->_next != NULL) {
		cur = cur->_next;

		DestoryNode(&to_free);

		to_free = cur;
	}

	DestoryNode(&to_free);

	plist->head->_next = NULL;
}
