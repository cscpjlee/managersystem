#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include"menu.h"//菜单头文件
#include"card.h"//卡
#define MAX 1000
int main() {
	int choice;
	int number = 0;
	Card cards[MAX];
	while (1) {
		showMenu();//显示菜单
		printf("请选择您需要的服务:");
		if (scanf("%d", &choice) != 1) {
			getchar();
			continue;
		}
		char s[20];
		char p[20];
		switch (choice) {
		case 1: 
			add_card(cards, &number);
			break;//添加
		case 2:
			 check_card(cards, number, s,p);
			break;//查询
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
			delete_card(cards,&number,s,p);//注销
			break;
		case 0:printf("欢迎下次使用\n");	
			exit(0);
			break;
		default:
			printf("请重新输入\n");
			break;
		}
		system("pause");
		system("cls");
	}
}
