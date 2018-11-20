#include <stdio.h>
#include "menu.h"
#include "csvFile.h"

int main()
{
    while (exitSystem)
    {
        showMenu();
        selectOption();
    }
}
