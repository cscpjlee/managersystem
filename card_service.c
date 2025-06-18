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
		printf("内存分配失败，无法添加新卡。\n");
		return 0;
	}

	if (cardList == NULL) {
		initNodeList();
	}

	cur->data = card;
	cur->next = NULL;

	lpCardNode temp = cardList; // 使用临时指针遍历链表，避免修改头指针
	while (temp->next != NULL) {
		temp = temp->next;
	}
	temp->next = cur; 
	return 1;
}

	//释放内存
	void releaseCardList() {
		lpCardNode cur;

		while (cardList != NULL) {
			cur = cardList;
			cardList = cur->next;
			free(cur);
			cur = NULL;
		}
	}
	//查询卡
	Card* queryCard(const char* pName) {
		// 先在内存链表中查询
		if (cardList == NULL) {
			initNodeList(); // 确保链表头节点存在
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


	// 删除卡
	int deleteCard(const char* pNumber) {
		lpCardNode prev = cardList;
		lpCardNode curr = cardList->next;
		int index = 1;
		while (curr != NULL) {
			if (strcmp(curr->data.c_Number, pNumber) == 0) {
				prev->next = curr->next;
				free(curr);
				printf("卡号 %s 删除成功!\n", pNumber);
				return 1;
			}
			prev = curr;
			curr = curr->next;
			index++;
		}
		printf("未找到卡号 %s!\n", pNumber);
		return 0;
	}

// 修改卡
int modifyCard(const char* pNumber) {
	lpCardNode curr = cardList->next;
	int index = 1;
	if (cardList == NULL) {
		printf("链表未初始化\n");
		return 0;
	}
	if (cardList->next == NULL) {
		printf("链表中无卡信息\n");
		return 0;
	}
	while (curr != NULL) {
		if (strcmp(curr->data.c_Number, pNumber) == 0) {
			char choice;
			printf("找到卡号 %s,请修改：\n", pNumber);
			char newPassword[9];
			printf("请输入新密码：");
			scanf("%s", newPassword);
			if (strlen(newPassword) > 8) {
				printf("密码长度超出范围!\n");
				return 0;
			}
			strcpy(curr->data.c_Password, newPassword);
			float newMoney;
			printf("请输入新金额：");
			scanf("%f", &newMoney);
			curr->data.c_Money = newMoney;
			printf("修改成功!");
			return 1;
		}
		curr = curr->next;
		index++;
	}
	printf("未找到卡号 %s\n", pNumber);
	return 0;
}
//模糊查询
Card* queryCards(char* pName, int* pCount) {
	*pCount = 0;
	if (cardList == NULL || cardList->next == NULL || pName == NULL) {
		return NULL;
	}
	lpCardNode cur = cardList->next;
	while (cur != NULL) {
		if (strstr(cur->data.c_Number, pName) != NULL) {
			(*pCount)++;
		}
		cur = cur->next;
	}
	if (*pCount == 0) {
		return NULL;
	}
	Card* resultArray = (Card*)malloc((*pCount) * sizeof(Card));
	if (resultArray == NULL) {
		printf("分配内存失败!\n");
		return NULL;
	}
	int index = 0;
	cur = cardList->next;
	while (cur != NULL) {
		if (strstr(cur->data.c_Number, pName) != NULL) {
			resultArray[index] = cur->data;
			index++;
			if (index == *pCount) {
				break;
			}
		}
		cur = cur->next;
	}
	return resultArray;
}
//上机函数
int startUsingCard(const char* pNumber, const char* pwd) {

	lpCardNode cardNode = cardList->next;
	int index = 1;

	// 遍历链表查找卡片
	while (cardNode != NULL) {
		if (strcmp(cardNode->data.c_Number, pNumber) == 0 &&
			strcmp(cardNode->data.c_Password, pwd) == 0) {

			if (cardNode->data.c_Status == 1) {
				printf("该卡已上机，请勿重复上机\n");
				return 0;
			}

			// 设置卡状态与时间
			cardNode->data.c_Status = 1;
			cardNode->data.count++;
			cardNode->data.tStart = time(NULL);

			printf("卡号 %s 上机成功\n", pNumber);
			/*updateCard(&cardNode->data, CARDPATH, index);*/
			return 1;
		}
		cardNode = cardNode->next;
		index++;
	}
	printf("卡号或密码错误，请重新输入\n");
	return 0;
}
//下机函数
int endUsingCard(const char* pNumber, const char* pwd) {
	lpCardNode cardNode = cardList->next;
	while (cardNode != NULL) {
		if (strcmp(cardNode->data.c_Number, pNumber) == 0 && strcmp(cardNode->data.c_Password, pwd) == 0) {
			if (cardNode->data.c_Status == 0) {
				printf("该卡未上机，无法下机\n");
				return 0;
			}
			cardNode->data.c_Status = 0; // 设置卡片状态为未上机
			time_t endTime = time(NULL);
			double usedTime = difftime(endTime, cardNode->data.tStart); // 计算使用时长
			float fee = usedTime/60;
			if (cardNode->data.c_Money < fee) {
				printf("余额不足，无法下机，请先充值\n");
				cardNode->data.c_Status = 1; 
				return 0;
			}
			cardNode->data.c_Money -= fee; 
			cardNode->data.s_Money += fee; 
			cardNode->data.tLast = endTime; 
			printf("卡号 %s 下机成功，使用时长: %.2f 小时，扣除费用: %.2f 元，剩余余额: %.2f 元\n",
				pNumber, usedTime / 3600.0, fee, cardNode->data.c_Money);
			// 更新文件中的卡片信息
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
	printf("卡号或密码错误，请重新输入\n");
	return 0;
}
// 充值函数
int rechargeCard(const char* pNumber, float amount) {
	if (amount <= 0) {
		printf("充值金额必须为正数。\n");
		return 0;
	}
	Card* pCard = queryCard(pNumber);

	if (pCard == NULL) {
		printf("未找到卡号 %s，无法充值。\n", pNumber);
		return 0;
	}

	pCard->c_Money += amount;
	pCard->s_Money += amount;
	printf("充值成功！\n");
	printf("卡号: %s\n", pCard->c_Number);
	printf("当前余额: %.2f 元\n", pCard->c_Money);
	return 1;
}

// 退费函数
int refundCard(const char* pNumber, float amount) {
	if (amount <= 0) {
		printf("退费金额必须为正数。\n");
		return 0;
	}

	Card* pCard = queryCard(pNumber);

	if (pCard == NULL) {
		printf("未找到卡号 %s，无法退费。\n", pNumber);
		return 0;
	}

	if (pCard->c_Money < amount) {
		printf("退费失败！卡内余额 (%.2f 元) 不足，无法退款 %.2f 元。\n", pCard->c_Money, amount);
		return 0;
	}

	// 执行退费
	pCard->c_Money -= amount;

	printf("退费成功！\n");
	printf("卡号: %s\n", pCard->c_Number);
	printf("当前余额: %.2f 元\n", pCard->c_Money);

	return 1;
}
// 查询统计函数
void queryStatistics() {
	if (cardList == NULL || cardList->next == NULL) {
		printf("系统中没有任何卡片信息。\n");
		return;
	}
	int totalCards = 0;
	int onlineCards = 0;
	lpCardNode current = cardList->next; // 开始遍历
	while (current != NULL) {
		totalCards++;

		if (current->data.c_Status == 1) {
			onlineCards++; 
		}

		current = current->next;
	}

	printf("------ 系统数据统计 ------\n");
	printf("总发卡数量: %d 张\n", totalCards);
	printf("当前上机数量: %d 张\n", onlineCards);
	printf("---------------------------\n");
	printf("------ 所有卡片详细信息列表 ------\n");
	printf("%-18s\t%-8s\t%-6s\t余额\t\t上次使用时间\n", "卡号", "密码", "状态");

	current = cardList->next; 
	char timeStr[20];       

	while (current != NULL) {
		const char* statusText = (current->data.c_Status == 1) ? "上机中" : "空闲";
		timeToString(current->data.tLast, timeStr);
		printf("%-18s\t%-8s\t%-6s\t%-8.2f\t\t%s\n",
			current->data.c_Number,
			current->data.c_Password,
			statusText,
			current->data.c_Money,
			timeStr);
		current = current->next;
	}
}
//管理员登录
int adminLogin() {
	char username[20];
	char password[20];
	printf("请输入管理员账户: ");
	scanf("%s", username);
	printf("请输入管理员密码: ");
	getPassword(password, 8);

	if (strcmp(username, ADMIN_USERNAME) == 0 && strcmp(password, ADMIN_PASSWORD) == 0) {
		g_currentUserRole = ROLE_ADMIN;
		g_currentUserNode = NULL; // 管理员没有对应的卡节点
		printf("管理员登录成功！\n");
		return 1;
	}
	else {
		printf("账户或密码错误！\n");
		return 0;
	}
}
//用户登录
int userLogin() {
	char username[20];
	char password[20];
	printf("请输入您的卡号: ");
	scanf("%s", username); // 复用 username 变量存卡号
	printf("请输入您的密码: ");
	getPassword(password, 8);

	// 遍历链表查找用户
	lpCardNode userNode = cardList->next;
	while (userNode != NULL) {
		if (strcmp(userNode->data.c_Number, username) == 0 && strcmp(userNode->data.c_Password, password) == 0) {
			g_currentUserRole = ROLE_USER;
			g_currentUserNode = userNode; // 记录下当前登录的用户节点
			printf("用户 %s 登录成功！\n", username);
			return 1;
		}
		userNode = userNode->next;
	}
	printf("卡号或密码错误！\n");
	return 0;
}
