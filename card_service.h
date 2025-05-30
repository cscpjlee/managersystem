#pragma once
#include"model.h"
int addCard(Card card);//±£´æ¿¨
Card* queryCard(const char* pName);//²éÑ¯¿¨
void releaseCardList();
//Card* queryCards(const char* pName, int* pIndex);
Card* doLogon(const char* pNumber, const char* pwd);
int deleteCard(const char* pNumber);
int modifyCard(const char* pNumber);