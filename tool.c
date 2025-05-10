#define _CRT_SECURE_NO_WARNINGS
#include<time.h>
void timeToString(time_t t, char* pBuf) {
	struct tm* pTimeInfor;
	pTimeInfor = localtime(&t);
	strftime(pBuf, 20, "%Y-%m-%d %H:%M",pTimeInfor);
}