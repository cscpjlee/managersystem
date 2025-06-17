#define _CRT_SECURE_NO_WARNINGS
#include"card_file.h"
#include"tool.h"
lpCardNode cardList = NULL;
void saveCardListToFile() {
    // 如果链表为空或者只有一个头节点，则无需保存
    if (cardList == NULL || cardList->next == NULL) {
        return;
    }

    FILE* fp = fopen(CARDPATH, "wb"); // "wb" -> write binary, 以二进制写入模式打开文件
    if (fp == NULL) {
        printf("错误：无法打开文件 %s 进行写入！\n", CARDPATH);
        return;
    }

    lpCardNode current = cardList->next; // 从第一个有效节点开始
    while (current != NULL) {
        // 将当前节点的 data (即 Card 结构体) 写入文件
        fwrite(&(current->data), sizeof(Card), 1, fp);
        current = current->next;
    }

    fclose(fp); // 关闭文件
    printf("所有卡片信息已成功保存到 %s\n", CARDPATH);
}
// 在 card_file.c 文件末尾添加

// 从文件加载卡片信息到链表
void loadCardListFromFile() {
    // 首先确保链表已初始化（有一个头节点）
    if (cardList == NULL) {
        initNodeList();
    }

    FILE* fp = fopen(CARDPATH, "rb"); // "rb" -> read binary, 以二进制读取模式打开文件
    if (fp == NULL) {
        // 文件不存在是正常情况（首次运行），无需报错
        printf("未找到数据文件 %s，将创建一个新的空列表。\n", CARDPATH);
        return;
    }

    Card tempCard;
    // 循环读取文件，直到文件末尾
    // fread 返回成功读取的项数，当读到文件尾时，它会返回 0
    while (fread(&tempCard, sizeof(Card), 1, fp) == 1) {
        // 每读取一张卡的信息，就调用 addCard 将它加入链表
        addCard(tempCard);
    }

    fclose(fp); // 关闭文件
    printf("已成功从 %s 加载卡片信息。\n", CARDPATH);
}
void resetSystemData() {
    releaseCardList(); // 释放所有旧节点
    initNodeList();    // 创建一个新的空链表头
    FILE* fp = fopen(CARDPATH, "wb"); // "wb" 模式会覆盖或创建新文件
    if (fp != NULL) {
        fclose(fp); // 打开后立即关闭，文件内容就被清空了
        printf("数据文件 %s 已被清空。\n", CARDPATH);
    }
    else {
        printf("警告：无法操作数据文件 %s。\n", CARDPATH);
    }

    printf("系统数据已重置！内存和文件均已清空。\n");
}