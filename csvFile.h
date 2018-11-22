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

char ***sheetOpen();

void sheetQuery(BOOL adminMode, char *ID);

int queryContents(char ***sheet, char queryContent[]);

void sheetContentRemove();

//遍历表格，查询所有符合内容所在行
int *traverse(char *queryContent, int queryROw);

void queryByApart();

//初始化line和row变量
//涉及文件读取的操作，结束时必须调用函数
void refreshLineAndRowTemp();

void sheetAddLine();

void sheetModfiy();

char ***create3DArray();