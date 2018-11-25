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

int main1()
{
    int a= RSHash("admin", 15);
    printf("%d", a);
}


