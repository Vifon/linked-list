/* File: list.h */
/*************************************************************************/
/* Copyright (C) 2011  Wojciech Siewierski                               */
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

#ifndef _LIST_H_
#define _LIST_H_

 #ifdef __cplusplus
 extern "C"
 {
 #endif


typedef struct list
{
    void*        v;
    int          isRoot;        /* true only in the first one */
    struct list* n;
    struct list* p;
} *List;

#define NEXT(A)       (A = A->n)
#define PREV(A)       (A = A->p)
#define listBegin(A)  A->n
#define listVal(A, T) (*(T*) (A)->v)
#define listRef(A, T) ((T*) (A)->v)
#define newListNode() ((List) malloc(sizeof(struct list)))

List  listRBegin    (List root);
List  listInit      ();
void  listPushBack  (List root,  void* val);
void  listPushFront (List root,  void* val);
void  listPushSort  (List root,  void* val, int (*compare)(const void*, const void*));
void  listAddAfter  (List place, void* val);
void  listFree      (List root);
List  listGet       (List root,  int n);
List  listGetVal    (List root,  void* val, int (*compare)(const void*, const void*));
void  listRemove    (List root,  List element);
int   listRemoveN   (List root,  int n);
int   listRemoveVal (List root,  void* val, int (*compare)(const void*, const void*));
int   listLength    (List root);
int   listIsEmpty   (List root);
void  listEmpty     (List root);
void* listPopBack   (List root);
void* listPopFront  (List root);
List  listCopy      (List source);
void  listForeach   (List root, void (*fun)(void*, void*), void* arg);
int   listSwap      (List root, List place);
void  listSort      (List root, int (*cmp)(const void*, const void*));


 #ifdef __cplusplus
 }
 #endif
#endif
