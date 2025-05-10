#include<string.h>
#include"model.h"
#include"global.h"
Card cards[50];
int c_count = 0;
int addCard(Card card) {
	cards[c_count] = card;
	c_count++;
	return TURE;
}//±£´æ¿¨
Card* queryCard(const char* pName) {
	for (int i = 0; i < c_count; i++) {
		if (strcmp(pName, cards[i].c_Number) == 0) {
			return &cards[i];
		}
	}
	return NULL;
}//²éÑ¯¿¨