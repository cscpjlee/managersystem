#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include"model.h"
#include"menu.h"
#define MAX 1000
int main() {
    loadCardListFromFile(); 

    while (1) {
        while (g_currentUserRole == ROLE_NONE) {
            if (!login()) { // 如果登录失败
				system("pause");
                system("cls"); // 清屏
            }
            else {
                break; // 登录成功，跳出登录循环
            }
        }
        int choice = -1;
        while (g_currentUserRole != ROLE_NONE) {
            system("cls"); 
            if (g_currentUserRole == ROLE_ADMIN) {
                showAdminMenu();
                printf("管理员，请输入您的选择: ");
                scanf("%d", &choice);
                switch (choice) {
				case 1:
							add();
							break;//添加
						case 2:
							query();
							break;//查询
						case 3:
							startUsing();
							break;//上机
						case 4:
							endUsing();
							break;//下机
						case 5:
							recharge();
							break;//充值
						case 6:
							refund();
							break;//退费
						case 7:
							statistics();
							break;//查询统计
						case 8: 
						    delete();
							break;//注销卡
						case 9:
							modify();
							break;//修改卡
						case 10:
							resetData();
							break;//重置文件
						case 11:
							fuzzyQuery();
							break;//模糊查询
						case 0:
							logout();
							break;
						default:
							printf("请重新输入\n");
							break;
                }
				system("pause");
				system("cls");
            }
            else if (g_currentUserRole == ROLE_USER) {
                // --- 用户操作循环 ---
                showUserMenu();
                printf("用户，请输入您的选择: ");
                scanf("%d", &choice);
         
                switch (choice) {
                case 1: 
					userStartUsing(); 
					break; 
                case 2: 
					userEndUsing(); 
					break;
                case 3: 
					showMyInfo(); 
					break;
                case 4: 
					changeMyPassword();
					break;
                case 5: 
					userRecharge(); 
					break;
                case 0: 
					logout(); 
					break;
                default: printf("无效输入!请重新输入!\n");
                }
				system("pause");
				system("cls");
            }
        }

        // 注销后，清屏准备下一次登录
        system("cls");
        printf("您已成功注销登录。\n\n");
    }
    return 0;
}
