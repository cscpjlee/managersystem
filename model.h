#pragma once
#include<stdio.h>
#include<string.h>
#include<time.h>
typedef struct {
	char c_Number[20];//卡号
	char c_Password[20];//卡密
	float c_Money;//余额
	int c_Status;//状态
	time_t tStart;//开卡时间
	time_t tEnd;//截止时间
	float s_Money;//累计金额
	time_t tLast;//最后使用时间
	int count;//使用次数
	int nDel;//删除标识
}Card;
