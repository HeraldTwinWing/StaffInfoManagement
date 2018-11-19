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
        else if (a == ' ' && line == 0)
        {
            row++;
        }
    }

    temp = fopen("Staff.csv", "r");
    char sheet[line][row][100];

    //将文件内容存入数组
    for (int i = 0; i < line; ++i)
    {
        char row1[10][100] = {0};
        fscanf(temp, "%s %s %s %s %s %s %s", row1[0], row1[1], row1[2], row1[3], row1[4], row1[5], row1[6]);

        for (int j = 0; j < row; ++j)
        {
            for (int k = 0; k < 100; ++k)
            {
                sheet[i][j][k] = row1[j][k];
            }
        }
    }
    char *** st = (char ***) malloc(sizeof(line * row * 100));
    ***st = sheet;
    return st;

}

char ***sheetQuery()
{
    char ***sheet = sheetOpen();

    char queryContent[100];
    scanf("%s", queryContent);
    BOOL haveFound = false;
    int whereTheLine = 0;

    for (int i = 0; i < line; ++i)
    {
        for (int j = 0; j < row; ++j)
        {
            if (compareString())
            {
                printf("");
                haveFound = true;
                whereTheLine = i;
            }
        }
    }

    if (haveFound == false)
    {
        printf("The specified content was not found");
    }
    else if (haveFound == true)
    {
        for (int j = 0; j < 2; ++j)
        {
            for (int i = 0; i < row; ++i)
            {
                if (j == 1)
                {
                    j = whereTheLine;
                }
                printf("%s", sheet[j][i]);
            }
            if (j == whereTheLine)
            {
                break;
            }
        }
    }
}
