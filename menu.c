#define _CRT_SECURE_NO_WARNINGS
#include"menu.h"
#include<stdio.h>
#include"card_service.h"
#include"tool.h"
void showMenu() {
	printf("欢迎进入计费管理系统\n");
	printf("--------菜单-------\n");
	printf("1.添加卡\n");
	printf("2.查询卡\n");
	printf("3.文件内更新\n");
	printf("4.展示卡信息\n");
	printf("5.通过卡号看是否有无该卡\n");
	printf("6.退费\n");
	printf("7.查询统计\n");
	printf("8.注销卡\n");
	printf("0.退出\n");

}//菜单实现
void add() {
	Card card;
	printf("-----添加卡----\n");
	printf("输入卡号:\n");
	scanf("%s", card.c_Number);
	printf("输入密码:\n");
	scanf("%s", card.c_Password);
	int nNumberSize = getSize(card.c_Number);
	int nPasswordSize = getSize(card.c_Password);
	if (nNumberSize > 18 || nPasswordSize > 8) {
		printf("卡号或密码超过规定长度\n");
		return;
	}
	printf("输入开卡金额:\n");
	scanf("%f", &card.c_Money);
	card.s_Money = card.c_Money;
	card.count = card.c_Status = card.nDel = 0;
	card.tEnd = card.tStart = card.tLast = time(NULL);
	addCard(card);//保存卡
	printf("卡的信息如下:\n");
	printf("卡号\t密码\t卡状态\t余额\n");
	printf("%s\t%s\t%d\t%.1f\n", card.c_Number, card.c_Password, card.c_Status, card.c_Money);
}//添加卡
int getSize(const char* pInfo) {
	int nSize = 0;
	while (*(pInfo + nSize) != '\0') {
		nSize++;
	}
	return nSize;
}//获得卡号卡密长度
void query() {
	char q_Number[18] = {0};
	char atime[20] = { 0 };
	printf("请输入要查询的卡号\n");
	scanf("%s", q_Number);
	Card* pCard = NULL;
	pCard = queryCard(q_Number);
	if(pCard == NULL) {
		printf("出错了");
		return 0;
	}
	timeToString(pCard->tLast, atime);
	printf("查询到的卡信息如下:\n");
	printf("卡号\t状态\t余额\t累计使用\t使用次数\t上次使用时间\n");
	printf("%s\t%d\t%.1f\t%.1f\t%d\t%s\n", pCard->c_Number, pCard->c_Status, pCard->c_Money,pCard->s_Money, pCard->count,atime);
}//查询卡