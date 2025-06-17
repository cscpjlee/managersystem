#define _CRT_SECURE_NO_WARNINGS
#include"card_file.h"
#include"tool.h"
lpCardNode cardList = NULL;
void saveCardListToFile() {
    // �������Ϊ�ջ���ֻ��һ��ͷ�ڵ㣬�����豣��
    if (cardList == NULL || cardList->next == NULL) {
        return;
    }

    FILE* fp = fopen(CARDPATH, "wb"); // "wb" -> write binary, �Զ�����д��ģʽ���ļ�
    if (fp == NULL) {
        printf("�����޷����ļ� %s ����д�룡\n", CARDPATH);
        return;
    }

    lpCardNode current = cardList->next; // �ӵ�һ����Ч�ڵ㿪ʼ
    while (current != NULL) {
        // ����ǰ�ڵ�� data (�� Card �ṹ��) д���ļ�
        fwrite(&(current->data), sizeof(Card), 1, fp);
        current = current->next;
    }

    fclose(fp); // �ر��ļ�
    printf("���п�Ƭ��Ϣ�ѳɹ����浽 %s\n", CARDPATH);
}
// �� card_file.c �ļ�ĩβ���

// ���ļ����ؿ�Ƭ��Ϣ������
void loadCardListFromFile() {
    // ����ȷ�������ѳ�ʼ������һ��ͷ�ڵ㣩
    if (cardList == NULL) {
        initNodeList();
    }

    FILE* fp = fopen(CARDPATH, "rb"); // "rb" -> read binary, �Զ����ƶ�ȡģʽ���ļ�
    if (fp == NULL) {
        // �ļ�������������������״����У������豨��
        printf("δ�ҵ������ļ� %s��������һ���µĿ��б�\n", CARDPATH);
        return;
    }

    Card tempCard;
    // ѭ����ȡ�ļ���ֱ���ļ�ĩβ
    // fread ���سɹ���ȡ���������������ļ�βʱ�����᷵�� 0
    while (fread(&tempCard, sizeof(Card), 1, fp) == 1) {
        // ÿ��ȡһ�ſ�����Ϣ���͵��� addCard ������������
        addCard(tempCard);
    }

    fclose(fp); // �ر��ļ�
    printf("�ѳɹ��� %s ���ؿ�Ƭ��Ϣ��\n", CARDPATH);
}
void resetSystemData() {
    releaseCardList(); // �ͷ����оɽڵ�
    initNodeList();    // ����һ���µĿ�����ͷ
    FILE* fp = fopen(CARDPATH, "wb"); // "wb" ģʽ�Ḳ�ǻ򴴽����ļ�
    if (fp != NULL) {
        fclose(fp); // �򿪺������رգ��ļ����ݾͱ������
        printf("�����ļ� %s �ѱ���ա�\n", CARDPATH);
    }
    else {
        printf("���棺�޷����������ļ� %s��\n", CARDPATH);
    }

    printf("ϵͳ���������ã��ڴ���ļ�������ա�\n");
}