//
// Created by Avala on 2018/12/18.
//

#include "mainFunction.h"
#include <string.h>
#include <conio.h>

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