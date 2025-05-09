#define _CRT_SECURE_NO_WARNINGS
#include"card.h"
//Ìí¼Ó¿¨
void add_card(Card cards[], int *number) {

	printf("ÇëÊäÈë¿¨ºÅ:\n");
	scanf("%s", cards[*number].card_number);
	printf("ÇëÊäÈëĞÕÃû:\n");
	scanf("%s", cards[*number].name);
	printf("ÇëÊäÈëÃÜÂë:\n");
	scanf("%s", cards[*number].password);
	printf("ÇëÊäÈëÓà¶î:\n");
	scanf("%lf", &cards[*number].money);
	(*number)++;
}
//Ñ°ÕÒ¿¨
int find_card(Card cards[], int number, char* s,char *p) {
	for (int i = 0; i < number; i++) {
		if (strcmp(s, cards[i].card_number) == 0 && strcmp(p, cards[i].password) == 0) {//¼ì²é¿¨ºÅ
			return i;
		}
	}
	return -1;//Î´Ñ°ÕÒµ½
}
//²éÑ¯¿¨
void check_card(Card cards[], int number, char* s,char *p) {
	printf("ÇëÊäÈë¿¨ºÅ:\n");
	scanf("%s", s);
	printf("ÇëÊäÈëÃÜÂë:\n");
	scanf("%s", p);
	int index = find_card(cards, number, s,p);
	if (index == -1) {
		printf("Î´ÕÒµ½!\n");
		return;
	}
	else {
		printf("%s\n", cards[index].name);
		printf("%s\n", cards[index].password);
		printf("%lf\n", cards[index].money);
	}
}
//×¢Ïú¿¨
void delete_card(Card cards[], int *number, char* s,char *p) {
	printf("ÇëÊäÈë¿¨ºÅ:\n");
	scanf("%s", s);
	printf("ÇëÊäÈëÃÜÂë:\n");
	scanf("%s", p);
	int index = find_card(cards, *number, s,p);
	if (index == -1) {
		printf("Î´ÕÒµ½!\n");
		return;
	}
	for (int j = index; j < *number-1; j++) {
		cards[j] = cards[j+1];
	}
	(*number)--;
	printf("×¢Ïú³É¹¦!\n");
}
