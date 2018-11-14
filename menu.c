//
// Created by Avalanche_Exia on 2018/11/14.
//

#include "menu.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "stringOperation.h"
#include "conio.h"

int adminMode = 0;
int exitSystem = 1; //用于控制主循环

void showMenu()
{
    if (adminMode == 0)
    {
        printf("User Mode\n");
        printf("Enter serial number to chose\n");
        printf("1: Query yourself\n");
        printf("2: AdminMode\n");
        printf("3: Exit\n");
    }
    else if (adminMode == 1)
    {
        printf("Admin Mode\n");
        printf("Enter serial number to chose\n");
        printf("1: Query by job number\n");
        printf("2: Entry\n");
        printf("3: Modify\n");
        printf("4: Delete\n");
        printf("5: Change Password\n");
        printf("6: Exit\n");
    }
}

void selectOption()
{
    int selected = 0;
    char password[15] = "admin";    //密码
    char inputPassword[15] = "";
    scanf("%d", &selected);
    if (adminMode == 0)
    {
        switch (selected)
        {
            case 1:       //查询功能
                break;
            case 2:       //管理员模式
                enterAdminMode(password, inputPassword);
                break;
            case 3:       //退出系统
                exitSystem = 0;
                break;
        }
    }
    else if (adminMode == 1)
    {

    }
}

void enterAdminMode(char *password,char *inputPassword) //清屏并显示进入管理员模式
{
    printf("Please enter the password:");
    enterPassword(inputPassword);   //输入密码
    if (compareString(password, inputPassword))
    {
        adminMode = 1;  //进入管理员模式
        system("cls");
    }
    else
    {
        printf("Password Error!\n");
    }
}