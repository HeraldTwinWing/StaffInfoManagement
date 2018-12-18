//
// Created by Avalanche_Exia on 2018/11/15.
//

#ifndef STAFFINFOMANAGEMENT_CSVFILE_H
#define STAFFINFOMANAGEMENT_CSVFILE_H

#endif //STAFFINFOMANAGEMENT_CSVFILE_H

#include <stdio.h>
#include <stdlib.h>

#define BOOL int
#define false 0
#define true 1

int row;    //行数
int line;   //列数

char ***sheetOpen();

//该函数功能将查询表格的所有内容，并返回第一个匹配值所在行
int queryContents(char ***sheet, char queryContent[]);

void contentWrite(char ***sheet);

//遍历表格，查询所有符合内容所在行，返回所有匹配值所在行
//queryRow参数为查询的列，从1开始计算
int *traverse(char *queryContent, int queryRow);

void queryByDepart();

//初始化line和row变量
//涉及文件读取的操作，结束时必须调用函数
void refreshLineAndRowTemp();

void sheetModfiy();

char ***create3DArray();