#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
//#include"model.h"
#include"menu.h"//�˵�ͷ�ļ�
#define MAX 1000
int main() {
	int choice;
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
			add();
			break;//���
		case 2:
			query();
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
		    delete();
			break;
		case 9:
			modify();
			break;
		case 0:
			exitApp();
			break;
		default:
			printf("����������\n");
			break;
		}
		system("pause");
		system("cls");
	}
	return 0;
}
