#define _CRT_SECURE_NO_WARNINGS
#include<string.h>
#include<stdlib.h>
#include"model.h"
#include"global.h"
#include"card_file.h"
Card cards[50];
int c_count = 0;
lpCardNode cardList = NULL;
int initNodeList() {
	lpCardNode head = NULL;
	head = (lpCardNode)malloc(sizeof(CardNode));
	if (head != NULL) {
		head->next = NULL;
		cardList = head;
		return 1;
	}
	return 0;
}
//���濨
int addCard(Card card) {
	lpCardNode cur = NULL;
	cur = (lpCardNode)malloc(sizeof(CardNode));
	if (cardList == NULL) {
		initNodeList();
	}
	if (cur != NULL) {
		cur->data = card;
		cur->next = NULL;
		lpCardNode temp = cardList; // ʹ����ʱָ����������޸�ͷָ��
		while (temp->next != NULL) { // �ҵ��������һ���ڵ�
			temp = temp->next;
		}
		temp->next = cur; //
		return 1;
	}
	return 0;
	/*cards[c_count] = card;
	c_count++;
	if (0 == saveCard(&card, CARDPATH))
		printf("��ӿ���Ϣʧ�ܣ�\n");	
	else		
		printf("��ӿ���Ϣ�ɹ���\n");	
	return TURE;*/
}
//�ͷ��ڴ�
void releaseCardList(){
	lpCardNode cur;
	
		while (cardList != NULL) {
			cur = cardList;
			cardList = cur->next;
			free(cur);
			cur = NULL;
		}
}
//��ѯ��
Card* queryCard(const char* pName) {
	/*for (int i = 0; i < c_count; i++) {
		if (strcmp(pName, cards[i].c_Number) == 0) {
			return &cards[i];
		}
	}*/
	lpCardNode cur = NULL;
	if (cardList != NULL) {
		cur = cardList->next;
		while (cur != NULL) {
			if (strcmp(cur->data.c_Number, pName) == 0) {
				return &cur->data;
			}
			cur = cur->next;
		}
	}
	return NULL;
}
//ע����
int deleteCard(const char* pNumber) {
	lpCardNode prev = cardList;  // ͷ�ڵ�
	lpCardNode curr = cardList->next;  // ��һ�����ݽڵ�

	while (curr != NULL) {
		if (strcmp(curr->data.c_Number, pNumber) == 0) {
			prev->next = curr->next;  // ������ǰ�ڵ�
			free(curr);  // �ͷ��ڴ�
			printf("���� %s ��ɾ��\n", pNumber);
			return 1;  // ɾ���ɹ�
		}
		prev = curr;
		curr = curr->next;
	}

	printf("δ�ҵ����� %s\n", pNumber);
	return 0;  // δ�ҵ���
}
//�޸Ŀ�
int modifyCard(const char* pNumber) {
	lpCardNode curr = cardList->next;  // ��һ�����ݽڵ�
	if (cardList == NULL) { // ͷ�ڵ�δ��ʼ��
		printf("����δ��ʼ��\n");
		return 0;
	}
	if (cardList->next == NULL) { // �����ݽڵ�
		printf("�������޿���Ϣ\n");
		return 0;
	}
	while (curr != NULL) {
		if (strcmp(curr->data.c_Number, pNumber) == 0) {
			char choice;
			printf("�ҵ����� %s,�޸ģ�\n", pNumber);
			char newPassword[9];
			printf("���������룺");
			scanf("%s", newPassword);
			if (getSize(newPassword) > 8) {
				printf("���볬���涨����\n");
				return 0;
			}
			strcpy(curr->data.c_Password, newPassword);
			float newMoney;
			printf("��������");
			scanf("%f", &newMoney);
			curr->data.c_Money = newMoney;
		}
		curr = curr->next;
	}
	return 0;  // δ�ҵ���
}
//Card* queryCards(const char* pName,  int* pIndex) {
//	lpCardNode cur = NULL;
//	Card* pCard = (Card*)malloc(sizeof(Card));
//	if (pCard == NULL) {
//		return NULL;
//	}
//	if (cardList != NULL) {
//		cur = cardList->next;
//		while (cur != NULL) {
//			if (strstr(cur->data.c_Number, pName) != NULL) {
//				pCard[*pIndex] = cur->data;
//				(*pIndex)++;
//				pCard = (Card*)realloc(pCard, (*pIndex) * sizeof(Card));
//			}
//			cur = cur->next;
//		}
//	}
//	return NULL;
//}//ģ����ѯ
//Card* doLogon(const char* pNumber, const char* pwd) {
//	lpCardNode cardNode = NULL;
//	if (0 == getCard()) {
//		return NULL;
//	}
//	cardNode = cardList->next;
//	while (cardNode != NULL) {
//		if (strcmp(cardNode->data.c_Number, pNumber) == 0 && strcmp(cardNode->data.c_Password, pwd)) {
//			cardNode->data.c_Status = 1;
//			cardNode->data.count++;
//			cardNode->data.tLast = time(NULL);
//			return &cardNode->data;
//		}
//	}
//	return NULL;
//}