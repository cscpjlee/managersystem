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
		case 3:updateCardInfo(CARDPATH);

			break;
		case 4:loadAndDisplayCards(CARDPATH);
			break;
		case 5: {
			Card card;
			printf("�����뿨��(����Ϊ1~18)��");
			scanf("%s", card.c_Number);
			// ������Ŀ��ű��浽���ṹ����
			if (1 == isExsit(card.c_Number, CARDPATH))
				printf("����Ϣ�ļ�%s�У���%s����Ϣ��\n", CARDPATH, card.c_Number);
			else
				printf("����Ϣ�ļ�%s�У���%s����Ϣ��\n", CARDPATH, card.c_Number);

		}
			break;
		case 6:
			break;
		case 7:
			break;
		case 8: 
			
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
	return 0;
}
