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
        // 若时间非法，给默认提示
        strcpy(pBuf, "Invalid Time");
    }
}
