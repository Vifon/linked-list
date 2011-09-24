#include <stdio.h>
#include "list.h"
#include <string.h>
#include <stdlib.h>

/* int cmp(int a, int b) */
/* { */
/*     if      (a < b) return -1; */
/*     else if (a > b) return 1; */
/*     else            return 0; */
/* } */

int main(int argc, char *argv[])
{
    List l = listInit();
    List p;
    char* str = malloc(sizeof(char)*10);
    strcpy(str, "bar");
    listPushSort(l, "foo" , strcmp);
    listPushSort(l, "bar", strcmp);
    listPushSort(l, "baz" , strcmp);
    listPushSort(l, "qux" , strcmp);

    p = listBegin(l);
    while (p != NULL)
    {
        printf("%s\n", listVal(p));
        NEXT(p);
    }
    puts("---");
    p = listRbegin(l);
    while (p != NULL)
    {
        printf("%s\n", listVal(p));
        PREV(p);
    }

    puts("+++");
    listRemoveValCustom(l, str, strcmp);
    free(str);

    p = listBegin(l);
    while (p != NULL)
    {
        printf("%s\n", listVal(p));
        NEXT(p);
    }
    puts("---");
    p = listRbegin(l);
    while (p != NULL)
    {
        printf("%s\n", listVal(p));
        PREV(p);
    }

    listFree(l);

    return 0;
}
