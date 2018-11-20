//
// Created by Avalanche_Exia on 2018/11/15.
//

#include "csvFile.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BOOL int
#define false 0
#define true 1

#include "stringOperation.h"

char ***Sheet;
int row = 0;    //行数
int line = 0;   //列数

char ***sheetOpen()
{
    FILE *csv;
    FILE *temp;
    csv = fopen("Staff.csv", "r");

    //统计文件行数和列数
    while (1)
    {
        char a = (char) getc(csv);
        if (a == EOF)
        {
            break;
        }

        if (a == '\n')
        {
            line++;
        }
        else if (a == ',' && line == 0)
        {
            row++;
        }
    }

    // 动态申请2维字符串数组，用于存放文件内容
    temp = fopen("Staff.csv", "r");
    char ***st = NULL;
    st = (char ***) malloc(line * sizeof(char **));
    for (int l = 0; l < line; ++l)
    {
        st[l] = (char **) malloc(row * sizeof(char *));
        for (int i = 0; i < row; ++i)
        {
            st[l][i] = (char *) malloc(100 * sizeof(char));

            // 初始化数组
            for (int j = 0; j < 100; ++j)
            {
                st[l][i][j] = '\0';
            }
        }
    }

    //将文件内容存入数组
    for (int j = 0; j < line; ++j)
    {
        char *str = malloc(100 * sizeof(char));
        fgets(str, 100, temp);
        char * a = strtok(str, ",");

        for (int k = 0; k < 100; ++k)
        {
            if (a[k] == '\0')
            {
                break;
            }
            st[j][0][k] = a[k];
        }

        for (int i = 1 ; i < row; ++i)
        {
            a = strtok(NULL, ",");
            for (int k = 0; k < 100; ++k)
            {
                if (a[k] == '\0')
                {
                    break;
                }
                st[j][i][k] = a[k];
            }
        }

        free(str);
    }

    return st;
}

void sheetQuery()
{
    char ***sheet = sheetOpen();

    char queryContent[100];
    scanf("%s", queryContent);
    BOOL haveFound = false;
    int whereTheLine = 0;

    system("cls");

    // 对比查询内容
    for (int i = 0; i < line; ++i)
    {
        for (int j = 0; j < row; ++j)
        {
            if (compareString(sheet[i][j], queryContent))
            {
                haveFound = true;
                whereTheLine = i;
            }
        }
    }

    if (haveFound == false)
    {
        printf("The specified content was not found\n");
        getch();
        system("cls");
    }
    else
    {
        for (int j = 0; j < 2; ++j)
        {
            for (int i = 0; i < row; ++i)
            {
                if (j == 1)
                {
                    j = whereTheLine;
                }
                printf("%s\t  ", sheet[j][i]);
            }
            if (j == whereTheLine)
            {
                break;
            }
        }
        getch();
        system("cls");
    }
    free(sheet);
}

void create3DArray()
{
    char ***st = NULL;
    st = (char ***) malloc(line * sizeof(char **));
    for (int l = 0; l < line; ++l)
    {
        st[l] = (char **) malloc(row * sizeof(char *));
        for (int i = 0; i < row; ++i)
        {
            st[l][i] = (char *) malloc(100 * sizeof(char));
        }
    }
}
