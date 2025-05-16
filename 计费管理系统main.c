#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
//#include"model.h"
#include"menu.h"//菜单头文件
#define MAX 1000
int main() {
	int choice;
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
			add();
			break;//添加
		case 2:
			query();
			break;//查询
		case 3:updateCardInfo(CARDPATH);

			break;
		case 4:loadAndDisplayCards(CARDPATH);
			break;
		case 5: {
			Card card;
			printf("请输入卡号(长度为1~18)：");
			scanf("%s", card.c_Number);
			// 将输入的卡号保存到卡结构体中
			if (1 == isExsit(card.c_Number, CARDPATH))
				printf("卡信息文件%s中，有%s卡信息。\n", CARDPATH, card.c_Number);
			else
				printf("卡信息文件%s中，无%s卡信息。\n", CARDPATH, card.c_Number);

		}
			break;
		case 6:
			break;
		case 7:
			break;
		case 8: 
			
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
	return 0;
}
