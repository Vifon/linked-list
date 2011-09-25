/* File: list.c */
#include "list.h"
#include <stdlib.h>

List listInit()
{
    List root   = newListNode();

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

void listFree(List root)
{
    if (root == NULL)
        return;
    listFree(root->n);
    free(root);
}

void listPushBack(List root, void* val)
{
    if (!listIsEmpty(root))
        root = listRbegin(root);
    listAddAfter(root, val);
}

void listPushFront(List root, void* val)
{
    listAddAfter(root, val);
}

void listPushSort(List root, void* val, int (*compare)(const void*, const void*))
{
    /* compare should return -1 on lesser, 0 on equal and 1 on greater */
    while (root->n != NULL && compare(root->n->v, val) < 0)
        NEXT(root);
    listAddAfter(root, val);
}

void listAddAfter(List place, void* val)
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

/* compare should return -1 on lesser, 0 on equal and 1 on greater */
List listGetVal(List root, void* val, int (*compare)(const void*, const void*))
{
    List element = listBegin(root);
    for (; element != NULL && element->v != NULL && compare(element->v, val) != 0; NEXT(element));
    return element;
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

/* compare should return -1 on lesser, 0 on equal and 1 on greater */
int listRemoveVal(List root, void* val, int (*compare)(const void*, const void*))
{
    List element = listGetVal(root, val, compare);
    if (element == NULL || element->v == NULL)
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

void listEmpty(List root)
{
    listFree(root->n);
    root->n = NULL;
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
        listPushBack(copy, source->v);
    }
    return copy;
}

void listForeach(List root, void (*fun)(void*, void*), void* arg)
{
    root = listBegin(root);
    while (root != NULL)
    {
        fun(root->v, arg);
        NEXT(root);
    }
}
