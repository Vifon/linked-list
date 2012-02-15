/* File: list.c */
/*************************************************************************/
/* Copyright (C) 2011-2012  Wojciech Siewierski                          */
/*                                                                       */
/* This program is free software: you can redistribute it and/or modify  */
/* it under the terms of the GNU General Public License as published by  */
/* the Free Software Foundation, either version 3 of the License, or     */
/* (at your option) any later version.                                   */
/*                                                                       */
/* This program is distributed in the hope that it will be useful,       */
/* but WITHOUT ANY WARRANTY; without even the implied warranty of        */
/* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         */
/* GNU General Public License for more details.                          */
/*                                                                       */
/* You should have received a copy of the GNU General Public License     */
/* along with this program.  If not, see <http://www.gnu.org/licenses/>. */
/*************************************************************************/

#include "list.h"
#include <stdlib.h>

List listInit(void)
{
    List root = newListNode();

    root->isRoot = 1;
    root->n      = NULL;
    root->p      = NULL;
    return root;
}

void listFree(List root)
{
    List it1 = root;
    List it2;
    while (it1 != NULL)
    {
        it2 = it1;
        it1 = listNext(it1);
        free(it2);
    }
}

void listFreeDeep(List root)
{
    List it1 = root;
    List it2;
    while (it1 != NULL)
    {
        it2 = it1;
        it1 = listNext(it1);
        free(it2->v);
        free(it2);
    }
}

void listPushBack(List root, void* val)
{
    listAddAfter(root,
                 listIsEmpty(root) ? root : listRBegin(root),
                 val);
}

void listPushFront(List root, void* val)
{
    listAddAfter(root, root, val);
}

void listPushSort(List root, void* val, int (*compare)(const void*, const void*))
{
    /* compare should return -1 on lesser, 0 on equal and 1 on greater */
    List iterator = root;
    while (iterator->n && compare(iterator->n->v, val) < 0)
        iterator = listNext(iterator);
    listAddAfter(root, iterator, val);
}

List listAddAfter(List root, List place, void* val)
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
    if (place->n)
        place->n->p = ptr;
    place->n        = ptr;

    if (ptr->n == NULL)
        root->p = ptr;

    return ptr;
}

List listGet(List root, int n)
{
    int i;
    for (i = 0; i <= n; ++i)    /* intentional apparent off-by-one! */
    {
        root = listNext(root);
        if (root == NULL)
            return NULL;        /* out-of-list exception */
    }
    return root;
}

/* compare should return -1 on lesser, 0 on equal and 1 on greater */
List listGetVal(List root, void* val, int (*compare)(const void*, const void*))
{
    List element = listBegin(root);
    for (; element && element->v && compare(element->v, val) != 0; element = listNext(element))
        ;
    return element;
}

void listRemove(List root, List element)
{
    if (root->n == element)
        root->n       = element->n;
    if (element->p)
        element->p->n = element->n;
    if (element->n)
        element->n->p = element->p;
    else
        root->p = element->p;
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
    root = listNext(root);
    while (root)
    {
        root = listNext(root);
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
    root->p = NULL;
}

void* listPopBack(List root)
{
    List last = listRBegin(root);
    if (last)
    {
        void* tmp = last->v;
        listRemove(root, last);
        return tmp;
    }
    else
        return NULL;
}

void* listPopFront(List root)
{
    List last = listBegin(root);
    if (last)
    {
        void* tmp = last->v;
        listRemove(root, last);
        return tmp;
    }
    else
        return NULL;
}

List listCopy(List source)
{
    List copy = listInit();
    while ((source = listNext(source)))
    {
        listPushBack(copy, source->v);
    }
    return copy;
}

void listForeach(List root, void (*fun)(void*, void*), void* arg)
{
    root = listBegin(root);
    while (root)
    {
        fun(root->v, arg);
        root = listNext(root);
    }
}

int listSwap(List root, List place)
{
    void* p;
    if (place->isRoot || place->n == NULL)
        return 0;
    else if (place->n == root->p)
        root->p = place;

    p = place->v;
    place->v = place->n->v;
    place->n->v = p;

    return 1;
}


/* This is a modified version of Simon Tatham's mergesort for linked lists */
/*
 * This file is copyright 2001 Simon Tatham.
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following
 * conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT.  IN NO EVENT SHALL SIMON TATHAM BE LIABLE FOR
 * ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF
 * CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */
void listSort(List root, int (*cmp)(const void*, const void*))
{
    List p, q, e, tail;
    List list = listBegin(root);
    int insize, nmerges, psize, qsize, i;

    /*
     * Silly special case: if `list' was passed in as NULL, return
     * NULL immediately.
     */
    if (!list)
        return;

    insize = 1;

    while (1) {
        p = list;
        list = NULL;
        tail = NULL;

        nmerges = 0;  /* count number of merges we do in this pass */

        while (p) {
            ++nmerges;  /* there exists a merge to be done */
            /* step `insize' places along from p */
            q = p;
            psize = 0;
            for (i = 0; i < insize && q; ++i) {
                ++psize;
                q = listNext(q);
            }

            /* if q hasn't fallen off end, we have two lists to merge */
            qsize = insize;

            /* now we have two lists; merge them */
            while (psize > 0 || (qsize > 0 && q)) {

                /* decide whether next element of merge comes from p or q */
                if (psize == 0) {
                    /* p is empty; e must come from q. */
                    e = q; q = listNext(q); --qsize;
                } else if (qsize == 0 || !q) {
                    /* q is empty; e must come from p. */
                    e = p; p = listNext(p); --psize;
                } else if (cmp(p->v,q->v) <= 0) {
                    /* First element of p is lower (or same);
                     * e must come from p. */
                    e = p; p = listNext(p); --psize;
                } else {
                    /* First element of q is lower; e must come from q. */
                    e = q; q = listNext(q); --qsize;
                }

                /* add the next element to the merged list */
                if (tail) {
                    tail->n = e;
                } else {
                    list = e;
                }
                e->p = tail;
                tail = e;
            }

            /* now p has stepped `insize' places along, and q has too */
            p = q;
        }
        tail->n = NULL;

        /* If we have done only one merge, we're finished. */
        if (nmerges <= 1) {  /* allow for nmerges==0, the empty list case */
            List iterator;
            root->n = list;
            for (iterator = root->n; iterator->n != NULL; iterator = listNext(iterator))
                ;
            root->p = iterator;
            return;
        }

        /* Otherwise repeat, merging lists twice the size */
        insize *= 2;
    }
}
