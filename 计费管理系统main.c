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
            if (!login()) { // �����¼ʧ��
				system("pause");
                system("cls"); // ����
            }
            else {
                break; // ��¼�ɹ���������¼ѭ��
            }
        }
        int choice = -1;
        while (g_currentUserRole != ROLE_NONE) {
            system("cls"); 
            if (g_currentUserRole == ROLE_ADMIN) {
                showAdminMenu();
                printf("����Ա������������ѡ��: ");
                scanf("%d", &choice);
                switch (choice) {
				case 1:
							add();
							break;//���
						case 2:
							query();
							break;//��ѯ
						case 3:
							startUsing();
							break;//�ϻ�
						case 4:
							endUsing();
							break;//�»�
						case 5:
							recharge();
							break;//��ֵ
						case 6:
							refund();
							break;//�˷�
						case 7:
							statistics();
							break;//��ѯͳ��
						case 8: 
						    delete();
							break;//ע����
						case 9:
							modify();
							break;//�޸Ŀ�
						case 10:
							resetData();
							break;//�����ļ�
						case 11:
							fuzzyQuery();
							break;//ģ����ѯ
						case 0:
							logout();
							break;
						default:
							printf("����������\n");
							break;
                }
				system("pause");
				system("cls");
            }
            else if (g_currentUserRole == ROLE_USER) {
                // --- �û�����ѭ�� ---
                showUserMenu();
                printf("�û�������������ѡ��: ");
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
                default: printf("��Ч����!����������!\n");
                }
				system("pause");
				system("cls");
            }
        }

        // ע��������׼����һ�ε�¼
        system("cls");
        printf("���ѳɹ�ע����¼��\n\n");
    }
    return 0;
}
