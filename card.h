#pragma once
#include<stdio.h>
#include<string.h>
typedef struct {
	char name[20];
	char card_number[20];
	char password[20];
	double money;
}Card;
void add_card(Card cards[],int *number);//添加
int  find_card(Card cards [],int number,char *s,char *p);//寻找
void delete_card(Card cards[], int *number, char* s,char *p);//注销
void check_card(Card cards[], int number, char* s, char *p);//查询
void on_board(Card cards[], char* s, char* password);//上机
void off_board(Card cards[], char* s, char* password);//下机
void recharge_card(Card cards[], int *number,char* s, int m);//充值
void refund_card(Card cards[]);//退费