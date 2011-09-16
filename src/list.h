#ifndef _LIST_H_
#define _LIST_H_

/* MODIFY ME */
typedef int T;
/* MODIFY ME */

typedef struct list
{
    T            v;
    int          isRoot;        /* true only in the first one */
    struct list* n;
    struct list* p;
}
    List;

#define NEXT(A) A = A->n
#define PREV(A) A = A->p
#define listVal(A) A->v
#define listBegin(A) A->n
#define newListNode() (List*) malloc(sizeof(List))

List* listRbegin(List* root);
List* listInit();
void  listPushBack(List* root, T val);
void  listPushBackSort(List* root, T val, int (*compare)(T, T));
void  listAddAfter(List* place, T val);
void  listFree(List* root);
List* listGet(List* root, int n);
void  listRemove(List* element);
int   listRemoveN(List* root, int n);
int   listRemoveVal(List* root, T val);

#endif
