//
// Created by Avala on 2018/12/18.
//

#include "mainFunction.h"
#include <string.h>
#include <conio.h>

//�޸Ĺ���Աģʽ����
void changePassword()
{
    //�����������hashֵ
    printf("Please Enter the new password:");
    char newPassword[15] = {0};
    scanf("%s", newPassword);
    int newPasswordHash = RSHash(newPassword, 15);

    //��������hashֵд���ļ�
    FILE *pw = fopen("password", "w");
    fprintf(pw, "%d", newPasswordHash);
    fclose(pw);

    printf("Change completed\n");
    getch();
    system("cls");
}

//��ȡStaff.csv����ѯָ��ID
//��ѯ��������ָ�����������е�ȫ������
//adminMode ���ڼ���Ƿ��ڹ���Աģʽ
//�ǹ���Աģʽ��Ĭ�ϲ�ѯ����ID
//����Աģʽ����ָ��ID
//�����ص�һ��ƥ������
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

//ΪCSV�ļ������
//����¼����Ա����Ϣ
//¼��ǰ���������ID�Ƿ����
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

        //������Ϊ��ʱ��*ռλ
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

//��ID������ɾ����ID������
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