#define _CRT_SECURE_NO_WARNINGS
#include"card.h"
//��ӿ�
void add_card(Card cards[], int *number) {

	printf("�����뿨��:\n");
	scanf("%s", cards[*number].card_number);
	printf("����������:\n");
	scanf("%s", cards[*number].name);
	printf("����������:\n");
	scanf("%s", cards[*number].password);
	printf("���������:\n");
	scanf("%lf", &cards[*number].money);
	(*number)++;
}
//Ѱ�ҿ�
int find_card(Card cards[], int number, char* s,char *p) {
	for (int i = 0; i < number; i++) {
		if (strcmp(s, cards[i].card_number) == 0 && strcmp(p, cards[i].password) == 0) {//��鿨��
			return i;
		}
	}
	return -1;//δѰ�ҵ�
}
//��ѯ��
void check_card(Card cards[], int number, char* s,char *p) {
	printf("�����뿨��:\n");
	scanf("%s", s);
	printf("����������:\n");
	scanf("%s", p);
	int index = find_card(cards, number, s,p);
	if (index == -1) {
		printf("δ�ҵ�!\n");
		return;
	}
	else {
		printf("%s\n", cards[index].name);
		printf("%s\n", cards[index].password);
		printf("%lf\n", cards[index].money);
	}
}
//ע����
void delete_card(Card cards[], int *number, char* s,char *p) {
	printf("�����뿨��:\n");
	scanf("%s", s);
	printf("����������:\n");
	scanf("%s", p);
	int index = find_card(cards, *number, s,p);
	if (index == -1) {
		printf("δ�ҵ�!\n");
		return;
	}
	for (int j = index; j < *number-1; j++) {
		cards[j] = cards[j+1];
	}
	(*number)--;
	printf("ע���ɹ�!\n");
}
