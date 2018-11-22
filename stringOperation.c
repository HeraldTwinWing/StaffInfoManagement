//
// Created by Avalanche_Exia on 2018/11/14.
//

#include "stringOperation.h"
#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <windows.h>

const char BACKSPACE = 8;

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

int invertBOOL(int a)
{
    switch (a)
    {
        case 1:
            a = 0;
            break;
        case 0:
            a = 1;
            break;
        default:
            break;
    }
    return a;
}

//获取光标的位置x
int whereX()
{
    CONSOLE_SCREEN_BUFFER_INFO pBuffer;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &pBuffer);
    return (pBuffer.dwCursorPosition.X + 1);
}

//获取光标的位置y
int whereY()
{
    CONSOLE_SCREEN_BUFFER_INFO pBuffer;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &pBuffer);
    return (pBuffer.dwCursorPosition.Y + 1);
}


void enterPassword(char *a) //用于隐藏输入的密码
{
    for (int i = 0; i < 15; ++i)
    {
        //int startPosition = whereX();
        //char inputValue;
        //scanf("%c", &inputValue);
        char inputValue = (char) getch();
        if (i != 14)
        {
            if (inputValue == '\r')
            {
                break;
            }
            else if (inputValue == BACKSPACE)   //退格
            {
                //int coord = whereX();
                //if (coord > startPosition)
                {
                    printf("\b ");
                    printf("\b");
                }
                i -= i;
            }
            else    //用*表示密码
            {
                *(a + i) = inputValue;
                printf("*");
            }
        }
        else
        {
            fflush(stdin);
            i -= 1;
        }
    }
}
