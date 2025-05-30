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
//保存卡
int addCard(Card card) {
	lpCardNode cur = NULL;
	cur = (lpCardNode)malloc(sizeof(CardNode));
	if (cardList == NULL) {
		initNodeList();
	}
	if (cur != NULL) {
		cur->data = card;
		cur->next = NULL;
		lpCardNode temp = cardList; // 使用临时指针遍历，不修改头指针
		while (temp->next != NULL) { // 找到链表最后一个节点
			temp = temp->next;
		}
		temp->next = cur; //
		return 1;
	}
	return 0;
	/*cards[c_count] = card;
	c_count++;
	if (0 == saveCard(&card, CARDPATH))
		printf("添加卡信息失败！\n");	
	else		
		printf("添加卡信息成功！\n");	
	return TURE;*/
}
//释放内存
void releaseCardList(){
	lpCardNode cur;
	
		while (cardList != NULL) {
			cur = cardList;
			cardList = cur->next;
			free(cur);
			cur = NULL;
		}
}
//查询卡
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
//注销卡
int deleteCard(const char* pNumber) {
	lpCardNode prev = cardList;  // 头节点
	lpCardNode curr = cardList->next;  // 第一个数据节点

	while (curr != NULL) {
		if (strcmp(curr->data.c_Number, pNumber) == 0) {
			prev->next = curr->next;  // 跳过当前节点
			free(curr);  // 释放内存
			printf("卡号 %s 已删除\n", pNumber);
			return 1;  // 删除成功
		}
		prev = curr;
		curr = curr->next;
	}

	printf("未找到卡号 %s\n", pNumber);
	return 0;  // 未找到卡
}
//修改卡
int modifyCard(const char* pNumber) {
	lpCardNode curr = cardList->next;  // 第一个数据节点
	if (cardList == NULL) { // 头节点未初始化
		printf("链表未初始化\n");
		return 0;
	}
	if (cardList->next == NULL) { // 无数据节点
		printf("链表中无卡信息\n");
		return 0;
	}
	while (curr != NULL) {
		if (strcmp(curr->data.c_Number, pNumber) == 0) {
			char choice;
			printf("找到卡号 %s,修改：\n", pNumber);
			char newPassword[9];
			printf("输入新密码：");
			scanf("%s", newPassword);
			if (getSize(newPassword) > 8) {
				printf("密码超过规定长度\n");
				return 0;
			}
			strcpy(curr->data.c_Password, newPassword);
			float newMoney;
			printf("输入新余额：");
			scanf("%f", &newMoney);
			curr->data.c_Money = newMoney;
		}
		curr = curr->next;
	}
	return 0;  // 未找到卡
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
//}//模糊查询
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