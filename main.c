#include <stdio.h>
#include "menu.h"
#include "csvFile.h"

int maain()
{
    while (exitSystem)
    {
        showMenu();
        selectOption();
    }
}

int main()
{
    char *sheet = sheetOpen();
}