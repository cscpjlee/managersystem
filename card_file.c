#define _CRT_SECURE_NO_WARNINGS
#include"card_file.h"
#include"tool.h"
int saveCard(const Card* pCard, const char* pPath)
{
    FILE* fp = NULL;   // �ļ��ṹ��ָ��

    // ��׷�ӵ�ģʽ���ļ��������ʧ�ܣ�����ֻд��ģʽ���ļ�
    if ((fp = fopen(pPath, "ab")) == NULL)
    {
        if ((fp = fopen(pPath, "wb")) == NULL)
        {
            return 0;
        }
    }

    fwrite(pCard, sizeof(Card), 1, fp);

    // �ر��ļ�
    fclose(fp);
    return 1;
}
void loadAndDisplayCards(const char* pPath)
{
    FILE* fp = fopen(pPath, "rb"); // �Զ����ƶ�ȡģʽ���ļ�
    if (fp == NULL)
    {
        printf("�޷����ļ� %s\n", pPath);
        return;
    }

    Card card;
    int count = 0;

    // ѭ����ȡ�ļ��еĿ���Ϣ
    while (fread(&card, sizeof(Card), 1, fp) == 1)
    {
        // ��ʾ����Ϣ
        char aLastTime[50];
        timeToString(card.tLast, aLastTime);
        printf("��ѯ���Ŀ���Ϣ����:\n");
        printf("����\t״̬\t���\t�ۼ�ʹ��\tʹ�ô���\t�ϴ�ʹ��ʱ��\n");
        printf("%s\t%d\t%.1f\t%.1f\t%d\t%s\n", card.c_Number, card.c_Status, card.c_Money, card.s_Money, card.count, aLastTime);
        count++;
    }

    fclose(fp); // �ر��ļ�
    printf("����ȡ�� %d �ſ�����Ϣ��\n", count);
}
int updateCard(const Card* pCard, const char* pPath, int nIndex) {
    FILE* fp = NULL;    // �ļ�ָ��  
    int nLine = 0;      // �ļ�����Ϣ��  
    long lPosition = 0; // �ļ�λ�ñ��  
    Card bBuf;
    if((fp = fopen(pPath, "rb+")) == NULL)  {    
        return 0;  
    }  
    while((!feof(fp)) && (nLine < nIndex-1))  
    {    
        if(fread(&bBuf, sizeof(Card), 1, fp) != 0)    {      // ��ȡ�ļ���ʶλ��      
            lPosition = ftell(fp);      
            nLine++;    
        }  
    }
    fseek(fp, lPosition, 0);  
    fwrite(pCard, sizeof(Card), 1, fp);    
    fclose(fp);  
    return 1;
}
int updateCardInFile(const Card* pCard, const char* pPath, int nIndex)
{
    FILE* fp = NULL;    // �ļ�ָ��
    int nLine = 0;      // �ļ�����Ϣ��
    long lPosition = 0; // �ļ�λ�ñ��
    Card bBuf;

    if ((fp = fopen(pPath, "rb+")) == NULL)
    {
        printf("�޷����ļ� %s\n", pPath);
        return 0;
    }

    while ((!feof(fp)) && (nLine < nIndex - 1))
    {
        if (fread(&bBuf, sizeof(Card), 1, fp) != 0)
        {
            lPosition = ftell(fp);
            nLine++;
        }
    }

    fseek(fp, lPosition, 0);
    fwrite(pCard, sizeof(Card), 1, fp);
    fclose(fp);
    return 1;
}

// ���¿���Ϣ��������
int updateCardInfo(const char* filePath)
{
    struct tm* endTime;     // ��ֹʱ��
    struct tm* startTime;   // ����ʱ��
    int nIndex;             // Ҫ���µļ�¼����
    Card card;

    printf("�����ļ� %s �еڼ�����¼��", CARDPATH);
    scanf("%d", &nIndex);

    printf("������������ݣ�\n");
    printf("�����뿨�ţ�");
    scanf("%s", card.c_Number);
    printf("���������룺");
    scanf("%s", card.c_Password);
    printf("�����뿪����");
    scanf("%f", &card.c_Money);

    card.s_Money = card.c_Money;    // ��ӿ�ʱ���ۼƽ����ڿ������
    card.nDel = 0;                     // ɾ����ʶ
    card.c_Status = 0;                  // ��״̬
    card.count = 0;                // ʹ�ô���
    card.tStart = card.tEnd = card.tLast = time(NULL);  // ���ݿ���ʱ�䣬�����ֹʱ�䣬ÿ�ſ�����Ч��Ϊһ��

    startTime = localtime(&card.tStart);
    endTime = localtime(&card.tEnd);
    endTime->tm_year = startTime->tm_year + 1;
    card.tEnd = mktime(endTime);

    if (updateCardInFile(&card, filePath, nIndex))
    {
        printf("����Ϣ���³ɹ���\n");
        return 1;
    }
    else
    {
        printf("����Ϣ����ʧ�ܣ�\n");
        return 0;
    }
}
int isExsit(const char* pNum, const char* pPath) {
    FILE* fp = NULL;  // �ļ��ṹ��ָ��  
    char aName[18]={0};   // ��Ŷ�ȡ���Ŀ���
    if((fp = fopen(pPath, "rb")) == NULL)  {    
        return 0; 
    }
    while(!feof(fp))  {    // ��ȡ���ţ����ȽϿ����Ƿ�Ϊ��ǰ���ҵĿ���    
        if(fread(aName, sizeof(aName), 1, fp) != 0)    {      
            if(strcmp(aName, pNum) == 0)      {        
                fclose(fp);        
                return 1;      
            }      else         
                fseek(fp, sizeof(Card) - sizeof(aName), SEEK_CUR);    }  }  
    fclose(fp);  
    return 0;
}
