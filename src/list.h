#ifndef _LIST_H_
#define _LIST_H_

 #ifdef __cplusplus
 extern "C"
 {
 #endif


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
    *List;

#define NEXT(A) A = A->n
#define PREV(A) A = A->p
#define listVal(A) A->v
#define listBegin(A) A->n
#define newListNode() (List) malloc(sizeof(struct list))
#define listFree(A) listFreeReal(&A)

List listRbegin(List root);
List listInit();
void listPushBack(List root, T val);
void listPushFront(List root, T val);
void listPushSort(List root, T val, int (*compare)(T, T));
void listAddAfter(List place, T val);
void listFreeReal(List* root);
List listGet(List root, int n);
void listRemove(List root, List element);
int  listRemoveN(List root, int n);
int  listRemoveVal(List root, T val);
int  listLength(List root);
int  listIsEmpty(List root);
int  listPopBack(List root);
int  listPopFront(List root);
List listCopy(List source);


 #ifdef __cplusplus
 }
 #endif
#endif
