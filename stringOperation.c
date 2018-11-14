//
// Created by Avalanche_Exia on 2018/11/14.
//

#include "stringOperation.h"
#include <stdio.h>
#include <string.h>


int compareString(char *a, char *b) //比较两个字符串是否相同
{
    if (strlen(a) == strlen(b))
    {
        for (int i = 0; i < strlen(a); ++i)
        {
            if ((*(a + i)) != (*(b + i)))
            {
                return 0;
            }
        }
        return 1;
    }
    else
    {
        return 0;
    }
}

void enterPassword(char *a) //用于隐藏输入的密码
{
    for (int i = 0; i < 15; ++i)
    {
        char inputValue = (char) getch();
        if (inputValue == '\r')
        {
            printf("\n\n");
            break;
        }
        *(a + i) = inputValue;
        printf("*");
    }


}