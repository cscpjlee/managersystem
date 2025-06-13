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
	printf("3.上机\n");
	printf("4.下机\n");
	printf("5.充值\n");
	printf("6.退费\n");
	printf("7.查询统计\n");
	printf("8.注销卡\n");
	printf("9.修改卡\n");
	printf("10.重置文件数据\n");
	printf("0.退出\n");

}//菜单实现
void add() {
	Card card;
	printf("------ 添加卡 ------\n");

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
	card.s_Money = 0;
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
// 在查询函数中使用完指针后释放内存
void query() {
	printf("------ 查询卡------\n");

	char q_Number[18] = { 0 };
	char atime[20] = { 0 };
	printf("请输入要查询的卡号\n");
	scanf("%s", q_Number);
	Card* pCard = NULL;
	pCard = queryCard(q_Number);
	if (pCard == NULL) {
		printf("卡号不存在");
		return;
	}
	timeToString(pCard->tLast, atime);
	printf("查询到的卡信息如下:\n");
	printf("卡号\t状态\t金额\t累计使用\t使用次数\t上次使用时间\n");
	printf("%s\t%d\t%.1f\t%.1f\t\t%d\t\t%s\n", pCard->c_Number, pCard->c_Status, pCard->c_Money, pCard->s_Money, pCard->count, atime);
	//if (pCard != NULL) {
	//	free(pCard); // 释放动态分配的内存
	//}
}
	// 在 menu.c 中
	void exitApp() {
		printf("正在保存卡片数据...\n");
		saveCardListToFile(); // 在释放内存前，先保存数据到文件

		releaseCardList();
		printf("欢迎下次使用!\n");
		exit(0);
	}
	void delete() {
		printf("------ 删除卡 ------\n");
		char number[19];
		printf("请输入要删除的卡号：");
		scanf("%s", number);
		deleteCard(number);
	}
	void modify() {
		printf("------ 修改卡 ------\n");
		char number[19];
		printf("请输入要修改的卡号：");
		scanf("%s", number);
		modifyCard(number);
	}
	void startUsing() {
		printf("------ 上机 ------\n");
		char number[19];
		char password[9];
		printf("请输入卡号:");
		scanf("%s", number);
		printf("请输入密码:");
		scanf("%s", password);
		startUsingCard(number, password);
	}
	void endUsing() {
		printf("------ 下机 ------\n");
		char number[19];
		char password[9];
		printf("请输入卡号:");
		scanf("%s", number);
		printf("请输入密码:");
		scanf("%s", password);
		endUsingCard(number, password); // 调用下机功能函数
	}
	// 在 menu.c 中添加

	void recharge() {
		char number[19];
		float amount;
		printf("------ 充值 ------\n");
		printf("请输入要充值的卡号: ");
		scanf("%s", number);

		printf("请输入充值金额: ");
		scanf("%f", &amount);

		rechargeCard(number, amount);
	}
	// 在 menu.c 中添加

	void refund() {
		char number[19];
		float amount;

		printf("------ 退费 ------\n");
		printf("请输入要退费的卡号: ");
		scanf("%s", number);

		printf("请输入退费金额: ");
		scanf("%f", &amount);

		refundCard(number, amount);
	}
	void statistics() {
		queryStatistics();
	}
	void resetData() {
		char confirm[10];
		printf("!!!!!! 警告 !!!!!!\n");
		printf("此操作将永久删除所有卡片数据，且无法恢复！\n");
		printf("如果您确定要继续，请输入 'YES' 并按回车: ");
		scanf("%s", confirm);

		if (strcmp(confirm, "YES") == 0) {
			resetSystemData(); // 调用核心重置函数
		}
		else {
			printf("操作已取消。\n");
		}
	}