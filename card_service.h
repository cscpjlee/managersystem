#pragma once
#include"model.h"
int addCard(Card card);//���濨
Card* queryCard(const char* pName);//��ѯ��
void releaseCardList();
//Card* queryCards(const char* pName, int* pIndex);
Card* doLogon(const char* pNumber, const char* pwd);
int deleteCard(const char* pNumber);
int modifyCard(const char* pNumber);