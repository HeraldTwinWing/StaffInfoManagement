//
// Created by Avalanche_Exia on 2018/11/15.
//

#include "csvFile.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stringOperation.h"

#define BOOL int
#define false 0
#define true 1


int row = 0;    //行数
int line = 0;   //列数

char ***sheetOpen(int openMode)
{
    FILE *csv;
    FILE *temp;

    /* openMode:
     * 0: 读
     * 1: 写
     */
    switch (openMode)
    {
        case 1:
            csv = fopen("Staff.csv", "w");
            break;
        default:
            csv = fopen("Staff.csv", "r");
            break;
    }

    //统计文件行数和列数
    while (1)
    {
        char a = (char) getc(csv);
        if (a == EOF)
        {
            break;
        }
        else if (a == '\n')
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

    for (int j = 0; j < line; ++j)
    {
        char *str = malloc(100 * sizeof(char));
        fgets(str, 100, temp);
        char *a = strtok(str, ",");

        // 将表格内容存入数组
        for (int k = 0; k < 100; ++k)
        {
            if (a[k] == '\0')
            {
                break;
            }
            st[j][0][k] = a[k];
        }
        for (int i = 1; i < row; ++i)
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

    fclose(csv);
    return st;
}

void sheetQuery(BOOL adminMode, char *ID)
{
    char queryContent[100];

    if (adminMode == false)
    {
        strcpy(queryContent, ID);
        queryContents(queryContent);
    }
    else
    {
        scanf("%s", queryContent);
        queryContents(queryContent);
    }
}

void queryContents(char queryContent[])
{
    char ***sheet = sheetOpen(0);
    BOOL haveFound = false;
    int whereTheLine = 0;

    // 对比查询内容,搜索查询内容所在列
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
        // 输出表头
        for (int i = 0; i < row; ++i)
        {
            printf("%s\t", sheet[0][i]);
            // 格式化
            if (i == 1)
            {
                printf("\t");
            }
        }

        printf("\n");
        for (int j = 0; j < row; ++j)
        {
            printf("%s\t", sheet[whereTheLine][j]);
            // 格式化
            if (j == 2 || j == 5)
            {
                printf("\t");
            }
        }
        getchar();
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
