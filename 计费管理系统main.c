#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include"menu.h"//�˵�ͷ�ļ�
#include"card.h"//��
#define MAX 1000
int main() {
	int choice;
	int number = 0;
	Card cards[MAX];
	while (1) {
		showMenu();//��ʾ�˵�
		printf("��ѡ������Ҫ�ķ���:");
		if (scanf("%d", &choice) != 1) {
			getchar();
			continue;
		}
		char s[20];
		char p[20];
		switch (choice) {
		case 1: 
			add_card(cards, &number);
			break;//���
		case 2:
			 check_card(cards, number, s,p);
			break;//��ѯ
		case 3:

			break;
		case 4:
			break;
		case 5:
			break;
		case 6:
			break;
		case 7:
			break;
		case 8: 
			delete_card(cards,&number,s,p);//ע��
			break;
		case 0:printf("��ӭ�´�ʹ��\n");	
			exit(0);
			break;
		default:
			printf("����������\n");
			break;
		}
		system("pause");
		system("cls");
	}
}
