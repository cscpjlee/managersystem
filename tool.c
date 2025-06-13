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
