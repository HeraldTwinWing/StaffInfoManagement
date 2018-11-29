#include <stdio.h>
#include "menu.h"
#include "csvFile.h"
#include "hash.h"

int main()
{
    while (exitSystem)
    {
        showMenu();
        selectOption();
    }
}