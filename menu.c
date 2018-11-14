//
// Created by Avalanche_Exia on 2018/11/14.
//

#include "menu.h"
#include <stdio.h>
#include <string.h>

int adminMode = 0;

void showMenu()
{
    if (adminMode == 0)
    {
        printf("Enter serial number to chose");
        printf("1: Query yourself");
        printf("2: AdminMode");
        printf("3: Exit");
    }
    else if (adminMode == 1)
    {
        printf("Enter serial number to chose");
        printf("1: Query by job number");
        printf("2: Entry");
        printf("3: Modify");
        printf("4: Delete");
    }
}

void selectOption()
{
    int selected = 0;
    char *password = "TwinWing";
    char *inputPassword = "";
    scanf("%d", &selected);
    if (adminMode == 0)
    {
        switch (selected)
        {
            case 1:       //查询功能
                break;
            case 2:       //管理员模式
                gets(inputPassword);
                if (*inputPassword == *password)
                {
                    adminMode == 1;
                }
                break;
            case 3:       //退出
                break;
        }
    }
    else if (adminMode == 1)
    {

    }
}