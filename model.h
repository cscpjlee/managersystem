#pragma once
#include<stdio.h>
#include<string.h>
#include<time.h>
#define CARDPATH   "d:\\card.dat"
typedef struct {
	char c_Number[20];//����
	char c_Password[20];//����
	float c_Money;//���
	int c_Status;//״̬
	time_t tStart;//����ʱ��
	time_t tEnd;//��ֹʱ��
	float s_Money;//�ۼƽ��
	time_t tLast;//���ʹ��ʱ��
	int count;//ʹ�ô���
	int nDel;//ɾ����ʶ
}Card;
typedef struct CardNode {
	Card data;
	struct CardNode* next;
}CardNode,*lpCardNode;
typedef enum {
	ROLE_NONE,
	ROLE_ADMIN,
	ROLE_USER
}UserRole;
extern UserRole g_currentUserRole;
// ��һ��ָ������¼��ǰ��¼�����ĸ��û����ڵ�
extern lpCardNode g_currentUserNode;
#define ADMIN_USERNAME "admin"
#define ADMIN_PASSWORD "admin123"