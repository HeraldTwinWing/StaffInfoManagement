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

int adminMode = 0;
int exitSystem = 1; //用于控制主循环

void showMenu()
{
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
        printf("2: Entry\n");
        printf("3: Modify\n");
        printf("4: Delete\n");
        printf("5: Change Password\n");
        printf("6: Exit Admin Mode\n");
    }
}

void selectOption()
{
    int selected = 0;
    char password[15] = "admin";    //密码
    scanf("%d", &selected);
    fflush(stdin);  //刷新缓存区
    system("cls");
    if (adminMode == 0)
    {
        switch (selected)
        {
            case 1:       //查询功能
                sheetQuery();
                break;
            case 2:       //管理员模式
                enterAdminMode(password);
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
                break;
            case 2:
                break;
            case 3:
                break;
            case 4:
                break;
            case 5:
                break;
            case 6:
                adminMode = 0;
            default:
                system("cls");
                break;
        }
    }
}

void enterAdminMode(char *password) //清屏并显示进入管理员模式
{
    char inputPassword[15] = "";
    printf("Please enter the password:");
    enterPassword(inputPassword);   //输入密码
    if (compareString(password, inputPassword))
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
                enterAdminMode(password);
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