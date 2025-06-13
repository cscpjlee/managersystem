#pragma once
#include<stdio.h>
#include<string.h>
#include"model.h"
void showMenu();
void add();
int getSize(const char* pInfo);
void query();
void copy(char* aInput, char* aOutput, int nSize);
void exitApp();
void delete();
void modify();
void startUsing();
void endUsing();
void recharge();
void refund();
void statistics();
void resetData();