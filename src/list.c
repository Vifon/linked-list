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
    NEXT(root);
    while (root != NULL && root->n != NULL)
        NEXT(root);
    return root;
}

void listFreeReal(List* root)
{
    if (*root == NULL)
        return;
    listFreeReal(&(*root)->n);
    free(*root);
    *root = NULL;
}

void listPushBack(List root, T val)
{
    if (!listIsEmpty(root))
        root = listRbegin(root);
    listAddAfter(root, val);
}

void listPushFront(List root, T val)
{
    listAddAfter(root, val);
}

void listPushSort(List root, T val, int (*compare)(T, T))
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

void listRemove(List root, List element)
{
    if (root->n == element)
        root->n = element->n;
    if (element->p != NULL)
        element->p->n = element->n;
    if (element->n != NULL)
        element->n->p = element->p;
    free(element);
}

int listRemoveN(List root, int n)
{
    List element = listGet(root, n);
    if (element == NULL)
        return 0;               /* out-of-list exception */
    listRemove(root, element);
    return 1;
}

int listRemoveVal(List root, T val)
{
    List element = root;
    for (; element != NULL && element->v != val; NEXT(element));
    if (element == NULL)
        return 0;
    listRemove(root, element);
    return 1;
}

int listLength(List root)
{
    int i = 0;
    NEXT(root);
    while (root != NULL)
    {
        NEXT(root);
        ++i;
    }
    return i;
}

int listIsEmpty(List root)
{
    return root->n == NULL;
}

int listPopBack(List root)
{
    List last = listRbegin(root);
    if (last != NULL)
    {
        listRemove(root, last);
        return 1;
    }
    else
        return 0;
}

int listPopFront(List root)
{
    List last = listBegin(root);
    if (last != NULL)
    {
        listRemove(root, last);
        return 1;
    }
    else
        return 0;
}

List listCopy(List source)
{
    List copy = listInit();
    while ((NEXT(source)))
    {
        listPushBack(copy, listVal(source));
    }
    return copy;
}
