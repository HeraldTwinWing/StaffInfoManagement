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


//打开CSV文件
// 返回值为一个内容与该文件内容相同的二维数组的指针
char ***sheetOpen()
{
    refreshLineAndRowTemp();
    FILE *temp;
    FILE *csv;

    csv = fopen("Staff.csv", "r");

    //统计文件行数和列数
    while (1)
    {
        char a = (char) getc(csv);
        if (a == EOF)
        {
            row++;
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
        char *str =(char *) malloc(100 * sizeof(char));
        fgets(str, 100, temp);
        char *a = strtok(str, ",");

        //检测最后一行是否为空格
        if (compareString(str, "\r"))
        {
            break;
        }
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
            if (i == 7)
            {
                a = strtok(NULL, "\n");
            }
            else
            {
                a = strtok(NULL, ",");
            }
            strcpy(st[j][i], a);
        }

        free(str);
    }

    fclose(temp);
    return st;
}

//按ID查询表格内容
//输出匹配ID的所在行全部信息


//查询指定内容，并返回所在行
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
        printf("Press enter to continue.\n");
        while (true)
        {
            int pressKey = getch();
            if (pressKey == 13)
            {
                break;
            }
        }
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
            printf("%s", sheet[whereTheLine][j]);
            int y = whereY();
            switch (j + 1)
            {
                case 1:
                    gotoxy(9, y);
                    break;
                case 2:
                    gotoxy(25, y);
                    break;
                case 3:
                    gotoxy(41, y);
                    break;
                case 4:
                    gotoxy(49, y);
                    break;
                case 5:
                    gotoxy(57, y);
                    break;
                case 6:
                    gotoxy(73, y);
                    break;
                case 7:
                    gotoxy(89, y);
                    break;
                default:
                    break;
            }
        }
        printf("\n");
    }
    //free(sheet);
    return whereTheLine;
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
            //int a = getch();
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

            FILE *csv = fopen("Staff.csv", "w");
            for (int j = 0; j < line; ++j)
            {
                for (int i = 0; i < row; ++i)
                {
                    fputs(sheet[j][i], csv);
                    if (i != row - 1 && invertBOOL(compareString(sheet[j][i], "")))
                    {
                        fputc(',', csv);
                    }
                }

                //当首列为空的时候，不换行，即跳过空行
                if (invertBOOL(compareString(sheet[j][0], "")))
                {
                    fputc('\n', csv);
                }
            }
            fclose(csv);
        }
    }

    free(sheet);
    //refreshLineAndRowTemp();
    system("cls");
}

//初始化line和row变量
void refreshLineAndRowTemp()
{
    line = 0;
    row = 0;
}

//遍历表格查询内容所在行
//返回值为 int 数组
//第一项为查找到的行的数量
//从第二项开始为所在行
int *traverse(char *queryContent, int queryRow)
{
    queryRow--;
    char ***csv = sheetOpen();

    int countLines = 0;
    int *whereTheLines = NULL;
    int arrayPos = 1;
    for (int j = 0; j < 2; ++j)
    {
        for (int i = 1; i < line; ++i)
        {
            BOOL haveFound = false;
            haveFound = compareString(csv[i][queryRow], queryContent);
            if (j == 0)
            {
                if (haveFound == true)
                {
                    countLines++;
                }
            }
            else if (j == 1 && haveFound == true)
            {
                whereTheLines[arrayPos] = i;
                arrayPos++;
            }
        }
        if (j == 0)
        {
            whereTheLines =(int *) malloc((countLines + 1) * sizeof(int));
            whereTheLines[0] = countLines;
        }
    }
    free(csv);
    return whereTheLines;
}

//查询并打印某个部门的全部员工信息
void queryByDepart()
{
    printf("Please enter the department you want to list:");
    char queryContent[100] = {0};
    scanf("%s", queryContent);

    int *whereTheLines = traverse(queryContent, 3);
    char ***sheet = sheetOpen();


    if (whereTheLines != 0)
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

        // 打印查询到的内容
        //whereTheLines第一项为列数
        for (int i = 1; i <= whereTheLines[0]; ++i)
        {
            for (int j = 0; j < row; ++j)
            {
                if (i != row)
                {
                    printf("%s", sheet[whereTheLines[i]][j]);
                }
                else
                {
                    printf("%s\n", sheet[whereTheLines[i]][j]);
                }
                int y = whereY();
                switch (j + 1)
                {
                    case 1:
                        gotoxy(9, y);
                        break;
                    case 2:
                        gotoxy(25, y);
                        break;
                    case 3:
                        gotoxy(41, y);
                        break;
                    case 4:
                        gotoxy(49, y);
                        break;
                    case 5:
                        gotoxy(57, y);
                        break;
                    case 6:
                        gotoxy(73, y);
                        break;
                    case 7:
                        gotoxy(89, y);
                        break;
                    default:
                        break;
                }
            }
            printf("\n");
        }
    }
    else
    {
        printf("The Department do not exist, or have no worker");
    }

    printf("Press enter to continue.\n");
    while (true)
    {
        int pressKey = getch();
        if (pressKey == 13)
        {
            system("cls");
            break;
        }
    }

    free(sheet);
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
            idAlreadyExist = traverse(inputData, 1)[0];
            if (idAlreadyExist != 0)
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

//修改CSV文件的某项的内容
void sheetModfiy()
{
    char ***sheet = sheetOpen();
    char ID[10] = {0};

    printf("Enter ID you want to modfiy:");
    scanf("%s", ID);

    int whereTheLine = 0;
    whereTheLine = queryContents(sheet, ID);

    if (whereTheLine != 0)
    {
        printf("Please enter the head of row you want to change:");
        char changeRow[100] = {0};
        scanf("%s", changeRow);

        printf("\n");
        printf("Please enter the content:");
        char content[100] = {0};
        getchar();
        gets(content);
        if (content[0] == '\0')
        {
            content[0] = '*';
        }

        char *listHead[8] = {"ID", "name", "department", "age", "sex", "birthday", "phonenumber", "address"};
        int targetRow = 0;

        if (compareString(changeRow, "exit"))
        {
            free(sheet);
            system("cls");
            return;
        }
        else
        {
            for (int i = 0; i < row; ++i)
            {
                BOOL found = compareString(listHead[i], changeRow);
                if (found == true)
                {
                    targetRow = i;
                }
            }
        }

        sheet[whereTheLine][targetRow] = content;

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
        printf("\nModfiy completed\n");
        getch();
        fclose(csv);
        free(sheet);
    }


    system("cls");
}



char ***create3DArray()
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
    return st;
}
