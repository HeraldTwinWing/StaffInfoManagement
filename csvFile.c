//
// Created by Avalanche_Exia on 2018/11/15.
//

#include "csvFile.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stringOperation.h"
#include <string.h>

#define BOOL int
#define false 0
#define true 1

int row = 0;    //行数
int line = 0;   //列数


char ***sheetOpen()
{
    FILE *temp;
    FILE *csv;

    csv = fopen("Staff.csv", "r");

    //统计文件行数和列数
    while (1)
    {
        char a = (char) getc(csv);
        if (a == EOF)
        {
            line++;
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
        char *a = malloc(100 * sizeof(char));
        for (int l = 0; l < 100; ++l)
        {
            *(a + l) = '\0';
        }

        a = strtok(str, ",");

        // 将表格内容存入数组
        for (int k = 0; k < sizeof(st[j][0]); ++k)
        {
            if (a[k] == '\0')
            {
                break;
            }
            //st[j][0][k] = a[k];
            strcpy(st[j][0], a);
        }
        for (int i = 1; i < row; ++i)
        {
            a = strtok(NULL, ",");
            /*for (int k = 0; k < sizeof(st[j][0]); ++k)
            {
                if (a[k] == '\0')
                {
                    break;
                }
                //st[j][0][k] = a[k];

            }*/
            strcpy(st[j][i], a);
        }
        free(a);
        free(str);
    }

    fclose(temp);
    return st;
}

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

    getch();
    system("cls");
    line = 0;
    row = 0;
    //fclose(csv);
}

int queryContents(char ***sheet, char queryContent[])
{
    BOOL haveFound = false;
    int whereTheLine = 0;

    // 对比查询内容,搜索查询内容所在行
    for (int i = 0; i < line; ++i)
    {
        if (compareString(sheet[i][0], queryContent))
        {
            haveFound = true;
            whereTheLine = i;
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
        printf("\n");
    }
    free(sheet);
}

void sheetContentRemove()
{
    char ***sheet = sheetOpen();
    char *ID = NULL;

    printf("Enter ID you want to remove:");
    scanf("%s", ID);

    int whereTheLine = 0;
    whereTheLine = queryContents(sheet, ID);

    printf("Do you want to remove this ID and its all contents?[Y/N]");
    BOOL remove = false;
    while (true)
    {
        int a = getch();
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
            sheet[whereTheLine][i] = NULL;
        }
    }

    FILE *csv = fopen("Staff.csv", "w");
    for (int j = 0; j < line; ++j)
    {
        for (int i = 0; i < row; ++i)
        {
            fputs(sheet[j][i], csv);
            if (i != row - 1)
            {
                fputc(',', csv);
            }
        }
        fputc('\n', csv);
    }
    free(sheet);
    fclose(csv);
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
