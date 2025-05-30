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
		    delete();
			break;
		case 9:
			modify();
			break;
		case 0:
			exitApp();
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
