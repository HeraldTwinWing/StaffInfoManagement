//
// Created by Avalanche_Exia on 2018/11/14.
//

#include "menu.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "stringOperation.h"
#include "conio.h"
#include "csvFile.h"
#include "hash.h"

int adminMode = false;
int login = false;
int exitSystem = 1; //用于控制主循环
char ID[100];

void showMenu()
{
    if (login == false)
    {
        printf("Please enter your ID:");
        scanf("%s", ID);
        login = true;
        system("cls");
    }
    if (adminMode == 0)
    {
        printf("==========User Mode==========\n");
        printf("Enter serial number to chose\n");
        printf("1: Query yourself\n");
        printf("2: AdminMode\n");
        printf("3: Exit\n");
    }
    else if (adminMode == 1)
    {
        printf("=========Admin Mode==========\n");
        printf("Enter serial number to chose\n");
        printf("1: Query by job number\n");
        printf("2: Query whole department\n");
        printf("3: Entry\n");
        printf("4: Modify\n");
        printf("5: Delete\n");
        printf("6: Change Password\n");
        printf("7: Exit Admin Mode\n");
    }
}

void selectOption()
{
    int selected = 0;
    //char password[15] = "admin";    //密码
    scanf("%d", &selected);
    fflush(stdin);  //刷新缓存区
    system("cls");
    if (adminMode == 0)
    {
        switch (selected)
        {
            case 1:       //查询功能
                sheetQuery(false, ID);
                break;
            case 2:       //管理员模式
//                enterAdminMode();
                adminMode = true;
                break;
            case 3:       //退出系统
                exitSystem = 0;
                break;
            default:
                system("cls");
                printf("No such option. Press Enter to return\n");
                getch();
                system("cls");
                break;
        }
    }
    else if (adminMode == 1)
    {
        switch (selected)
        {
            case 1:
                sheetQuery(true, ID);
                break;
            case 2:
                queryByApart();
                break;
            case 3:
                sheetAddLine();
                break;
            case 4:
                sheetModfiy();
                break;
            case 5:
                sheetContentRemove();
                break;
            case 6:
                changePassword();
                break;
            case 7:
                adminMode = 0;
                break;
            default:
                system("cls");
                break;
        }
    }

}

void enterAdminMode() //清屏并显示进入管理员模式
{
    char inputPassword[15] = "";
    FILE *pw = fopen("password", "r");
    int password = 0;
    fscanf(pw,"%d", &password);
    printf("Please enter the password:");
    enterPassword(inputPassword);   //输入密码
    //scanf("%s", inputPassword);
    int inputPasswordHash = RSHash(inputPassword, 15);
    if (inputPasswordHash == password)
    {
        adminMode = 1;  //进入管理员模式
        system("cls");
    }
    else
    {
        system("cls");
        printf("Password Error!\n");
        printf("Press ENTER to retry. Press the other keys to return\n");
        char pressKey;
        pressKey = (char) getch();
        switch (pressKey)
        {
            case '\r':  //重新输入密码
                system("cls");
                enterAdminMode();
                break;
//            case 27:    //返回主菜单
//                system("cls");
//                break;
            default:    //返回主菜单
                system("cls");
                break;
        }
    }
}

void changePassword()
{
    printf("Please Enter the new password:");
    char newPassword[15] = {0};
    scanf("%s", newPassword);
    int newPasswordHash = RSHash(newPassword, 15);
    FILE *pw = fopen("password", "w");
    fprintf(pw, "%d", newPasswordHash);
    fclose(pw);
    printf("Change completed\n");
    getch();
    system("cls");
}