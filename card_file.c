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
        printf("�����޷����ļ� %s ����д�룡\n", CARDPATH);
        return;
    }
    lpCardNode current = cardList->next; 
    while (current != NULL) {
        fwrite(&(current->data), sizeof(Card), 1, fp);
        current = current->next;
    }

    fclose(fp); // �ر��ļ�
    printf("���п�Ƭ��Ϣ�ѳɹ����浽 %s\n", CARDPATH);
}
void loadCardListFromFile() {
    if (cardList == NULL) {
        initNodeList();
    }
    FILE* fp = fopen(CARDPATH, "rb"); 
    if (fp == NULL) {
        printf("δ�ҵ������ļ� %s��������һ���µĿ��б�\n", CARDPATH);
        return;
    }

    Card tempCard;
    while (fread(&tempCard, sizeof(Card), 1, fp) == 1) {
        addCard(tempCard);
    }

    fclose(fp); 
    printf("�ѳɹ��� %s ���ؿ�Ƭ��Ϣ��\n", CARDPATH);
}
void resetSystemData() {
    releaseCardList(); 
    initNodeList();    
    FILE* fp = fopen(CARDPATH, "wb"); 
    if (fp != NULL) {
        fclose(fp); 
        printf("�����ļ� %s �ѱ���ա�\n", CARDPATH);
    }
    else {
        printf("���棺�޷����������ļ� %s��\n", CARDPATH);
    }

    printf("ϵͳ���������ã��ڴ���ļ�������ա�\n");
}