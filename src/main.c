#include <stdio.h>
#include "list.h"

int cmp(int a, int b)
{
    if      (a < b) return -1;
    else if (a > b) return 1;
    else            return 0;
}

int main(int argc, char *argv[])
{
    List l = listInit();
    List p;
    listPushBackSort(l, 5 , cmp);
    listPushBackSort(l, 33, cmp);
    listPushBackSort(l, 9 , cmp);
    listPushBackSort(l, 1 , cmp);
    listPushBackSort(l, 99, cmp);

    p = listBegin(l);
    while (p != NULL)
    {
        printf("%d\n", listVal(p));
        NEXT(p);
    }
    puts("---");
    p = listRbegin(l);
    while (p != NULL)
    {
        printf("%d\n", listVal(p));
        PREV(p);
    }

    puts("+++");
    listRemoveVal(l, 5);

    p = listBegin(l);
    while (p != NULL)
    {
        printf("%d\n", listVal(p));
        NEXT(p);
    }
    puts("---");
    p = listRbegin(l);
    while (p != NULL)
    {
        printf("%d\n", listVal(p));
        PREV(p);
    }

    listFree(l);

    return 0;
}
