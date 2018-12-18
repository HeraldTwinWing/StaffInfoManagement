//
// Created by Avala on 2018/12/18.
//

#include "mainFunction.h"
#include <string.h>
#include <conio.h>

//读取Staff.csv并查询指定ID
//查询到后会输出指定内容所在行的全部内容
//adminMode 用于检测是否处于管理员模式
//非管理员模式下默认查询本人ID
//管理员模式下需指定ID
//仅返回第一个匹配内容
void sheetQuery(BOOL adminMode, char *ID)
{
    char ***sheet = sheetOpen();
    char queryContent[100];

    if (adminMode == false)
    {
        strcpy(queryContent, ID);
        queryContents(sheet, queryContent);
    }
    else
    {
        printf("Please enter ID that you want to query:");
        scanf("%s", queryContent);
        queryContents(sheet, queryContent);
    }

    printf("Press enter to continue.\n");
    while (true)
    {
        int pressKey = getch();
        if (pressKey == 13)
        {
            break;
        }
    }

    system("cls");
}