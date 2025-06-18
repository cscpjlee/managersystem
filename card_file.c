#define _CRT_SECURE_NO_WARNINGS
#include"card_file.h"
#include"tool.h"
lpCardNode cardList = NULL;
void saveCardListToFile() {
    if (cardList == NULL || cardList->next == NULL) {
        return;
    }
    FILE* fp = fopen(CARDPATH, "wb"); 
    if (fp == NULL) {
        printf("错误：无法打开文件 %s 进行写入！\n", CARDPATH);
        return;
    }
    lpCardNode current = cardList->next; 
    while (current != NULL) {
        fwrite(&(current->data), sizeof(Card), 1, fp);
        current = current->next;
    }

    fclose(fp); // 关闭文件
    printf("所有卡片信息已成功保存到 %s\n", CARDPATH);
}
void loadCardListFromFile() {
    if (cardList == NULL) {
        initNodeList();
    }
    FILE* fp = fopen(CARDPATH, "rb"); 
    if (fp == NULL) {
        printf("未找到数据文件 %s，将创建一个新的空列表。\n", CARDPATH);
        return;
    }

    Card tempCard;
    while (fread(&tempCard, sizeof(Card), 1, fp) == 1) {
        addCard(tempCard);
    }

    fclose(fp); 
    printf("已成功从 %s 加载卡片信息。\n", CARDPATH);
}
void resetSystemData() {
    releaseCardList(); 
    initNodeList();    
    FILE* fp = fopen(CARDPATH, "wb"); 
    if (fp != NULL) {
        fclose(fp); 
        printf("数据文件 %s 已被清空。\n", CARDPATH);
    }
    else {
        printf("警告：无法操作数据文件 %s。\n", CARDPATH);
    }

    printf("系统数据已重置！内存和文件均已清空。\n");
}