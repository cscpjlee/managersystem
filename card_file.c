#define _CRT_SECURE_NO_WARNINGS
#include"card_file.h"
#include"tool.h"
int saveCard(const Card* pCard, const char* pPath)
{
    FILE* fp = NULL;   // 文件结构体指针

    // 以追加的模式打开文件，如果打开失败，则以只写的模式打开文件
    if ((fp = fopen(pPath, "ab")) == NULL)
    {
        if ((fp = fopen(pPath, "wb")) == NULL)
        {
            return 0;
        }
    }

    fwrite(pCard, sizeof(Card), 1, fp);

    // 关闭文件
    fclose(fp);
    return 1;
}
void loadAndDisplayCards(const char* pPath)
{
    FILE* fp = fopen(pPath, "rb"); // 以二进制读取模式打开文件
    if (fp == NULL)
    {
        printf("无法打开文件 %s\n", pPath);
        return;
    }

    Card card;
    int count = 0;

    // 循环读取文件中的卡信息
    while (fread(&card, sizeof(Card), 1, fp) == 1)
    {
        // 显示卡信息
        char aLastTime[50];
        timeToString(card.tLast, aLastTime);
        printf("查询到的卡信息如下:\n");
        printf("卡号\t状态\t余额\t累计使用\t使用次数\t上次使用时间\n");
        printf("%s\t%d\t%.1f\t%.1f\t%d\t%s\n", card.c_Number, card.c_Status, card.c_Money, card.s_Money, card.count, aLastTime);
        count++;
    }

    fclose(fp); // 关闭文件
    printf("共读取了 %d 张卡的信息。\n", count);
}
int updateCard(const Card* pCard, const char* pPath, int nIndex) {
    FILE* fp = NULL;    // 文件指针  
    int nLine = 0;      // 文件卡信息数  
    long lPosition = 0; // 文件位置标记  
    Card bBuf;
    if((fp = fopen(pPath, "rb+")) == NULL)  {    
        return 0;  
    }  
    while((!feof(fp)) && (nLine < nIndex-1))  
    {    
        if(fread(&bBuf, sizeof(Card), 1, fp) != 0)    {      // 获取文件标识位置      
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
    FILE* fp = NULL;    // 文件指针
    int nLine = 0;      // 文件卡信息数
    long lPosition = 0; // 文件位置标记
    Card bBuf;

    if ((fp = fopen(pPath, "rb+")) == NULL)
    {
        printf("无法打开文件 %s\n", pPath);
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

// 更新卡信息的主函数
int updateCardInfo(const char* filePath)
{
    struct tm* endTime;     // 截止时间
    struct tm* startTime;   // 开卡时间
    int nIndex;             // 要更新的记录索引
    Card card;

    printf("更新文件 %s 中第几条记录：", CARDPATH);
    scanf("%d", &nIndex);

    printf("请输入更新内容：\n");
    printf("请输入卡号：");
    scanf("%s", card.c_Number);
    printf("请输入密码：");
    scanf("%s", card.c_Password);
    printf("请输入开卡金额：");
    scanf("%f", &card.c_Money);

    card.s_Money = card.c_Money;    // 添加卡时，累计金额等于开卡金额
    card.nDel = 0;                     // 删除标识
    card.c_Status = 0;                  // 卡状态
    card.count = 0;                // 使用次数
    card.tStart = card.tEnd = card.tLast = time(NULL);  // 根据开卡时间，计算截止时间，每张卡的有效期为一年

    startTime = localtime(&card.tStart);
    endTime = localtime(&card.tEnd);
    endTime->tm_year = startTime->tm_year + 1;
    card.tEnd = mktime(endTime);

    if (updateCardInFile(&card, filePath, nIndex))
    {
        printf("卡信息更新成功！\n");
        return 1;
    }
    else
    {
        printf("卡信息更新失败！\n");
        return 0;
    }
}
int isExsit(const char* pNum, const char* pPath) {
    FILE* fp = NULL;  // 文件结构体指针  
    char aName[18]={0};   // 存放读取出的卡号
    if((fp = fopen(pPath, "rb")) == NULL)  {    
        return 0; 
    }
    while(!feof(fp))  {    // 读取卡号，并比较卡号是否为当前查找的卡号    
        if(fread(aName, sizeof(aName), 1, fp) != 0)    {      
            if(strcmp(aName, pNum) == 0)      {        
                fclose(fp);        
                return 1;      
            }      else         
                fseek(fp, sizeof(Card) - sizeof(aName), SEEK_CUR);    }  }  
    fclose(fp);  
    return 0;
}
