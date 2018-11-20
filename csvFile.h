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

char ***sheetOpen(int openMode);
void sheetQuery(BOOL adminMode, char* ID);
void queryContents(char queryContent[]);
void sheetModfiy();
void create3DArray();