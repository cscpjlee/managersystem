#define _CRT_SECURE_NO_WARNINGS
#include <time.h>
#include <stdio.h>
#include <string.h>

void timeToString(time_t t, char* pBuf) {
    struct tm* pTimeInfor;
    pTimeInfor = localtime(&t);

    if (pTimeInfor != NULL) {
        strftime(pBuf, 20, "%Y-%m-%d %H:%M", pTimeInfor);
    }
    else {
        // ��ʱ��Ƿ�����Ĭ����ʾ
        strcpy(pBuf, "Invalid Time");
    }
}
//�������
void getPassword(char* password, int maxLength) {
	char ch;
	int i = 0;
	while (i < maxLength) {
		ch = _getch();
		if (ch == '\r' || ch == '\n') {
			break;
		}
		if (ch == '\b') {
			if (i > 0) {
				i--;
				printf("\b \b");
			}
		}
		else {
			password[i] = ch;
			printf("*");
			i++;
		}
	}
	password[i] = '\0';
	printf("\n");
}