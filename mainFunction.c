//
// Created by Avala on 2018/12/18.
//

#include "mainFunction.h"
#include <string.h>
#include <conio.h>

//修改管理员模式密码
void changePassword()
{
    //计算新密码的hash值
    printf("Please Enter the new password:");
    char newPassword[15] = {0};
    scanf("%s", newPassword);
    int newPasswordHash = RSHash(newPassword, 15);

    //将新密码hash值写入文件
    FILE *pw = fopen("password", "w");
    fprintf(pw, "%d", newPasswordHash);
    fclose(pw);

    printf("Change completed\n");
    getch();
    system("cls");
}

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

//为CSV文件添加行
//用于录入新员工信息
//录入前会检查输入的ID是否存在
void sheetAddLine()
{
    char ***sheet = sheetOpen();
    FILE *csv = fopen("Staff.csv", "a");
    BOOL idAlreadyExist = false;

    char inputData[100] = {0};

    for (int i = 0; i < row; ++i)
    {
        printf("Please enter the %s:", sheet[0][i]);
        gets(inputData);

        if (i == 0)
        {
            idAlreadyExist = traverse(sheet[0][i], 1)[0];
            if (idAlreadyExist == 0)
            {
                printf("The ID has already existed\n");
                break;
            }
        }

        //当输入为空时用*占位
        if (compareString(inputData, ""))
        {
            strcpy(inputData, "*");
        }

        fputs(inputData, csv);
        if (i != row - 1)
        {
            fputc(',', csv);
        }
        else
        {
            fputc('\n', csv);
        }
    }

    if (idAlreadyExist == true)
    {
        printf("Entry completed\n");
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
    free(sheet);
    fclose(csv);
    system("cls");
}

//按ID检索后删除该ID所在行
void sheetContentRemove()
{
    char ***sheet = sheetOpen();
    char ID[100] = {0};

    printf("Enter ID you want to remove:");
    scanf("%s", ID);

    int whereTheLine = 0;
    whereTheLine = queryContents(sheet, ID);
    if (whereTheLine != 0)
    {
        printf("Do you want to remove this ID and its all contents?[Y/N]");
        BOOL remove = false;
        while (true)
        {
            char a = 0;
            scanf("%c", &a);
            if (a == 89 || a == 121)
            {
                remove = true;
                break;
            }
            else if (a == 78 || a == 110)
            {
                break;
            }
        }

        if (remove == true)
        {
            for (int i = 0; i < row; ++i)
            {
                sheet[whereTheLine][i] = "";
            }

            contentWrite(sheet);
        }
    }

    free(sheet);
    system("cls");
}