#define _CRT_SECURE_NO_WARNINGS
#include<string.h>
#include<stdlib.h>
#include"model.h"
#include"global.h"
#include"card_file.h"
Card cards[50];
int c_count = 0;
int addCard(Card card) {
	cards[c_count] = card;
	c_count++;
	if (0 == saveCard(&card, CARDPATH))
		printf("��ӿ���Ϣʧ�ܣ�\n");	
	else		
		printf("��ӿ���Ϣ�ɹ���\n");	
	return TURE;
}//���濨
Card* queryCard(const char* pName) {
	for (int i = 0; i < c_count; i++) {
		if (strcmp(pName, cards[i].c_Number) == 0) {
			return &cards[i];
		}
	}
	return NULL;
}//��ѯ��