#define _CRT_SECURE_NO_WARNINGS
#include"menu.h"
#include<stdio.h>
#include"card_service.h"
#include"tool.h"
UserRole g_currentUserRole = ROLE_NONE;
lpCardNode g_currentUserNode = NULL;
//����Ա�˵�
void showAdminMenu() {
	printf("------ ����Ա�˵� ------\n");
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
	printf("11.ģ����ѯ\n");
	printf("0.�˳�\n");
}
//�û��˵�
void showUserMenu() {
	printf("------ �û��˵� ------\n");
	printf("1.�ϻ�\n");
	printf("2.�»�\n");
	printf("3.��ѯ������Ϣ\n");
	printf("4.�޸ı�������\n");
	printf("5.������ֵ\n");
	printf("0.ע����¼\n");
}
//��½����
int login() {
	int choice;
	printf("------ ��ӭ�����Ʒѹ���ϵͳ ------\n");
	printf("1.����Ա��¼\n");
	printf("2.�û���¼\n");
	printf("0.�˳�ϵͳ\n");
	printf("��½��ʽ:\n");
	scanf("%d", &choice);
	switch (choice) {
	case 1:
		adminLogin();
		break;
	case 2:
		userLogin();
		break;
	case 0:
		exitApp();
		break;
	default:
		return 1;
	}
}
//�˳���¼
int logout() {
	if (g_currentUserRole == ROLE_USER) {
		printf("�û� %s ��ע����\n", g_currentUserNode->data.c_Number);
	}
	else if (g_currentUserRole == ROLE_ADMIN) {
		printf("����Ա��ע����\n");
	}
	g_currentUserRole = ROLE_NONE;
	g_currentUserNode = NULL;
}
//��ӿ�
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
}
int getSize(const char* pInfo) {
	int nSize = 0;
	while (*(pInfo + nSize) != '\0') {
		nSize++;
	}
	return nSize;
}//��ÿ��ſ��ܳ���
//��ѯ��
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
	//ע����
	void delete() {
		printf("------ ɾ���� ------\n");
		char number[19];
		printf("������Ҫɾ���Ŀ��ţ�");
		scanf("%s", number);
		deleteCard(number);
	}
	//�޸Ŀ�
	void modify() {
		printf("------ �޸Ŀ� ------\n");
		char number[19];
		printf("������Ҫ�޸ĵĿ��ţ�");
		scanf("%s", number);
		modifyCard(number);
	}
	//�ϻ�
	void startUsing() {
		printf("------ �ϻ� ------\n");
		char number[19];
		char password[9];
		printf("�����뿨��:");
		scanf("%s", number);
		printf("����������:");
		getPassword(password, 8);
		startUsingCard(number, password);
	}
	//�»�
	void endUsing() {
		printf("------ �»� ------\n");
		char number[19];
		char password[9];
		printf("�����뿨��:");
		scanf("%s", number);
		printf("����������:");
		getPassword(password, 8);
		endUsingCard(number, password); // �����»����ܺ���
	}
	//��ֵ
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
	//�˷�
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
	//��ѯͳ��
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
	//ģ����ѯ
	void fuzzyQuery() {
		char number[20];
		printf("------ ģ����ѯ ------\n");
		printf("������Ҫ���ҵĿ���Ƭ��:\n");
		scanf("%s", number);
		int count = 0;
		Card* results = queryCards(number, &count);
		if (results == NULL || count == 0) {
			printf("δ�ҵ�����%s�Ŀ���\n", number);
		}
		char timeStr[20];
		for (int i = 0; i < count; i++) {
			timeToString(results[i].tLast, timeStr);
			printf("����\t״̬\t���\t�ۼ�ʹ��\tʹ�ô���\t�ϴ�ʹ��ʱ��\n");
			printf("%s\t%d\t%.1f\t%.1f\t\t%d\t\t%s\n", results[i].c_Number, results[i].c_Status, results[i].c_Money, results[i].s_Money, results[i].count, timeStr);
		}
		free(results);
	}
	//�û��ϻ�
	void userStartUsing() {
		if (g_currentUserRole != ROLE_USER || g_currentUserNode == NULL) {
			printf("���û���������Ч��\n");
			return;
		}
		const char* myNumber = g_currentUserNode->data.c_Number;
		const char* myPassword = g_currentUserNode->data.c_Password;
		startUsingCard(myNumber, myPassword);
	}
	//�û��»�
	void userEndUsing() {
		if (g_currentUserRole != ROLE_USER || g_currentUserNode == NULL) {
			printf("���û���������Ч��\n");
			return;
		}
		const char* myNumber = g_currentUserNode->data.c_Number;
		const char* myPassword = g_currentUserNode->data.c_Password;
		endUsingCard(myNumber, myPassword);
	}
	//�û���Ϣ
	void showMyInfo() {
		if (g_currentUserRole != ROLE_USER || g_currentUserNode == NULL) {
			printf("���û���������Ч��\n");
			return;
		}
		printf("------ ��ѯ��------\n");
		const char* myNumber = g_currentUserNode->data.c_Number;
		Card* pCard = NULL;
		pCard = queryCard(myNumber);
		if (pCard == NULL) {
			printf("���Ų�����");
			return;
		}
		char atime[20] = { 0 };
		timeToString(pCard->tLast, atime);
		printf("��ѯ���Ŀ���Ϣ����:\n");
		printf("����\t״̬\t���\t�ۼ�ʹ��\tʹ�ô���\t�ϴ�ʹ��ʱ��\n");
		printf("%s\t%d\t%.1f\t%.1f\t\t%d\t\t%s\n", pCard->c_Number, pCard->c_Status, pCard->c_Money, pCard->s_Money, pCard->count, atime);
	}
	//�޸�����
	void changeMyPassword() {
		printf("------ �޸Ŀ� ------\n");
		const char* myNumber = g_currentUserNode->data.c_Number;
		modifyCard(myNumber);
	}
	//������ֵ
	void userRecharge() {
		const char* myNumber = g_currentUserNode->data.c_Number;
		float amount;
		printf("------ ��ֵ ------\n");
		printf("�������ֵ���: ");
		scanf("%f", &amount);
		rechargeCard(myNumber, amount);
	}