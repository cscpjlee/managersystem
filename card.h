#pragma once
#include<stdio.h>
#include<string.h>
typedef struct {
	char name[20];
	char card_number[20];
	char password[20];
	double money;
}Card;
void add_card(Card cards[],int *number);//���
int  find_card(Card cards [],int number,char *s,char *p);//Ѱ��
void delete_card(Card cards[], int *number, char* s,char *p);//ע��
void check_card(Card cards[], int number, char* s, char *p);//��ѯ
void on_board(Card cards[], char* s, char* password);//�ϻ�
void off_board(Card cards[], char* s, char* password);//�»�
void recharge_card(Card cards[], int *number,char* s, int m);//��ֵ
void refund_card(Card cards[]);//�˷�