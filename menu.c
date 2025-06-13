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
	printf("10.�����ļ�����\n");
	printf("0.�˳�\n");

}//�˵�ʵ��
void add() {
	Card card;
	printf("------ ��ӿ� ------\n");

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
	card.s_Money = 0;
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
// �ڲ�ѯ������ʹ����ָ����ͷ��ڴ�
void query() {
	printf("------ ��ѯ��------\n");

	char q_Number[18] = { 0 };
	char atime[20] = { 0 };
	printf("������Ҫ��ѯ�Ŀ���\n");
	scanf("%s", q_Number);
	Card* pCard = NULL;
	pCard = queryCard(q_Number);
	if (pCard == NULL) {
		printf("���Ų�����");
		return;
	}
	timeToString(pCard->tLast, atime);
	printf("��ѯ���Ŀ���Ϣ����:\n");
	printf("����\t״̬\t���\t�ۼ�ʹ��\tʹ�ô���\t�ϴ�ʹ��ʱ��\n");
	printf("%s\t%d\t%.1f\t%.1f\t\t%d\t\t%s\n", pCard->c_Number, pCard->c_Status, pCard->c_Money, pCard->s_Money, pCard->count, atime);
	//if (pCard != NULL) {
	//	free(pCard); // �ͷŶ�̬������ڴ�
	//}
}
	// �� menu.c ��
	void exitApp() {
		printf("���ڱ��濨Ƭ����...\n");
		saveCardListToFile(); // ���ͷ��ڴ�ǰ���ȱ������ݵ��ļ�

		releaseCardList();
		printf("��ӭ�´�ʹ��!\n");
		exit(0);
	}
	void delete() {
		printf("------ ɾ���� ------\n");
		char number[19];
		printf("������Ҫɾ���Ŀ��ţ�");
		scanf("%s", number);
		deleteCard(number);
	}
	void modify() {
		printf("------ �޸Ŀ� ------\n");
		char number[19];
		printf("������Ҫ�޸ĵĿ��ţ�");
		scanf("%s", number);
		modifyCard(number);
	}
	void startUsing() {
		printf("------ �ϻ� ------\n");
		char number[19];
		char password[9];
		printf("�����뿨��:");
		scanf("%s", number);
		printf("����������:");
		scanf("%s", password);
		startUsingCard(number, password);
	}
	void endUsing() {
		printf("------ �»� ------\n");
		char number[19];
		char password[9];
		printf("�����뿨��:");
		scanf("%s", number);
		printf("����������:");
		scanf("%s", password);
		endUsingCard(number, password); // �����»����ܺ���
	}
	// �� menu.c �����

	void recharge() {
		char number[19];
		float amount;
		printf("------ ��ֵ ------\n");
		printf("������Ҫ��ֵ�Ŀ���: ");
		scanf("%s", number);

		printf("�������ֵ���: ");
		scanf("%f", &amount);

		rechargeCard(number, amount);
	}
	// �� menu.c �����

	void refund() {
		char number[19];
		float amount;

		printf("------ �˷� ------\n");
		printf("������Ҫ�˷ѵĿ���: ");
		scanf("%s", number);

		printf("�������˷ѽ��: ");
		scanf("%f", &amount);

		refundCard(number, amount);
	}
	void statistics() {
		queryStatistics();
	}
	void resetData() {
		char confirm[10];
		printf("!!!!!! ���� !!!!!!\n");
		printf("�˲���������ɾ�����п�Ƭ���ݣ����޷��ָ���\n");
		printf("�����ȷ��Ҫ������������ 'YES' �����س�: ");
		scanf("%s", confirm);

		if (strcmp(confirm, "YES") == 0) {
			resetSystemData(); // ���ú������ú���
		}
		else {
			printf("������ȡ����\n");
		}
	}