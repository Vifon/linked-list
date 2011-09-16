#include "list.h"
#include <stdlib.h>

List listInit()
{
    List root   = newListNode();

    /* MODIFY ME */
    root->v      = 0x80000000;
    /* MODIFY ME */

    root->isRoot = 1;
    root->n      = NULL;
    root->p      = NULL;
    return root;
}

List listRbegin(List root)
{
    while (root->n != NULL)
        NEXT(root);
    return root;
}

void listFree(List root)
{
    if (root->n != NULL)
        listFree(root->n);
    free(root);
}

void listPushBack(List root, T val)
{
    root = listRbegin(root);
    listAddAfter(root, val);
}

void listPushBackSort(List root, T val, int (*compare)(T, T))
{
    /* compare should return -1 on lesser, 0 on equal and 1 on greater */
    while (root->n != NULL && compare(root->n->v, val) < 0)
        NEXT(root);
    listAddAfter(root, val);
}

void listAddAfter(List place, T val)
{
    List ptr;
    ptr             = newListNode();
    ptr->isRoot     = 0;
    ptr->v          = val;
    ptr->n          = place->n;
    if (!place->isRoot)
        ptr->p      = place;
    else
        ptr->p      = NULL;
    if (place->n != NULL)
        place->n->p = ptr;
    place->n        = ptr;
}

List listGet(List root, int n)
{
    int i;
    for (i = 0; i <= n; ++i)    /* intentional apparent off-by-one! */
    {
        NEXT(root);
        if (root == NULL)
            return NULL;        /* out-of-list exception */
    }
    return root;
}

void listRemove(List element)
{
    if (element->p != NULL)
        element->p->n = element->n;
    if (element->n != NULL)
        element->n->p = element->p;
    free(element);
}

int listRemoveN(List root, int n)
{
    root = listGet(root, n);
    if (root == NULL)
        return 0;               /* out-of-list exception */
    listRemove(root);
    return 1;
}

int listRemoveVal(List root, T val)
{
    for (; root != NULL && root->v != val; NEXT(root));
    if (root == NULL)
        return 0;
    listRemove(root);
    return 1;
}
