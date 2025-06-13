#define _CRT_SECURE_NO_WARNINGS
#include<string.h>
#include<stdlib.h>
#include"model.h"
#include"global.h"
#include"card_file.h"
Card cards[50];
int c_count = 0;
int initNodeList() {
	lpCardNode head = NULL;
	head = (lpCardNode)malloc(sizeof(CardNode));
	if (head != NULL) {
		head->next = NULL;
		cardList = head;
		return 1;
	}
	return 0;
}

int addCard(Card card) {
	lpCardNode cur = NULL;
	cur = (lpCardNode)malloc(sizeof(CardNode));
	if (cur == NULL) {
		printf("�ڴ����ʧ�ܣ��޷�����¿���\n");
		return 0;
	}

	if (cardList == NULL) {
		initNodeList();
	}

	cur->data = card;
	cur->next = NULL;

	lpCardNode temp = cardList; // ʹ����ʱָ��������������޸�ͷָ��
	while (temp->next != NULL) { // �ҵ���������һ���ڵ�
		temp = temp->next;
	}
	temp->next = cur; // ���½ڵ���ӵ�����ĩβ
	return 1;
}

	//�ͷ��ڴ�
	void releaseCardList() {
		lpCardNode cur;

		while (cardList != NULL) {
			cur = cardList;
			cardList = cur->next;
			free(cur);
			cur = NULL;
		}
	}

	Card* queryCard(const char* pName) {
		// �����ڴ������в�ѯ
		if (cardList == NULL) {
			initNodeList(); // ȷ������ͷ�ڵ����
		}
		lpCardNode cur = NULL;
		if (cardList != NULL) {
			cur = cardList->next;
			while (cur != NULL) {
				if (strcmp(cur->data.c_Number, pName) == 0) {
					return &cur->data;
				}
				cur = cur->next;
			}
		}
		return NULL;
	}


	// ɾ����
	int deleteCard(const char* pNumber) {
		lpCardNode prev = cardList;
		lpCardNode curr = cardList->next;
		int index = 1;
		while (curr != NULL) {
			if (strcmp(curr->data.c_Number, pNumber) == 0) {
				prev->next = curr->next;
				free(curr);
				printf("���� %s ɾ���ɹ�!\n", pNumber);
				return 1;
			}
			prev = curr;
			curr = curr->next;
			index++;
		}
		printf("δ�ҵ����� %s!\n", pNumber);
		return 0;
	}

// �޸Ŀ�
int modifyCard(const char* pNumber) {
	lpCardNode curr = cardList->next;
	int index = 1;
	if (cardList == NULL) {
		printf("����δ��ʼ��\n");
		return 0;
	}
	if (cardList->next == NULL) {
		printf("�������޿���Ϣ\n");
		return 0;
	}
	while (curr != NULL) {
		if (strcmp(curr->data.c_Number, pNumber) == 0) {
			char choice;
			printf("�ҵ����� %s,���޸ģ�\n", pNumber);
			char newPassword[9];
			printf("�����������룺");
			scanf("%s", newPassword);
			if (strlen(newPassword) > 8) {
				printf("���볤�ȳ�����Χ!\n");
				return 0;
			}
			strcpy(curr->data.c_Password, newPassword);
			float newMoney;
			printf("�������½�");
			scanf("%f", &newMoney);
			curr->data.c_Money = newMoney;
			printf("�޸ĳɹ�!");
			return 1;
		}
		curr = curr->next;
		index++;
	}
	printf("δ�ҵ����� %s\n", pNumber);
	return 0;
}
//Card* queryCards(const char* pName,  int* pIndex) {
//	lpCardNode cur = NULL;
//	Card* pCard = (Card*)malloc(sizeof(Card));
//	if (pCard == NULL) {
//		return NULL;
//	}
//	if (cardList != NULL) {
//		cur = cardList->next;
//		while (cur != NULL) {
//			if (strstr(cur->data.c_Number, pName) != NULL) {
//				pCard[*pIndex] = cur->data;
//				(*pIndex)++;
//				pCard = (Card*)realloc(pCard, (*pIndex) * sizeof(Card));
//			}
//			cur = cur->next;
//		}
//	}
//	return NULL;
//}//ģ����ѯ
//�ϻ�����
int startUsingCard(const char* pNumber, const char* pwd) {

	lpCardNode cardNode = cardList->next;
	int index = 1;

	// ����������ҿ�Ƭ
	while (cardNode != NULL) {
		if (strcmp(cardNode->data.c_Number, pNumber) == 0 &&
			strcmp(cardNode->data.c_Password, pwd) == 0) {

			if (cardNode->data.c_Status == 1) {
				printf("�ÿ����ϻ��������ظ��ϻ�\n");
				return 0;
			}

			// ���ÿ�״̬��ʱ��
			cardNode->data.c_Status = 1;
			cardNode->data.count++;
			cardNode->data.tStart = time(NULL);

			printf("���� %s �ϻ��ɹ�\n", pNumber);
			/*updateCard(&cardNode->data, CARDPATH, index);*/
			return 1;
		}
		cardNode = cardNode->next;
		index++;
	}
	printf("���Ż������������������\n");
	return 0;
}
//�»�����
int endUsingCard(const char* pNumber, const char* pwd) {
	lpCardNode cardNode = cardList->next;
	while (cardNode != NULL) {
		if (strcmp(cardNode->data.c_Number, pNumber) == 0 && strcmp(cardNode->data.c_Password, pwd) == 0) {
			if (cardNode->data.c_Status == 0) {
				printf("�ÿ�δ�ϻ����޷��»�\n");
				return 0;
			}
			cardNode->data.c_Status = 0; // ���ÿ�Ƭ״̬Ϊδ�ϻ�
			time_t endTime = time(NULL);
			double usedTime = difftime(endTime, cardNode->data.tStart); // ����ʹ��ʱ��
			float fee = usedTime/60;
			if (cardNode->data.c_Money < fee) {
				printf("���㣬�޷��»������ȳ�ֵ\n");
				cardNode->data.c_Status = 1; // �ָ��ϻ�״̬
				return 0;
			}
			cardNode->data.c_Money -= fee; // �۳�����
			cardNode->data.s_Money += fee; // �ۼ�ʹ�ý��
			cardNode->data.tLast = endTime; // �������ʹ��ʱ��
			printf("���� %s �»��ɹ���ʹ��ʱ��: %.2f Сʱ���۳�����: %.2f Ԫ��ʣ�����: %.2f Ԫ\n",
				pNumber, usedTime / 3600.0, fee, cardNode->data.c_Money);
			// �����ļ��еĿ�Ƭ��Ϣ
			int index = 1;
			lpCardNode temp = cardList->next;
			while (temp != cardNode) {
				temp = temp->next;
				index++;
			}
			/*updateCard(&cardNode->data, CARDPATH, index);*/
			return 1;
		}
		cardNode = cardNode->next;
	}
	printf("���Ż������������������\n");
	return 0;
}
// ��ֵ����
int rechargeCard(const char* pNumber, float amount) {
	if (amount <= 0) {
		printf("��ֵ������Ϊ������\n");
		return 0;
	}

	// �������е� queryCard �������ҿ�Ƭ
	Card* pCard = queryCard(pNumber);

	if (pCard == NULL) {
		printf("δ�ҵ����� %s���޷���ֵ��\n", pNumber);
		return 0;
	}

	// ִ�г�ֵ
	pCard->c_Money += amount;
	// �ۼƿ���/��ֵ�ܶ�ҲӦ������
	pCard->s_Money += amount;

	printf("��ֵ�ɹ���\n");
	printf("����: %s\n", pCard->c_Number);
	printf("��ǰ���: %.2f Ԫ\n", pCard->c_Money);
	return 1;
}
// �� card_file.c �����

// �˷Ѻ���
int refundCard(const char* pNumber, float amount) {
	if (amount <= 0) {
		printf("�˷ѽ�����Ϊ������\n");
		return 0;
	}

	Card* pCard = queryCard(pNumber);

	if (pCard == NULL) {
		printf("δ�ҵ����� %s���޷��˷ѡ�\n", pNumber);
		return 0;
	}

	if (pCard->c_Money < amount) {
		printf("�˷�ʧ�ܣ�������� (%.2f Ԫ) ���㣬�޷��˿� %.2f Ԫ��\n", pCard->c_Money, amount);
		return 0;
	}

	// ִ���˷�
	pCard->c_Money -= amount;

	printf("�˷ѳɹ���\n");
	printf("����: %s\n", pCard->c_Number);
	printf("��ǰ���: %.2f Ԫ\n", pCard->c_Money);

	return 1;
}
// ��ѯͳ�ƺ���
void queryStatistics() {
	if (cardList == NULL || cardList->next == NULL) {
		printf("ϵͳ��û���κο�Ƭ��Ϣ��\n");
		return;
	}

	int totalCards = 0;
	int onlineCards = 0;
	float totalMoney = 0.0f;

	lpCardNode current = cardList->next; // �ӵ�һ����Ч�ڵ㿪ʼ����

	while (current != NULL) {
		totalCards++; // ÿ����һ���ڵ㣬�ܿ���+1

		if (current->data.c_Status == 1) {
			onlineCards++; // �����Ƭ״̬Ϊ�ϻ���������+1
		}

		totalMoney += current->data.c_Money; // �ۼ����п������

		current = current->next;
	}

	printf("------ ϵͳ����ͳ�� ------\n");
	printf("�ܷ�������: %d ��\n", totalCards);
	printf("��ǰ�ϻ�����: %d ��\n", onlineCards);
	printf("���п������: %.2f Ԫ\n", totalMoney);
	printf("---------------------------\n");
}