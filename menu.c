#define _CRT_SECURE_NO_WARNINGS
#include"menu.h"
#include<stdio.h>
#include"card_service.h"
#include"tool.h"
void showMenu() {
	printf("��ӭ����Ʒѹ���ϵͳ\n");
	printf("--------�˵�-------\n");
	printf("1.��ӿ�\n");
	printf("2.��ѯ��\n");
	printf("3.�ϻ�\n");
	printf("4.�»�\n");
	printf("5.��ֵ\n");
	printf("6.�˷�\n");
	printf("7.��ѯͳ��\n");
	printf("8.ע����\n");
	printf("9.�޸Ŀ�\n");
	printf("0.�˳�\n");

}//�˵�ʵ��
void add() {
	Card card;
	printf("-----��ӿ�----\n");
	printf("���뿨��:\n");
	scanf("%s", card.c_Number);
	printf("��������:\n");
	scanf("%s", card.c_Password);
	int nNumberSize = getSize(card.c_Number);
	int nPasswordSize = getSize(card.c_Password);
	if (nNumberSize > 18 || nPasswordSize > 8) {
		printf("���Ż����볬���涨����\n");
		return;
	}
	printf("���뿪�����:\n");
	scanf("%f", &card.c_Money);
	card.s_Money = card.c_Money;
	card.count = card.c_Status = card.nDel = 0;
	card.tEnd = card.tStart = card.tLast = time(NULL);
	addCard(card);//���濨
	printf("������Ϣ����:\n");
	printf("����\t����\t��״̬\t���\n");
	printf("%s\t%s\t%d\t%.1f\n", card.c_Number, card.c_Password, card.c_Status, card.c_Money);
}//��ӿ�
int getSize(const char* pInfo) {
	int nSize = 0;
	while (*(pInfo + nSize) != '\0') {
		nSize++;
	}
	return nSize;
}//��ÿ��ſ��ܳ���
void query() {
	char q_Number[18] = { 0 };
	char atime[20] = { 0 };
	printf("������Ҫ��ѯ�Ŀ���\n");
	scanf("%s", q_Number);
	Card* pCard = NULL;
	pCard = queryCard(q_Number);
	if (pCard == NULL) {
		printf("������");
		return;
	}
	timeToString(pCard->tLast, atime);
	/*for (int i = 0; i < nIndex; i++) {
		printf("��ѯ���Ŀ���Ϣ����:\n");
		printf("����\t״̬\t���\t�ۼ�ʹ��\tʹ�ô���\t�ϴ�ʹ��ʱ��\n");
		printf("%s\t%d\t%.1f\t%.1f\t\t%d\t\t%s\n", (pCard + i)->c_Number, (pCard + i)->c_Status, (pCard + i)->c_Money, (pCard + i)->s_Money, (pCard + i)->count, atime);
	}*/
		printf("��ѯ���Ŀ���Ϣ����:\n");
		printf("����\t״̬\t���\t�ۼ�ʹ��\tʹ�ô���\t�ϴ�ʹ��ʱ��\n");
		printf("%s\t%d\t%.1f\t%.1f\t\t%d\t\t%s\n", pCard->c_Number, pCard->c_Status, pCard->c_Money,pCard->s_Money, pCard->count,atime);
	}//��ѯ��

	void exitApp() {
		releaseCardList();
		printf("��ӭ�´�ʹ��!\n");
		exit(0);
	}
	void delete() {
		char number[19];
		printf("������Ҫɾ���Ŀ��ţ�");
		scanf("%s", number);
		deleteCard(number);
	}
	void modify() {
		char number[19];
		printf("������Ҫ�޸ĵĿ��ţ�");
		scanf("%s", number);
		modifyCard(number);
	}