#pragma once
#include"model.h"
int addCard(Card card);//���濨
Card* queryCard(const char* pName);//��ѯ��
void releaseCardList();
//Card* queryCards(const char* pName, int* pIndex);
int deleteCard(const char* pNumber);
int modifyCard(const char* pNumber);
int startUsingCard(const char* pNumber, const char* pwd);
int endUsingCard(const char* pNumber, const char* pwd);
int rechargeCard(const char* pNumber, float amount);
int refundCard(const char* pNumber, float amount);
void queryStatistics();
Card* queryCards(char* pName, int* pCount);
int adminLogin();
int userLogin();
