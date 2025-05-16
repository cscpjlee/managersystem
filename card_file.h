#pragma once
#include"model.h"
int saveCard(const Card* pcard, const char* pPath);
void loadAndDisplayCards(const char* pPath);
int updateCard(const Card* pCard, const char* pPath, int nIndex);
int getCardCount(const char* pPath);
